/* test_todo.c - Unit tests for todo.c functionality */

#include <stdio.h>
#include <assert.h>
#include "../src/todo.h"

void test_initialize_task_list() {
    TaskList list;
    initialize_task_list(&list);
    
    assert(list.count == 0);
    printf("test_initialize_task_list: PASSED\n");
}

void test_add_task() {
    TaskList list;
    initialize_task_list(&list);
    
    int id1 = add_task(&list, "Test task 1");
    assert(id1 == 1);
    assert(list.count == 1);
    assert(strcmp(list.tasks[0].title, "Test task 1") == 0);
    assert(list.tasks[0].completed == false);
    
    int id2 = add_task(&list, "Test task 2");
    assert(id2 == 2);
    assert(list.count == 2);
    
    printf("test_add_task: PASSED\n");
}

void test_remove_task() {
    TaskList list;
    initialize_task_list(&list);
    
    add_task(&list, "Task to remove");
    add_task(&list, "Another task");
    
    assert(remove_task(&list, 1) == true);
    assert(list.count == 1);
    assert(list.tasks[0].id == 2); // IDs should remain unchanged
    
    assert(remove_task(&list, 99) == false); // Non-existent ID
    
    printf("test_remove_task: PASSED\n");
}

void test_toggle_task_completion() {
    TaskList list;
    initialize_task_list(&list);
    
    add_task(&list, "Task to toggle");
    
    assert(toggle_task_completion(&list, 1) == true);
    assert(list.tasks[0].completed == true);
    
    assert(toggle_task_completion(&list, 1) == true);
    assert(list.tasks[0].completed == false);
    
    assert(toggle_task_completion(&list, 99) == false); // Non-existent ID
    
    printf("test_toggle_task_completion: PASSED\n");
}

void test_clear_completed_tasks() {
    TaskList list;
    initialize_task_list(&list);
    
    add_task(&list, "Incomplete task");
    add_task(&list, "Complete task");
    toggle_task_completion(&list, 2);
    
    clear_completed_tasks(&list);
    assert(list.count == 1);
    assert(list.tasks[0].id == 1);
    
    printf("test_clear_completed_tasks: PASSED\n");
}

int main() {
    printf("Running todo.c tests...\n");
    
    test_initialize_task_list();
    test_add_task();
    test_remove_task();
    test_toggle_task_completion();
    test_clear_completed_tasks();
    
    printf("All todo.c tests passed!\n");
    return 0;
}
