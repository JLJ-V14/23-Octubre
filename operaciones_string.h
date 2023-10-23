#pragma once

#ifndef OPERACIONES_STRING_H
#define OPERACIONES_STRING_H

#include <stdbool.h>
#include <wchar.h>
/* Include files */


#ifdef __cplusplus
extern "C" {
#endif

	bool strings_iguales(const wchar_t* String_1, const wchar_t* String_2);

#ifdef __cplusplus
}
#endif

#endif