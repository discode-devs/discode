FROM alpine:latest

COPY . /usr/src/myapp
WORKDIR /usr/src/myapp

RUN \
  apk add curl-dev libc-dev clang gcc make git && \
  git clone https://github.com/Cogmasters/concord.git && \
  cd concord && \
  make && \
  make install && \
  cd .. && \
  make
  
WORKDIR /usr/src/myapp/build

CMD ["./discode"]