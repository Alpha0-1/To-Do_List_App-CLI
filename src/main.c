/* main.c - CLI interface and command dispatch */

#include <stdio.h>
#include <string.h>
#include "todo.h"
#include "storage.h"
#include "display.h"
#include "config.h"

int main(int argc, char *argv[]) {
    TaskList tasks;
    initialize_task_list(&tasks);
    
    // Try to load existing tasks
    load_from_file(&tasks, DATA_FILE);

    if (argc < 2) {
        show_help();
        return 0;
    }

    const char *command = argv[1];

    if (strcmp(command, "add") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: Missing task description\n");
            return 1;
        }
        
        // Combine all arguments after "add" as the task title
        char title[MAX_TITLE_LENGTH] = {0};
        for (int i = 2; i < argc; i++) {
            strncat(title, argv[i], MAX_TITLE_LENGTH - strlen(title) - 1);
            if (i < argc - 1) {
                strncat(title, " ", MAX_TITLE_LENGTH - strlen(title) - 1);
            }
        }
        
        int id = add_task(&tasks, title);
        if (id != -1) {
            printf("Added task #%d: %s\n", id, title);
        }
    }
    else if (strcmp(command, "done") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: Missing task ID\n");
            return 1;
        }
        
        int id = atoi(argv[2]);
        if (toggle_task_completion(&tasks, id)) {
            printf("Marked task #%d as %s\n", id, 
                   tasks.tasks[id-1].completed ? "complete" : "incomplete");
        } else {
            fprintf(stderr, "Error: Task #%d not found\n", id);
        }
    }
    else if (strcmp(command, "rm") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: Missing task ID\n");
            return 1;
        }
        
        int id = atoi(argv[2]);
        if (remove_task(&tasks, id)) {
            printf("Removed task #%d\n", id);
        } else {
            fprintf(stderr, "Error: Task #%d not found\n", id);
        }
    }
    else if (strcmp(command, "list") == 0) {
        display_task_list(&tasks);
    }
    else if (strcmp(command, "clear") == 0) {
        int before_count = tasks.count;
        clear_completed_tasks(&tasks);
        printf("Removed %d completed tasks\n", before_count - tasks.count);
    }
    else if (strcmp(command, "help") == 0) {
        show_help();
    }
    else if (strcmp(command, "version") == 0) {
        printf("Todo CLI App version %s\n", VERSION);
    }
    else {
        fprintf(stderr, "Error: Unknown command '%s'\n", command);
        show_help();
        return 1;
    }

    // Save changes to file
    if (!save_to_file(&tasks, DATA_FILE)) {
        fprintf(stderr, "Warning: Failed to save tasks to file\n");
    }

    return 0;
}
