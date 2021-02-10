FROM golang:alpine AS builder
RUN apk update && apk add --no-cache git build-base
WORKDIR $GOPATH/src/linktamer/backend
COPY . .
RUN go get -d -v
RUN GOOS=linux GOARCH=amd64 go build -ldflags="-w -s" -o /go/bin/backend

FROM alpine
COPY --from=builder /go/bin/backend /go/bin/backend
ENTRYPOINT ["/go/bin/backend"]