# How to run?

### Run after commit
Download [Docker Desktop](https://www.docker.com/products/docker-desktop/)

Run this in your terminal: 
```bash
docker run -it -e "REPO=https://github.com/BakcylProgramowania/paragon_back.git" -e "BRANCH=main" --publish 8000:8000 --name paragon-back --restart always bakcyl/paragon_back:1.1.7
```
> 📝 Note: You can change the branch by changing main to your branch

### Run before commit (Not working yet)
Download [Docker Desktop](https://www.docker.com/products/docker-desktop/)

If you changed Dockerfile run this
```bash
docker build -t paragon_back:1.1.7.1 .
```
> 📝 Note: Each time you will need to change the tag (1.1.7.1) to a different one

```bash
docker run -it --publish 8000:8000 --name paragon-back --restart always paragon_back:1.1.7.1 .
```
> 📝 Note: Replace paragon_back:1.1.7.1 with what you set above

# How to clang-format?
```bash
apt-get install pre-commit
pre-commit install
cd .github/pre-commit
pre-commit run --all-files
```
