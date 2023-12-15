# Use an official Ubuntu image as the base
FROM ubuntu:latest

# Set the working directory
WORKDIR /app

# Install dependencies
RUN apt-get update && \
    apt-get install -y \
    libssl-dev \
    cmake \
    libgtest-dev \
    libgmock-dev && \
    rm -rf /var/lib/apt/lists/*

# Clone and build oatpp
RUN git clone --branch 1.3.0 --depth 1 https://github.com/oatpp/oatpp.git && \
    cd oatpp && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install && \
    cd ../../

# Clone and build oatpp-swagger
RUN git clone --branch 1.3.0 --depth 1 https://github.com/oatpp/oatpp-swagger.git && \
    cd oatpp-swagger && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install && \
    cd ../../
