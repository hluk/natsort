#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define BATCH_SIZE 1024

int natural_compare(const void *a, const void *b)
{
    const char *aa, *bb;
    int num1, num2;

    for( aa = *(const char**)a, bb = *(const char**)b; *aa && *bb; ++aa, ++bb ) {
        if ( isdigit(*aa) && isdigit(*bb) ) {
            sscanf(aa, "%d", &num1);
            sscanf(bb, "%d", &num2);
            if (num1 != num2) {
                return num1 - num2;
            }
            while ( *(++aa) && isdigit(*aa) );
            while ( *(++bb) && isdigit(*bb) );
            --aa; --bb;
        } else if (*aa != *bb) {
            return *aa - *bb;
        }
    }

    return *aa - *bb;
}

int main(int argc, const char *argv[])
{
    const char **list = 0;
    const char *item;
    int len = 0, i = 0;
    char *buffer;

    if (argc > 1) {
        /* read items as parameters */
        len = argc-1;
        list = malloc( sizeof(char *) * len );
        for ( ; (i+1)<argc; ++i) {
            list[i] = argv[i+1];
        }
    } else {
        /* read items from stdin */
        buffer = (char *) malloc(BUFFER_SIZE);
        if (!buffer)
            return 1;
        for ( ; fgets(buffer, BUFFER_SIZE, stdin); ++i ) {
            if (i >= len) {
                len += BATCH_SIZE;
                list = realloc( list, sizeof(char *) * len );
                if (!list)
                    return 1;
            }
            list[i] = buffer;
            buffer = (char *) malloc(BUFFER_SIZE);
            if (!buffer)
                return 1;
        }
    }

    /* no items */
    if (i == 0)
        return 0;

    if (i < len) {
        list[i] = 0;
    }

    qsort(list, i, sizeof(char *), natural_compare);

    for(i = 0; i<len; ++i) {
        item = list[i];
        if (item) {
            printf(item);
            if (argc > 1)
                printf("\n");
        } else {
            break;
        }
    }

    return 0;
}

