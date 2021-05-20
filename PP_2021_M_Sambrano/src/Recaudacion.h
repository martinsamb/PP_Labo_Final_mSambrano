/*
 * Recaudacion.h
 *
 *  Created on: 13 may. 2021
 *      Author: marti
 */

#include "Contribuyente.h"


#ifndef RECAUDACION_H_
#define RECAUDACION_H_

#define TIPO_ARBA 1
#define TIPO_IIBB 2
#define TIPO_GANANCIAS 3

#define E_NORMAL 0
#define E_REFINANCIAR 1
#define E_SALDADO 2

#define LEN_ARBA 5
#define LEN_IIBB 5
#define LEN_GANANCIAS 10

#define LEN_NORMAL 7
#define LEN_REFINANCIAR 12
#define LEN_SALDADO 8



typedef struct
{
	int id;
	int mes;
	int tipo;
	int importe;
	int idContribuyente;
	int estado;
	int isEmpty;
}Recaudacion;


#endif /* RECAUDACION_H_ */

int rec_imprimir(Recaudacion* pArray);
int rec_imprimirArray(Recaudacion* pArray,int len);
int rec_inicializarArray(Recaudacion* pArray,int len);
int rec_getEmptyIndex(Recaudacion* pArray,int len);
int rec_altaArray(Recaudacion* pArray,int len, int idContribuyente);
int rec_modificarRefinanciar(Recaudacion* pArray,int len, int indice);
int rec_modificarSaldado(Recaudacion* pArray,int len, int indice);
int rec_bajaArray(Recaudacion* arrayRec,int lenRec,Contribuyente* arrayCon,int lenCon,int idContribuyente);
int rec_buscarId(Recaudacion* pArray, int len, int valorBuscado);
int rec_getEmptyIndex(Recaudacion* pArray,int len);
int rec_ordenarID(Recaudacion* pArray,int len);
int rec_checkListaVacia(Recaudacion* pArray, int len);
int rec_encontrarPorId(Recaudacion* pArray,int len, int posicion, int* id);
int rec_mocksContratacion(Recaudacion* pArray,int len, int indice, int id,int mes,int tipo, int importe, int idContribuyente, int estado);
int rec_listarContribuyente(Recaudacion* arrayRec,int lenRec,Contribuyente* arrayCon,int lenCon,int idContribuyente);
int rec_listarRecaudacion(Contribuyente* arrayCon,int lenCon,Recaudacion* arrayRec,int lenRec);
int rec_listarIdRecaudacion(Recaudacion* pArray,int len, int idRecaudacion);
int rec_listarRecaudacionSaldadas(Recaudacion* pArray, int len,Contribuyente* pArrayCon,int lenCon,int estado);
int rec_listarcontribuyenteRecaudacion(Contribuyente* pArray, int len,Recaudacion* pArrayRec,int lenRec);


//---------------------------------------------

void menuPrincipal();
void Informes();



