#include "vec.h"  // Include your vector implementation
#include <stdio.h>

// Helper function to report test results
void report_test(const char* message, int passed) {
    printf("%s: %s\n", message, passed ? "PASSED" : "FAILED");
}

// Test initializing the vector
void test_init() {
    t_vec v;
    int result = vec_init(&v, 10, sizeof(int));
    report_test("test_init - Expect successful initialization", result == 0 && v.capacity == 10 && v.size == 0 && v.data != NULL);
}

// Test resizing the vector
void test_resize() {
    t_vec v;
    vec_init(&v, 2, sizeof(int));
    vec_resize(&v, 5);
    report_test("test_resize - Expect capacity to change to 5", v.capacity == 5);

    // Cleanup
    vec_free(&v);
}

// Test adding elements to the vector
void test_push() {
    t_vec v;
    vec_init(&v, 1, sizeof(int));  // Start with a small capacity to test resizing
    int numbers[] = {10, 20, 30};
    vec_push(&v, &numbers[0]);
    vec_push(&v, &numbers[1]);
    vec_push(&v, &numbers[2]);

    report_test("test_push - Expect size to be 3", v.size == 3);
    report_test("test_push - Expect correct elements in vector",
                *((int*)(v.data)) == 10 &&
                *((int*)(v.data + 1 * v.elem_size)) == 20 &&
                *((int*)(v.data + 2 * v.elem_size)) == 30);

    // Cleanup
    vec_free(&v);
}

// Test handling of null pointer inputs
void test_null_pointer() {
    t_vec v;
    vec_init(&v, 10, sizeof(int));
    int result = vec_push(&v, NULL);  // Trying to push a null element
    report_test("test_null_pointer - Expect handling of NULL element", result == 1);
    vec_free(&v);
}

// Test for zero initial capacity
void test_zero_initial_capacity() {
    t_vec v;
    vec_init(&v, 0, sizeof(int));
    int number = 42;
    vec_push(&v, &number);  // This should trigger a resize
    report_test("test_zero_initial_capacity - Expect resize from zero", v.capacity > 0 && v.size == 1);
    vec_free(&v);
}

// Stress test for pushing multiple elements
void test_stress_push() {
    t_vec v;
    vec_init(&v, 1, sizeof(int));  // Start small to force multiple resizes
    for (int i = 0; i < 1000; i++) {
        vec_push(&v, &i);
    }
    report_test("test_stress_push - Expect size to be 1000", v.size == 1000);
    report_test("test_stress_push - Expect capacity to be adequate", v.capacity >= 1000);
    vec_free(&v);
}

// Run all tests
void run_tests() {
    test_init();
    test_resize();
    test_push();
    test_null_pointer();
    test_zero_initial_capacity();
    test_stress_push();
}
int main() {
    run_tests();
    return 0;
}
