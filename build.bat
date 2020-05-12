@echo off

mkdir build
pushd build

cl -FC -Zi ..\src\main.cpp /EHsc
popd

