/*
 * utn.h
 *
 *  Created on: 12 may. 2022
 *      Author: Franco
 */

#ifndef UTN_H_
#define UTN_H_

int getInt(int *pResultado);

int utn_getNumero(int *pResultado, char *mensaje, char *mensajeError, int minimo, int maximo, int reintentos);

int getFloat(float *pResultado);

int utn_getNumeroFlotante(float *pResultado, char *mensaje, char *mensajeError, float minimo, float maximo, int reintentos);

int getString(char *cadena, int len);

int getCadena(char* pResultado, int longitud);

int utn_getCadena(char* pResultado, int lenMin, int lenMax, char* mensaje, char* mensajeError, int reintentos);

int getNombre(char* pResultado, int longitud);

int utn_getNombre(char* pResultado, int longitudMin, int longitudMax, char* mensaje, char* mensajeError, int reintentos);

int esNumerica(char *cadena, int len);

int esFlotante(char *cadena);

int esCadena(char *cadena, int longitud);

int esNombre(char *cadena, int len);

void strEnMayuscula(char cadena[]);

void strEnMinuscula(char cadena[]);

void uppercaseInitial(char string[]);


#endif /* UTN_H_ */
