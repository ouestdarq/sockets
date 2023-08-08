import { createClient } from 'redis';

const redis = {
    data: { client: null, subscriber: null },
    server: {
        host: process.env.REDIS_HOST ?? '127.0.0.1',
        port: process.env.REDIS_PORT ?? 6379,
    },
    createClient: function () {
        return createClient;
    },
    get client() {
        return this.data.client;
    },
    set client(fn) {
        this.data.client = fn({ url: this.url });
    },
    get subscriber() {
        return this.data.subscriber;
    },
    set subscriber(obj) {
        this.data.subscriber = obj;
    },
    get url() {
        return `redis://${this.server.host}:${this.server.port}`;
    },
};

export default redis;
