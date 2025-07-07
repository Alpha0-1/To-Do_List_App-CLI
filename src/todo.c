/* todo.c - Implementation of task management functions */

#include "todo.h"
#include <string.h>
#include <stdio.h>

void initialize_task_list(TaskList *list) {
    list->count = 0;
}

int add_task(TaskList *list, const char *title) {
    if (list->count >= MAX_TASKS) {
        fprintf(stderr, "Error: Maximum number of tasks reached\n");
        return -1;
    }

    if (strlen(title) >= MAX_TITLE_LENGTH) {
        fprintf(stderr, "Error: Task title too long\n");
        return -1;
    }

    Task new_task = {
        .id = list->count + 1,
        .completed = false
    };
    strncpy(new_task.title, title, MAX_TITLE_LENGTH - 1);
    new_task.title[MAX_TITLE_LENGTH - 1] = '\0';

    list->tasks[list->count] = new_task;
    list->count++;

    return new_task.id;
}

bool remove_task(TaskList *list, int task_id) {
    int found_index = -1;
    
    for (int i = 0; i < list->count; i++) {
        if (list->tasks[i].id == task_id) {
            found_index = i;
            break;
        }
    }

    if (found_index == -1) {
        return false;
    }

    // Shift all subsequent tasks left
    for (int i = found_index; i < list->count - 1; i++) {
        list->tasks[i] = list->tasks[i + 1];
    }

    list->count--;
    return true;
}

bool toggle_task_completion(TaskList *list, int task_id) {
    for (int i = 0; i < list->count; i++) {
        if (list->tasks[i].id == task_id) {
            list->tasks[i].completed = !list->tasks[i].completed;
            return true;
        }
    }
    return false;
}

void clear_completed_tasks(TaskList *list) {
    int write_index = 0;
    
    for (int i = 0; i < list->count; i++) {
        if (!list->tasks[i].completed) {
            list->tasks[write_index] = list->tasks[i];
            write_index++;
        }
    }
    
    list->count = write_index;
}
