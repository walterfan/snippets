some test programs on cygwin or ubuntu

Prerequisite
------------------

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

## text2image
scons -Q ./bin/text2image

## unittst
scons

Reference
-------------------
## Protobuf
* https://developers.google.com/protocol-buffers/docs/cpptutorial
* http://www.cnblogs.com/Solstice/archive/2011/04/03/2004458.html
