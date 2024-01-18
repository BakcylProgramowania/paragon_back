# Bill Splitting App Backend - 2023 BakcylProgramowania

This repository contains the backend source code for the Bill Splitting application, developed by 2023 BakcylProgramowania team.

## Prerequisites

Before getting started, ensure [Docker Desktop](https://www.docker.com/products/docker-desktop/) is installed on your machine. This application is developed and packaged into Docker containers, hence Docker Desktop is essential for its deployment and testing.

## Installation Guide

Follow these steps to get a copy of this application and its dependencies on your local machine.

### Build Docker Image (only if changes have been made to the Dockerfile)

You'll need to build a Docker imag. Use the following command:

```bash
docker build -t paragon_back:1.1.7.1 .
```
> 📝  **Note:** Each time a new Docker image is built, ensure to update the tag (1.1.7.1) to maintain versioning.

### Set Up Working Directory 

Create a new directory on your machine, for example, `C:\Users\ddnow\Documents\app`, and open Visual Studio Code within this directory. 

### Run Docker Container

To initialize the Docker container, use the command below:

```bash
docker run -it -e "REPO=https://github.com/BakcylProgramowania/paragon_back.git" -e "BRANCH=main" -v C:\Users\ddnow\Documents\app:/app --entrypoint /bin/bash --publish 8000:8000 --name paragon-back bakcyl/paragon_back:1.1.7
```
> 📝 **Note:** Remember to replace `paragon_back:1.1.7.1` with the custom tag you used during Docker image build and update `C:\Users\ddnow\Documents\app` to the directory path you've created.

### Clone Repository 

Run the `appbuild.sh` script to clone the repository into your docker.
Run `cd paragon_back` to enter project folder.

### Run tests
```bash
cmake --build build
ctest --test-dir build
```
### Run code
```bash
cmake --build build
./build/src/example-main
```


## How to clang-format?
Install pre-commit on your local machine (outside of Docker) and execute the following commands:
```bash
pre-commit install
cd .github/pre-commit
pre-commit run --all-files
```
