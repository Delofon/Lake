#if 0

gcc -O2 -Wall -Wextra -o atoi_test atoi_test.c ../stdlib.c
chmod u+x atoi_test
./atoi_test

exit

#endif

#include <stdio.h>

#include "../stdlib.h"

int main()
{
    char s[64];
    fgets(s, sizeof(s), stdin);

    printf("%d\n", atoi(s));

    return 0;
}

