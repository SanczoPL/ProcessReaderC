#include "../src/processreader.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

static void processreader_checkIsDigit(void** state)
{
    (void)state; /* unused */

    assert_true(checkIsDigit("1"));
    assert_false(checkIsDigit("asds"));
    assert_true(checkIsDigit("123124124124"));
    assert_false(checkIsDigit("a"));
}

static void processreader_getPid(void** state)
{
    (void)state; /* unused */

    int pid = 142804;
    char* curr_path = "test_proc_status.txt";
    char* name = malloc(sizeof(char) * 100);
    getPid(name, curr_path);
    assert_string_equal(name, "code");
    free(name);

    char* badName = malloc(sizeof(char) * 100);
    curr_path = "not_exist";
    getPid(badName, curr_path);
    assert_string_not_equal(badName, "code");
    assert_string_equal(name, "not_readed");
}

static void processreader_readProcessIntoQueue(void** state)
{
    (void)state; /* unused */

    struct Queue* q = createQueue();
    const char* procDir = "bin";
    readProcessIntoQueue(q, procDir);

    assert_non_null(q->front);
    assert_non_null(q->rear);

    assert_int_equal(q->count, 1);

    assert_true(printQueue(q));
    deleteQueue(q);
    assert_int_equal(q->count, 0);
}

static void processreader_readProcessIntoQueue_not_ok(void** state)
{
    (void)state; /* unused */

    struct Queue* q = createQueue();
    const char* procDir = "binNotExist";
    readProcessIntoQueue(q, procDir);

    assert_null(q->front);
    assert_null(q->rear);

    assert_int_equal(q->count, 0);

    deleteQueue(q);
    assert_int_equal(q->count, 0);
}

static void processreader_showName(void** state)
{
    (void)state; /* unused */

    const char* procDir = "bin";

    assert_true(showName("142804", procDir));
    assert_false(showName("not_exist", procDir));
}

static void processreader_showName_not_ok(void** state)
{
    (void)state; /* unused */

    const char* procDir = "binNotExist";

    assert_false(showName("142804", procDir));
    assert_false(showName("not_exist", procDir));
}

static void processreader_showPid(void** state)
{
    (void)state; /* unused */
    const char* procDir = "bin";

    assert_true(showPid("code", procDir));
    assert_false(showPid("not_exist", procDir));
}

static void processreader_showPid_not_ok(void** state)
{
    (void)state; /* unused */
    const char* procDir = "binNotExist";

    assert_false(showPid("code", procDir));
    assert_false(showPid("not_exist", procDir));
}
