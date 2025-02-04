#!/usr/bin/env bash
projectName="Maguic"

mkdir build 2> /dev/null
mkdir debug 2> /dev/null

makearg=""
cmakearg=""
folder="build"
for arg in "$@"; do
    if [ "$arg" = "--release" ]; then
        cmakearg+=" -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS=\"-O3\" "
    elif [ "$arg" = "--debug" ]; then
        cmakearg+=" -DCMAKE_BUILD_TYPE=Debug "
        folder="debug"
    elif [ "$arg" = "--fastcompile" ]; then
        makearg+=" -j4 "
    elif [[ "$arg" =~ -j[0-9]+ ]]; then
	echo FAST COMPILE DEBUG $arg
	makearg+=" $arg "
    elif [ "$arg" = "--reset" ]; then
        rm -rf build/*
        rm -rf debug/*
    elif [ "$arg" = "--vendored" ]; then
	cmakearg+=" -DMAGUIC_VENDORED=ON "
    else
	echo adding $arg to cmake args 
	cmakearg+=" $arg "
    fi	
done

cd $folder/
cmake $cmakearg ..
if [[ $? != 0 ]]; then
    err=$?
    echo -ne "$(tput setaf 9)"
    echo "Compilation of $projectName went wrong.$(tput sgr0)"
    cd ../
    exit $err
fi
make $makearg
if [[ $? != 0 ]]; then
    err=$?
    echo -ne "$(tput setaf 9)"
    echo "Compilation of $projectName went wrong.$(tput sgr0)"
    cd ../
    exit $err
elif [[ $? == 0 ]]; then
    echo "$(tput setaf 2)$(tput bold)Compilation of $projectName finished.$(tput sgr0)
    Execute example with build/$projectName"
fi

cd ../
echo -ne "$(tput sgr0)"
