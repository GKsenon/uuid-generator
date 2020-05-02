#include <stdio.h>
#include <stdlib.h>
#include <uuid_generator.h>

#define REQUIRE(predicate)                                                     \
        if (!(predicate)) {                                                    \
                fprintf(stderr,                                                \
                        "Assertion failed: " #predicate ", "                   \
                        "file %s, line %d\n", __FILE__, __LINE__);             \
                exit(EXIT_FAILURE);                                            \
        }

int main()
{
    if (!uuid_init())
    {
        fprintf(stderr, "failed to init uuid lib\n");
        return -1;
    }

    uuid_t first = uuid_generate();
    uuid_t second = uuid_generate();

    char buf[37];
    uuid_to_string(&first, buf);
    printf("First uuid = %s\n", buf);
    uuid_to_string(&second, buf);
    printf("Second uuid = %s\n", buf);

    REQUIRE(uuid_compare(&first, &second) == 0);
    REQUIRE(uuid_compare(&first, &first) == 1);

    uuid_close();

    return 0;
}
