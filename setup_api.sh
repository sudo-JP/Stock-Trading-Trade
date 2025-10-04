#!/bin/bash

set -e 

if [ ! -d "api/IBJts" ]; then 
    echo "Please down Interactive Brokers API"
    echo "Besure to make a directory called api/ then clone it in there"
    exit 1 
fi 

echo "Installing Intel Math modules"
wget http://www.netlib.org/misc/intel/IntelRDFPMathLib20U2.tar.gz && tar -xvzf IntelRDFPMathLib20U2.tar.gz
