#! /bin/sh

if [ "$#" -eq 1 ]; then
    ln -s $1 splitspace
    cd splitspace
else
    git clone https://github.com/RostakaGmfun/splitspace.git
    cd splitspace
    ./third_party/install-assimp.sh
    ./third_party/installGLM.sh
    ./third_party/install-json.sh
    ./third_party/installSOIL.sh
fi
cd ..
rm -rf splitspace-build
mkdir splitspace-build
cd splitspace-build
cmake -DRUN_TESTS=false ../splitspace
make -j4

