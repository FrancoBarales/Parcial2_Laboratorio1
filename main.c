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
#define FALSE 1

/****************************************************
    Menu:
     1. Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).
     2. Cargar los datos de los pasajeros desde el archivo data.csv (modo binario).
     3. Alta de pasajero
     4. Modificar datos de pasajero
     5. Baja de pasajero
     6. Listar pasajeros
     7. Ordenar pasajeros
     8. Guardar los datos de los pasajeros en el archivo data.csv (modo texto).
     9. Guardar los datos de los pasajeros en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/

int main(void)
{
	setbuf(stdout, NULL);

	int opcion;
	int flagSalir = FALSE;
	int flagText = FALSE;
	int flagBinary = FALSE;
	int flagSaveText = FALSE;
	int flagSaveBinary = FALSE;
    LinkedList* pArrayListPassenger = ll_newLinkedList();

    do
    {
    	opcion = menu_principal();
        switch(opcion)
        {
            case 1:
            	if(flagText == FALSE && flagBinary == FALSE)
				{
					controller_loadFromText("data.csv", pArrayListPassenger);
					flagText = TRUE;
				}
            	else
				{
					printf("\nERROR. El archivo ya fue cargado.\n");
				}
				break;
            case 2:
            	if(flagText == FALSE && flagBinary == FALSE)
				{
					controller_loadFromBinary("data.bin", pArrayListPassenger);
					flagBinary = TRUE;
				}
				else
				{
					printf("\nERROR. El archivo ya fue cargado.\n");
				}
				break;
            case 3:
            	controller_addPassenger(pArrayListPassenger);
				break;
			case 4:
				if(!ll_isEmpty(pArrayListPassenger))
				{
					controller_editPassenger(pArrayListPassenger);
				}
				else
				{
					printf("\nERROR. No hay pasajeros para modificar.\n");
				}
				break;
			case 5:
				if(!ll_isEmpty(pArrayListPassenger))
				{
					controller_removePassenger(pArrayListPassenger);
				}
				else
				{
					printf("\nERROR. No hay pasajeros para eliminar.\n");
				}
				break;
			case 6:
				if(!ll_isEmpty(pArrayListPassenger))
				{
					controller_ListPassenger(pArrayListPassenger);
				}
				else
				{
					printf("\nERROR. No hay pasajeros para mostrar.\n");
				}
				break;
			case 7:
				if(!ll_isEmpty(pArrayListPassenger))
				{
					controller_sortPassenger(pArrayListPassenger);
				}
				else
				{
					printf("\nERROR. No hay pasajeros para ordenar.\n");
				}
				break;
			case 8:
				if(!ll_isEmpty(pArrayListPassenger))
				{
					controller_saveAsText("data.csv",pArrayListPassenger);
					flagSaveText = TRUE;
				}
				else
				{
					printf("\nERROR. No hay pasajeros para guardar.\n");
				}
				break;
			case 9:
				if(!ll_isEmpty(pArrayListPassenger))
				{
					controller_saveAsBinary("data.bin",pArrayListPassenger);
					flagSaveBinary = TRUE;
				}
				else
				{
					printf("\nERROR. No hay pasajeros para guardar.\n");
				}
				break;
			case 10:
				if(flagSaveText == FALSE && flagSaveBinary == FALSE)
				{
					printf("\nERROR. No se realizo ningun guardado.\n");
					break;
				}
				else
				{
					Passenger_deleteAll(pArrayListPassenger);
					ll_deleteLinkedList(pArrayListPassenger);
					printf("\nCerrando el programa...\n");
					flagSalir = TRUE;
				}
				break;
        }
    }while(flagSalir != TRUE);

    return 0;
}

