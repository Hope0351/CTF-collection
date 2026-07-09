#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define TEST_ASSERT(condition) \
    do { \
        if (!(condition)) { \
            printf("FAIL: %s:%d - Assertion failed: %s\n", __FILE__, __LINE__, #condition); \
            return 1; \
        } \
    } while (0)

#define TEST_ASSERT_NULL(ptr) \
    do { \
        if ((ptr) != NULL) { \
            printf("FAIL: %s:%d - Expected NULL, got %p\n", __FILE__, __LINE__, (void*)(ptr)); \
            return 1; \
        } \
    } while (0)

#define TEST_ASSERT_NOT_NULL(ptr) \
    do { \
        if ((ptr) == NULL) { \
            printf("FAIL: %s:%d - Expected non-NULL, got NULL\n", __FILE__, __LINE__); \
            return 1; \
        } \
    } while (0)

#define RUN_TEST(test_func) \
    do { \
        printf("Running %s... ", #test_func); \
        if (test_func() == 0) { \
            printf("PASS\n"); \
            tests_passed++; \
        } else { \
            tests_failed++; \
        } \
        tests_run++; \
    } while (0)

#define TEST_SUMMARY() \
    do { \
        printf("\n=== Test Summary ===\n"); \
        printf("Tests run: %d\n", tests_run); \
        printf("Tests passed: %d\n", tests_passed); \
        printf("Tests failed: %d\n", tests_failed); \
        if (tests_failed == 0) { \
            printf("All tests passed!\n"); \
        } else { \
            printf("Some tests failed.\n"); \
        } \
    } while (0)

static int tests_run = 0;
static int tests_passed = 0;
static int tests_failed = 0;

// Helper structure to hold WAV file data
typedef struct {
    uint64_t size;
    void* data;
} test_wav_data_t;

// Helper function to read WAV file from tests/data directory
static test_wav_data_t* read_test_wav_file(const char* filename) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "tests/data/%s", filename);
    
    FILE* file = fopen(filepath, "rb");
    if (!file) {
        printf("ERROR: Could not open test file: %s\n", filepath);
        return NULL;
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (file_size <= 0) {
        printf("ERROR: Invalid file size for: %s\n", filepath);
        fclose(file);
        return NULL;
    }
    
    // Allocate memory for data structure and file content
    test_wav_data_t* wav_data = malloc(sizeof(test_wav_data_t));
    if (!wav_data) {
        printf("ERROR: Could not allocate memory for wav_data\n");
        fclose(file);
        return NULL;
    }
    
    wav_data->data = malloc(file_size);
    if (!wav_data->data) {
        printf("ERROR: Could not allocate memory for file data\n");
        free(wav_data);
        fclose(file);
        return NULL;
    }
    
    // Read file content
    size_t bytes_read = fread(wav_data->data, 1, file_size, file);
    if (bytes_read != (size_t)file_size) {
        printf("ERROR: Could not read complete file: %s\n", filepath);
        free(wav_data->data);
        free(wav_data);
        fclose(file);
        return NULL;
    }
    
    wav_data->size = (uint64_t)file_size;
    fclose(file);
    
    return wav_data;
}

// Helper function to free WAV file data
static void free_test_wav_data(test_wav_data_t* wav_data) {
    if (wav_data) {
        if (wav_data->data) {
            free(wav_data->data);
        }
        free(wav_data);
    }
}


#endif
