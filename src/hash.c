#include <stdlib.h>
#include <stdint.h>
#include <hash.h>

uint32_t hash(const char *str, uint32_t taille)
{
    uint32_t hash = 5381;
    int c;
    /* */
    while ((c = *str++))  //== while(*str != '\0'), mais il faut ajouter str++ a la fin
    {
        hash = ((hash << 5 )+hash) +c; // c'est le meme chose que hash*33 +c
    }
    hash=hash%taille;
    return hash;
}
