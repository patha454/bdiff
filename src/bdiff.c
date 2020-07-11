#include "buffer.h"
#include "file.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    FILE* old = NULL;
    FILE* new = NULL;
    if (argc != 3) {
        fprintf(stderr, "bdiff requires two arguments.\n");
        exit(EXIT_FAILURE);
    }
    old = fopen(argv[0], "rb");
    new = fopen(argv[1], "rb");
    assert(old != NULL && new != NULL);
    printf("Old length: %lu\n", file_length(old));
    printf("New length: %lu\n", file_length(new));
    struct Buffer* a = new_buffer_from_file(old);
    struct Buffer* b = new_buffer_from_file(new);
    printf("A len: %zu, alloclen: %zu\n", buffer_length(a), buffer_allocated_length(a));
    printf("B len: %zu, alloclen: %zu\n", buffer_length(b), buffer_allocated_length(b));
    printf("A len: %zu, alloclen: %zu\n", buffer_length(a), buffer_allocated_length(a));
    free_buffer(a);
    free_buffer(b);
    fclose(old);
    fclose(new);
    return EXIT_SUCCESS;
}
