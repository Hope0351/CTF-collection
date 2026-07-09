CHAL_NAME?=$(shell basename $(shell pwd))
PORT?=1337

docker:
	docker build --target $(CHAL_NAME)-all -t $(CHAL_NAME)-all:latest .
	docker build --target $(CHAL_NAME)-echooo -t $(CHAL_NAME)-echooo:latest .
	docker build --target $(CHAL_NAME)-laptooop -t $(CHAL_NAME)-laptooop:latest .
	docker build --target $(CHAL_NAME)-prooodigi -t $(CHAL_NAME)-prooodigi:latest .

run: docker
	echo "Running $(CHAL_NAME) on port $(PORT)"
	docker rm -f $(CHAL_NAME)-test || true
	sh -c "echo 'flag{4+6Q38zDmXwjTTdsKyYv+gSC9CNY1VUP6rA=:goXk+cVZu9mDNcAY:5b0dcb002586177a}' > example_flag.txt"
	chmod 777 example_flag.txt
	docker run \
		--name $(CHAL_NAME)-test --rm \
		-p $(PORT):$(PORT) \
		-v $(shell pwd)/example_flag.txt:/flag \
		-i $(CHAL_NAME)-all:latest

.PHONY: poller poller/pollerlib

poller: poller/pollerlib
	cp ./requirements.txt poller/
	cp ./src/tests/x.py poller/
	mkdir -p poller/data
	cp ./src/tests/data/adamd-simon-says.wav ./poller/data/
	cp ./src/tests/data/wow-this-is-cool-say-hello-tts.wav ./poller/data/wow-this-is-cool-say-hello-tts.wav
	docker build -t $(CHAL_NAME):poller poller

poller/pollerlib:
	if [ ! -d poller/pollerlib ]; then git clone git@github.com:The-Nautilus-Institute/pollerlib.git poller/pollerlib; fi
	git -C poller/pollerlib pull origin main
	cp poller/pollerlib/nautpolling.py poller/nautpolling.py

poller-run: poller
	echo "Running poller for $(CHAL_NAME) on port $(PORT)"
	docker rm -f $(CHAL_NAME)-poller || true
	docker run \
		--name $(CHAL_NAME)-poller --rm \
		--network host \
		-e HOST=127.0.0.1 \
		-e PORT=$(PORT) \
		-e POLLER_TESTING_CHANGED_FILES=/patches \
		-v `pwd`/patches/echooo-patch:/patches \
		-v /tmp:/tmp \
		-i $(CHAL_NAME):poller
