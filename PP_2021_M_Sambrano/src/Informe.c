/*
 * Informe.c
 *
 *  Created on: 20 may. 2021
 *      Author: marti
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Contribuyente.h"
#include "Recaudacion.h"

//Contribuyentes con más recaudaciones en estado “refinanciar”.
int info_ContribuyenteRefinanciar(Recaudacion* arrayRec,int lenRec,Contribuyente* arrayCon,int lenCon,int idContribuyente)
{
	int retorno = -1;
	int i;
	int auxIndice;
	int conContribuyente = 0;
	if(arrayRec != NULL && lenRec > 0 && arrayCon != NULL && lenCon > 0)
	{
		for(i=0;i<lenCon;i++)
		{
			if((arrayRec[i].isEmpty == 0) && (arrayRec[i].estado == 1))
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

//Cantidad de recaudaciones saldadas de importe mayor a 1000: Se imprimirá
int info_RecaudaciobSaldada(Recaudacion* arrayRec,int lenRec,Contribuyente* arrayCon,int lenCon,int idContribuyente)
{
	int retorno = -1;
	int i;
	int auxIndice;
	if(arrayRec != NULL && lenRec > 0 && arrayCon != NULL && lenCon > 0)
	{
		for(i=0;i<lenCon;i++)
		{
			if((arrayRec[i].isEmpty == 0) && (arrayRec[i].estado == 2))
			{
				//auxIndice = rec_buscarId(arrayRec, lenRec, idContribuyente);
				auxIndice = con_buscarId(arrayCon, lenCon, idContribuyente);
				if(arrayRec[auxIndice].importe > 1000)
				{
					printf("\nImporte: %d\n",arrayRec[auxIndice].importe);
				}

				retorno = 0;

			}
		}
	}
	return retorno;
}


//Informar todos los datos de los contribuyentes de un tipo de recaudación
int info_ContribuyenteTipo(Recaudacion* arrayRec,int lenRec,Contribuyente* arrayCon,int lenCon,int idContribuyente)
{
	int retorno = -1;
	int i;
	int auxIndice;
	if(arrayRec != NULL && lenRec > 0 && arrayCon != NULL && lenCon > 0)
	{
		for(i=0;i<lenCon;i++)
		{
			if((arrayRec[i].isEmpty == 0) && (arrayRec[i].tipo == 1))
			{
				//auxIndice = rec_buscarId(arrayRec, lenRec, idContribuyente);
				auxIndice = con_buscarId(arrayCon, lenCon, idContribuyente);
				if(arrayRec[auxIndice].importe > 1000)
				{
					printf("\nImporte: %d\n",arrayRec[auxIndice].importe);
				}

				retorno = 0;

			}
		}
	}
	return retorno;
}


//Nombre y c.u.i.l. de los Contribuyentes que pagaron impuestos en el mes de FEBRERO.
int info_ContribuyenteFebrero(Recaudacion* arrayRec,int lenRec,Contribuyente* arrayCon,int lenCon,int idContribuyente)
{
	int retorno = -1;
	int i;
	int auxIndice;
	if(arrayRec != NULL && lenRec > 0 && arrayCon != NULL && lenCon > 0)
	{
		for(i=0;i<lenCon;i++)
		{
			if((arrayRec[i].isEmpty == 0) && (arrayRec[i].mes == 2))
			{
				//auxIndice = rec_buscarId(arrayRec, lenRec, idContribuyente);
				auxIndice = con_buscarId(arrayCon, lenCon, idContribuyente);
				printf("Nombre: %s - CUIL:%s\n",
										arrayCon[i].nombre,
										arrayCon[i].cuil);

				retorno = 0;

			}
		}
	}
	return retorno;
}

