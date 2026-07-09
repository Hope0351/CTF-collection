CC = gcc
CFLAGS = -std=c2x -Wall -Wextra -Wpedantic -D_DEFAULT_SOURCE
DEBUG_FLAGS = -g -O0 -DDEBUG
RELEASE_FLAGS = -O2 -DNDEBUG
LDFLAGS = -lm -rdynamic

BUILD_DIR = build
TARGET = $(BUILD_DIR)/jukebooox
TEST_TARGET = $(BUILD_DIR)/test_wav
FUZZ_TARGET = $(BUILD_DIR)/fuzz_wav

# Shared libraries for devices
ECHOOO_SO = $(BUILD_DIR)/echooo.so
LAPTOOOP_SO = $(BUILD_DIR)/laptooop.so
PROOODIGI_SO = $(BUILD_DIR)/prooodigi.so

SRCS = main.c wav.c common.c whisper.c md5.c
DEVICE_SRCS = echooo.c laptooop.c prooodigi.c

# Conditionally add macOS play device on Apple platforms
ifeq ($(shell uname),Darwin)
    MACOS_SRCS = macos_play_device.c
    MACOS_LDFLAGS = -framework AudioToolbox
else
    MACOS_SRCS =
    MACOS_LDFLAGS =
endif

# For debug builds, include macOS sources on Darwin
DEBUG_SRCS = $(SRCS)
ifeq ($(shell uname),Darwin)
    DEBUG_SRCS += $(MACOS_SRCS)
endif

OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
DEBUG_OBJS = $(DEBUG_SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

TEST_SRCS = wav.c common.c
TEST_OBJS = $(TEST_SRCS:%.c=$(BUILD_DIR)/%.o)
TEST_DEPS = $(TEST_OBJS:.o=.d)
TEST_MAIN = tests/test_wav.c
TEST_MAIN_OBJ = $(BUILD_DIR)/test_wav.o

FUZZ_SRCS = wav.c common.c
FUZZ_OBJS = $(FUZZ_SRCS:%.c=$(BUILD_DIR)/%.o)
FUZZ_MAIN = fuzz_wav.c
FUZZ_MAIN_OBJ = $(BUILD_DIR)/fuzz_wav.o

WHISPER_TEST_SRCS = whisper.c common.c
WHISPER_TEST_OBJS = $(WHISPER_TEST_SRCS:%.c=$(BUILD_DIR)/%.o)
WHISPER_TEST_MAIN = tests/test_whisper.c
WHISPER_TEST_MAIN_OBJ = $(BUILD_DIR)/test_whisper.o
WHISPER_TEST_TARGET = $(BUILD_DIR)/test_whisper

.PHONY: all debug release clean test fuzz pytest test-all test-whisper devices

all: debug

debug: CFLAGS += $(DEBUG_FLAGS)
debug: LDFLAGS += $(MACOS_LDFLAGS)
debug: $(BUILD_DIR) $(DEBUG_OBJS) devices
	$(CC) $(DEBUG_OBJS) -o $(TARGET) $(LDFLAGS)

release: CFLAGS += $(RELEASE_FLAGS)
release: $(TARGET) devices

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(BUILD_DIR) $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)
-include $(TEST_DEPS)
-include $(FUZZ_MAIN_OBJ:.o=.d)
-include $(WHISPER_TEST_MAIN_OBJ:.o=.d)

clean:
	rm -rf $(BUILD_DIR)

run: debug
	./$(TARGET)

test: CFLAGS += $(DEBUG_FLAGS)
test: $(BUILD_DIR) $(TEST_OBJS) $(TEST_MAIN_OBJ) $(WHISPER_TEST_OBJS) $(WHISPER_TEST_MAIN_OBJ)
	$(CC) $(TEST_OBJS) $(TEST_MAIN_OBJ) -o $(TEST_TARGET) $(LDFLAGS)
	./$(TEST_TARGET)
	$(CC) $(WHISPER_TEST_OBJS) $(WHISPER_TEST_MAIN_OBJ) -o $(WHISPER_TEST_TARGET) $(LDFLAGS)
	./$(WHISPER_TEST_TARGET)

$(TEST_MAIN_OBJ): $(TEST_MAIN) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $(TEST_MAIN) -o $(TEST_MAIN_OBJ)

fuzz: CC = clang
fuzz: CFLAGS = -fsanitize=fuzzer,address -g -O1 -std=c2x -Wall -Wextra -Wpedantic -D_DEFAULT_SOURCE
fuzz: LDFLAGS = -fsanitize=fuzzer,address -lm
fuzz: $(BUILD_DIR) $(FUZZ_OBJS) $(FUZZ_MAIN_OBJ)
	$(CC) $(FUZZ_OBJS) $(FUZZ_MAIN_OBJ) -o $(FUZZ_TARGET) $(LDFLAGS)

$(FUZZ_MAIN_OBJ): $(FUZZ_MAIN) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $(FUZZ_MAIN) -o $(FUZZ_MAIN_OBJ)

test-whisper: CFLAGS += $(DEBUG_FLAGS)
test-whisper: $(BUILD_DIR) $(WHISPER_TEST_OBJS) $(WHISPER_TEST_MAIN_OBJ)
	$(CC) $(WHISPER_TEST_OBJS) $(WHISPER_TEST_MAIN_OBJ) -o $(WHISPER_TEST_TARGET) $(LDFLAGS)
	./$(WHISPER_TEST_TARGET)

$(WHISPER_TEST_MAIN_OBJ): $(WHISPER_TEST_MAIN) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $(WHISPER_TEST_MAIN) -o $(WHISPER_TEST_MAIN_OBJ)

pytest: debug
	@echo "Running Python tests..."
	cd .. && python -m pytest src/tests/test_upload.py -v

test-all: test pytest
	@echo "All tests completed!"

# Device shared libraries
devices: $(ECHOOO_SO) $(LAPTOOOP_SO) $(PROOODIGI_SO)

$(ECHOOO_SO): echooo.c whisper.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^ $(LDFLAGS)

$(LAPTOOOP_SO): laptooop.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^ $(LDFLAGS)

$(PROOODIGI_SO): prooodigi.c prooodigi.h key_detection.c kiss_fftr.c kiss_fft.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^ $(LDFLAGS)

