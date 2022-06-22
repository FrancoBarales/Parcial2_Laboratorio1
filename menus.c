/*
 * menus.c
 *
 *  Created on: 8 jun. 2022
 *      Author: Franco
 */

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

int menu_principal(void)
{
	int opcion;

	printf("\n------------------------------MENU PRINCIPAL-----------------------------\n"
			"1) Cargar los datos de los pasajeros desde el archivo data.csv (modo texto)\n"
			"2) Cargar los datos de los pasajeros desde el archivo data.bin (modo binario)\n"
			"3) Alta de pasajero\n"
			"4) Modificar datos de pasajero\n"
			"5) Baja de pasajero\n"
			"6) Listar pasajeros\n"
			"7) Ordenar pasajeros\n"
			"8) Guardar los datos de los pasajeros en el archivo data.csv (modo texto).\n"
			"9) Guardar los datos de los pasajeros en el archivo data.bin (modo binario).\n"
			"10) Salir\n");
	utn_getNumero(&opcion,"\nElegir opcion: ","\nERROR. Opcion incorrecta.", 1, 10, 10);

	return opcion;
}

int menu_ModifyPassenger(void)
{
	int opcion;

	printf("\n--------------------MENU DE MODIFICACIONES---------------------\n"
			"Que desea modificar?\n"
			"1) Nombre\n"
			"2) Apellido\n"
			"3) Precio\n"
			"4) Tipo de Pasajero\n"
			"5) Codigo de vuelo\n"
			"6) Estado de vuelo\n"
			"7) Volver al menu principal\n");
	utn_getNumero(&opcion,"\nElegir opcion: ","\nERROR. Opcion incorrecta.", 1, 7, 10);

	return opcion;
}

int menu_PassengerOrder(void)
{
	int opcion;

	printf("\n--------------------MENU DE ORDEN--------------------\n"
			"Que orden desea?"
			"1) ID\n"
			"2) Nombre\n"
			"3) Apellido\n"
			"4) Precio\n"
			"5) Tipo de pasajero\n"
			"6) Codigo de vuelo\n"
			"7) Estado de vuelo\n"
			"8) Volver al menu principal\n");
	utn_getNumero(&opcion,"\nElegir opcion: ","\nERROR. Opcion incorrecta.", 1, 8, 10);

	return opcion;
}


