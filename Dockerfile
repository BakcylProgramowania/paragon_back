# Use the official Ubuntu base image
FROM ubuntu:latest

# Install system dependencies
RUN apt-get update && apt-get install -y \
    libssl-dev \
    cmake \
    libgtest-dev \
    libgmock-dev \
    git

# Set the working directory
WORKDIR /app

# Clone and build oat++
RUN git clone --branch 1.3.0 --depth 1 https://github.com/oatpp/oatpp.git \
    && cd oatpp \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make \
    && make install \
    && cd ../..

# Clone and build oat++-swagger
RUN git clone --branch 1.3.0 --depth 1 https://github.com/oatpp/oatpp-swagger.git \
    && cd oatpp-swagger \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make \
    && make install \
    && cd ../..

# Copy the rest of your project files
COPY . .

# Create build directory
RUN cmake -B build

# Entrypoint - do not run any tests here
CMD ["echo", "Docker image built with cached dependencies"]
