# How to run?

### Run before commit
Download [Docker Desktop](https://www.docker.com/products/docker-desktop/)

If you changed Dockerfile run this
```bash
docker build -t paragon_back:1.1.7.1 .
```
> 📝 Note: Each time you will need to change the tag (1.1.7.1) to a different one

Create new dir like `C:\Users\ddnow\Documents\app` and open vscode in it
Then open new terminal and run this:

```bash
docker run -it -e "REPO=https://github.com/BakcylProgramowania/paragon_back.git" -e "BRANCH=main" -v C:\Users\ddnow\Documents\app:/app --entrypoint /bin/bash --publish 8000:8000 --name paragon-back bakcyl/paragon_back:1.1.7
```
> 📝 Note: Replace paragon_back:1.1.7.1 with what you set above and change C:\Users\ddnow\Documents\app to dir you set above

To copy repo run `appbuild.sh`

### Run after commit
Download [Docker Desktop](https://www.docker.com/products/docker-desktop/)

Run this in your terminal: 
```bash
docker run -it -e "REPO=https://github.com/BakcylProgramowania/paragon_back.git" -e "BRANCH=main" --publish 8000:8000 --name paragon-back --restart always bakcyl/paragon_back:1.1.7
```
> 📝 Note: You can change the branch by changing main to your branch

To run test in repo use:
```bash
cd paragon_back
cmake --build build
ctest --test-dir build
```


# How to clang-format?
```bash
apt-get install pre-commit
pre-commit install
cd .github/pre-commit
pre-commit run --all-files
```
