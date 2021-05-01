#include "../src/queue.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

static void queue_printQueues(void** state)
{
    (void)state; /* unused */

    struct Queue* q = createQueue();

    assert_false(printNameFromQueue(q));
    assert_false(printPidFromQueue(q));
    assert_false(printQueue(q));

    push_back(q, 111, "111");

    assert_true(printNameFromQueue(q));
    assert_true(printPidFromQueue(q));
    assert_true(printQueue(q));
}

static void queue_findPidInQueue(void** state)
{
    (void)state; /* unused */

    struct Queue* q = createQueue();

    assert_int_equal(q->count, 0);
    assert_non_null(q);
    assert_null(q->front);
    assert_null(q->rear);

    push_back(q, 111, "111");
    push_back(q, 222, "222");
    push_back(q, 333, "333");
    push_back(q, 444, "444");
    push_back(q, 555, "555");
    push_back(q, 666, "666");
    push_back(q, 777, "777");

    assert_int_equal(q->count, 7);

    struct Queue* findQ = findPidInQueue(q, 444);
    assert_int_equal(findQ->count, 1);
    assert_int_equal(findQ->front->pid, 444);
    assert_string_equal(findQ->front->name, "444");
}

static void queue_findPidInQueue_oneValue(void** state)
{
    (void)state; /* unused */

    struct Queue* q = createQueue();

    assert_int_equal(q->count, 0);
    assert_non_null(q);
    assert_null(q->front);
    assert_null(q->rear);

    push_back(q, 111, "111");
    assert_int_equal(q->count, 1);

    struct Queue* findQ = findPidInQueue(q, 111);
    assert_int_equal(findQ->count, 1);
    assert_int_equal(findQ->front->pid, 111);
    assert_string_equal(findQ->front->name, "111");
}

static void queue_findNameInQueue(void** state)
{
    (void)state; /* unused */

    struct Queue* q = createQueue();

    assert_int_equal(q->count, 0);
    assert_non_null(q);
    assert_null(q->front);
    assert_null(q->rear);

    push_back(q, 111, "111");
    push_back(q, 222, "222");
    push_back(q, 333, "333");
    push_back(q, 444, "444");
    push_back(q, 555, "555");
    push_back(q, 666, "666");
    push_back(q, 777, "777");

    assert_int_equal(q->count, 7);

    struct Queue* findQ = findNameInQueue(q, "666");
    assert_int_equal(findQ->count, 1);
    assert_int_equal(findQ->front->pid, 666);
    assert_string_equal(findQ->front->name, "666");
    assert_false(isEmpty(findQ));
}

static void queue_findNameInQueue_oneValue(void** state)
{
    (void)state; /* unused */

    struct Queue* q = createQueue();
    assert_true(isEmpty(q));

    assert_int_equal(q->count, 0);
    assert_non_null(q);
    assert_null(q->front);
    assert_null(q->rear);

    push_back(q, 111, "111");

    assert_int_equal(q->count, 1);

    struct Queue* findQ = findNameInQueue(q, "111");
    assert_int_equal(findQ->count, 1);
    assert_int_equal(findQ->front->pid, 111);
    assert_string_equal(findQ->front->name, "111");
    assert_false(isEmpty(findQ));
}

static void queue_newNode(void** state)
{
    (void)state; /* unused */

    struct QNode* temp = newNode(123, "123");
    assert_non_null(temp);
    assert_int_equal(temp->pid, 123);
    assert_string_equal(temp->name, "123");
    assert_null(temp->next);
    free(temp);
}

static void queue_createQueue(void** state)
{
    (void)state; /* unused */

    struct Queue* q = createQueue();

    assert_int_equal(q->count, 0);
    assert_non_null(q);
    assert_null(q->front);
    assert_null(q->rear);

    deleteQueue(q);
}

static void queue_push_back(void** state)
{
    (void)state; /* unused */

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

static void queue_isEmpty(void** state)
{
    (void)state; /* unused */

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

static void queue_pop_front(void** state)
{
    (void)state; /* unused */

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

static void queue_deleteQueue(void** state)
{
    (void)state; /* unused */

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

static void queue_deleteQueue_empty(void** state)
{
    (void)state; /* unused */

    struct Queue* q = createQueue();
    assert_null(q->rear);
    assert_null(q->front);
    assert_non_null(q);

    assert_true(deleteQueue(q));
}

static void queue_deleteQueue_empty_after_pop(void** state)
{
    (void)state; /* unused */

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
