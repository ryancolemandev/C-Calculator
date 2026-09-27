#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct {
    const char *s;
} Parser;

static void skipSpaces(Parser *p)
{
    while (isspace((unsigned char)*p->s))
        p->s++;
}

static void error(const char *msg, Parser *p)
{
    printf(stderr, "Error: %s near \"%s\"\n", msg, p->s);
    exit(1);
}

static double expression(Parser *p);
static double term(Parser *p);
static double factor(Parser *p);

static double factor(Parser *p)
{
    double result;
    int negative = 0;

    skipSpaces(p);

    if (*p->s == '-' || *p->s == '+') {
        if (*p->s == '-')
            negative = 1;

        p->s++;
    }

    skipSpaces(p);

    if (*p->s == '(') {
        p->s++;

        result = expression(p);

        skipSpaces(p);

        if (*p->s != ')')
            error("expected ')'", p);

        p->s++;
    }
    else if (isdigit((unsigned char)*p->s) || *p->s == '.') {
        char *end;

        errno = 0;
        result = strtod(p->s, &end);

        if (end == p->s)
            error("invalid number", p);

        p->s = end;
    }
    else {
        error("expected a number or '('", p);
    }

    if (negative)
        result = -result;

    return result;
}

static double term(Parser *p)
{
    double result = factor(p);

    while (1) {
        skipSpaces(p);

        if (*p->s == '*') {
            p->s++;
            result = result * factor(p);
        }
        else if (*p->s == '/') {
            double number;

            p->s++;
            number = factor(p);

            if (number == 0)
                error("division by zero", p);

            result = result / number;
        }
        else {
            break;
        }
    }

    return result;
}

static double expression(Parser *p)
{
    double result = term(p);

    while (1) {
        skipSpaces(p);

        if (*p->s == '+') {
            p->s++;
            result = result + term(p);
        }
        else if (*p->s == '-') {
            p->s++;
            result = result - term(p);
        }
        else {
            break;
        }
    }

    return result;
}

int main(int argc, char **argv)
{
    Parser p;
    double result;

    if (argc != 2) {
        printf("Usage: %s \"expression\"\n", argv[0]);
        return 1;
    }

    p.s = argv[1];

    result = expression(&p);

    skipSpaces(&p);

    if (*p.s != '\0')
        error("unexpected characters", &p);

    printf("%.15g\n", result);

    return 0;
}
