# Use an official Ubuntu runtime as a parent image
FROM ubuntu:latest

# Set the working directory to /app
WORKDIR /app

# Install dependencies
RUN apt-get update && apt-get install -y \
    libssl-dev \
    cmake \
    libgtest-dev \
    libgmock-dev \
    git

# Clone and build oatpp
RUN git clone --branch 1.3.0 --depth 1 https://github.com/oatpp/oatpp.git
WORKDIR /app/oatpp/build
RUN cmake ..
RUN make
RUN make install
WORKDIR /app

# Clone and build oatpp-swagger
RUN git clone --branch 1.3.0 --depth 1 https://github.com/oatpp/oatpp-swagger.git
WORKDIR /app/oatpp-swagger/build
RUN cmake ..
RUN make
RUN make install
WORKDIR /app

# Create build directory
RUN cmake -B build

# Build
RUN cmake --build build

# Run tests
CMD ["ctest"]
