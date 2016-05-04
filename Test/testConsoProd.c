#include <stdlib.h> 
#include <stdio.h>
#include <CUnit/Basic.h>
#include "../libfractal/fractal.h"
#include "../main.h"
#include "../myStack.h"

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
	if(NULL == CU_add_test(pSuite, "calculFractal", calculFractal)
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
