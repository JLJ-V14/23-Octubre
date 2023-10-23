
#include <stdio.h>
#include <wchar.h>

#ifndef FUNCIONES_PLATAFORMA_DEPENDIENTE_H
#define FUNCIONES_PLATAFORMA_DEPENDIENTE_H

#ifdef __cplusplus
extern "C" {
#endif
	const char* obtener_tiempo_string(time_t* tiempo);
	wchar_t* wcstok_seguro(wchar_t* str, const wchar_t* delimitador, wchar_t** token);
	wchar_t* wcsdup_plataforma(const wchar_t* src);
	int      abrir_archivo(const char* nombre_archivo, const char* modo, FILE** archivo);
	void     imprimir_error(int codigo_error);
#ifdef __cplusplus
}
#endif

#endif