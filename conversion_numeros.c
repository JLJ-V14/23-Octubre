#include "definiciones_globales.h"
#include <stdio.h>
#include <wchar.h>

// En este archivo se incluyen los subprogramas 
// relacionados con convertir caracteres a numeros.

int convertir_a_entero(wchar_t* str, int* num) {
    // Este subprograma se utiliza para convertir un dato de tipo wchar
    // a una variable de tipo int.

    // Comprobación inicial.
    if (str == NULL) {
        return ERROR;
    }

    wchar_t* puntero_final;
    *num = wcstol(str, &puntero_final, 10);

    // Puntero_Final se utiliza para comprobar que la conversion fue exitosa.
    return *puntero_final == L'\0' ? EXITO : ERROR;
}

int convertir_a_decimal(wchar_t* str, double* num) {
    // Este subprograma se utiliza para convertir un dato de tipo wchar
    // a una variable de tipo double.

    // Comprobación inicial.
    if (str == NULL) {
        return ERROR;
    }

    wchar_t* puntero_final;
    wprintf(L"%ls\n", str);

    printf("%f\n", *num);

    *num = wcstod(str, &puntero_final);
    wprintf(L"%ls\n", str);
    wprintf(L"%ls\n", puntero_final);
    printf("%f\n", *num);

    // Puntero_Final se utiliza para comprobar que la conversion fue exitosa.
    printf("%f\n", *num);
    return *puntero_final == L'\0' ? EXITO : ERROR;
}
