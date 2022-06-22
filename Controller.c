#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Passenger.h"
#include "Controller.h"
#include "LinkedList.h"
#include "parser.h"
#include "menus.h"
#include "utn.h"

#define TRUE 0
#define FALSE -1

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	FILE* pArchivo;

	if(path != NULL && pArrayListPassenger != NULL)
	{
		pArchivo = fopen(path, "r");
		if(pArchivo != NULL)
		{
			parser_PassengerFromText(pArchivo , pArrayListPassenger);
			printf("Archivo de texto cargado correctamente.");
			retorno = 0;
		}
	}
	fclose(pArchivo);

	return retorno;
}

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path, LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	FILE* pArchivo;

	if(path != NULL && pArrayListPassenger != NULL)
	{
		pArchivo = fopen(path,"rb");
		if(pArchivo != NULL)
		{
			if(parser_PassengerFromBinary(pArchivo, pArrayListPassenger) == 0)
			{
				printf("Archivo cargado exitosamente.\n");
				retorno=0;
			}
			fclose(pArchivo);
		}
		else
		{
			printf("Error al abrir el archivo\n");
		}
	}

    return retorno;
}

/** \brief Alta de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_addPassenger(LinkedList* pArrayListPassenger)
{
	int nextId;
	int retorno = -1;
	char auxNombre[128];
	char auxApellido[128];
	float auxPrecio;
	char auxCodigoVuelo[128];
	int auxTipoPasajero;
	int auxEstadoVuelo;
	Passenger* auxPasajero = NULL;

	if(pArrayListPassenger != NULL)
	{
		if((!(utn_getNombre(auxNombre, 1, 50, "\nIngrese el nombre: ","\nERROR. Datos no validos.", 3)) &&
			!(utn_getNombre(auxApellido, 1, 50, "\nIngrese el apellido: ","\nERROR. Datos no validos.", 3)) &&
			!(utn_getNumeroFlotante(&auxPrecio, "\nIngrese precio (Min: $10000 - Max: $1000000): $","\nERROR. Datos no validos.", 10000, 1000000, 3)) &&
			!(utn_getCadena(auxCodigoVuelo, 1, 10,"\nIngrese el codigo de vuelo (hasta 9 caracteres): ","\nERROR. Datos no validos.", 3)) &&
			!(utn_getNumero(&auxTipoPasajero,"\nIngrese el tipo de pasajero\n(1.FirstClass, 2.Executive, 3.Economy): ","\nERROR. Datos no validos.", 1, 3, 3)) &&
			!(utn_getNumero(&auxEstadoVuelo,"\nIngrese el estado de vuelo\n(1. En horario, 2.Aterrizado, 3.En vuelo, 4.Demorado): ","\nERROR. Datos no validos.", 1, 4, 3))
		))
		{
			auxPasajero = Passenger_new();
			nextId = Passenger_encontrarUltimoID(pArrayListPassenger) + 1;
			Passenger_setId(auxPasajero, nextId);
			Passenger_setNombre(auxPasajero, auxNombre);
			Passenger_setApellido(auxPasajero, auxApellido);
			Passenger_setPrecio(auxPasajero, auxPrecio);
			Passenger_setCodigoVuelo(auxPasajero, auxCodigoVuelo);
			Passenger_setTipoPasajero(auxPasajero, auxTipoPasajero);
			Passenger_setEstadoVuelo(auxPasajero, auxEstadoVuelo);
			ll_add(pArrayListPassenger, auxPasajero);
			printf("\nCarga de pasajero realizada exitosamente.\n");
		}
	}
    return retorno;
}

/** \brief Modificar datos de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_editPassenger(LinkedList* pArrayListPassenger)
{
	int retorno = -1;

	if(pArrayListPassenger != NULL)
	{
		Passenger_edit(pArrayListPassenger);
	}
	return retorno;
}

/** \brief Baja de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_removePassenger(LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	int auxId;
	int lastId;
	int index;
	char respuesta;
	Passenger* auxPasajero = NULL;

	lastId = Passenger_encontrarUltimoID(pArrayListPassenger);

	if(pArrayListPassenger != NULL)
	{
		controller_ListPassenger(pArrayListPassenger);
		utn_getNumero(&auxId, "\nIndique el ID del pasajero a dar de baja: ", "ERROR. ID invalido. \n", 1, lastId, 2);
		index = Passenger_encontrarID(pArrayListPassenger, auxId);

		if(index != -1)
		{
			printListHeader();
			Passenger_printPassenger(pArrayListPassenger, index);
			auxPasajero = (Passenger*)ll_get(pArrayListPassenger, index);

			do
			{
				utn_getNombre(&respuesta, 0, 2, "\nEsta seguro que desea borrar este pasajero? (S/N): ","\nERROR. Respuesta invalida.", 3);
				strEnMinuscula(&respuesta);
			}while(respuesta != 's' && respuesta != 'n');

			if(respuesta == 's')
			{
				ll_remove(pArrayListPassenger, index);
				Passenger_delete(auxPasajero);
				printf("\nBaja de pasajero realizada exitosamente.\n");
				retorno = 0;
			}
			else
			{
				printf("\nBaja de pasajero cancelada.");
			}
		}
		else
		{
			printf("ERROR. No se ha encontrado pasajero asociado a ese ID.\n");
		}
	}
    return retorno;
}

/** \brief Listar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_ListPassenger(LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	int len;
	int id;
	char nombre[128];
	char apellido[128];
	float precio;
	char codigoVuelo[128];
	int tipoPasajero;
	int estadoVuelo;
	char auxTipoPasajero[128];
	char auxEstadoVuelo[128];
	Passenger* auxPasajero = NULL;

	if(pArrayListPassenger != NULL)
	{
		printListHeader();
		len = ll_len(pArrayListPassenger);

		for(int i = 0; i < len; i++)
		{
			auxPasajero = (Passenger*)ll_get(pArrayListPassenger, i);
			Passenger_getId(auxPasajero, &id);
			Passenger_getNombre(auxPasajero, nombre);
			Passenger_getApellido(auxPasajero, apellido);
			Passenger_getPrecio(auxPasajero, &precio);
			Passenger_getCodigoVuelo(auxPasajero, codigoVuelo);
			Passenger_getTipoPasajero(auxPasajero, &tipoPasajero);
			Passenger_getEstadoVuelo(auxPasajero, &estadoVuelo);

			Passenger_TipoPasajeroAChar(tipoPasajero, auxTipoPasajero);
			Passenger_EstadoVueloAChar(estadoVuelo, auxEstadoVuelo);

			printf("|%4d |%15s |%15s |%12.2f |%15s |%16s |%15s|\n", id, nombre, apellido, precio, codigoVuelo, auxTipoPasajero, auxEstadoVuelo);

			retorno = 0;
		}
		printf("+-----+----------------+----------------+-------------+----------------+-----------------+---------------+\n");
	}
    return retorno;
}

/** \brief Ordenar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_sortPassenger(LinkedList* pArrayListPassenger)
{
	int retorno = -1;

	if(pArrayListPassenger != NULL)
	{
		Passenger_sort(pArrayListPassenger);
		retorno = 0;
	}
	return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListPassenger){

	int retorno = -1;
	int len;
	int auxId;
	char auxNombre[128];
	char auxApellido[128];
	float auxPrecio;
	int auxTipoPasajero;
	char auxCodigoVuelo[128];
	int auxEstadoVuelo;
	FILE* pArchivo = NULL;
	Passenger* auxPasajero = NULL;

	if(path != NULL && pArrayListPassenger != NULL)
	{
		pArchivo = fopen(path, "w");
		len = ll_len(pArrayListPassenger);

		if(pArchivo != NULL && len > 0)
		{
			fprintf(pArchivo,"id,name,lastname,price,flycode,typePassenger,statusFlight\n");

			for(int i = 0; i < len; i++)
			{
				auxPasajero = (Passenger*)ll_get(pArrayListPassenger, i);
				if(auxPasajero != NULL)
				{
					if(!Passenger_getId(auxPasajero, &auxId) &&
						!Passenger_getNombre(auxPasajero, auxNombre) &&
						!Passenger_getApellido(auxPasajero, auxApellido) &&
						!Passenger_getPrecio(auxPasajero, &auxPrecio) &&
						!Passenger_getCodigoVuelo(auxPasajero, auxCodigoVuelo) &&
						!Passenger_getTipoPasajero(auxPasajero, &auxTipoPasajero) &&
						!Passenger_getEstadoVuelo(auxPasajero, &auxEstadoVuelo))
					{
						fprintf(pArchivo, "%d,%s,%s,%.2f,%d,%s,%d\n", auxId, auxNombre, auxApellido, auxPrecio, auxTipoPasajero, auxCodigoVuelo, auxEstadoVuelo);
						retorno = 0;
					}
					else
					{
						Passenger_delete(auxPasajero);
						printf("ERROR. No se pudo guardar el archivo.\n");
					}
				}
			}
			fclose(pArchivo);

			if(retorno == 0)
			{
				printf("Archivo guardado exitosamente.\n");
			}
		}
		else
		{
			printf("ERROR. No se pudo abrir el archivo.\n");
		}
	}

    return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	int len;
	FILE* pArchivo;
	Passenger* auxPassenger = NULL;

	if(path != NULL && pArrayListPassenger != NULL)
	{
		len = ll_len(pArrayListPassenger);
		pArchivo = fopen(path,"wb");

		if(pArchivo != NULL && len > 0)
		{
			for(int i=0; i < len; i++)
			{
				auxPassenger = (Passenger*)ll_get(pArrayListPassenger, i);

				if(auxPassenger != NULL)
				{
					fwrite(auxPassenger, sizeof(Passenger), 1, pArchivo);
					retorno = 0;
				}
			}
		}
		else
		{
			printf("ERROR. No se pudo abrir el archivo.\n");
		}
		fclose(pArchivo);
		if(retorno == 0)
		{
			printf("Archivo guardado exitosamente.\n");
		}
	}
    return retorno;
}
