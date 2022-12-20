import { WebSocketServer } from 'ws';
import { parse } from 'url';
import redis from './redis.js';
import https from './https.js';

export default (async () => {
    console.log('> proxymurder-ws@1.0.0 dev');
    console.log('> websockets/ws');
    console.time('> wss v1.0.0 ready in');

    const server = await https;
    const port = process.env.WS_PORT ?? 5000;

    redis.client = redis.createClient();
    redis.subscriber = {
        terminal: redis.client.duplicate(),
        app: redis.client.duplicate(),
    };

    await redis.client.connect();
    redis.client.on('error', (err) =>
        console.log('redis.client (host) [Err]', err)
    );

    await redis.subscriber.terminal.connect();
    redis.subscriber.terminal.on('error', (err) =>
        console.log('redis.subscriber (terminal) [Err]', err)
    );

    await redis.subscriber.app.connect();
    redis.subscriber.app.on('error', (err) =>
        console.log('redis.subscriber (app) [Err]', err)
    );

    await redis.subscriber.terminal.subscribe(
        'app:notifications',
        (message, channel) => {
            console.log(channel);
            console.log(message);
        }
    );

    const wss = {
        app: new WebSocketServer({ noServer: true }),
    };

    wss.app.on('connection', function connection(ws) {
        redis.subscriber.app.subscribe(
            'app:notifications',
            (message, channel) => {
                ws.send(JSON.stringify({ channel: channel, message: message }));
            }
        );
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

    console.log('');
    console.timeEnd('> wss v1.0.0 ready in');
    console.log('');

    server.listen(port, () => {
        console.log(` ➜  Local:  https://localhost:${port}`);
        console.log(` ➜  Socket: wss://localhost:${port}`);
    });
})();
