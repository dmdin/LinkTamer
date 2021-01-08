FROM rikorose/gcc-cmake as builder

ADD . /service
WORKDIR /service/utility

RUN sed -i 's/\r$//' ./install-oatpp-modules.sh
RUN /bin/bash -c "source ./install-oatpp-modules.sh Release"

WORKDIR /service/build
RUN cmake ..
RUN make

#FROM alpine
#COPY --from=builder /service/build /service

#WORKDIR /service
EXPOSE 8000
#ENTRYPOINT ["./service/build/crud-exe"]
ENTRYPOINT ["./crud-exe"]