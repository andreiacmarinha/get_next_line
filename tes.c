#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "get_next_line.h"

// --- Helper: check if string ends with \n ---
int ends_with_newline(char *s)
{
    if (!s) return 0;
    size_t len = strlen(s);
    return len > 0 && s[len - 1] == '\n';
}

// --- Function pointer trick to test multiple buffer sizes ---
// We temporarily redefine BUFFER_SIZE and include get_next_line.c separately
// You must create copies of get_next_line.c if you want to test multiple sizes
// For simplicity here, we'll simulate it by telling the user to compile with -D BUFFER_SIZE=X

// --- Test a single FD ---
void test_fd(int fd, const char *desc)
{
    char *line;
    printf("Testing FD: %s\n", desc);
    while ((line = get_next_line(fd)) != NULL)
    {
        if (!ends_with_newline(line))
            printf("❌ Line does not end with \\n: %s\n", line);
        else
            printf("✅ Read line: %s", line); // line already has \n
        free(line);
    }
}

// --- Test invalid FD ---
void test_invalid_fd()
{
    char *line = get_next_line(42);
    if (!line)
        printf("✅ Invalid FD returned NULL\n");
    else
    {
        printf("❌ Invalid FD test failed\n");
        free(line);
    }
}

// --- Test reading from stdin ---
void test_stdin()
{
    printf("\n--- Reading from stdin (type a few lines, Ctrl+D to finish) ---\n");
    test_fd(0, "stdin");
}

// --- Test reading from a file ---
void test_file(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return;
    }
    test_fd(fd, filename);
    close(fd);
}

// --- Main test suite ---
int main(void)
{
    printf("=== GET_NEXT_LINE AUTOMATED TESTS ===\n");

    // 1. Invalid FD
    test_invalid_fd();

    // 2. Test files
    const char *files[] = {
        "test_short.txt",    // <4 characters
        "test_long.txt",     // 2k+ characters
        "test_mix.txt",    // multiple lines, mixed lengths
        "empty_lines.txt"     // empty lines
    };

    // Simulated buffer sizes to test (compile-time limitation)
    const int buffer_sizes[] = {1, 4, 7, 8, 16, 32, 1024, 2048};
    size_t nbuff = sizeof(buffer_sizes)/sizeof(buffer_sizes[0]);

    printf("\nNote: To test each BUFFER_SIZE, recompile with -D BUFFER_SIZE=N\n");
    printf("Suggested sizes: ");
    for (size_t i = 0; i < nbuff; i++)
        printf("%d ", buffer_sizes[i]);
    printf("\n");

    // 3. Loop through files
    for (size_t i = 0; i < sizeof(files)/sizeof(files[0]); i++)
        test_file(files[i]);

    printf("=== TESTS COMPLETED ===\n");
    return 0;
}
