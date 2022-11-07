import { createClient } from 'redis';
import { WebSocketServer } from 'ws';
import express from 'express';

import { createServer as createHttpsServer } from 'https';
import { parse } from 'url';
import fs from 'fs';

console.log('> proxymurder-socket@1.0.0 dev');
console.log('> wss');
console.time('  wss v1.0.0 ready in');

async function getServerConf() {
    let https = null;

    try {
        https = {
            key: fs.readFileSync(process.env.WS_SERVER_KEY),
            cert: fs.readFileSync(process.env.WS_SERVER_CERT),
        };
    } catch (err) {
        await getServerConf();
    }

    let redis = {
        url: `redis://${process.env.REDIS_HOST}:${process.env.REDIS_PORT}`,
    };
    let port = process.env.WS_PORT;

    return { https, redis, port };
}

(async () => {
    const { https, redis, port } = await getServerConf();
    const router = express();

    const server = createHttpsServer(https, router);
    const client = createClient(redis);

    await client.connect();
    client.on('error', (err) => console.log('redis client error', err));

    const wss = {
        app: new WebSocketServer({ noServer: true }),
    };

    const subscriber = {
        terminal: client.duplicate(),
        app: client.duplicate(),
    };

    await subscriber.terminal.connect();
    subscriber.terminal.on('error', (err) =>
        console.log('subscriber (duplicate) redis client error', err)
    );

    await subscriber.app.connect();
    subscriber.app.on('error', (err) =>
        console.log('app (duplicate) redis client error', err)
    );

    await subscriber.terminal.subscribe(
        'app:notifications',
        (message, channel) => {
            console.log(channel);
            console.log(message);
        }
    );

    wss.app.on('connection', function connection(ws) {
        subscriber.app.subscribe('app:notifications', (message, channel) => {
            ws.send(JSON.stringify({ channel: channel, message: message }));
        });
    });

    server.on('upgrade', function upgrade(request, socket, head) {
        const { pathname } = parse(request.url);

        if (pathname === '/app') {
            wss.app.handleUpgrade(request, socket, head, function done(ws) {
                wss.app.emit('connection', ws, request);
            });
        } else {
            socket.destroy();
        }
    });

    router.get('/', (req, res) => {
        res.send('Hello from express server.');
    });

    console.log('\n');
    console.timeEnd('  wss v1.0.0 ready in');
    console.log('');

    server.listen(port, () => {
        console.log(`  ➜  Local:  https://localhost:${port}`);
        console.log(`  ➜  Socket: wss://localhost:${port}`);
    });
})();
