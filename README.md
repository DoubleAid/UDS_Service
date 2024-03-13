# Unified Diagnostic Service (UDS) developed in C++

## Usage

```shell
Usage: ./configure [option]
    -h, --help      Display this help message.
    -p, --platform  Specify the platform to build for [x86 (default), aarch64].
    -r, --release   Build for release mode.
    -c, --clean     Clean the build and release directory.
```

## Environment Setup

```bash
# determine Dockerfile exists in the current directory
docker build -f Dockerfile -t uds_builder:v1.0 .

# use docker images to check the image
docker images
# you can see the images named uds_builder:v1.0

# run the container
docker run -idt -v /path/to/the/project:/app --name uds_container uds_builder:v1.0

# enter the container
docker exec -it uds_container bash
```

## Build for Special Architecture

```bash
./configure -p aarch64

# current test solution
# upload server to lidar
chmod +x server
./server [-c CUSTOMER_NAME]
# current supported customer list
# dev (default)
```

