# Dependencies
- googletest
- libgtest-dev
- google-mock
- libgmock-dev

```bash
$ sudo apt install googletest libgtest-dev  google-mock libgmock-dev -y
```

# download json
```bash
$ git clone https://github.com/nlohmann/json.git

$ cd json

$ mkdir build
$ cd build

$ cmake ..
$ make
$ sudo make install
```


# Run
```bash
$ cmake -B<build_dir> -H<headers_dir>

e.g.
$ cmake -Bbuild -H.
```
```bash
$ cmake --build <build_dir> --target <target>

e.g.
$ cmake --build build --target example-test
```

# To run Ctest
```bash
$ cd build
$ ctest .
```
or
```bash
$ ctest --test-dir build
```
