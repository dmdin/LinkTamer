FROM alexxxnf/spa-builder as builder

COPY ./package.json /app/
RUN cd /app && yarn

COPY . /app
RUN cd /app \
    && yarn run build && for i in `find | grep -E "\.css$|\.html$|\.js$|\.svg$|\.txt$|\.ttf$"`; do gzip -9kf "$i" \
    && brotli -fZ "$i" ; done

FROM alexxxnf/nginx-spa
COPY --from=builder /app/public /etc/nginx/html/