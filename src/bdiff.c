#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

size_t file_length(FILE* file)
{
    assert(file != NULL);
    size_t initial_pos = ftell(file);
    assert(fseek(file, 0, SEEK_END) == 0);
    size_t length = ftell(file);
    assert(fseek(file, initial_pos, SEEK_SET) == 0);
    return length;
}

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
    printf("Old length: %zu\n", file_length(old));
    printf("New length: %zu\n", file_length(new));
    fclose(old);
    fclose(new);
    return EXIT_SUCCESS;
}
