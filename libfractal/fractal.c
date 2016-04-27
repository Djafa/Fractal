#include <stdlib.h>
#include <string.h>
#include "fractal.h"

struct fractal *fractal_new(const char *name, int width, int height, double a, double b)
{
	struct fractal* f = (struct fractal*)malloc(sizeof(struct fractal));
	if(f == NULL)
		return NULL;
	char *copy  = (char*)malloc(sizeof(char)*(strlen(name)+1));
	if(copy == NULL)
		return NULL;
	strcpy(copy, name);
	//On set les valeurs
	f->name = copy;
	f->width = width;
	f->height = height;
	f->a = a;
	f->b = b;
	f->pixl = (int*)malloc(sizeof(int)*((width*height)-1));
	if(f->pixl == NULL)
		return NULL;
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
    return *(f->pixl+x*f->width+y);
}

void fractal_set_value(struct fractal *f, int x, int y, int val)
{
    *(f->pixl+x*f->width+y) = val;
}

int fractal_get_width(const struct fractal *f)
{
    return f->width;
}

int fractal_get_height(const struct fractal *f)
{
    return f->height;
}

double fractal_get_a(const struct fractal *f)
{
    return f->a;
}

double fractal_get_b(const struct fractal *f)
{
    return f->b;
}
