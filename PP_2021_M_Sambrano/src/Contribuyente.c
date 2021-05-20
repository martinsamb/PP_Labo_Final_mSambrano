/*
 * Contribuyente.c
 *
 *  Created on: 13 may. 2021
 *      Author: marti
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Contribuyente.h"
#include "Recaudacion.h"
#include "utn.h"

static int con_generarNuevoId(void);

/**
 * \brief Genera un nuevo ID cada vez que se da de alta un Contribuyente
 * \return Retorna el id que se genero.
 */
static int con_generarNuevoId(void)
{
	static int id = 1000;
	id = id+1;
	return id;
}

/**
 * \brief Imprime los datos de un Contribuyente
 * \param pArray Puntero al producto que se busca imprimir
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int con_imprimir(Contribuyente* pArray)
{
	int retorno=-1;
	if(pArray != NULL && pArray->isEmpty == 0)
	{
		printf("\nID:%d - Nombre:%s - Apellido:%s - CUIL:%s",
				pArray->id,
				pArray->nombre,
				pArray->apellido,
				pArray->cuil);
		retorno=0;
	}
	return retorno;
}

/**
 * \brief Imprime el array de Contribuyente
 * \param pArray Array de Contribuyente a ser actualizado
 * \param len Limite del array de Pantallaes
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int con_imprimirArray(Contribuyente* pArray,int len)
{
	int ret = -1;
	int i;
	if(pArray != NULL && len > 0)
	{
		con_ordenarContribuyenteID(pArray,len);
		for(i=0;i<len;i++)
		{
			con_imprimir(&pArray[i]);
		}
		ret = 0;
	}
	return ret;
}

/**
 * \brief Inicializa el array
 * \param pArray Array de Contribuyente a ser actualizado
 * \param len Limite del array de Contribuyente
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int con_inicializarArray(Contribuyente* pArray,int len)
{
	int ret = -1;
	int i;
	if(pArray != NULL && len > 0)
	{
		for(i=0;i<len;i++)
		{
			pArray[i].isEmpty =1;
		}
		ret = 0;
	}
	return ret;
}

/**
 * \brief Da de alta un Contribuyente en una posicion del array
 * \param pArray Array de Contribuyente a ser actualizado
 * \param len Limite del array de Contribuyente
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int con_altaArray(Contribuyente* pArray,int len)
{
	int ret = -1;
	Contribuyente bufferContribuyente;
	int auxIndice;
	if(pArray != NULL && len > 0)
	{
		auxIndice = con_getEmptyIndex(pArray,len);
		if(auxIndice>=0)
		{
			if(!utn_getNombre(bufferContribuyente.nombre,LEN_NOMBRE,"\nIngrese el Nombre: ","\nERROR, nombre invalido.\n",2) &&
			   !utn_getApellido(bufferContribuyente.apellido, LEN_APELLIDO,"\nIngrese el Apellido: ","\nERROR, apellido invalido.\n",2) &&
			   !utn_getCuil(bufferContribuyente.cuil, LEN_CUIL,"\nIngrese el Cuil[xx-xxxxxxxx-x]: ","\nERROR cuil invalido.\n",2))
			{
				bufferContribuyente.id = con_generarNuevoId();
				bufferContribuyente.isEmpty = 0;//Cero es falso y cualquier valor diferente de cero es verdadero.
				pArray[auxIndice] = bufferContribuyente;
				ret = 0;

				printf("\nID:%d - Nombre:%s - Apellido:%s - CUIL:%s",pArray->id,pArray->nombre,pArray->apellido,pArray->cuil);
			}
			else
			{
				printf("No hay lugares vacios en el Array.\n");
			}
		}
	}
	return ret;
}

/**
 * \brief Actualiza los datos de un Contribuyente en una posicion del array
 * \param array Array de Contribuyente a ser actualizado
 * \param limite Limite del array de Contribuyente
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int con_modificarArray(Contribuyente* pArray,int len, int indice)
{
	int ret = -1;
	Contribuyente bufferContribuyente;
	if(pArray != NULL && len > 0)
	{
		if(	!utn_getNombre(bufferContribuyente.nombre,LEN_NOMBRE,"\nIngrese Nombre del contribuyente: \n","\nERROR, nombre invalido.\n",2) &&
			!utn_getApellido(bufferContribuyente.apellido, LEN_APELLIDO,"\nIngrese el Apellido: ","\nERROR, apellido invalido.\n",2) &&
			!utn_getCuil(bufferContribuyente.cuil,LEN_CUIL,"\nIngrese CUIL del contribuyente: \n","\nERROR, nombre invalido.\n", 2))
		{
			bufferContribuyente.id = pArray[indice].id;
			bufferContribuyente.isEmpty = 0;
			pArray[indice] = bufferContribuyente;
			ret = 0;
		}
		else
		{
			printf("No se encontro el ID ingresado.\n");
		}
	}
	return ret;
}

/**
 * \brief Actualiza una posicion del array
 * \param pArray Array de Contribuyente a ser actualizado
 * \param len Limite del array de Contribuyente
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int con_bajaArray(Contribuyente* pArray,int len,int indice)
{
	int ret = -1;
	char auxChar;
	if(pArray != NULL && len > 0)
	{
		if(!utn_getCaracterSN(&auxChar,LEN_CHAR,"\nEsta seguro que desea borrar un Contribuyendo?[S/N]:", "ERROR\n",2))
		{
			switch(auxChar)
			{
				 case 'S':
				 case 's':
					 pArray[indice].isEmpty = 1;
					 ret = 0;
					break;
				 case 'N':
				 case 'n':
					 break;
			}
		}
	}
	return ret;
}

/**
* \brief Busca un ID en un array y devuelve la posicion en que se encuentra
* \param pArray Contribuyente Array de Contribuyente
* \param len int Tamaño del array
* \param posicion int* Puntero a la posicion del array donde se encuentra el valor buscado
* \return int Return (-1) si no encuentra el valor buscado o Error [Invalid length or NULL pointer] - (0) si encuentra el valor buscado
*/
int con_buscarId(Contribuyente* pArray, int len, int valorBuscado)
{
	int ret = -1;
	int i;
	if(pArray != NULL && len > 0 && valorBuscado >= 0)
	{
		for(i=0;i<len;i++)
		{
			if(pArray[i].isEmpty==0 && pArray[i].id == valorBuscado)
			{
				ret = i;
				break;
			}
		}
	}
	return ret;
}

/**
 * \brief Buscar primer posicion vacia
 * \param pArray Array de Contribuyente
 * \param len Limite del array de Contribuyente
 * \return Retorna el incice de la posicion vacia y -1 (ERROR)
 */
int con_getEmptyIndex(Contribuyente* pArray,int len)
{
	int ret = -1;
	int i;
	if(pArray != NULL && len > 0)
	{
		for(i=0;i<len;i++)
		{
			if(pArray[i].isEmpty == 1)
			{
				ret = i;
				break;
			}
		}
	}
	return ret;
}

/**
 * \brief Ordenar el array de Contribuyente por ID ascendente
 * \param pArray Array de Contribuyente
 * \param len Limite del array de Contribuyente
 * \return Retorna el incice de la posicion vacia y -1 (ERROR)
 */
int con_ordenarContribuyenteID(Contribuyente* pArray,int len)
{
	int ret = -1;
	int flagSwap;
	int i;
	Contribuyente buffer;
	if(pArray != NULL && len > 0)
	{
		do
		{
			flagSwap = 0;
			for(i=0;i<len-1;i++)
			{
				if(pArray[i].isEmpty || pArray[i+1].isEmpty)
				{
					continue;
				}
				if(pArray[i].id > pArray[i+1].id)
				{
					flagSwap = 1;
					buffer = pArray[i];
					pArray[i] = pArray[i+1];
					pArray[i+1]=buffer;
				}
			}
			len--;
		}while(flagSwap);
	}
	return ret;
}

/**
 * \brief Ordenar el array de Contribuyente por un doble criterio ascendente o descendente
 * \param pArray Array de Contribuyente
 * \param len int Limite del array de Contribuyente
 * \param orden int [1]-Indica ascendente - [0]-Indica Descendente
 * \return Retorna el incice de la posicion vacia y -1 (ERROR)
 */
int con_ordenarDobleCriterio(Contribuyente* pArray, int len, int order)
{
	int ret=-1;
	int flagSwap;
	int i;
	Contribuyente buffer;
	if(pArray!=NULL && len>0)
	{
		do
		{
			flagSwap = 0;
			for(i=0;i<len-1;i++)
			{
				if(
					(order==1 && strncmp(pArray[i].nombre,pArray[i+1].nombre,ARRAY_LEN_NOMBRE)>0) ||
				    ((order==1 && strncmp(pArray[i].nombre,pArray[i+1].nombre,ARRAY_LEN_NOMBRE)==0) &&
				    (pArray[i].id > pArray[i+1].id)) ||
				    (order==0 && strncmp(pArray[i].nombre,pArray[i+1].nombre,ARRAY_LEN_NOMBRE) < 0) ||
				    ((order==0 && strncmp(pArray[i].nombre,pArray[i+1].nombre,ARRAY_LEN_NOMBRE) == 0) &&
				    (pArray[i].id < pArray[i+1].id)))
				{
					flagSwap = 1;
					buffer = pArray[i];
					pArray[i] = pArray[i+1];
					pArray[i+1]=buffer;
				}
			}
			len--;
		}while(flagSwap);
	}
	return ret;
}

/**
 * \brief Chequea que la lista de Contribuyente este cargada
 * \param pArray Array de Contribuyente a ser actualizado
 * \param int len longitud del array de Contribuyente
 * \return Retorna 0, si la lista esta con al menos 1 empleado y -1 si la lista esta vacia.
 */
int con_checkListaVacia(Contribuyente* pArray, int len)
{
	int ret=-1;
	int contador = 0;
	int i;
	if(pArray!=NULL && len>0)
	{
		for(i=0;i<len;i++)
		{
			if(pArray[i].isEmpty==0)
			{
				contador++;
			}
		}
		if(contador>0)
		{
			ret=0;
		}
	}
	return ret;
}

/**
 * \brief Da de alta una Pantalla en una posicion del array
 * \param array Array de Pantalla a ser actualizado
 * \param limite Limite del array de Pantalla
 * \param indice Posicion a ser actualizada
 * \param id Identificador a ser asignado a la Pantalla
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */

/*
 * int id;
	int tipo;
	char nombre [LENGTH_NOMBRE];
	char direccion [LENGTH_DIRECCION];
	float precio;
 * */

/*
 * int id;
	char nombre [LEN_NOMBRE];
	char apellido [LEN_APELLIDO];
	char cuil[LEN_CUIL];
 * */

int con_mocksContribuyente(Contribuyente* pArray,int len, int indice, int id, char* nombre,char* apellido, char *cuil)
{
	int ret = -1;
	Contribuyente bufferContribuyente;
	if(pArray != NULL && len > 0 && indice < len && indice >= 0)
	{
		    bufferContribuyente.id = con_generarNuevoId();
		    strncpy(bufferContribuyente.nombre,nombre,LEN_NOMBRE);
			strncpy(bufferContribuyente.apellido,apellido,LEN_APELLIDO);
			bufferContribuyente.isEmpty = 0;
			pArray[indice] = bufferContribuyente;
			ret = 0;
	}
	return ret;
}
/*
int con_listarConRecaudacion(Recaudacion* arrayRec,int lenRec,Contribuyente* arrayCon,int lenCon,int idRecaudacion)
{
	int retorno = -1;
	int i;
	int auxIndice;
	int contRecaudacion = 0;
	if(arrayRec != NULL && lenRec > 0 && arrayCon != NULL && lenCon > 0)
	{
		for(i=0;i<lenCon;i++)
		{
			if((arrayRec[i].isEmpty == 0) && (arrayRec[i].id == idRecaudacion))
			{
				auxIndice = con_buscarId(arrayCon,lenCon,idRecaudacion);
				//estado:Saldadas(R) +cuil(C);nombre Contribuyente(C)
				printf("Nombre contribuyente: %s -Cuil: %d - Estado:%d\n",
						arrayCon[i].nombre,
						arrayCon[i].cuil,
						arrayRec[auxIndice].estado);
				retorno = 0;
				contRecaudacion++;
			}
		}
		if(contRecaudacion==0)
		{
			printf("Esta pantalla no tiene contrataciones.\n");
		}
	}
	return retorno;
}
*/





/*
int con_listarRecaudacion(Contribuyente* arrayCon,int lenCon,Recaudacion* arrayRec,int lenRec)
{
	int retorno = -1;
	int i;
	int auxIndice;//Pantalla
	if(arrayCon != NULL && lenCon > 0 && arrayRec != NULL && lenRec > 0)
	{
		for(i=0;i<lenRec;i++)
		{
			if((arrayCon[i].isEmpty == 0))
			{
				auxIndice = rec_buscarId(arrayRec, lenRec, arrayCon[i].id);
				printf("Nombre: %s - Apellido: %s - Cuil: %s - Importe: %d\n",
						arrayCon[i].nombre,
						arrayCon[i].apellido,
						arrayCon[i].cuil,
						arrayRec[auxIndice].importe);
				retorno=0;
			}
		}
	}
	return retorno;

}
*/

