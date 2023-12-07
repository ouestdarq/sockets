import express from 'express';

const router = express();

router.get('/', (req, res) => {
    res.send('Hello from express server.');
});

export default router;
