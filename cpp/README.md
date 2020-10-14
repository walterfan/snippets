some test programs on cygwin or ubuntu

Prerequisite
------------------
* Install Boost
refer to https://www.boost.org


* Build googletest

1) mkdir lib
2) git clone https://github.com/google/googletest.git
3) cd lib
4) cmake /workspace/cpp/googletest

* Install protobuf
1) download google protobuf from http://code.google.com/p/protobuf
2) ./autogen.sh, ./configure, make, make install

* Install jsoncpp

```
git clone https://github.com/open-source-parsers/jsoncpp.git
cd jsoncpp
mkdir bld
cd bld
cmake ..
make
make install
```

* set LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

# Build tool

Scons, refer to https://scons.org/

the Build script is SConstruct

Just run `scons`

# Example
## cpp example
./bin/run_example

## text2image
scons -Q ./bin/text2image

## unittst
./bin/unittest

# Reference
* Boost: https://www.boost.org/doc/libs/1_74_0/
* Protobuf: https://developers.google.com/protocol-buffers/docs/cpptutorial
