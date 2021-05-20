/*
 * Contribuyente.h
 *
 *  Created on: 13 may. 2021
 *      Author: marti
 */

#ifndef CONTRIBUYENTE_H_
#define CONTRIBUYENTE_H_

# define  LEN_NOMBRE  30
# define  LEN_APELLIDO  50
# define  LEN_CUIL 14
# define  LEN_CHAR 2


# define  LEN_CONTRIBUYENTE  100
# define  LEN_RECAUDACION  1000
# define  TRUE  1
# define  FALSE  0


typedef struct
{
	int id;
	char nombre [LEN_NOMBRE];
	char apellido [LEN_APELLIDO];
	char cuil[LEN_CUIL];
	int isEmpty;
} Contribuyente;

#endif /* CONTRIBUYENTE_H_ */


int  con_imprimir(Contribuyente * pArray);
int  con_imprimirArray(Contribuyente * pArray, int len);
int  con_inicializarArray(Contribuyente* pArray,int len);
int  con_altaArray(Contribuyente* pArray,int len);
int  con_modificarArray(Contribuyente* pArray,int len, int indice);
int  con_bajaArray(Contribuyente* pArray,int len,int indice);
int  con_buscarId(Contribuyente* pArray, int len, int valorBuscado);
int  con_getEmptyIndex(Contribuyente* pArray,int len);
int  con_ordenarContribuyenteID(Contribuyente* pArray,int len);
int  con_ordenarDobleCriterio(Contribuyente* pArray, int len, int order);
int  con_checkListaVacia(Contribuyente* pArray, int len);
int  con_mocksContribuyente(Contribuyente* pArray,int len, int indice, int id, char* nombre,char* apellido, char *cuil);
//int con_listarRecaudacion(Contribuyente* arrayCon,int lenCon,Recaudacion* arrayRec,int lenRec);

