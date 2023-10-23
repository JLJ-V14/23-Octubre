#include "conversion_numeros.h"
#include "definiciones_globales.h"
#include "registrar_errores.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h> 


//Este subprograma se utiliza para 
//comprobar si el dato del csv leido
//es un numero o no. Ademas se 
//diferencia si el numero leido 
//puede tener decimales o no.

bool es_un_numero(const wchar_t* str, int permitir_decimal) {


	int numero_puntos = 0;

	printf("Entra comprobacion numero\n");
	for (int i = 0; str[i] != '\0'; i++) {
		printf("Iteracion numero %d\n", i);
		wprintf(L"%lc\n", str[i]);
		if (!iswdigit(str[i])) {
			printf("No es un digito\n");
			printf("%d\n", permitir_decimal);
			wprintf(L"%lc\n", str[i]);
			printf("%d\n", numero_puntos);
			if (permitir_decimal && str[i] == L'.' && numero_puntos == 0) {
				printf("Punto reconocido\n");
				numero_puntos++;
				continue;
			}
			return false; // No es un numero
		}
	}
	//Como mucho hay un punto decimal.
	if (numero_puntos > 1) {
		return false;
	}
	return true;
}

bool comprobar_porcentaje_bateria(const double porcentaje_bateria) {
	//Este subprograma se utiliza para
	//comprobar que el porcentaje de 
	//bateria se encuentra entre 0 y 1

	return ((porcentaje_bateria >= 0) && (porcentaje_bateria <= 1));
}

int verificar_numero_terminal(const wchar_t* numero_terminal_string, const int numero_fila) {
	//Este subprograma se utiliza
	//para verificar que el dato 
	//de terminal es correcto.

	//Se comprueba que el numero 
	//del terminal esté dentro del 
	//rango y que sea un dato numerico
	//no decimal.
	if (!es_un_numero(numero_terminal_string, DECIMAL_NO_INCLUIDO)) {
		char mensaje_error[512];
		snprintf(mensaje_error, sizeof(mensaje_error), "El numero de Terminal en la fila %d no es un numero natural",
			numero_fila);

		printf("%s\n", mensaje_error);
		registrar_error(mensaje_error, REGISTRO_ERRORES);
		return ERROR;
	}
	int num_terminal = 0;

	//Se convierte el numero en un numero entero.
	if (convertir_a_entero(numero_terminal_string, &num_terminal) == ERROR) {
		char mensaje_error[512];
		snprintf(mensaje_error, sizeof(mensaje_error), "El numero de terminal en la fila %d no"
			"se puede convertir a dato numerico\n", numero_fila);
		printf("%s\n", mensaje_error);
		registrar_error(mensaje_error, REGISTRO_ERRORES);
		return ERROR;
	}


	//Se comprueba que el numero de terminal esté entre 1 y 12.
	if ((num_terminal < 1) || (num_terminal > NUMERO_TERMINALES)) {
		char mensaje_error[512];
		snprintf(mensaje_error, sizeof(mensaje_error), "Error el numero de terminales"
			"ha de estar entre 1 y %d en el CSV de los vehiculos\n", NUMERO_TERMINALES);

		printf("%s\n", mensaje_error);
		registrar_error(mensaje_error, REGISTRO_ERRORES);
		return ERROR;
	}
	return EXITO;
}

bool  es_negativo(double numero) {
	//Este subprograma se utiliza
	//para comprobar si un numero
	//es negativo

	return numero < 0;
}
