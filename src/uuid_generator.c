#include <stdio.h>
#include <ctype.h>
#include <uuid_generator.h>

#include "random_number_generator.h"

int uuid_validate_char(int position, char uuid_char);

int uuid_init()
{
    return generator_init();
}

void uuid_close()
{
    generator_close();
}

uuid_t uuid_generate()
{
    uuid_t uuid;
    int i, high = 0, low = 0;

    for (i = 0; i < 16; i++)
    {
        high = generator_random_number(0, 16);
        uuid.data[i] = high << 4;
        low = generator_random_number(0, 16);
        uuid.data[i] |= low;
    }

    // set the version bits to 0100
    uuid.data[6] = uuid.data[6] & 0b01001111 | 0b01000000;

    // set the variant bits to 10
    uuid.data[8] = uuid.data[8] & 0b10111111 | 0b10000000;

    return uuid;
}

void uuid_to_string(uuid_t *uuid, char *buf)
{
    int i;
    for (i = 0; i < 16; i++)
    {
        buf += sprintf(buf, "%02x", uuid->data[i]);
        if (i == 3 || i == 5 || i == 7 || i == 9)
        {
            buf += sprintf(buf, "-");
        }
    }
}

int uuid_compare(uuid_t *first, uuid_t *second)
{
    int i;
    for(i = 0; i < 16; i++)
    {
        if(first->data[i] != second->data[i])
        {
            return 0;
        }
    }
    return 1;
}

int uuid_validate(char *buf)
{
    int i;
    char lower_case_uuid_char;

    for(i = 0; i < 36; i++)
    {
        if(buf[i] == '\0' || buf[i] == '\n')
            return 0;

        lower_case_uuid_char = tolower(buf[i]);
        if(!uuid_validate_char(i, lower_case_uuid_char))
            return 0;
    }

    return buf[i] == '\0';
}

int uuid_validate_char(int position, char uuid_char)
{
    switch(position)
    {
        case 8:
        case 13:
        case 18:
        case 23:
            return uuid_char == '-';

        case 14:
            return uuid_char == '4';
    
        case 19:
            return uuid_char == '8' || uuid_char == '9' || uuid_char == 'a' || uuid_char == 'b';

        default:
            return isxdigit(uuid_char);
    }
}
