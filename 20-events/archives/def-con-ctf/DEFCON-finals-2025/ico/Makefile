CHAL_NAME?=ico
PORT?=4265

docker:
	docker build -t $(CHAL_NAME):latest .

run: docker
	echo "Running $(CHAL_NAME) on port $(PORT)"
	docker rm -f $(CHAL_NAME)-test || true
	sh -c "echo 'flag{4+6Q38zDmXwjTTdsKyYv+gSC9CNY1VUP6rA=:goXk+cVZu9mDNcAY:5b0dcb002586177a}' > example_flag.txt"
	chmod 777 example_flag.txt
	docker run \
		--name $(CHAL_NAME)-test --rm \
		-p $(PORT):$(PORT) \
		-v $(shell pwd)/example_flag.txt:/flag \
		-i $(CHAL_NAME):latest

.PHONY: poller poller/pollerlib

poller: poller/pollerlib docker
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
		-i $(CHAL_NAME):poller

test:
	cd ./service && fpc -vh -Sd -Un -Cg -gw -O- -dDEBUG -oico_test test.pas

clean:
	rm service/ico_test service/*.o service/*.ppu
