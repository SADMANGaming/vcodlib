#!/bin/bash

# E.g.: ./build.sh -1 -d --sqlite

cc="g++"
options="-I. -m32 -fPIC -Wall -fvisibility=hidden"
# -Wno-write-strings // not full warnings

separator="---------------------"

while [[ $# -gt 0 ]]; do
    arg="$1"
    case $arg in
        -1 | --1.1)
            if [ -v patch ]; then
                multiple_patch_attempt=true
                break
            fi
            patch=1.1
            ;;
        -5 | --1.5)
            if [ -v patch ]; then
                multiple_patch_attempt=true
                break
            fi
            patch=1.5
            ;;
        -d | --debug)
            debug="-g -ggdb -O0" # debug build without optimization
            ;;
        -s | --sqlite)
            sqlite=true
            ;;
        -u | --unsafe)
            unsafe=true
            ;;
        *)
            unrecognized_arg=$arg
            break
            ;;
    esac
    shift
done

if [ -v unrecognized_arg ]; then
    echo "Unrecognized argument \"$unrecognized_arg\", aborting."
    exit 1
fi

if [ ! -v patch ]; then
    echo "Patch version not specified, aborting."
    exit 1
elif [ -v multiple_patch_attempt ]; then
    echo "Only one patch version must be specified, aborting."
    exit 1
fi

echo $separator

echo "Patch:  $patch"
if [ $patch == 1.1 ]; then
    set -- "vcodlib1_1_1"
    constants+="-D COD_VERSION=COD1_1_1"
elif [ $patch == 1.5 ]; then
    set -- "vcodlib1_1_5"
    constants+="-D COD_VERSION=COD1_1_5"
fi

echo -n "Debug: "
if [ -v debug ]; then
    echo " ON"
else
    echo " OFF"
    debug=""
fi

echo -n "Unsafe: "
if [ -v unsafe ]; then
    echo "ON"
    constants+=" -D ENABLE_UNSAFE=1"
else
    echo "OFF"
    constants+=" -D ENABLE_UNSAFE=0"
fi

sqlite_found=0
sqlite_link=""
sqlite_libpath="/usr/lib32/libsqlite3.so"
sqlite_libpath2="/usr/lib/i386-linux-gnu/libsqlite3.so"
sqlite_libpath3="/usr/lib/libsqlite3.so"
echo -n "SQLite: "
if [ -v sqlite ]; then
    if [ -e "$sqlite_libpath" ] || [ -e "$sqlite_libpath2" ] || [ -e "$sqlite_libpath3" ]; then
        sqlite_found=1
        sqlite_link="-lsqlite3"
        constants+=" -D COMPILE_SQLITE=1"
        echo "ON"
    else
        echo "requested but lib not found, aborting."
        exit 1
    fi
else
    echo "OFF"
    constants+=" -D COMPILE_SQLITE=0"
fi

echo $separator

mkdir -p ../bin
mkdir -p objects_$1

echo "##### COMPILE $1 CRACKING.CPP #####"
$cc $debug $options $constants -c cracking.cpp -o objects_$1/cracking.opp

echo "##### COMPILE $1 GSC.CPP #####"
$cc $debug $options $constants -c gsc.cpp -o objects_$1/gsc.opp

echo "##### COMPILE $1 GSC_ENTITY.CPP #####"
$cc $debug $options $constants -c gsc_entity.cpp -o objects_$1/gsc_entity.opp

if [ $sqlite_found == 1 ]; then
    echo "##### COMPILE $1 GSC_SQLITE.CPP #####"
    $cc $debug $options $constants -c gsc_sqlite.cpp -o objects_"$1"/gsc_sqlite.opp
fi

echo "##### COMPILE $1 GSC_PLAYER.CPP #####"
$cc $debug $options $constants -c gsc_player.cpp -o objects_$1/gsc_player.opp

echo "##### COMPILE $1 GSC_UTILS.CPP #####"
$cc $debug $options $constants -c gsc_utils.cpp -o objects_$1/gsc_utils.opp

echo "##### COMPILE $1 GSC_WEAPONS.CPP #####"
$cc $debug $options $constants -c gsc_weapons.cpp -o objects_$1/gsc_weapons.opp

if [ $patch == 1.5 ]; then
    echo "##### COMPILE $1 JUMP.CPP #####"
    $cc $debug $options $constants -c jump.cpp -o objects_"$1"/jump.opp
fi

echo "##### COMPILE $1 VCODLIB.CPP #####"
$cc $debug $options $constants -c vcodlib.cpp -o objects_$1/vcodlib.opp

echo "##### COMPILE $1 QVSNPRINTF.C #####"
$cc $debug $options $constants -c lib/qvsnprintf.c -o objects_"$1"/qvsnprintf.opp

echo "##### COMPILE $1 STRCMP_CONSTANT_TIME.C #####"
$cc $debug $options $constants -c lib/strcmp_constant_time.c -o objects_"$1"/strcmp_constant_time.opp


echo "##### LINK    $1.so #####"
objects="$(ls objects_$1/*.opp)"
$cc -m32 -shared -L/lib32 -o ../bin/$1.so -ldl $objects -lpthread $sqlite_link
rm objects_$1 -r
