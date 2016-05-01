#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./libfractal/fractal.h"

int main()
{
    //Test des calculs
	const char *name = "projet";
	struct fractal *f = fractal_new(name, 4 , 4, 2, 1);
	int w = fractal_get_width(f);
	int h = fractal_get_height(f);

	//Calcule de chaque pixel
	for(int x =0; x<w; x++)
	{
		for(int y =0; y<h ;y++)
		{
			fractal_compute_value(f,x,y);
		}
	}
	//On écrit la fractale
	write_bitmap_sdl(f, fractal_get_name(f));
}
