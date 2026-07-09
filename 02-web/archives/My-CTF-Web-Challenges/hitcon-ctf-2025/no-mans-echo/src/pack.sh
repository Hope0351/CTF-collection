#!/bin/bash

DEST="../../qual-challenges/no-mans-echo/chall/"
FILES="Dockerfile docker-compose.yml flag www/"

rm -rf $DEST
mkdir -p $DEST/dist

# tar -zcvf orange.tgz $FILES
cp -r $FILES $DEST/dist/
cp ../challenge.yml $DEST