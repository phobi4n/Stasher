#!/bin/bash

# Need to run this as privileged user
if [ $EUID != 0 ]; then
    echo "You need to run me as sudo"
    exit 1
fi

# Clean up any previous work
if [ -f Makefile ]; then
    make distclean
fi

qmake
make

# Test we have a binary before trying to proceed
if [ -x stasher ]; then
    cp -fv ./stasher /usr/bin
    
    # Find kf5 services path under /usr/share
    SERVICES=$(kf5-config --path services 2>/dev/null)
    IFS=:
    set $SERVICES

    if [[ "$1" == *"/usr/share/"* ]]; then
        SERVICE_LOCATION=$1
    elif [[ "$2" == *"/usr/share/"* ]]; then
        SERVICE_LOCATION=$2
    elif [[ "$3" == *"/usr/share/"* ]]; then
        SERVICE_LOCATION=$3
    elif [[ "$4" == *"/usr/share/"* ]]; then
        SERVICE_LOCATION=$4
    fi
        
    cp -fv ./stash.desktop $SERVICE_LOCATION/ServiceMenus
    cp -fv ./da.svg /usr/share/icons/hicolor/scalable/apps
else
    echo ""
    echo "Compiling binary failed. Check you have Qt5 development packages installed."
fi
