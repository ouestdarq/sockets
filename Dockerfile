FROM node:alpine
USER root

# Install dependencies
RUN apk update
RUN apk add --no-cache \
    git 


# Install global npm dependencies
RUN npm install -g \
    npm \
    npm-check-updates \
    nodemon

RUN mkdir -p /var/www/websockets
RUN chown node:node /var/www/websockets

WORKDIR /var/www/websockets

USER node

CMD ["npm", "run", "websockets"]