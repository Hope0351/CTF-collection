CC = clang
CFLAGS = -g -DDEBUG=1 -O2 -s -I include -lpthread -fPIE -pie -fstack-protector-strong -Wl,-z,relro -Wl,-z,now

default: all

all: build/shredder build/leonardo build/raphael build/michelangelo build/donatello build/splinter build/april

build/shredder: src/main.c src/bus.c
	$(CC) $(CFLAGS) -o build/shredder src/main.c src/bus.c

build/leonardo: src/chips/dma.c src/bus.c
	$(CC) $(CFLAGS) -o build/leonardo src/chips/dma.c src/bus.c

build/raphael: src/chips/cache.c src/bus.c
	$(CC) $(CFLAGS) -o build/raphael src/chips/cache.c src/bus.c

build/michelangelo: src/chips/sram.c src/bus.c src/aes.c
	$(CC) $(CFLAGS) -D ECB=1 -o build/michelangelo src/chips/sram.c src/bus.c src/aes.c

build/donatello: src/chips/flag.c src/bus.c
	$(CC) $(CFLAGS) -o build/donatello src/chips/flag.c src/bus.c

build/splinter: src/chips/player.c src/bus.c
	$(CC) $(CFLAGS) -o build/splinter src/chips/player.c src/bus.c

build/april: src/chips/cpu.zig
	#zig build-exe -femit-bin=build/april -OReleaseFast -fstrip -fPIE src/chips/cpu.zig
	zig build-exe -femit-bin=build/april src/chips/cpu.zig

clean:
	rm -f build/*.dsym build/*.o build/shredder build/leonardo build/michelangelo build/donatello build/raphael build/splinter build/april
