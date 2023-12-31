
#include "conversion_numeros.h"
#include "definiciones_globales.h"
#include "operaciones_csv.h"
#include "operaciones_fecha.h"
#include "operaciones_string.h"
#include "registrar_errores.h"
#include "tipos_optimizacion.h"
#include "validaciones.h"
#include <stdio.h>

#define MINIMO_FILAS_CSV_VEHICULOS    1
#define NUMERO_COLUMNAS_CSV_VEHICULOS 16

//Este subprograma se utiliza para
//comprobar que las dimensiones
//del CSV de los vehiculos son
//correctos.


static int comprobar_dimensiones_csv_vehiculos(datos_csv_t* datos_vehiculos) {


	if (comprobar_dimensiones_csv_variable(datos_vehiculos, MINIMO_FILAS_CSV_VEHICULOS,
		NUMERO_COLUMNAS_CSV_VEHICULOS, "Vehiculos") == ERROR) {
		printf("El CSV de los vehiculos no tienen dimensiones correctas\n");
		registrar_error("El CSV de los vehiculos no tienen dimensiones correctas", REGISTRO_ERRORES);
		return ERROR;
	}
	return EXITO;
}

//Este subprograma se utiliza para 
//verificar que los encabezados del 
//CSV que contiene la informacion
//de los vehiculos es correcta.s



int comprobar_encabezados_vehiculos(datos_csv_t* datos_vehiculos) {


	const wchar_t* valores_aceptables[] = { L"Terminal",L"Modo Carga",L"Capacidad Bateria",
										   L"Bateria Inicial",L"Bateria Final",L"Maxima Potencia",
										   L"A�o Inicial Carga",L"Mes Inicial Carga",L"Dia Inicial Carga",
										   L"Hora Inicial Carga",L"Minuto Inicial Carga",L"A�o Final Carga",
										   L"Mes Final Carga",L"Dia Final Carga",L"Hora Final Carga",
										   L"Minuto Final Carga" };
	const int numero_encabezados = sizeof(valores_aceptables) / sizeof(valores_aceptables[0]);

	if (verificar_encabezado_csv(datos_vehiculos, valores_aceptables, numero_encabezados,
		"Vehiculos") == ERROR) {
		printf("Los encabezados del CSV de los vehiculos son incorrectos");
		registrar_error("Los encabezados del CSV de los vehiculos son incorrectos", REGISTRO_ERRORES);
		return ERROR;
	}


	return EXITO;
}
//Este subprograma se utiliza
//para verificar que los modos
//de carga de los Vehiculos 
//estan escritos correctamente.

static int verificar_modo_carga(const wchar_t* modo_carga, const int numero_fila) {


	if (strings_iguales(modo_carga, L"Rapida") || strings_iguales(modo_carga, L"Normal")) {
		return EXITO;
	}
	wchar_t* mensaje_error[512];
	swprintf(mensaje_error, sizeof(mensaje_error) / sizeof(wchar_t), L"Error el modo de carga de los vehiculos debe ser Normal o Rapida y es %ls\n", modo_carga);
	wprintf(L"%ls", mensaje_error);

	registrar_error(mensaje_error, REGISTRO_ERRORES);
	return ERROR;
}

//Este subprograma se utiliza para verificar los
//datos relacionados con la bateria y la maxima
//potencia que puede intercambiar el vehiculo.

static int verificar_datos_bateria_vehiculo(datos_csv_vehiculos_t* datos_csv, const int numero_fila) {

	//Obtengo el puntero que apunta a las posiciones de memoria donde se encuentra la informacion
	//de los vehiculos
	datos_csv_t* informacion_vehiculos = &(datos_csv->informacion_vehiculos);

	//Cargo las columna donde se encuentra la informacion
	int columna_csv_vehiculos_capacidad = datos_csv->posiciones_informacion_vehiculos.columna_capacidad_bateria;
	int columna_csv_vehiculos_max_potencia = datos_csv->posiciones_informacion_vehiculos.columna_maxima_potencia;
	int columna_csv_vehiculos_bat_inicial = datos_csv->posiciones_informacion_vehiculos.columna_porcentaje_bateria_inicial;
	int columna_csv_vehiculos_bat_deseada = datos_csv->posiciones_informacion_vehiculos.columna_porcentaje_bateria_deseada;

	wchar_t* capacidad_bateria = informacion_vehiculos->datos[numero_fila][columna_csv_vehiculos_capacidad];
	wchar_t* maxima_potencia = informacion_vehiculos->datos[numero_fila][columna_csv_vehiculos_max_potencia];
	wchar_t* bateria_inicial = informacion_vehiculos->datos[numero_fila][columna_csv_vehiculos_bat_inicial];
	wchar_t* bateria_deseada = informacion_vehiculos->datos[numero_fila][columna_csv_vehiculos_bat_deseada];

	if (!es_un_numero(capacidad_bateria, DECIMAL_INCLUIDO)) {
		char mensaje_error[512];
		snprintf(mensaje_error, sizeof(mensaje_error), "Error la bateria del vehiculo de la fila %d del CSV de los vehiculos no es un numero",
			numero_fila);
		printf("%s\n", mensaje_error);
		registrar_error(mensaje_error, REGISTRO_ERRORES);
		return ERROR;
	}

	if (!es_un_numero(maxima_potencia, DECIMAL_INCLUIDO)) {
		char mensaje_error[512];
		snprintf(mensaje_error, sizeof(mensaje_error), "Error la maxima potencia que puede intercambiar el vehiculo de la fila %d del CSV de los vehiculos no es valido\n", numero_fila);
		printf("%s\n", mensaje_error);
		registrar_error(mensaje_error, REGISTRO_ERRORES);
		return ERROR;
	}
	if (!es_un_numero(bateria_inicial, DECIMAL_INCLUIDO)) {
		char mensaje_error[512];
		snprintf(mensaje_error, sizeof(mensaje_error),
			"Error el porcentaje de bateria inicial del vehiculo de la fila %d del CSV de los vehiculos no es un numero valido", numero_fila);
		printf("%s\n", mensaje_error);
		registrar_error(mensaje_error, REGISTRO_ERRORES);
		return ERROR;
	}
	if (!es_un_numero(bateria_deseada, DECIMAL_INCLUIDO)) {
		char mensaje_error[512];
		snprintf(mensaje_error, sizeof(mensaje_error),
			"Error el porcentaje de bateria deseada del vehiculo de la fila %d del CSV de los vehiculos no es un numero valido", numero_fila);
		printf("%s\n", mensaje_error);
		registrar_error(mensaje_error, REGISTRO_ERRORES);
		return ERROR;
	}

	double capacidad_bateria_num = 0;
	double maxima_potencia_num = 0;
	double bateria_inicial_num = 0;
	double bateria_deseada_num = 0;

	if ((convertir_a_decimal(capacidad_bateria, &capacidad_bateria_num) == ERROR) ||
		(convertir_a_decimal(maxima_potencia, &maxima_potencia_num) == ERROR) ||
		(convertir_a_decimal(bateria_inicial, &bateria_inicial_num) == ERROR) ||
		(convertir_a_decimal(bateria_deseada, &bateria_deseada_num) == ERROR)) {


		printf("No se ha podido convertir a dato numerico la informacion de la bateria\n");
		registrar_error("No se ha podido convertir a dato numerico la informacion de la bateria\n", REGISTRO_ERRORES);
		return ERROR;
	}

	if (!comprobar_porcentaje_bateria(bateria_inicial_num)) {
		char mensaje_error[512];
		snprintf(mensaje_error, sizeof(mensaje_error), "Error en la fila %d,el porcentaje de bateria inicial ha de estar entre 0 y 1\n", numero_fila);
		printf("%s\n", mensaje_error);
		registrar_error(mensaje_error, REGISTRO_ERRORES);
		return ERROR;
	}

	if (!comprobar_porcentaje_bateria(bateria_deseada_num)) {
		char mensaje_error[512];
		snprintf(mensaje_error, sizeof(mensaje_error), "Error en la fila %d el porcentaje de bateria ha de estar entre 0 y 1\n", numero_fila);
		printf("%s", mensaje_error);
		registrar_error(mensaje_error, REGISTRO_ERRORES);
		return ERROR;
	}

	if (es_negativo(capacidad_bateria_num)) {
		char mensaje_error[512];
		snprintf(mensaje_error, sizeof(mensaje_error), "Error en la fila %d del CSV de los vehiculos la capacidad de la bateria no puede ser negativa\n", numero_fila);
		printf("%s", mensaje_error);
		registrar_error(mensaje_error, REGISTRO_ERRORES);
		return ERROR;
	}

	if (es_negativo(maxima_potencia_num)) {
		char mensaje_error[512];
		snprintf(mensaje_error, sizeof(mensaje_error), "Error en la fila %d del CSV de los vehiculos, la potencia maxima del vehiculo no puede ser negativa\n",
			numero_fila);
		registrar_error(mensaje_error, REGISTRO_ERRORES);
		return ERROR;
	}
	return EXITO;

}

//Este subprograma se utiliza para
//comprobar que los datos de los 
//vehiculos son correctos.


static int comprobar_datos_csv_vehiculos(datos_csv_vehiculos_t* datos_vehiculos, datos_csv_algoritmo_t* datos_algoritmo) {

	//Cargo el puntero que apunta a la posicion de memoria donde se encuentra la informacion de los
	//vehiculos y el algoritmo
	datos_csv_t* informacion_vehiculos = &(datos_vehiculos->informacion_vehiculos);
	datos_csv_t* informacion_algoritmo = &(datos_algoritmo->informacion_algoritmo);

	//Cargo el numero de filas que hay en el csv
	int numero_filas = informacion_vehiculos->filas;

	//Se carga las columnas donde se encuentra la diferente informacion en el csv.
	int columna_vehiculos_terminal = datos_vehiculos->posiciones_informacion_vehiculos.columna_terminales;
	int columna_modo_carga = datos_vehiculos->posiciones_informacion_vehiculos.columna_modo_carga;

	//Se van comprobando los datos de 
	//la fila del CSV, para comprobar
	//que son correctos.

	for (int numero_fila = 1; numero_fila < numero_filas; numero_fila++) {

		if (verificar_numero_terminal(informacion_vehiculos->datos[numero_fila][columna_vehiculos_terminal], numero_fila) == ERROR) {

			char mensaje_error[512];
			snprintf(mensaje_error, sizeof(mensaje_error), "El campo del numero del terminal en la fila %d es incorrecto", numero_fila);
			printf("%s", mensaje_error);
			registrar_error(mensaje_error, REGISTRO_ERRORES);
			return ERROR;
		}


		if (verificar_modo_carga(informacion_vehiculos->datos[numero_fila][columna_modo_carga], numero_fila) == ERROR) {
			char mensaje_error[512];
			snprintf(mensaje_error, sizeof(mensaje_error), "El Modo de carga en la fila % d del CSV de los vehiculos es incorrecto\n", numero_fila);
			printf("%s", mensaje_error);
			registrar_error(mensaje_error, REGISTRO_ERRORES);
			return ERROR;
		}

		if (verificar_datos_bateria_vehiculo(datos_vehiculos, numero_fila) == ERROR) {
			char mensaje_error[512];
			snprintf(mensaje_error, sizeof(mensaje_error), "Los datos de la bateria del vehiculo en la fila %d son incorrectos",
				numero_fila);
			printf(mensaje_error);
			registrar_error(mensaje_error, REGISTRO_ERRORES);
			return ERROR;
		}

		if (verificar_fecha_carga(informacion_vehiculos, datos_algoritmo, numero_fila) == ERROR) {
			char mensaje_error[512];
			snprintf(mensaje_error, sizeof(mensaje_error), "Los datos de fecha del vehiculo en la fila %d son incorrectos", numero_fila);
			printf(mensaje_error);
			registrar_error(mensaje_error, REGISTRO_ERRORES);
			return ERROR;
		}


	}
	return EXITO;
}

int verificar_datos_vehiculos(datos_csv_vehiculos_t* datos_vehiculos, datos_csv_algoritmo_t* datos_algoritmo) {
	//Este subprograma se utiliza para
	//comprobar que el CSV 
	//que contiene los datos de los 
	//vehiculos es correcto->

	if (comprobar_dimensiones_csv_vehiculos(datos_vehiculos) == ERROR) {
		return ERROR;
	}
	if (comprobar_encabezados_vehiculos(datos_vehiculos) == ERROR) {
		return ERROR;
	}
	if (comprobar_datos_csv_vehiculos(datos_vehiculos, datos_algoritmo) == ERROR) {
		return ERROR;
	}

	return EXITO;

}