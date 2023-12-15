# Use an official Ubuntu runtime as a parent image
FROM ubuntu:latest

# Set the working directory to /app
WORKDIR /app

# Install dependencies
RUN apt-get update && \
    apt-get install -y libssl-dev && \
    apt-get install -y cmake && \
    apt-get install -y libgtest-dev && \
    apt-get install -y libgmock-dev

# Build and install oat++
RUN git clone --branch 1.3.0 --depth 1 https://github.com/oatpp/oatpp.git && \
    cd oatpp && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install && \
    cd ../..

# Build and install oat++-swagger
RUN git clone --branch 1.3.0 --depth 1 https://github.com/oatpp/oatpp-swagger.git && \
    cd oatpp-swagger && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install && \
    cd ../..
