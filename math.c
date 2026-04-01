#include "common.h"

// ── recursive descent parser ───────────────────────────────
const char *expr_ptr;

int parse_expr(void);

int parse_number(void)
{
    int sign = 1, n = 0;
    if (*expr_ptr == '-')
    {
        sign = -1;
        expr_ptr++;
    }
    while (*expr_ptr >= '0' && *expr_ptr <= '9')
        n = n * 10 + (*expr_ptr++ - '0');
    return sign * n;
}

int parse_factor(void)
{
    if (*expr_ptr == '(')
    {
        expr_ptr++;
        int val = parse_expr();
        if (*expr_ptr == ')')
            expr_ptr++;
        return val;
    }
    return parse_number();
}

int parse_term(void)
{
    int val = parse_factor();
    while (*expr_ptr == '*' || *expr_ptr == '/')
    {
        char op = *expr_ptr++;
        int rhs = parse_factor();
        if (op == '*')
            val *= rhs;
        else if (rhs != 0)
            val /= rhs;
    }
    return val;
}

int parse_expr(void)
{
    int val = parse_term();
    while (*expr_ptr == '+' || *expr_ptr == '-')
    {
        char op = *expr_ptr++;
        int rhs = parse_term();
        if (op == '+')
            val += rhs;
        else
            val -= rhs;
    }
    return val;
}

int eval_expr(const char *expr)
{
    expr_ptr = expr;
    return parse_expr();
}

// ── expression detector ────────────────────────────────────
int is_expr(const char *s)
{
    for (int i = 0; s[i]; i++)
    {
        char c = s[i];
        if (c == '+' || c == '*' || c == '/')
            return 1;
        // '-' only counts as operator if not the first char (not a negative number)
        if (c == '-' && i > 0)
            return 1;
    }
    return 0;
}