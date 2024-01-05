# How to run?
Download [Docker Desktop](https://www.docker.com/products/docker-desktop/)

Run this in your terminal: 
```bash
docker run -it -e "REPO=https://github.com/BakcylProgramowania/paragon_back.git" -e "BRANCH=main" --publish 8000:8000 --name paragon-back --restart always bakcyl/paragon_back:1.1.7
```
> 📝 Note: You can change the branch by changing main to your branch
