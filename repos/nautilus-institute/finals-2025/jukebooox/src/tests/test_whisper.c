#include "test_framework.h"
#include "../whisper.h"

#include <strings.h>

// Helper function to free whisper result
static void free_whisper_result(char** result) {
    if (result) {
        for (int i = 0; result[i]; i++) {
            free(result[i]);
        }
        free(result);
    }
}

// Test whisper_transcribe with NULL data
int test_whisper_transcribe_null_data() {
    char** result = whisper_transcribe(NULL, 0);
    TEST_ASSERT_NULL(result);
    
    result = whisper_transcribe(NULL, 100);
    TEST_ASSERT_NULL(result);
    
    return 0;
}

// Test whisper_transcribe with zero size
int test_whisper_transcribe_zero_size() {
    char dummy_data[] = "dummy";
    char** result = whisper_transcribe(dummy_data, 0);
    TEST_ASSERT_NULL(result);
    
    return 0;
}

// Test whisper_transcribe with valid WAV file - basic crash test
int test_whisper_transcribe_simple_wav() {
    test_wav_data_t* wav_data = read_test_wav_file("test_simple.wav");
    TEST_ASSERT_NOT_NULL(wav_data);
    
    char** result = whisper_transcribe((const char*)wav_data->data, wav_data->size);
    
    // We don't assert the result is not NULL because whisper might not be installed
    // We just verify it doesn't crash and if it succeeds, the result is valid
    if (result) {
        // If we get a result, it should be a valid NULL-terminated array
        // Just verify we can access the first element without crashing
        for (int i = 0; result[i]; i++) {
            TEST_ASSERT_NOT_NULL(result[i]);
        }
        free_whisper_result(result);
    }
    
    free_test_wav_data(wav_data);
    return 0;
}

// Test whisper_transcribe with 8-bit WAV file
int test_whisper_transcribe_test_test() {
    test_wav_data_t* wav_data = read_test_wav_file("test_test.wav");
    TEST_ASSERT_NOT_NULL(wav_data);
    
    char** result = whisper_transcribe((const char*)wav_data->data, wav_data->size);
        
    if (result) {
       // that there's a test somewhere here
       bool found = false;
        for (int i = 0; result[i]; i++) {
           TEST_ASSERT_NOT_NULL(result[i]);
           if (strncasecmp("test", result[i], strlen("test")) == 0)
           {
              found = true;
           }
        }
        TEST_ASSERT(found);
        free_whisper_result(result);
    }
    
    free_test_wav_data(wav_data);
    return 0;
}

// Test whisper_transcribe with 32-bit WAV file
int test_whisper_transcribe_32bit_wav() {
    test_wav_data_t* wav_data = read_test_wav_file("test_32bit.wav");
    TEST_ASSERT_NOT_NULL(wav_data);
    
    char** result = whisper_transcribe((const char*)wav_data->data, wav_data->size);
    
    // Same as above - just verify no crash
    if (result) {
        for (int i = 0; result[i]; i++) {
            TEST_ASSERT_NOT_NULL(result[i]);
        }
        free_whisper_result(result);
    }
    
    free_test_wav_data(wav_data);
    return 0;
}

// Test whisper_transcribe with another WAV file
int test_whisper_transcribe_m1f1_wav() {
    test_wav_data_t* wav_data = read_test_wav_file("M1F1-uint8-AFsp.wav");
    TEST_ASSERT_NOT_NULL(wav_data);
    
    char** result = whisper_transcribe((const char*)wav_data->data, wav_data->size);
    
    // Same as above - just verify no crash
    if (result) {
        for (int i = 0; result[i]; i++) {
            TEST_ASSERT_NOT_NULL(result[i]);
        }
        free_whisper_result(result);
    }
    
    free_test_wav_data(wav_data);
    return 0;
}

// Test whisper_transcribe with invalid WAV data
int test_whisper_transcribe_invalid_data() {
    char invalid_data[] = "This is not a WAV file";
    char** result = whisper_transcribe(invalid_data, strlen(invalid_data));
    
    // Invalid data should either return NULL or handle gracefully
    // We just verify it doesn't crash
    if (result) {
        free_whisper_result(result);
    }
    
    return 0;
}

// Test whisper_transcribe with very small data
int test_whisper_transcribe_small_data() {
    char small_data[] = "XYZ";
    char** result = whisper_transcribe(small_data, sizeof(small_data));
    
    // Small data should either return NULL or handle gracefully
    // We just verify it doesn't crash
    if (result) {
        free_whisper_result(result);
    }
    
    return 0;
}

// Test whisper_transcribe result structure
int test_whisper_transcribe_result_structure() {
    test_wav_data_t* wav_data = read_test_wav_file("test_simple.wav");
    TEST_ASSERT_NOT_NULL(wav_data);
    
    char** result = whisper_transcribe((const char*)wav_data->data, wav_data->size);
    
    if (result) {
        // Verify the result is properly NULL-terminated
        int count = 0;
        while (result[count]) {
            TEST_ASSERT_NOT_NULL(result[count]);
            // Verify each string is not empty
            TEST_ASSERT(strlen(result[count]) > 0);
            count++;
        }
        
        // Verify NULL termination
        TEST_ASSERT_NULL(result[count]);
        
        free_whisper_result(result);
    }
    
    free_test_wav_data(wav_data);
    return 0;
}

int main() {
    printf("Running whisper transcription tests...\n\n");
    
    RUN_TEST(test_whisper_transcribe_null_data);
    RUN_TEST(test_whisper_transcribe_zero_size);
    RUN_TEST(test_whisper_transcribe_simple_wav);
    RUN_TEST(test_whisper_transcribe_test_test);
    RUN_TEST(test_whisper_transcribe_32bit_wav);
    RUN_TEST(test_whisper_transcribe_m1f1_wav);
    RUN_TEST(test_whisper_transcribe_invalid_data);
    RUN_TEST(test_whisper_transcribe_small_data);
    RUN_TEST(test_whisper_transcribe_result_structure);
    
    TEST_SUMMARY();
    
    return tests_failed > 0 ? 1 : 0;
}
