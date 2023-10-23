#pragma once
/*En este archivo se definen las diferentes variables que se
  van a utilizar durante todo el codigo*/

#pragma once
#include <wchar.h>
#include <wctype.h>




  //Tipo que sirve para almacenar la posicion de una fecha en los
  //csvs.
typedef struct {
    int columna_anyo;
    int columna_mes;
    int columna_dia;
    int columna_hora;
    int columna_minuto;
}ubicacion_fecha_t;

//Tipo que sirve para definir el tipo de variable donde se almacenan los datos del CSV.
typedef struct {
    wchar_t*** datos;
    int filas;
    int columnas;
} datos_csv_t;


//Defino un tipo para almacenar los diferentes csvs de entrada.
typedef struct {
    const char* nombre_archivo;
    datos_csv_t* datos;
} entrada_csv;

/*Se definen una serie de estructuras para almacenar
  la posicion de la informaicon en los diferentes csv
  es decir donde se encuentra la informacion      */
typedef struct {
    int columna_terminales;
    int columna_modo_carga;
    int columna_capacidad_bateria;
    int columna_porcentaje_bateria_inicial;
    int columna_porcentaje_bateria_deseada;
    int columna_maxima_potencia;
    ubicacion_fecha_t ubicacion_fecha_inicial_vehiculo;
    ubicacion_fecha_t ubicacion_fecha_final_vehiculo;
}ubicacion_csv_vehiculos_t;

typedef struct {
    int fila_encabezados;
    int fila_informacion;
    ubicacion_fecha_t ubicacion_fecha_inicial_algoritmo;
    ubicacion_fecha_t ubicacion_fecha_final_algoritmo;
    int resolucion_minutos;
}ubicacion_csv_algoritmo_t;

typedef struct {
    int fila_encabezados;
    int columna_terminal;
    int columna_capacidad_bateria;
    int columna_porcentaje_bateria_inicial;
    int columna_porcentaje_bateria_deseada;
    int columna_potencia_maxima_bateria;
    ubicacion_fecha_t ubicacion_fecha_inicial_baterias;
    ubicacion_fecha_t ubicacion_fecha_final_baterias;
    ubicacion_fecha_t ubicacion_fecha_objetivo_baterias;
    int columna_consideracion_objetivo;
}ubicacion_csv_baterias_t;

typedef struct {
    int fila_encabezados;
    ubicacion_fecha_t ubicacion_fecha_precios;
    int columna_precio;
}ubicacion_csv_precios_t;


typedef struct {
    int fila_encabezados;
    int columna_numero_terminal;
    int columna_fase;
}ubicacion_csv_terminales_t;

typedef struct {
    int fila_encabezados;
    int fila_valores;
    int columna_max_potencia_sistema;
    int columna_max_potencia_terminal_1;
    int columna_max_potencia_terminal_2;
    int columna_max_potencia_terminal_3;
    int columna_max_potencia_terminal_4;
    int columna_max_potencia_terminal_5;
    int columna_max_potencia_terminal_6;
    int columna_max_potencia_terminal_7;
    int columna_max_potencia_terminal_8;
    int columna_max_potencia_terminal_9;
    int columna_max_potencia_terminal_10;
    int columna_max_potencia_terminal_11;
    int columna_max_potencia_terminal_12;
}ubicacion_csv_restricciones_t;

typedef struct {
    datos_csv_t               informacion_algoritmo;
    ubicacion_csv_algoritmo_t posiciones_informacion_algoritmo;
}datos_csv_algoritmo_t;

typedef struct {
    datos_csv_t               informacion_vehiculos;
    ubicacion_csv_vehiculos_t posiciones_informacion_vehiculos;
}datos_csv_vehiculos_t;

typedef struct {
    datos_csv_t               informacion_baterias;
    ubicacion_csv_baterias_t  posiciones_informacion_baterias;
}datos_csv_baterias_t;

typedef struct {
    datos_csv_t               informacion_restricciones;
    ubicacion_csv_restricciones_t posiciones_informacion_restricciones;
}datos_csv_restricciones_t;

typedef struct {
    datos_csv_t                informacion_terminales;
    ubicacion_csv_terminales_t posiciones_informacion_terminales;
}datos_csv_terminales_t;


typedef struct {
    datos_csv_t                    informacion_precio;
    ubicacion_csv_precios_t        posiciones_informacion_precio;
}datos_csv_precio_t;



typedef struct {
    datos_csv_algoritmo_t       datos_algoritmo;
    datos_csv_vehiculos_t       datos_vehiculos;
    datos_csv_baterias_t        datos_baterias;
    datos_csv_restricciones_t   datos_restricciones;
    datos_csv_terminales_t      datos_terminales;
    datos_csv_precio_t          datos_precio_compra;
    datos_csv_precio_t          datos_precio_venta;

}informacion_entrada_t;


