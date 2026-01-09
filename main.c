
#include <stdio.h>
#include "include/TestHelpers.h"

int main() {
    test_eventLog();
    test_eventQueue();

    printf("All tests completed!\n");
    return 0;
}