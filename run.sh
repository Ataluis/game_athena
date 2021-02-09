#!/bin/bash
sfml_installed=$(dpkg -l | grep -E '^ii' | grep libsfml-dev)
if [[ $sfml_installed == '' ]]; then
    sudo apt-get -y install libsfml-dev
fi
make -release
./spacebattle
