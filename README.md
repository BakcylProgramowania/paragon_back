# Dependencies
- googletest
- libgtest-dev
- google-mock
- libgmock-dev
- mongo-cxx-driver

```bash
$ sudo apt install googletest libgtest-dev  google-mock libgmock-dev -y

# MongoDB driver:
$ curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.9.0/mongo-cxx-driver-r3.9.0.tar.gz
$ tar -xzf mongo-cxx-driver-r3.9.0.tar.gz
$ cd mongo-cxx-driver-r3.9.0/build

$ cmake ..                                \
     -DCMAKE_BUILD_TYPE=Release           \
     -DMONGOCXX_OVERRIDE_DEFAULT_INSTALL_PREFIX=OFF
$ cmake --build .
$ sudo cmake --build . --target install
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
# DataBase
MongoDB Compass: https://www.mongodb.com/products/tools/compass
GUI DataBase Adres: (mongodb+srv://bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/)

MongoDB C++
Adres_URI: (mongodb+srv://bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/)
