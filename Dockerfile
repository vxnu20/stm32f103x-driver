FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies for ARM GCC toolchain and make
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    gcc-arm-none-eabi \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

COPY . .

CMD ["make"]

