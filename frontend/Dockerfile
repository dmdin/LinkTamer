#FROM alexxxnf/spa-builder as builder
#
#COPY ./package.json /app/
#RUN cd /app && yarn
#
#COPY . /app
#RUN cd /app \
#    && yarn run build && for i in `find | grep -E "\.css$|\.html$|\.js$|\.svg$|\.txt$|\.ttf$"`; do gzip -9kf "$i" \
#    && brotli -fZ "$i" ; done
#
#FROM alexxxnf/nginx-spa
#COPY --from=builder /app/public /etc/nginx/html/
FROM node:14-alpine as build

WORKDIR /usr/src/app

COPY rollup.config.js ./
COPY package*.json ./

RUN npm install

COPY ./src ./src
COPY ./public ./public

RUN npm run-script build


FROM nginx:stable-alpine
COPY --from=build /usr/src/app/public /usr/share/nginx/html
EXPOSE 80
ENTRYPOINT ["nginx", "-g", "daemon off;"]