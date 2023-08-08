import { createServer } from 'https';
import fs from 'fs';
import path from 'path';
import router from './router.js';

async function getHttps(step = {}) {
    let https = null;
    let i = 10;
    while (!https && i > 0) {
        try {
            https = {
                cert: fs.readFileSync(step.crt),
                key: fs.readFileSync(step.key),
            };
        } catch (err) {
            await new Promise((resolve) => setTimeout(resolve, 1000));
            console.log(err);
            i--;
        }
    }
    return https;
}

export default (async () => {
    const steppath = process.env.WS_STEPPATH;
    const step = {
        crt: path.resolve(steppath, 'site.crt'),
        key: path.resolve(steppath, 'site.key'),
    };
    const https = await getHttps(step);

    return createServer(https, router);
})();
