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

    char *valid_uuid = "95cfb805-ade0-4b6c-b561-aed771505020";
    char *too_long_uuid = "95cfb805-ade0-4b6c-b561-aed771505020-abcd456";
    char *wrong_version_uuid = "95cfb805-ade0-8b6c-b561-aed771505020";
    char *wrong_variant_uuid = "95cfb805-ade0-4b6c-1561-aed771505020";
    char *not_separated_uuid = "95cfb805ade0-4b6cb561-aed771505020";
    REQUIRE(uuid_validate(valid_uuid) == 1);
    REQUIRE(uuid_validate(too_long_uuid) == 0);
    REQUIRE(uuid_validate(wrong_version_uuid) == 0);
    REQUIRE(uuid_validate(wrong_variant_uuid) == 0);
    REQUIRE(uuid_validate(not_separated_uuid) == 0);

    uuid_t parsed_uuid = uuid_parse(valid_uuid);
    unsigned char uuid_data[] = { 0x95, 0xcf, 0xb8, 0x5, 0xad, 0xe0, 0x4b, 0x6c, 0xb5, 0x61, 0xae, 0xd7, 0x71, 0x50, 0x50, 0x20 };
    int i;
    for(i = 0; i < 16; i++)
    {
        REQUIRE(parsed_uuid.data[i] == uuid_data[i]);
    }

    uuid_close();

    return 0;
}
