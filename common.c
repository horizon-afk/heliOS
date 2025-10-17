#include "common.h"

void putchar(char ch);

static void print_string(const char *s)
{
    if (!s)
        s = "(null)";
    while (*s)
        putchar(*s++); // sends each char to the putchar_kernel, so you can see it on screen
}

static void print_decimal(int v)
{
    if (v == 0)
    {
        putchar('0');
        return;
    }

    unsigned int mag;
    if (v < 0)
    {
        putchar('-');
        mag = (unsigned int)(-v);
    }
    else
    {
        mag = (unsigned int)v;
    }

    char buf[16];
    int i = 0;
    while (mag > 0)
    {
        buf[i++] = '0' + (mag % 10);
        mag /= 10;
    }
    while (i-- > 0)
        putchar(buf[i]);
}

static void print_hex(unsigned int v)
{
    const char *digits = "0123456789abcdef";
    if (v == 0)
    {
        putchar('0');
        return;
    }
    char buf[16];
    int i = 0;
    while (v > 0)
    {
        buf[i++] = digits[v & 0xF];
        v >>= 4;
    }
    while (i-- > 0)
        putchar(buf[i]);
}

void printf(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    for (; *fmt; ++fmt)
    {
        if (*fmt != '%')
        {
            putchar(*fmt);
            continue;
        }
        ++fmt;
        switch (*fmt)
        {
        case '%':
            putchar('%');
            break;
        case 'c':
            putchar((char)va_arg(ap, int));
            break;
        case 's':
            print_string(va_arg(ap, const char *));
            break;
        case 'd':
            print_decimal(va_arg(ap, int));
            break;
        case 'x':
            print_hex(va_arg(ap, unsigned int));
            break;
        default:
            putchar('%');
            putchar(*fmt);
            break;
        }
    }

    va_end(ap);
}

