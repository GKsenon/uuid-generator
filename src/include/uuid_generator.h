#pragma once

typedef struct
{
    unsigned char data[16];
} uuid_t;

int uuid_init();

void uuid_close();

uuid_t uuid_generate();

void uuid_to_string(uuid_t *uuid, char *buf);

int uuid_compare(uuid_t *first, uuid_t *second);

int uuid_validate(char *buf);

uuid_t uuid_parse(char *buf);
