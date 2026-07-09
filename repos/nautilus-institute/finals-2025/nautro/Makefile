all: cards
	zig build-exe -lc ./src/main.zig -fno-stack-protector -fno-omit-frame-pointer
	zig build-lib -lc -dynamic ./src/engine_base.zig -fno-stack-protector -fno-omit-frame-pointer

nice: cards
	rm -rf ./src_preprocessed/
	./preprocess.py
	zig build-exe -lc ./src_preprocessed/main.zig  -O ReleaseFast -fno-strip -fno-stack-protector -fno-omit-frame-pointer
	zig build-lib -lc -dynamic ./src_preprocessed/engine_base.zig -fno-stack-protector -fno-omit-frame-pointer -O ReleaseFast -fno-strip 

final: nice
	./strip.py main
	./strip.py libengine_base.so

final-symbols: nice
	strip -g main

cards:
	zig build-exe ./src/basic_decks.zig -fno-stack-protector -fno-omit-frame-pointer
	rm data/cards/* || true
	rm poller/cards/* || true
	rm exploits/cards/* || true
	./basic_decks > /dev/null 2>/dev/null
	mkdir poller/cards/ -p
	mkdir exploits/cards/ -p
	cp data/cards/op_* poller/cards/
	cp data/cards/op_* exploits/cards/
	rm data/cards/op_* || true

crypto_client: src/crypto_client.zig
	zig build-exe ./src/crypto_client.zig -fno-stack-protector -fno-omit-frame-pointer

CHAL_NAME?=nautro
PORT?=8080

docker:
	docker build -t $(CHAL_NAME):builder --target builder .
	docker build -t $(CHAL_NAME):latest .

run:
	echo "Running $(CHAL_NAME) on port $(PORT)"
	docker rm -f $(CHAL_NAME)-test || true
	sh -c "echo 'flag{4+6Q38zDmXwjTTdsKyYv+gSC9CNY1VUP6rA=:goXk+cVZu9mDNcAY:5b0dcb002586177a}' > example_flag.txt"
	chmod 777 example_flag.txt
	docker run \
		--name $(CHAL_NAME)-test --rm \
		-p $(PORT):$(PORT) \
		-v $(shell pwd)/example_flag.txt:/flag \
		-v /mnt/crypto/1_sign_0_1:/srv/crypto/sign \
		-v /mnt/crypto/1_verify_0_1:/srv/crypto/verify \
		-i $(CHAL_NAME):latest

