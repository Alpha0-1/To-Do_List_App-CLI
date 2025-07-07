/* display.c - Implementation of display rendering functions */

#include "display.h"
#include "todo.h"
#include <stdio.h>

void show_help() {
    printf("\nTodo CLI App - Usage:\n");
    printf("  todo add <task>      Add a new task\n");
    printf("  todo done <id>       Mark task as complete\n");
    printf("  todo rm <id>         Remove a task\n");
    printf("  todo list            Show all tasks\n");
    printf("  todo clear           Remove completed tasks\n");
    printf("  todo help            Show this help\n");
    printf("  todo version         Show version\n");
}

void display_task_list(const TaskList *list) {
    if (list->count == 0) {
        printf("No tasks found.\n");
        return;
    }

    printf("\nID\tStatus\tTask\n");
    printf("--\t------\t----\n");
    
    for (int i = 0; i < list->count; i++) {
        const Task *task = &list->tasks[i];
        printf("%d\t%s\t%s\n", 
               task->id,
               task->completed ? "[X]" : "[ ]",
               task->title);
    }
    printf("\nTotal tasks: %d\n", list->count);
}
