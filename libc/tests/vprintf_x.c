#include <stdio.h>

#define vga_puts(s) (void) (s)

// s is assumed to be of size 9 and null initialized
static inline int vprintf_x(char *s, int d)
{
    const char dig[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

    unsigned int ud = (unsigned int) d;

    int bytes = 0;
    s[0] = '0';

    char *p = s;
    if(ud == 0) bytes++;

    while(ud != 0)
    {
        *(p++) = dig[ud & 0xf];
        ud >>= 4;
    }

    size_t sz = p - s;
    bytes += sz;

    for(size_t i = 0; i < sz / 2; i++)
    {
        char tmp = s[i];
        s[i] = s[sz - i - 1];
        s[sz - i - 1] = tmp;
    }

    return bytes;
}

int main()
{
    int abc = 0xdeadbeef;
    int printf_ret = printf("%x\n", abc)-1;

    char s[9] = {0};
    int custom_ret = vprintf_x(s, abc);
    printf("%s\n", s);

    printf("\n");

    printf("%d %d\n", printf_ret, custom_ret);
}

