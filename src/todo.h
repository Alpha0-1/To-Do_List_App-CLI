/* todo.h - Core data structures and function declarations for task management */

#ifndef TODO_H
#define TODO_H

#include <stdbool.h>
#include "config.h"

typedef struct {
    int id;
    char title[MAX_TITLE_LENGTH];
    bool completed;
} Task;

typedef struct {
    Task tasks[MAX_TASKS];
    int count;
} TaskList;

/* Task management functions */
void initialize_task_list(TaskList *list);
int add_task(TaskList *list, const char *title);
bool remove_task(TaskList *list, int task_id);
bool toggle_task_completion(TaskList *list, int task_id);
void clear_completed_tasks(TaskList *list);

#endif /* TODO_H */
