#include <windows.h>
#include <bcrypt.h>

#include "random_number_generator.h"

BCRYPT_ALG_HANDLE provider;

int generator_init()
{
    if(!BCRYPT_SUCCESS(BCryptOpenAlgorithmProvider(&provider, BCRYPT_RNG_ALGORITHM, NULL, 0)))
    {
        return 0;
    }
    return 1;
}

void generator_close()
{
    BCryptCloseAlgorithmProvider(provider, 0);
}

int generator_random_number(int min, int max)
{
    int buffer;
    if (!BCRYPT_SUCCESS(BCryptGenRandom(provider, (PUCHAR)(&buffer), sizeof (buffer), 0))) 
    {
        return 0;
    }
    if(buffer < 0) buffer = -buffer;
    return buffer % max + min;
}
