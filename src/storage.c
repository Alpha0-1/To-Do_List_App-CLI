/* storage.c - Implementation of file save/load functions */

#include "storage.h"
#include "todo.h"
#include <stdio.h>
#include <stdlib.h>

bool save_to_file(const TaskList *list, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file for writing");
        return false;
    }

    size_t items_written = fwrite(list, sizeof(TaskList), 1, file);
    fclose(file);

    return items_written == 1;
}

bool load_from_file(TaskList *list, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file for reading");
        return false;
    }

    size_t items_read = fread(list, sizeof(TaskList), 1, file);
    fclose(file);

    return items_read == 1;
}
