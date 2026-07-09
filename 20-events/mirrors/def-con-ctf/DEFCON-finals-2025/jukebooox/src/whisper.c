#include "whisper.h"
#include <fcntl.h>
#include <errno.h>
#include <sys/file.h>

#define DEFAULT_WHISPER_CLI_PATH "/Users/adamd/src/whisper.cpp/build/bin/whisper-cli"
#define DEFAULT_WHISPER_MODEL "/Users/adamd/src/whisper.cpp/models/ggml-tiny.en.bin"
#define MAX_OUTPUT_SIZE 4096
#define MAX_WORDS 1024
#define WHISPER_LOCK_FILE "/tmp/.whisper_lock"

static char** split_by_spaces(const char* input) {
    if (!input) return NULL;
    
    char** result = calloc(MAX_WORDS, sizeof(char*));
    if (!result) return NULL;
    
    char* input_copy = strdup(input);
    if (!input_copy) {
        free(result);
        return NULL;
    }
    
    char* token = strtok(input_copy, " \t\n\r");
    int count = 0;
    
    while (token && count < MAX_WORDS - 1) {
        result[count] = strdup(token);
        if (!result[count]) {
            for (int i = 0; i < count; i++) {
                free(result[i]);
            }
            free(result);
            free(input_copy);
            return NULL;
        }
        count++;
        token = strtok(NULL, " \t\n\r");
    }
    
    result[count] = NULL;
    free(input_copy);
    return result;
}

// Replace all occurrences of 'old' with 'new' in 'str'
static char* str_replace(const char* str, const char* old, const char* new_str) {
    if (!str || !old || !new_str) return NULL;

    size_t old_len = strlen(old);
    size_t new_len = strlen(new_str);

    // Count occurrences of 'old'
    size_t count = 0;
    const char* p = str;
    while ((p = strstr(p, old)) != NULL) {
        count++;
        p += old_len;
    }

    // Allocate space for the new string
    size_t new_size = strlen(str) + count * (new_len - old_len) + 1;
    char* result = malloc(new_size);
    if (!result) return NULL;

    // Do the replacement
    const char* src = str;
    char* dst = result;
    while ((p = strstr(src, old)) != NULL) {
        size_t n = p - src;
        memcpy(dst, src, n);
        dst += n;
        memcpy(dst, new_str, new_len);
        dst += new_len;
        src = p + old_len;
    }
    strcpy(dst, src);  // Copy the remainder
    return result;
}

static char* filter_output(const char* output) {
   char* after = str_replace(output, "slash ", "/");

   char* next = str_replace(after, "semicolon ", ";");
   free(after);

   after = str_replace(next, "colon ", ":");
   free(next);

   next = str_replace(after, "backtick ", "`");
   free(after);

   after = str_replace(next, "backslash ", "\\");
   free(next);

   next = str_replace(after, "pipe ", "|");
   free(after);

   after = str_replace(next, "dash ", "-");
   free(next);

   next = str_replace(after, "dot ", ".");
   free(after);

   after = str_replace(next, "comma ", ",");
   free(next);

   next = str_replace(after, "underscore ", "_");
   free(after);

   after = str_replace(next, "equals ", "=");
   free(next);

   next = str_replace(after, "hash ", "#");
   free(after);

   after = str_replace(next, "percent ", "%");
   free(next);

   next = str_replace(after, "ampersand ", "&");
   free(after);

   after = str_replace(next, "question ", "?");
   free(next);

   next = str_replace(after, "exclamation ", "!");
   free(after);
   
   return next;
}

char** whisper_transcribe(const char* wav_data, size_t size) {
    if (!wav_data || size == 0) {
        return NULL;
    }
    
    // Acquire exclusive lock to prevent multiple whisper processes
    int lock_fd = open(WHISPER_LOCK_FILE, O_CREAT | O_RDWR, 0666);
    if (lock_fd == -1) {
        return NULL;
    }
    
    if (flock(lock_fd, LOCK_EX) == -1) {
        close(lock_fd);
        return NULL;
    }
    
    char* whisper_cli_path = get_env_or_default("WHISPER_CLI_PATH", DEFAULT_WHISPER_CLI_PATH);
    char* whisper_model = get_env_or_default("WHISPER_MODEL", DEFAULT_WHISPER_MODEL);
    
    char temp_template[] = "/tmp/whisper_XXXXXX.txt";
    int temp_fd = mkstemps(temp_template, 4);
    if (temp_fd == -1) {
        flock(lock_fd, LOCK_UN);
        close(lock_fd);
        return NULL;
    }
    close(temp_fd);
    
    char output_file[256];
    strncpy(output_file, temp_template, sizeof(output_file) - 5);
    output_file[strlen(output_file) - 4] = '\0';
    
    int stdin_pipe[2];
    
    if (pipe(stdin_pipe) == -1) {
        unlink(temp_template);
        flock(lock_fd, LOCK_UN);
        close(lock_fd);
        return NULL;
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        close(stdin_pipe[0]);
        close(stdin_pipe[1]);
        unlink(temp_template);
        flock(lock_fd, LOCK_UN);
        close(lock_fd);
        return NULL;
    }
    
    if (pid == 0) {
        close(stdin_pipe[1]);
        
        dup2(stdin_pipe[0], STDIN_FILENO);
        
        close(stdin_pipe[0]);

        int null_fd = open("/dev/null", O_WRONLY);
        if (null_fd != -1) {
            dup2(null_fd, STDOUT_FILENO);
            dup2(null_fd, STDERR_FILENO);
            close(null_fd);
        }
        
        char* args[] = {
            whisper_cli_path,
            "-f", "-",
            "-m", whisper_model,
            "--no-prints",
            "--no-timestamps",
            "--temperature", "0",
            "--no-fallback",
            "--output-txt",
            "--output-file", output_file,
            "-t","1",
            NULL
        };
        
        execvp(whisper_cli_path, args);
        _exit(127);
    }
    
    close(stdin_pipe[0]);
    
    size_t total_written = 0;
    while (total_written < size) {
        ssize_t bytes_written = write(stdin_pipe[1], wav_data + total_written, size - total_written);
        if (bytes_written == -1) {
            if (errno == EINTR) {
                continue;
            }
            close(stdin_pipe[1]);
            waitpid(pid, NULL, 0);
            unlink(temp_template);
            flock(lock_fd, LOCK_UN);
            close(lock_fd);
            return NULL;
        }
        total_written += bytes_written;
    }
    close(stdin_pipe[1]);

    int status;
    waitpid(pid, &status, 0);
    
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
        unlink(temp_template);
        flock(lock_fd, LOCK_UN);
        close(lock_fd);
        return NULL;
    }

    int fd = open(temp_template, O_RDONLY);
    
    char* output = malloc(MAX_OUTPUT_SIZE);
    if (!output) {
        close(fd);
        waitpid(pid, NULL, 0);
        unlink(temp_template);
        flock(lock_fd, LOCK_UN);
        close(lock_fd);
        return NULL;
    }
    
    ssize_t total_read = 0;
    ssize_t bytes_read;
    
    while ((bytes_read = read(fd, output + total_read, MAX_OUTPUT_SIZE - total_read - 1)) > 0) {
        total_read += bytes_read;
        if (total_read >= MAX_OUTPUT_SIZE - 1) {
            break;
        }
    }
    
    close(fd);
    unlink(temp_template);
    
    output[total_read] = '\0';
    
    char* filtered_output = filter_output(output);
    free(output);
    
    if (!filtered_output) {
        flock(lock_fd, LOCK_UN);
        close(lock_fd);
        return NULL;
    }
    
    char** result = split_by_spaces(filtered_output);
    free(filtered_output);
    
    // Release lock before returning
    flock(lock_fd, LOCK_UN);
    close(lock_fd);
    
    return result;
}
