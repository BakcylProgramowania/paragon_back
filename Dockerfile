# Use an official Ubuntu image as the base
FROM ubuntu:latest

# Set the working directory
WORKDIR /app

# Install dependencies
RUN apt update && \
    apt install -y \
    libssl-dev \
    cmake \
    git \
    curl \
    build-essential \
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

# Clone and build json
RUN git clone https://github.com/nlohmann/json.git && \
    cd json && \
    mkdir build  && \
    cd build && \
    cmake .. && \
    make && \
    make install && \
    cd ../..

# Install dependencies
RUN apt update && \
    apt install -y \
    libbson-dev \
    libmongoc-dev && \
    rm -rf /var/lib/apt/lists/*

# download and build mongo
RUN  curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.9.0/mongo-cxx-driver-r3.9.0.tar.gz && \
    tar -xzf mongo-cxx-driver-r3.9.0.tar.gz && \
    cd mongo-cxx-driver-r3.9.0/build && \
    cmake -DBUILD_VERSION=3.9.0 -DMONGOCXX_OVERRIDE_DEFAULT_INSTALL_PREFIX=OFF .. && \
    cmake --build . && \
    cmake --build . --target install && \
    cd ../..

COPY appbuild.sh /usr/local/bin/appbuild.sh
COPY appstarter.sh /usr/local/bin/appstarter.sh

ENTRYPOINT ["appstarter.sh"]
