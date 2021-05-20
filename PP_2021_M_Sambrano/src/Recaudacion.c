/*
 * Recaudacion.c
 *
 *  Created on: 13 may. 2021
 *      Author: marti
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Contribuyente.h"
#include "Recaudacion.h"

static int rec_generarNuevoId(void);

/**
 * \brief Genera un nuevo ID cada vez que se da de alta una Contratacion
 * \return Retorna el id que se genero.
 */
static int rec_generarNuevoId(void)
{
	static int id = 100;
	id = id+1;
	return id;
}

/**
 * \brief Imprime los datos de un Recaudacion
 * \param pContratacion Puntero al producto que se busca imprimir
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int rec_imprimir(Recaudacion* pArray)
{
	int retorno=-1;
	char cadenaTipo[32];
	char cadenaEstado[32];
	if(pArray != NULL && pArray->isEmpty == 0)
	{
		retorno=0;

		switch(pArray->tipo)
		{
		case TIPO_ARBA:
			strncpy(cadenaTipo,"ARBA",LEN_ARBA);
			break;
		case TIPO_IIBB:
			strncpy(cadenaTipo,"IIBB",LEN_IIBB);
			break;
		case TIPO_GANANCIAS:
			strncpy(cadenaTipo,"GANANCIAS",LEN_GANANCIAS);
			break;
		}
		switch(pArray->estado)
		{
		case E_NORMAL:
			strncpy(cadenaEstado,"NORMAL",LEN_NORMAL);
			break;
		case E_REFINANCIAR:
			strncpy(cadenaEstado,"REFINANCIAR",LEN_REFINANCIAR);
			break;
		case E_SALDADO:
			strncpy(cadenaEstado,"SALDADO",LEN_SALDADO);
			break;
		}
		printf("\nidRecaudacion: %d - Mes: %d - Tipo: %s - Importe: %d - IdContribuyente: %d - Estado %s",
				pArray->id,
				pArray->mes,
				cadenaTipo,
				pArray->importe,
				pArray->idContribuyente,
				cadenaEstado);
	}
	return retorno;
}

/**
 * \brief Imprime el array de Recaudacion
 * \param pArray Array de Recaudacion a ser actualizado
 * \param len Limite del array de Recaudacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */

int rec_imprimirArray(Recaudacion* pArray,int len)
{
	int ret = -1;
	int i;
	if(pArray != NULL && len > 0)
	{
		rec_ordenarID(pArray,len);
		for(i=0;i<len;i++)
		{
			rec_imprimir(&pArray[i]);
		}
		ret = 0;
	}
	return ret;
}

/**
 * \brief Inicializa el array
 * \param pArray Array de Recaudacion a ser actualizado
 * \param len Limite del array de Recaudacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int rec_inicializarArray(Recaudacion* pArray,int len)
{
	int ret = -1;
	int i;
	if(pArray != NULL && len > 0)
	{
		for(i=0;i<len;i++)
		{
			pArray[i].isEmpty = 1;
		}
		ret = 0;
	}
	return ret;
}

/**
 * \brief Da de alta un Contratacion en una posicion del array
 * \param array Array de Contratacion a ser actualizado
 * \param limite Limite del array de Contratacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int rec_altaArray(Recaudacion* pArray,int len, int idContribuyente)
{
	int ret = -1;
	Recaudacion bufferRecaudacion;
	int auxIndice;
	if(pArray != NULL && len > 0)
	{
		auxIndice = rec_getEmptyIndex(pArray, len);
		if(auxIndice>=0)
		{
			if(!utn_getNumero(&bufferRecaudacion.mes,"\nIngrese mes:[1-Ene,2-Feb,3-Mar, 4-Abr, 5-May,6-Jun, 7-Jul, 8-Ago, 9-Sep, 10-Oct, 11-Nov, 12-Dic] ","\nERROR",1,12,2) &&
			   !utn_getNumero(&bufferRecaudacion.tipo,"\nIngrese tipo[1-ARBA, 2-IIBB, 3-GANANCIAS]: ","\nERROR",1,3,2) &&
			   !utn_getNumero(&bufferRecaudacion.importe,"\nIngrese Importe: ","\nERROR",1,100000,2))
			{
				bufferRecaudacion.id = rec_generarNuevoId();
				bufferRecaudacion.isEmpty = 0;
				bufferRecaudacion.idContribuyente = idContribuyente;
				bufferRecaudacion.estado = 0;
				pArray[auxIndice] = bufferRecaudacion;

				ret = 0;
			}
			else
			{
				printf("No hay lugares vacios en el Array.\n");
			}
		}
	}
	return ret;
}

/*------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------*/

/**
 * \brief Actualiza los datos de un Recaudacion en una posicion del array
 * \param pArray Array de Recaudacion a ser actualizado
 * \param len Limite del array de Recaudacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int rec_modificarRefinanciar(Recaudacion* pArray,int len, int indice)
{
	int ret = -1;
	Recaudacion bufferRecaudacion;
	if(pArray != NULL && len > 0)
	{
		if(	!utn_getNumero(&bufferRecaudacion.estado,"Desea cambiar a estado refinanciar[1-Si 0-No]","ERROR",1,3,2))
		{
			bufferRecaudacion.id = pArray[indice].id;
			bufferRecaudacion.mes = pArray[indice].mes;
			bufferRecaudacion.tipo = pArray[indice].tipo;
			bufferRecaudacion.importe = pArray[indice].importe;
			bufferRecaudacion.idContribuyente = pArray[indice].idContribuyente;
			bufferRecaudacion.estado = 1;
			bufferRecaudacion.isEmpty = 0;
			pArray[indice] = bufferRecaudacion;
			ret = 0;
		}
	}
	return ret;
}

/**
 * \brief Actualiza los datos de un Recaudacion en una posicion del array
 * \param pArray Array de Recaudacion a ser actualizado
 * \param len Limite del array de Recaudacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int rec_modificarSaldado(Recaudacion* pArray,int len, int indice)
{
	int ret = -1;
	Recaudacion bufferRecaudacion;
	if(pArray != NULL && len > 0)
	{
		if(	!utn_getNumero(&bufferRecaudacion.estado,"Desea cambiar a estado saldado[1-Si 0-No]","\nError",1,3,2))
		{
			bufferRecaudacion.id = pArray[indice].id;
			bufferRecaudacion.mes = pArray[indice].mes;
			bufferRecaudacion.tipo = pArray[indice].tipo;
			bufferRecaudacion.importe = pArray[indice].importe;
			bufferRecaudacion.idContribuyente = pArray[indice].idContribuyente;
			bufferRecaudacion.estado = 2;
			bufferRecaudacion.isEmpty = 0;
			pArray[indice] = bufferRecaudacion;
			ret = 0;
		}
	}
	return ret;
}



/**
 * \brief Actualiza una posicion del array
 * \param arrayRec Array de Recaudacion a ser actualizado
 * \param len Limite del array de Recaudacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int rec_bajaArray(Recaudacion* arrayRec,int lenRec,Contribuyente* arrayCon,int lenCon,int idContribuyente)
{
	int retorno = -1;
	int i;
	if(arrayRec != NULL && lenRec > 0 && arrayCon != NULL && lenCon > 0)
	{
		for(i=0;i<lenRec;i++)
		{
			if((arrayRec[i].isEmpty == 0 ) && (arrayRec[i].idContribuyente == idContribuyente))
			{
				arrayRec[i].isEmpty = 1;
				retorno = 0;
			}
		}
	}
	return retorno;
}


/**
* \brief Busca un ID en un array y devuelve la posicion en que se encuentra
* \param pArray Contratacion Array de Recaudacion
* \param len int Tamaño del array
* \param posicion int* Puntero a la posicion del array donde se encuentra el valor buscado
* \return int Return (-1) si no encuentra el valor buscado o Error [Invalid length or NULL pointer] - (0) si encuentra el valor buscado
*/
int rec_buscarId(Recaudacion* pArray, int len, int valorBuscado)
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

/*---------------------------------------------------------------------*/

/** \brief Encontrar un orquestas por Id en devuelve la posición del índice.
* \param pArray Orquestas
* \param len int
* \param posicion int valor buscado
* \param id int Puntero.
* \return Retorno de la posición del índice de alumnos or (-1) si[Longitud no válida o puntero NULL recibido o alumno no encontrado]
*
*/

int rec_encontrarPorId(Recaudacion* pArray,int len, int posicion, int* id)
{
    int retorno = -1;
    int i;
    if(pArray != NULL && len > 0)
    {
        for(i=0;i<len;i++)
        {
        	if(pArray[i].isEmpty==1)
        		continue;
        	else if(pArray[i].id == posicion)
            {
                retorno = 0;
                *id=i;
                break;
            }
        }
    }
    return retorno;
}

/*----------------------------------------------------------------------*/

/**
 * \brief Buscar primer posicion vacia
 * \param pArray Array de Recaudacion
 * \param len Limite del array de Recaudacion
 * \return Retorna el incice de la posicion vacia y -1 (ERROR)
 */
int rec_getEmptyIndex(Recaudacion* pArray,int len)
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
 * \brief Ordenar el array de Recaudacion por ID ascendente
 * \param pArray Array de Recaudacion
 * \param len Limite del array de Recaudacion
 * \return Retorna el incice de la posicion vacia y -1 (ERROR)
 */
int rec_ordenarID(Recaudacion* pArray,int len)
{
	int ret = -1;
	int flagSwap;
	int i;
	Recaudacion buffer;
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
 * \brief Chequea que la lista de Recaudacion este cargada
 * \param array Array de Recaudacion a ser actualizado
 * \param int len longitud del array de Recaudacion
 * \return Retorna 0, si la lista esta con al menos 1 empleado y -1 si la lista esta vacia.
 */
int rec_checkListaVacia(Recaudacion* pArray, int len)
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
 * \brief Da de alta una Recaudacion en una posicion del array
 * \param array pArray de Recaudacion a ser actualizado
 * \param len Limite del array de Recaudacion
 * \param indice Posicion a ser actualizada
 * \param id Identificador a ser asignado a la Contratacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */

//id;mes;tipo;importe;idContribuyente;estado;
int rec_mocksContratacion(Recaudacion* pArray,int len, int indice, int id,int mes,int tipo, int importe, int idContribuyente, int estado)
{
	int ret = -1;
	Recaudacion bufferRecaudacion;
	if(pArray != NULL && len > 0 && indice < len && indice >= 0)
	{
		    bufferRecaudacion.id = rec_generarNuevoId();
		    bufferRecaudacion.mes = mes;
			bufferRecaudacion.tipo = tipo;
			bufferRecaudacion.importe= importe;
			bufferRecaudacion.idContribuyente = idContribuyente;
			bufferRecaudacion.estado = estado;
			pArray[indice] = bufferRecaudacion;
			ret = 0;
	}
	return ret;
}



int rec_listarRecaudacionSaldadas(Recaudacion* pArray, int len,Contribuyente* pArrayCon,int lenCon,int estado)
{
	int retorno =-1;
	int i;
	int indiceArrayContribuyente;
	int idContribuyente;
	if(pArray != NULL && len>0 && pArrayCon != NULL &&lenCon>0 && estado>=0)
	{
		for(i=0;i<len; i++)
		{
			idContribuyente = pArray[i].idContribuyente;
			indiceArrayContribuyente = con_buscarId(pArrayCon, lenCon, idContribuyente);

			if(pArray[i].estado == 2)
			{
				printf("\nID: %d - Mes: %d - Tipo: %d - Importe: %d - idContribuyente: %d - Estado: %d",
											    pArray[i].id,
											    pArray[i].mes,
												pArray[i].tipo,
											    pArray[i].importe,
												pArray[i].idContribuyente,
												pArray[i].estado);
				printf("- Cuil: %s - Nombre: %s",
												pArrayCon[indiceArrayContribuyente].cuil,
												pArrayCon[indiceArrayContribuyente].nombre);

			}
		}
	}

	return retorno;
}




int rec_listarContribuyente(Recaudacion* arrayRec,int lenRec,Contribuyente* arrayCon,int lenCon,int idContribuyente)
{
	int retorno = -1;
	int i;
	int auxIndice;
	int conContribuyente = 0;
	if(arrayRec != NULL && lenRec > 0 && arrayCon != NULL && lenCon > 0)
	{
		for(i=0;i<lenCon;i++)
		{
			if((arrayRec[i].isEmpty == 0) && (arrayRec[i].idContribuyente == idContribuyente))
			{
				//auxIndice = rec_buscarId(arrayRec, lenRec, idContribuyente);
				auxIndice = con_buscarId(arrayCon, lenCon, idContribuyente);
				printf("Nombre: %s - Apellido: %s - CUIL:%s - Importe: %d\n",
						arrayCon[i].nombre,
						arrayCon[i].apellido,
						arrayCon[i].cuil,
						arrayRec[auxIndice].importe);
				retorno = 0;
				conContribuyente++;
			}
		}
		if(conContribuyente==0)
		{
			printf("Este contribuyente no tiene recaudaciones.\n");
		}
	}
	return retorno;
}

//-------------------------------------------------------------------------
/*
int cont_listarPantallasContratadas(Contratacion* arrayCont,int limiteCont,Pantalla* arrayPan,int limitePan,int idPantalla)
{
	int retorno = -1;
	int i;
	int auxIndice;
	int contPantalla = 0;
	if(arrayCont != NULL && limiteCont > 0 && arrayPan != NULL && limitePan > 0)
	{
		for(i=0;i<limitePan;i++)
		{
			if((arrayCont[i].isEmpty == FALSE) && (arrayCont[i].idPantalla == idPantalla))
			{
				auxIndice = cont_buscarIdContratacion(arrayCont,LENGTH_CONT,idPantalla);

				printf("Cliente: %s - Pantalla: %d - Precio:%.2f\n",
						arrayCont[i].cuitCliente,
						arrayPan[auxIndice].id,
						arrayPan[i].precio);
				retorno = 0;
				contPantalla++;
			}
		}
		if(contPantalla==0)
		{
			printf("Esta pantalla no tiene contrataciones.\n");
		}
	}
	return retorno;
}
*/
//-------------------------------------------------------------------------

int rec_listarRecaudacion(Contribuyente* arrayCon,int lenCon,Recaudacion* arrayRec,int lenRec)
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

int rec_listarIdRecaudacion(Recaudacion* pArray,int len, int idRecaudacion)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && len > 0)
	{
		for(i=0;i<len;i++)
		{
			if((pArray[i].isEmpty == 0))//tengo algo en el arrayCont
			{
				retorno = 0;
				if(pArray[i].id == idRecaudacion)
				{
					printf("IdRecaudacion: %d - idContribuyente: %d - Importe: %d - Mes: %d - Tipo: %d\n",
							pArray[i].id,
							pArray[i].idContribuyente,
						    pArray[i].importe,
							pArray[i].mes,
							pArray[i].tipo);
				}
			}
		}
	}
	return retorno;
}


int rec_listarcontribuyenteRecaudacion(Contribuyente* pArray, int len,Recaudacion* pArrayRec,int lenRec)
{
	int retorno =-1;
	int i;
	int indiceArrayContribuyente;
	int idContribuyente;
	char cadenaTipo[32];
	char cadenaEstado[32];
	if(pArray != NULL && len>0 && pArrayRec != NULL &&lenRec>0)
	{
		for(i=0;i<len; i++)
		{
			idContribuyente = pArray[i].id;
			indiceArrayContribuyente = con_buscarId(pArray, len, idContribuyente);
			//indiceArrayContribuyente = rec_buscarId(pArrayRec, lenRec, idContribuyente);

			if(indiceArrayContribuyente >= 0)
			{
				printf("\nID:%d - Nombre:%s - Apellido:%s - CUIL:%s",
																pArray[i].id,
																pArray[i].nombre,
																pArray[i].apellido,
																pArray[i].cuil);

				switch(pArrayRec[indiceArrayContribuyente].tipo)
						{
						case TIPO_ARBA:
							strncpy(cadenaTipo,"ARBA",LEN_ARBA);
							break;
						case TIPO_IIBB:
							strncpy(cadenaTipo,"IIBB",LEN_IIBB);
							break;
						case TIPO_GANANCIAS:
							strncpy(cadenaTipo,"GANANCIAS",LEN_GANANCIAS);
							break;
						}
				switch(pArrayRec[indiceArrayContribuyente].estado)
						{
						case E_NORMAL:
							strncpy(cadenaEstado,"NORMAL",LEN_NORMAL);
							break;
						case E_REFINANCIAR:
							strncpy(cadenaEstado,"REFINANCIAR",LEN_REFINANCIAR);
							break;
						case E_SALDADO:
							strncpy(cadenaEstado,"SALDADO",LEN_SALDADO);
							break;
						}
						printf(" - idRecaudacion: %d - Mes: %d - Tipo: %s - Importe: %d - IdContribuyente: %d - Estado %s",
								pArrayRec[indiceArrayContribuyente].id,
								pArrayRec[indiceArrayContribuyente].mes,
								cadenaTipo,
								pArrayRec[indiceArrayContribuyente].importe,
								pArrayRec[indiceArrayContribuyente].idContribuyente,
								cadenaEstado);
			}
		}
	}

	return retorno;
}


//-----------------------------------------------------

void menuPrincipal()
{
    printf("\nMENU PRINCIPAL\n");
    printf("--------------\n");
    printf("1 - Alta de Contribuyente\n");
    printf("2 - Modificar datos del contribuyente\n");
    printf("3 - Baja de contribuyente\n");
    printf("4 - Recaudación\n");
    printf("5 - Refinanciar Recaudación \n");
    printf("6 - Saldar Recaudación\n");
    printf("7 - Imprimir Contribuyentesn\n");
    printf("8 - Imprimir Recaudación\n");
    printf("9 - Informes\n");
    printf("10 - Salir\n");
}


void Informes()
{
    printf("\nInformes\n");
    printf("--------------\n");
    printf("1 - ContribuyenteRecaudacionRefinar\n");
    printf("2 - RecaudacionSaldadasMayor1000\n");
    printf("3 - InformasDatosRecaudacuon\n");
    printf("4 - ContribuyenteFebrero\n");
    printf("5 - Salir\n");
}




