/*
 * Passenger.h
 *
 *  Created on: 19 may. 2022
 *
 */

#ifndef PASSENGER_H_
#define PASSENGER_H_

#include "LinkedList.h"

struct
{
	int id;
	char nombre[50];
	char apellido[50];
	float precio;
	int tipoPasajero;
	char codigoVuelo[50];
	int estadoVuelo;
}typedef Passenger;

Passenger* Passenger_new();
Passenger* Passenger_newParametros(char* idStr,char* nombreStr,char* apellidoStr,char* precioStr,char* codigoVueloStr,char* tipoPasajeroStr,char* estadoVueloStr);

int Passenger_encontrarID(LinkedList* listaPasajeros, int id);
int Passenger_encontrarUltimoID(LinkedList* listaPasajeros);

void Passenger_delete();
void Passenger_deleteAll(LinkedList* listaPasajeros);

int Passenger_edit(LinkedList* listaPasajeros);
int Passenger_sort(LinkedList* listaPasajeros);
int Passenger_sortById(void* primerPasajero, void* segundoPasajero);
int Passenger_sortByNombre(void* primerPasajero, void* segundoPasajero);
int Passenger_sortByApellido(void* primerPasajero, void* segundoPasajero);
int Passenger_sortByPrecio(void* primerPasajero, void* segundoPasajero);
int Passenger_sortByCodigoVuelo(void* primerPasajero, void* segundoPasajero);
int Passenger_sortByTipoPasajero(void* primerPasajero, void* segundoPasajero);
int Passenger_sortByEstadoVuelo(void* primerPasajero, void* segundoPasajero);

void printListHeader();
int Passenger_printPassenger(LinkedList* listaPasajeros, int index);

int Passenger_TipoPasajeroAChar(int tipoPasajeroInt, char tipoPasajero[]);
int Passenger_TipoPasajeroAInt(char* tipoPasajero);
int Passenger_EstadoVueloAChar(int estadoVueloInt, char estadoVuelo[]);
int Passenger_EstadoVueloAInt(char* estadoVuelo);

int Passenger_setId(Passenger* this,int id);
int Passenger_getId(Passenger* this,int* id);

int Passenger_setNombre(Passenger* this,char* nombre);
int Passenger_getNombre(Passenger* this,char* nombre);

int Passenger_setApellido(Passenger* this,char* apellido);
int Passenger_getApellido(Passenger* this,char* apellido);

int Passenger_setPrecio(Passenger* this,float precio);
int Passenger_getPrecio(Passenger* this,float* precio);

int Passenger_setTipoPasajero(Passenger* this,int tipoPasajero);
int Passenger_getTipoPasajero(Passenger* this,int* tipoPasajero);

int Passenger_setCodigoVuelo(Passenger* this,char* codigoVuelo);
int Passenger_getCodigoVuelo(Passenger* this,char* codigoVuelo);

int Passenger_setEstadoVuelo(Passenger* this,int estadoVuelo);
int Passenger_getEstadoVuelo(Passenger* this,int* estadoVuelo);

#endif /* PASSENGER_H_ */
