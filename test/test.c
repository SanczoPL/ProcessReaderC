#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include "test_processreader.h"
#include "test_queue.h"

int main(void)
{
    const struct CMUnitTest tests[] = {

        cmocka_unit_test(processreader_checkIsDigit),
        cmocka_unit_test(processreader_getPid),
        cmocka_unit_test(processreader_readProcessIntoQueue),
        cmocka_unit_test(processreader_readProcessIntoQueue_not_ok),
        cmocka_unit_test(processreader_showName),
        cmocka_unit_test(processreader_showName_not_ok),
        cmocka_unit_test(processreader_showPid),
        cmocka_unit_test(processreader_showPid_not_ok),

		cmocka_unit_test(queue_printQueues),
        cmocka_unit_test(queue_findPidInQueue),
		cmocka_unit_test(queue_findPidInQueue_oneValue),
		cmocka_unit_test(queue_findNameInQueue),
		cmocka_unit_test(queue_findNameInQueue_oneValue),
        cmocka_unit_test(queue_newNode),
        cmocka_unit_test(queue_createQueue),
        cmocka_unit_test(queue_push_back),
        cmocka_unit_test(queue_isEmpty),
        cmocka_unit_test(queue_pop_front),
        cmocka_unit_test(queue_deleteQueue),
        cmocka_unit_test(queue_deleteQueue_empty),
        cmocka_unit_test(queue_deleteQueue_empty_after_pop)

    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
