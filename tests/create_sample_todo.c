/* create_sample_todo.c - Creates an initial todo.dat file with sample tasks */

#include <stdio.h>
#include "src/todo.h"
#include "src/storage.h"

int main() {
    TaskList list;
    initialize_task_list(&list);
    
    add_task(&list, "Buy groceries");
    add_task(&list, "Finish project");
    add_task(&list, "Call mom");
    
    // Mark one task as completed
    toggle_task_completion(&list, 2);
    
    if (save_to_file(&list, "todo.dat")) {
        printf("Created todo.dat with sample tasks\n");
        return 0;
    } else {
        fprintf(stderr, "Failed to create todo.dat\n");
        return 1;
    }
}
