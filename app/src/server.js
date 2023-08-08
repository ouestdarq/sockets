import { WebSocketServer } from 'ws';
import { parse } from 'url';
import redis from './redis.js';
import https from './https.js';

export default (async () => {
    console.time('> ws v1.0.0 ready in');

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

    const ws = {
        app: new WebSocketServer({ noServer: true }),
    };

    ws.app.on('connection', function connection(ws) {
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
            ws.app.handleUpgrade(
                request,
                socket,
                head,
                function done(websocket) {
                    ws.app.emit('connection', websocket, request);
                }
            );
        } else {
            socket.destroy();
        }
    });

    console.log('');
    console.timeEnd('> ws v1.0.0 ready in');
    console.log('');

    server.listen(port, () => {
        console.log(` ➜  Local:  https://localhost:${port}`);
        console.log(` ➜  Socket: ws://localhost:${port}`);
    });
})();
