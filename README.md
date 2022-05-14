# sprinklerapi

Based off what I did in the `ledapi` repository that is no where near completion.


## installing `libhttpserver` (based on `microhttpd`)

[libhttpserver](https://github.com/etr/libhttpserver.git)

## installing `microhttpd`

```console
apt install libmicrohttpd-dev
```

## building `libhttpserver`

```console
./bootstrap
mkdir build
cd build
../configure
make
```

## include in cmake project

To `CMakeLists.txt` add:

```cmake
include_directories($ENV{HOME}/github.com/etr/libhttpserver/src)
link_directories($ENV{HOME}/github.com/etr/libhttpserver/build/src/.libs)
```

## installing `rapidjson`

[Tencent/rapidjson](https://github.com/Tencent/rapidjson.git)

A header library.

Use:

```cpp
#include <rapidjson/document.h>
int main(int argc, char* argv) {
   return 0;
}
```

To `CMakeLists.txt` add:

```cmake
include_directories($ENV{HOME}/github.com/Tencent/rapidjson/include)
```
