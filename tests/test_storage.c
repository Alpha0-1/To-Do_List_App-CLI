/* test_storage.c - Unit tests for storage.c functionality */

#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include "../src/todo.h"
#include "../src/storage.h"

#define TEST_FILE "test_todo.dat"

void test_save_and_load() {
    TaskList original, loaded;
    initialize_task_list(&original);
    initialize_task_list(&loaded);
    
    add_task(&original, "Saved task 1");
    add_task(&original, "Saved task 2");
    toggle_task_completion(&original, 2);
    
    // Test saving
    assert(save_to_file(&original, TEST_FILE) == true);
    
    // Test loading
    assert(load_from_file(&loaded, TEST_FILE) == true);
    
    // Verify loaded data matches original
    assert(loaded.count == original.count);
    for (int i = 0; i < original.count; i++) {
        assert(loaded.tasks[i].id == original.tasks[i].id);
        assert(strcmp(loaded.tasks[i].title, original.tasks[i].title) == 0);
        assert(loaded.tasks[i].completed == original.tasks[i].completed);
    }
    
    // Clean up
    unlink(TEST_FILE);
    
    printf("test_save_and_load: PASSED\n");
}

void test_load_nonexistent_file() {
    TaskList list;
    initialize_task_list(&list);
    
    assert(load_from_file(&list, "nonexistent_file.dat") == false);
    assert(list.count == 0); // Should remain unchanged
    
    printf("test_load_nonexistent_file: PASSED\n");
}

int main() {
    printf("Running storage.c tests...\n");
    
    test_save_and_load();
    test_load_nonexistent_file();
    
    printf("All storage.c tests passed!\n");
    return 0;
}
