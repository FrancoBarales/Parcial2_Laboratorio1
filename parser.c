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

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromText(FILE* pFile , LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	char id[128];
	char nombre[128];
	char apellido[128];
	char precio[128];
	char codigoVuelo[128];
	char tipoPasajero[128];
	char estadoVuelo[128];
	Passenger* auxPasajero = NULL;

	if(pFile != NULL && pArrayListPassenger != NULL)
	{
		fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", id, nombre, apellido, precio, codigoVuelo, tipoPasajero, estadoVuelo);
		while(!feof(pFile))
		{
			if(fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", id, nombre, apellido, precio, codigoVuelo, tipoPasajero, estadoVuelo) == 7)
			{
				printf("%s,%s,%s,%s,%s,%s,%s\n", id, nombre, apellido, precio, codigoVuelo, tipoPasajero, estadoVuelo);
				auxPasajero = Passenger_newParametros(id, nombre, apellido, precio, codigoVuelo, tipoPasajero, estadoVuelo);
				if(auxPasajero != NULL)
				{
					ll_add(pArrayListPassenger, auxPasajero);
					retorno = 0;
				}
			}
		}
	}
    return retorno;
}

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromBinary(FILE* pFile , LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	Passenger* auxPassenger = NULL;

	if(pFile != NULL && pArrayListPassenger != NULL)
	{
		do
		{
			auxPassenger = Passenger_new();

			if(auxPassenger != NULL)
			{
				if(fread(auxPassenger,sizeof(Passenger),1,pFile))
				{
					ll_add(pArrayListPassenger, auxPassenger);
					retorno = 0;
				}
				else
				{
					Passenger_delete(auxPassenger);
				}
			}
		}while(!feof(pFile));
	}

    return retorno;
}
