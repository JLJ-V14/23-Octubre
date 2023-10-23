
#ifndef CONVERSION_NUMEROS_H
#define CONVERSION_NUMEROS_H

/* Include files */
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

	int  convertir_a_entero(wchar_t* str, int* Num);
	int  convertir_a_decimal(wchar_t* str, double* Num);

#ifdef __cplusplus
}
#endif

#endif