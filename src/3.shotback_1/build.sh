#!/bin/sh

root=`pwd`
build=$root/build
bin=$root/bin

if [ ! -f CMakeLists.txt ];then
    echo "CMakeLists.txt is not exist!"
    exit
fi

if [ -d $build ];then
    rm $build -rf
fi

if [ -d $bin ];then
    rm $bin -rf
fi

mkdir $build

cd $build
cmake ..
make

cd $root
cp $build/bin $root -r
rm $build -r
