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

# download and build mongo
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y
# installing the mongoc / mongocxx dependencies
RUN apt-get install -y \
    pkg-config \
    libssl-dev \
    libsasl2-dev \
    libbson-dev \
    git \
    curl

# compile and install mongoc
RUN cd /tmp \
    && curl -OL https://github.com/mongodb/mongo-c-driver/releases/download/1.17.2/mongo-c-driver-1.17.2.tar.gz \
    && tar xzf mongo-c-driver-1.17.2.tar.gz \
    && cd mongo-c-driver-1.17.2 \
    && mkdir cmake-build \
    && cd cmake-build \
    && cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF .. \
    && make \
    && make install

# compile and install mongocxx
RUN curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.9.0/mongo-cxx-driver-r3.9.0.tar.gz && \
    tar -xzf mongo-cxx-driver-r3.9.0.tar.gz && \
    cd mongo-cxx-driver-r3.9.0 && \
    cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local -DBUILD_VERSION=3.9.0 && \
    cmake --build build --target install -- -j4 && \
    cd build && \
    make && \
    make install && \
    cd ../../.. && \
    cd /usr/local/include && \
    mv mongocxx mongocxx1 && \
    ln -s mongocxx1/v_noabi/mongocxx mongocxx && \
    cd /usr/local/include && \
    mv bsoncxx bsoncxx1 && \
    ln -s bsoncxx1/v_noabi/bsoncxx bsoncxx && \
    cd /usr/local/include/mongocxx1/v_noabi/mongocxx && \
    ln -s /usr/local/include/mongocxx1/v_noabi v_noabi && \
    cd /usr/local/include/bsoncxx1/v_noabi/bsoncxx && \
    ln -s /usr/local/include/bsoncxx1/v_noabi v_noabi && \
    cd /usr/local/include && \
    ln -s ./bsoncxx1/v_noabi/bsoncxx/third_party/mnmlstc/core/ core && \
    cd /app

COPY appbuild.sh /usr/local/bin/appbuild.sh
COPY appstarter.sh /usr/local/bin/appstarter.sh

ENV LD_LIBRARY_PATH=/usr/local/lib

ENTRYPOINT ["appstarter.sh"]
