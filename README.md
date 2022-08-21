
# Building

## Native build (x86)

```terminal
$ mkdir build && cd build
$ cmake ../simdlib/
$ make && make test
```

## Cross compilation

```terminal
$ mkdir build && cd build
$ cmake -DCROSS_TOOLCHAIN=tachyum -DTACHY_TOOLCHAIN_HOME=<path>/install/set0 ../simdlib
$ make && make test
```