/* storage.h - Declarations for file persistence functions */

#ifndef STORAGE_H
#define STORAGE_H

#include "todo.h"

bool save_to_file(const TaskList *list, const char *filename);
bool load_from_file(TaskList *list, const char *filename);

#endif /* STORAGE_H */
