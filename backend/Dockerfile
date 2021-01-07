#FROM alpine:latest
#FROM ubuntu
FROM rikorose/gcc-cmake

#RUN apt-get update && apt-get upgrade

#RUN apk add g++
#RUN apk add git
#RUN apk add make
#RUN apk add cmake

#RUN apt-get update && apt-get install -y g++ make cmake git
#RUN apt-get install cmake

ADD . /service

WORKDIR /service/utility

RUN ./install-oatpp-modules.sh Release

WORKDIR /service/build

RUN cmake ..
RUN make

EXPOSE 8000 8000

ENTRYPOINT ["./crud-exe"]
