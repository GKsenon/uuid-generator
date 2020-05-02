#include <stdio.h>

#include <uuid_generator.h>

int main()
{
    if (!uuid_init()) {
        fprintf(stderr, "failed to init uuid\n");
        return -1;
    }

    uuid_close();

    return 0;
}
