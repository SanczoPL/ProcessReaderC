#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/queue.h"

static void processreader_newNode(void **state) {
    (void) state; /* unused */

    struct QNode* temp = newNode(123, "123");
    assert_non_null(temp);
    assert_int_equal(temp->pid, 123);
    assert_string_equal(temp->name, "123");
    assert_null(temp->next);
    free(temp);
}

static void processreader_createQueue(void **state) {
    (void) state; /* unused */

    struct Queue* q = createQueue();

    assert_int_equal(q->count, 0);
    assert_non_null(q);
    assert_null(q->front);
    assert_null(q->rear);

    deleteQueue(q);
}

static void processreader_push_back(void **state) {
    (void) state; /* unused */

    struct Queue* q = createQueue();

    assert_int_equal(q->count, 0);
    assert_non_null(q);
    assert_null(q->front);
    assert_null(q->rear);

    push_back(q, 123, "123");

    assert_int_equal(q->count, 1);
    assert_int_equal(q->front->pid, 123);
    assert_int_equal(q->rear->pid, 123);

    assert_string_equal(q->front->name, "123");
    assert_string_equal(q->rear->name, "123");

    push_back(q, 222, "222");

    assert_int_equal(q->count, 2);
    assert_int_equal(q->front->pid, 123);
    assert_int_equal(q->rear->pid, 222);

    assert_string_equal(q->front->name, "123");
    assert_string_equal(q->rear->name, "222");

    deleteQueue(q);
}


static void processreader_isEmpty(void **state) {
    (void) state; /* unused */

    struct Queue* q = createQueue();
    assert_null(q->rear);
    assert_true(isEmpty(q));

    push_back(q, 123, "123");

    assert_int_equal(q->count, 1);
    assert_int_equal(q->front->pid, 123);
    assert_int_equal(q->rear->pid, 123);

    assert_string_equal(q->front->name, "123");
    assert_string_equal(q->rear->name, "123");

    assert_false(isEmpty(q));

    deleteQueue(q);
}

static void processreader_pop_front(void **state) {
    (void) state; /* unused */

    struct Queue* q = createQueue();
    assert_null(q->rear);
    assert_true(isEmpty(q));

    push_back(q, 123, "123");

    assert_int_equal(q->count, 1);
    assert_int_equal(q->front->pid, 123);
    assert_int_equal(q->rear->pid, 123);

    assert_string_equal(q->front->name, "123");
    assert_string_equal(q->rear->name, "123");

    pop_front(q);
    assert_true(isEmpty(q));
    assert_int_equal(q->count, 0);

    push_back(q, 111, "111");
    push_back(q, 222, "222");
    push_back(q, 333, "333");
    assert_int_equal(q->count, 3);
    pop_front(q);
    assert_int_equal(q->count, 2);

    assert_int_equal(q->front->pid, 222);
    assert_int_equal(q->rear->pid, 333);
    assert_string_equal(q->front->name, "222");
    assert_string_equal(q->rear->name, "333");

    deleteQueue(q);
}

static void processreader_deleteQueue(void **state) {
    (void) state; /* unused */

    struct Queue* q = createQueue();
    assert_null(q->rear);
    assert_null(q->front);
    assert_non_null(q);

    push_back(q, 123, "123");
    assert_int_equal(q->count, 1);
    assert_int_equal(q->front->pid, 123);
    assert_int_equal(q->rear->pid, 123);
    assert_string_equal(q->front->name, "123");
    assert_string_equal(q->rear->name, "123");

    assert_true(deleteQueue(q));   
}

static void processreader_deleteQueue_empty(void **state) {
    (void) state; /* unused */

    struct Queue* q = createQueue();
    assert_null(q->rear);
    assert_null(q->front);
    assert_non_null(q);

    assert_true(deleteQueue(q));   
}

static void processreader_deleteQueue_empty_after_pop(void **state) {
    (void) state; /* unused */

    struct Queue* q = createQueue();
    assert_null(q->rear);
    assert_null(q->front);
    assert_non_null(q);

    push_back(q, 123, "123");
    assert_int_equal(q->count, 1);
    assert_int_equal(q->front->pid, 123);
    assert_int_equal(q->rear->pid, 123);
    assert_string_equal(q->front->name, "123");
    assert_string_equal(q->rear->name, "123");

    pop_front(q);
    assert_true(isEmpty(q));
    assert_int_equal(q->count, 0);

    assert_true(deleteQueue(q));   
}
