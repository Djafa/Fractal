#include <stdlib.h> 
#include <stdio.h>
#include <CUnit/Basic.h>
#include "fractal.h"
void getName(void) {
	const char *name = projet;
	int width = 4;
	int height = 2;
	double a = 0.5;
	double b = 0.4;
	struct fractal *f = fractal_new(name, width, height, a, b);
	CU_ASSERT_STRING_EQUAL(fractal_get_name(f), name);
}

void getValue(void) {
	const char *name = projet;
	int width = 4;
	int height = 2;
	double a = 0.5;
	double b = 0.4;
	struct fractal *f = fractal_new(name, width, height, a, b);
	CU_ASSERT_EQUAL(fractal_get_value(f, x, y), value);
} 

void setValue(void) {
	const char *name = projet;
	int width = 4;
	int height = 2;
	double a = 0.5;
	double b = 0.4;
	struct fractal *f = fractal_new(name, width, height, a, b);
	fractal_set_value(f, x, y, val);
	CU_ASSERT_EQUAL(fractal_get_value(f, x, y), value);
}

void getWidth(void) {
	const char *name = projet;
	int width = 4;
	int height = 2;
	double a = 0.5;
	double b = 0.4;
	struct fractal *f = fractal_new(name, width, height, a, b);
	CU_ASSERT_EQUAL(fractal_get_width(f), width);
}

void getHeight(void) {
	const char *name = projet;
	int width = 4;
	int height = 2;
	double a = 0.5;
	double b = 0.4;
	struct fractal *f = fractal_new(name, width, height, a, b);
	CU_ASSERT_EQUAL(fractal_get_height(f), height);
}

void getA(void) {
	const char *name = projet;
	int width = 4;
	int height = 2;
	double a = 0.5;
	double b = 0.4;
	struct fractal *f = fractal_new(name, width, height, a, b);
	CU_ASSERT_DOUBLE_EQUAL(fractal_get_a(f), a, 0);
}

void getA(void) {
	const char *name = projet;
	int width = 4;
	int height = 2;
	double a = 0.5;
	double b = 0.4;
	struct fractal *f = fractal_new(name, width, height, a, b);
	CU_ASSERT_DOUBLE_EQUAL(fractal_get_b(f), b, 0);
}

int main(int argc, const char *argv[]) {
	CU_pSuite pSuite = NULL;
	/* initialisation de la suite*/
	if(CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* création de la suite */
	pSuite = CU_add_suite("Suite",NULL,NULL);
	if(NULL == pSuite){
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Ajout à la suite */
	if(NULL == CU_add_test(pSuite, "GetName", getName) ||
	   NULL == CU_add_test(pSuite, "GetValue", getValue) ||
	   NULL == CU_add_test(pSuite, "SetValue", setValue) ||
	   NULL == CU_add_test(pSuite, "GetWidth", getWidth) ||
	   NULL == CU_add_test(pSuite, "GetHeight", getHeight) ||
	   NULL == CU_add_test(pSuite, "GetA", getA) ||
	   NULL == CU_add_test(pSuite, "GetB", getB)
			) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Lancement des tests */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
}
