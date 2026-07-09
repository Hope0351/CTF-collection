#include "test_framework.h"
#include "../wav.h"
#include "../common.h"

// Helper function to test WAV parsing with expected properties
static int test_wav_parsing_helper(const char* filename, uint16_t expected_channels, 
                                 uint32_t expected_frequency, uint16_t expected_bits_per_second) {
    test_wav_data_t* wav_data = read_test_wav_file(filename);
    TEST_ASSERT_NOT_NULL(wav_data);
    
    song_audio_t* result = parse_wav(wav_data->size, wav_data->data);
    TEST_ASSERT_NOT_NULL(result);
    
    // Verify expected properties
    TEST_ASSERT(result->channels == expected_channels);
    TEST_ASSERT(result->frequency == expected_frequency);
    TEST_ASSERT(result->bits_per_second == expected_bits_per_second);
    TEST_ASSERT(result->sample_count > 0);
    
    // Clean up
    free(result->samples);
    free(result);
    free_test_wav_data(wav_data);
    
    return 0;
}

int test_parse_wav_null_data() {
    song_audio_t* result = parse_wav(0, NULL);
    TEST_ASSERT_NULL(result);
    return 0;
}

int test_read_wav_file_helper() {
    test_wav_data_t* wav_data = read_test_wav_file("test_simple.wav");
    TEST_ASSERT_NOT_NULL(wav_data);
    TEST_ASSERT_NOT_NULL(wav_data->data);
    TEST_ASSERT(wav_data->size > 0);
    
    free_test_wav_data(wav_data);
    return 0;
}

int test_parse_wav_with_real_file() {
    return test_wav_parsing_helper("test_simple.wav", 1, 44100, 16);
}

int test_parse_wav_8bit() {
    return test_wav_parsing_helper("test_8bit.wav", 1, 44100, 8);
}

int test_parse_wav_32bit() {
    return test_wav_parsing_helper("test_32bit.wav", 1, 44100, 32);
}

int test_parse_cat_flag() {
    return test_wav_parsing_helper("hey-hacker-cat-slash-flag.wav", 1, 44100, 16); 
}


int main() {
    printf("Running WAV parser tests...\n\n");
    
    RUN_TEST(test_parse_wav_null_data);
    RUN_TEST(test_read_wav_file_helper);
    RUN_TEST(test_parse_wav_with_real_file);
    RUN_TEST(test_parse_wav_8bit);
    RUN_TEST(test_parse_wav_32bit);
    RUN_TEST(test_parse_cat_flag);
    
    TEST_SUMMARY();
    
    return tests_failed > 0 ? 1 : 0;
}
