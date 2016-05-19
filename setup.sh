#!/bin/bash

sudo make clear
sudo make
sudo make install

cd ../../kernel/
sudo make clear
sudo make
sudo make install

cd ..
sudo make clear
sudo make
sudo make install

qemu-system-i386 -fda ics-os-floppy.img 

cd contrib/whimm/