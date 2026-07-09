#!/bin/bash

DEST="../../qual-challenges/pholyglot/chall/"
FILES="Dockerfile docker-compose.yml flag read_flag www/"

rm -rf $DEST
mkdir -p $DEST/dist

cp -r $FILES $DEST/dist/
cp ../challenge.yml $DEST