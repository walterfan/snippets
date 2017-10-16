#!/bin/bash

source /etc/profile > /dev/null 2>&1 

export BOOST_ROOT=/Users/walter/Documents/workspace/cpp/boost_1_56_0
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$BOOST_ROOT/stage/lib


