#!/bin/bash

sudo make clean
sudo make
sudo make install

cd ../../kernel/
sudo make clean
sudo make
sudo make install

cd ..
sudo make clean
sudo make
sudo make install

qemu-system-i386 -fda ics-os-floppy.img 

cd contrib/whimm/