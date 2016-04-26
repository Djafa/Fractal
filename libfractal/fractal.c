#include <stdlib.h>
#include <string.h>
#include "fractal.h"

struct fractal *fractal_new(const char *name, int width, int height, double a, double b)
{
	struct fractal* f = (struct fractal*)malloc(sizeof(struct fractal));
	char *copy  = (char*)malloc(sizeof(char)*(strlen(name)+1));
	if(copy == NULL)
		return NULL;
	*copy = *name;
	f->name = copy;
	f->width = width;
	f->height = height;
	f->a = a;
	f->b = b;
    return f;
}

void fractal_free(struct fractal *f)
{
    free((void*)f);
}

const char *fractal_get_name(const struct fractal *f)
{
    return f->name;
}

int fractal_get_value(const struct fractal *f, int x, int y)
{
    
}

void fractal_set_value(struct fractal *f, int x, int y, int val)
{
    /* TODO */
}

int fractal_get_width(const struct fractal *f)
{
    /* TODO */
    return 0;
}

int fractal_get_height(const struct fractal *f)
{
    /* TODO */
    return 0;
}

double fractal_get_a(const struct fractal *f)
{
    /* TODO */
    return 0;
}

double fractal_get_b(const struct fractal *f)
{
    /* TODO */
    return 0;
}
