/*
 * utn.c
 *
 *  Created on: 12 may. 2022
 *      Author: Franco
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"

#define VACIO 0
#define LLENO 1

#define ACTIVO 1
#define INACTIVO 0


int getInt(int *pResultado)
{
	int retorno = -1;
	char bufferString[50];
	if(pResultado != NULL && getString(bufferString, sizeof(bufferString)) == 0 && esNumerica(bufferString, sizeof(bufferString)))
	{
		retorno = 0;
		*pResultado = atoi(bufferString);
	}
	return retorno;
}


int utn_getNumero(int *pResultado, char *mensaje, char *mensajeError, int minimo, int maximo, int reintentos)
{
	int retorno = -1;
	int bufferInt;
	do
	{
		printf("%s", mensaje);
		if (getInt(&bufferInt) == 0 && bufferInt >= minimo && bufferInt <= maximo)
		{
			retorno = 0;
			*pResultado = bufferInt;
			break;
		}
		printf("%s", mensajeError);
		reintentos--;
	}while(reintentos >= 0);

	return retorno;
}

int getFloat(float *pResultado)
{
	int retorno = -1;
	char buffer[64];

	if (pResultado != NULL)
	{
		if (getString(buffer, sizeof(buffer)) == 0 && esFlotante(buffer))
		{
			*pResultado = atof(buffer);
			retorno = 0;
		}
	}
	return retorno;
}

int utn_getNumeroFlotante(float *pResultado, char *mensaje, char *mensajeError, float minimo, float maximo, int reintentos)
{
	int retorno = -1;
	float bufferFloat;
	while (reintentos >= 0)
	{
		reintentos--;
		printf("%s", mensaje);
		if (getFloat(&bufferFloat) == 0)
		{
			if (bufferFloat >= minimo && bufferFloat <= maximo)
			{
				*pResultado = bufferFloat;
				retorno = 0;
				break;
			}
		}
		printf("%s", mensajeError);
	}
	return retorno;
}

int getString(char *cadena, int len)
{
	int retorno = -1;
	char bufferString[4096];

	if (cadena != NULL && len > 0)
	{
		fflush(stdin);
		if (fgets(bufferString, sizeof(bufferString), stdin) != NULL)
		{
			if (bufferString[strnlen(bufferString, sizeof(bufferString)) - 1] == '\n')
			{
				bufferString[strnlen(bufferString, sizeof(bufferString)) - 1] = '\0';
			}
			if (strnlen(bufferString, sizeof(bufferString)) <= len)
			{
				strncpy(cadena, bufferString, len);
				retorno = 0;
			}
		}
	}
	return retorno;
}

int getCadena(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(getString(buffer, sizeof(buffer)) == 0 && esCadena(buffer, sizeof(buffer)) && strnlen(buffer, sizeof(buffer)) < longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}

int utn_getCadena(char* pResultado, int lenMin, int lenMax, char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while (reintentos >= 0)
	{
		reintentos--;
		printf("%s", mensaje);
		if(getCadena(bufferString,sizeof(bufferString)) == 0 && strnlen(bufferString,sizeof(bufferString)) < lenMax && strnlen(bufferString, sizeof(bufferString)) > lenMin)
		{
			strncpy(pResultado, bufferString, lenMax);
			retorno = 0;
			break;
		}
		printf("%s", mensajeError);
	}
	return retorno;
}

int getNombre(char* pResultado, int len)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL){
    	if(getString(buffer,sizeof(buffer)) == 0 && esNombre(buffer,sizeof(buffer)) && strnlen(buffer,sizeof(buffer)) < len)
    	{
    		strncpy(pResultado, buffer, len);
			retorno = 0;
		}
    }
    return retorno;
}

int utn_getNombre(char* pResultado, int lenMin, int lenMax, char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos>=0)
	{
		reintentos--;
		printf("%s", mensaje);
		if(getNombre(bufferString, sizeof(bufferString)) == 0 && strnlen(bufferString, sizeof(bufferString)) < lenMax && strnlen(bufferString, sizeof(bufferString)) > lenMin)
		{
			uppercaseInitial(bufferString);
			strncpy(pResultado, bufferString, lenMax);
			retorno = 0;
			break;
		}
		printf("%s", mensajeError);
	}
	return retorno;
}

// PARA VALIDAR

int esNumerica(char *cadena, int len)
{
	int retorno = 1; // VERDADERO

	for (int i = 0; i < len && cadena[i] != '\0'; i++)
	{
		if (i == 0 && (cadena[i] == '+' || cadena[i] == '-'))
		{
			continue;
		}
		if (cadena[i] > '9' || cadena[i] < '0') {
			retorno = 0;
			break;
		}
	}
	return retorno;
}

int esFlotante(char *cadena)
{
	int retorno = 1;
	int contador = 0;

	if (cadena != NULL && strlen(cadena) > 0)
	{
		for (int i = 0; cadena[i] != '\0'; i++)
		{
			if (i == 0 && (cadena[i] == '-' || cadena[i] == '+'))
			{
				continue;
			}
			if (cadena[i] < '0' || cadena[i] > '9')
			{
				if (cadena[i] == '.' && contador == 0)
				{
					contador++;
				}
				else
				{
					retorno = 0;
					break;
				}
			}
		}
	}
	return retorno;
}

int esCadena(char *cadena, int longitud)
{
	int retorno = 1;

	if (cadena != NULL && longitud > 0)
	{
		for (int i = 0; cadena[i] != '\0' && i < longitud; i++)
		{
			if ((cadena[i] < '0' || cadena[i] > '9') && (cadena[i] < 'A' || cadena[i] > 'Z') && (cadena[i] < 'a' || cadena[i] > 'z'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}


int esNombre(char *cadena, int len)
{
	int retorno = 1;

	if (cadena != NULL && len > 0)
	{
		for (int i = 0; cadena[i] != '\0' && i < len; i++)
		{
			if ((cadena[i] < 'A' || cadena[i] > 'Z') && (cadena[i] < 'a' || cadena[i] > 'z'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}


// MINUSCULA Y MAYUSCULA

void strEnMayuscula(char string[])
{
	int i = 0;
	while (string[i] != '\0')
	{
		string[i] = toupper(string[i]);
		i++;
	}
}

void strEnMinuscula(char string[])
{
	int i = 0;
	while (string[i] != '\0')
	{
		string[i] = tolower(string[i]);
		i++;
	}
}

void uppercaseInitial(char string[])
{
	int cantidad;

	strEnMinuscula(string);
	string[0] = toupper(string[0]);
	cantidad = strlen(string);

	for (int i = 0; i < cantidad; i++)
	{
		if (string[i] == ' ')
		{
			string[i + 1] = toupper(string[i + 1]);
		}
	}
}

