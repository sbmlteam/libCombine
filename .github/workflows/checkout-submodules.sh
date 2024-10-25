#!/usr/bin/env bash

git submodule update --init --remote

pushd submodules/libSBML-dependencies
git submodule update --init --remote expat
popd

pushd submodules/zipper
git submodule update --init --remote
popd 