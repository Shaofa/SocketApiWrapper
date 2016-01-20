#!/bin/sh

cmake ..
make

if [ -f server ];then
    rm server
fi
if [ -f client ];then
    rm client
fi

ln -s ../bin/server  ./server
ln -s ../bin/client  ./client
