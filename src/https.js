import { createServer } from 'https';
import { readFileSync } from 'fs';
import router from './router.js';

async function init({ crt, key }) {
    let https = null;
    try {
        https = {
            cert: readFileSync(crt),
            key: readFileSync(key),
        };
    } catch (err) {
        await init({
            crt: crt,
            key: key,
        });
    }
    return https;
}

export default (async () => {
    const https = await init({
        crt: process.env.WS_SERVER_CRT,
        key: process.env.WS_SERVER_KEY,
    });

    return createServer(https, router);
})();
