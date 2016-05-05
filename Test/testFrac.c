#include <stdlib.h> 
#include <stdio.h>
#include <CUnit/Basic.h>
#include "../libfractal/fractal.h"
#include "../main.h"
#include "../stack/myStack.h"

void getName(void) {
	const char *name = "projet";
	int width = 4;
	int height = 2;
	double a = 0.5;
	double b = 0.4;
	struct fractal *f = fractal_new(name, width, height, a, b);
	CU_ASSERT_STRING_EQUAL(fractal_get_name(f), name);
	fractal_free(f);
}

void setAndGetValue(void) {
	const char *name = "projet";
	int width = 4;
	int height = 2;
	double a = 0.5;
	double b = 0.4;
	struct fractal *f = fractal_new(name, width, height, a, b);
	int x = 1;
	int y = 2;
	int value = 42;
	fractal_set_value(f, x, y, value);
	CU_ASSERT_EQUAL(fractal_get_value(f, x, y), value);
	fractal_free(f);
}

void getWidth(void) {
	const char *name = "projet";
	int width = 4;
	int height = 2;
	double a = 0.5;
	double b = 0.4;
	struct fractal *f = fractal_new(name, width, height, a, b);
	CU_ASSERT_EQUAL(fractal_get_width(f), width);
	fractal_free(f);
}

void getHeight(void) {
	const char *name = "projet";
	int width = 4;
	int height = 2;
	double a = 0.5;
	double b = 0.4;
	struct fractal *f = fractal_new(name, width, height, a, b);
	CU_ASSERT_EQUAL(fractal_get_height(f), height);
	fractal_free(f);
}

void getA(void) {
	const char *name = "projet";
	int width = 4;
	int height = 2;
	double a = 0.5;
	double b = 0.4;
	struct fractal *f = fractal_new(name, width, height, a, b);
	CU_ASSERT_DOUBLE_EQUAL(fractal_get_a(f), a, 0);
	fractal_free(f);
}

void getB(void) {
	const char *name = "projet";
	int width = 4;
	int height = 2;
	double a = 0.5;
	double b = 0.4;
	struct fractal *f = fractal_new(name, width, height, a, b);
	CU_ASSERT_DOUBLE_EQUAL(fractal_get_b(f), b, 0);
	fractal_free(f);
}

void calculFractal(void) {
	const char *name = "projet";
	int width = 4;
	int height = 2;
	double a = 0.5;
	double b = 0.4;
	struct fractal *f = fractal_new(name, width, height, a, b);
	CU_ASSERT_DOUBLE_EQUAL(calculDeFractal(f), 2.0, 0);
	fractal_free(f);
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
	   NULL == CU_add_test(pSuite, "SetAndGetValue", setAndGetValue) ||
	   NULL == CU_add_test(pSuite, "GetWidth", getWidth) ||
	   NULL == CU_add_test(pSuite, "GetHeight", getHeight) ||
	   NULL == CU_add_test(pSuite, "GetA", getA) ||
	   NULL == CU_add_test(pSuite, "GetB", getB) ||
	   NULL == CU_add_test(pSuite, "calculFractal", calculFractal))
	   {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Lancement des tests */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
}
