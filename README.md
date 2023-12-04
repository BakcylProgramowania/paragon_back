# Dependencies
- googletest
- libgtest-dev
- google-mock
- libgmock-dev

```bash
$ sudo apt install googletest libgtest-dev  google-mock libgmock-dev -y
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