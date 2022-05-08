FROM ubuntu:latest

COPY . /usr/src/myapp
WORKDIR /usr/src/myapp

RUN \
  apt update && \
  apt install -y build-essential libcurl4-openssl-dev git clang gcc && \
  git clone https://github.com/Cogmasters/concord.git && \
  cd concord && \
  make && \
  make install && \
  cd .. && \
  make
  
WORKDIR /usr/src/myapp/build

CMD ["./discode"]