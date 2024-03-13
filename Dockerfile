FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    gcc-aarch64-linux-gnu \
    g++-aarch64-linux-gnu \
    libfmt-dev \
    build-essential \
    cmake \
    git

RUN git clone https://github.com/google/googletest.git && \
    cd googletest && \
    mkdir build && \
    cd build && \
    make && \
    make install

RUN apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

WORKDIR /app