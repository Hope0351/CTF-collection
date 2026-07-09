#!/bin/bash
set -e

(
	cd server/
	if [ "$1" = "norecompile" ]; then
		./compile_rust.sh
	else
		./compile_rust.sh recompile
	fi

	docker build -t defcongame .
)


(
	cd website
	docker build -t defconweb .
)

rm -r /opt/finals/website
mkdir /opt/finals/website
mkdir /opt/finals/website/download
mkdir /opt/finals/website/upload


rm -r /opt/finals/game
mkdir /opt/finals/game
mkdir /opt/finals/game/submissions
mkdir /opt/finals/game/output

cp server/attestedfun /opt/finals/website/download

#(cd website/ && docker run  --rm --name defconweb -v /opt/finals/website/:/app/app/shared/  -u $(id -u):$(id -g) -p 5000:5000 defconweb )
#(cd server/ && docker run  --rm --name defcongame -v /opt/finals/game/:/app/  -u $(id -u):$(id -g) defcongame )

