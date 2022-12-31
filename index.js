import server from './src/server.js';

(async () => {
    console.log('> proxymurder-ws@0.0.0 dev');
    console.log('> websockets/ws');
    await server;
})();
