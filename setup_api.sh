#!/bin/bash

set -e 

echo "Downloading Interactive Brokers API..."
wget https://interactivebrokers.github.io/downloads/twsapi_macunix.1037.02.zip \
    && unzip twsapi_macunix.1037.02.zip \
    && mkdir -p api/ \
    && mv IBJts api/

API_SRC=api/IBJts/source

echo "Deleting unnecessary APIs..."
echo "Deleting Python Module"

echo "Deleting Java Module"


INTEL=IntelRDFPMathLib20U2

echo "Installing Intel Math modules..."
wget http://www.netlib.org/misc/intel/IntelRDFPMathLib20U2.tar.gz \
    && tar -xvzf "$INTEL.tar.gz" \
    && mv "$INTEL" "$API_SRC/cppclient/"

echo "Building the API..."
LIBRARY="$INTEL/LIBRARY/"

STDLIB="#include <stdlib.h>"

echo "Setting up proto"
cd "$API_SRC/proto"

# Regenerate all .pb.h files with your local protoc
protoc --cpp_out=../cppclient/client/protobufUnix/ *.proto

echo "Fixing bid_pow..."

cd "../cppclient/$LIBRARY/src"

if ! grep -q "$STDLIB" "./bid32_pow.c"; then 
    { echo "$STDLIB"; cat bid32_pow.c; } > test && mv test bid32_pow.c
fi

if ! grep -q "$STDLIB" "./bid64_pow.c"; then 
    { echo "$STDLIB"; cat bid64_pow.c; } > test && mv test bid64_pow.c
fi

if ! grep -q "$STDLIB" "./bid128_pow.c"; then 
    { echo "$STDLIB"; cat bid128_pow.c; } > test && mv test bid128_pow.c
fi

cd ..

make CC=gcc CALL_BY_REF=0 GLOBAL_RND=0 GLOBAL_FLAGS=0 UNCHANGED_BINARY_FLAGS=0 

cp libbid.a ../..


echo "Cleaning up..."
rm *.o
cd ../../..
rm -rf JavaClient/ 
rm -rf pythonclient/

cd ..
rm -rf ./samples/Java/ ./samples/Python

cd ../..
rm -rf ./META-INF/
rm -rf  "./$INTEL.tar.gz" ./twsapi_macunix.1037.02.zip

echo "Done!"

