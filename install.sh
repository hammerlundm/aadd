#!/bin/sh
if ! [ $(id -u) = 0 ]; then
    echo "You must be root to install AADD"
    exit 1
fi
make release
mv aadd /bin
make clean

