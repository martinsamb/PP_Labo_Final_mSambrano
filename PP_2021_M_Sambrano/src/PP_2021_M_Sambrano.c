/*
 ============================================================================
 Name        : PP_2021_M_Sambrano.c
 Author      : martin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Contribuyente.h"
#include "utn.h"
#include "Recaudacion.h"
#include  "Informe.h"

#define QTY_CONTRIBUYENTE 50
#define QTY_RECAUDACION 50

int main(void)
{
	//Declaracion de variables y arrays
	setbuf(stdout,NULL);
	Contribuyente arrayCon[LEN_CONTRIBUYENTE];
	Recaudacion arrayRec[LEN_RECAUDACION];
	int optionMenu;
	int optionInfo=0;
	int auxID;
	int auxIndice;
	int auxEstado=0;

	//Inicalizacion
	con_inicializarArray(arrayCon, QTY_CONTRIBUYENTE);
	rec_inicializarArray(arrayRec, QTY_RECAUDACION);

	do
	{
		menuPrincipal();
		if(!utn_getNumero(   &optionMenu,"\nElija una Opcion del Menu[1-9]: ","\nError",1,9,2))
		{
			switch(optionMenu)
			{
				case 1:
					printf("\n***************************************\n");
					if(!con_altaArray(arrayCon, QTY_CONTRIBUYENTE))
					{
						printf("Se dio de alta un contribuyente!\n");
					}
					printf("Lista de contribuyentes actualizada:");
					con_imprimirArray(arrayCon, QTY_CONTRIBUYENTE);
					printf("\n***************************************\n");
					break;
				case 2:
					printf("\n***************************************\n");
					if(con_checkListaVacia(arrayCon, QTY_CONTRIBUYENTE) == -1)
					{
						printf("El array de conntribuyente esta vacio.");
					}
					else
					{
						con_imprimirArray(arrayCon, QTY_CONTRIBUYENTE);
						if(!utn_getNumero(&auxID,"\nIngrese el ID a modificar: ","\nError",1,10000,2))
						{
							auxIndice = con_buscarId(arrayCon, QTY_CONTRIBUYENTE, auxID);
							if(auxIndice>=0)
							{
								if(!con_modificarArray(arrayCon, QTY_CONTRIBUYENTE, auxIndice))
								{
									printf("El contribuyenyr se actualizo con exito!!\n");
									printf("Lista de contribuyente actualizada");
									con_imprimirArray(arrayCon, QTY_CONTRIBUYENTE);
								}
							}
						}
						else
						{
							printf("No se encontro el ID ingresado.\n");
						}
					}
					printf("\n***************************************\n");
					break;
				case 3:
					printf("\n***************************************\n");
					if(con_checkListaVacia(arrayCon, QTY_CONTRIBUYENTE) == -1)
					{
						printf("El array de contribuyente esta vacio.");
					}
					else
					{
						con_imprimirArray(arrayCon, QTY_CONTRIBUYENTE);
						if(!utn_getNumero(&auxID,"\nIngrese el ID de Contribuyente a borrar: ","\nError",1,10000,2))
						{
							auxIndice = con_buscarId(arrayCon, QTY_CONTRIBUYENTE, auxID);
							if(auxIndice>=0)
							{
								//printf("Este Contribuyente tiene los siguientes recaudaciones:\n");
								//rec_listarContribuyente(arrayRec, QTY_RECAUDACION, arrayCon, QTY_CONTRIBUYENTE, auxIndice);

								if(!con_bajaArray(arrayCon, QTY_CONTRIBUYENTE, auxIndice))
								{
									rec_bajaArray(arrayRec, QTY_RECAUDACION, arrayCon, QTY_CONTRIBUYENTE, auxID);
									printf("Lista de Contribuyente actualizada");
									con_imprimirArray(arrayCon, QTY_CONTRIBUYENTE);
									printf("\nRecaudaciones:");
									rec_imprimirArray(arrayRec, QTY_RECAUDACION);
								}
							}
							else
							{
								printf("No se encontro el ID.\n");
							}
						}
					}
					printf("\n***************************************\n");
					break;
				case 4:
					printf("\n***************************************\n");

					con_imprimirArray(arrayCon, QTY_CONTRIBUYENTE);

					if(!utn_getNumero(&auxID,"\nIngrese el ID de Contribuyente a recaudar: ", "\nError",1,10000,2))
					{
						if(con_buscarId(arrayCon, QTY_CONTRIBUYENTE, auxID)>=0)//Valido id ingresado
						{
							if(!rec_altaArray(arrayRec, QTY_RECAUDACION, auxID))
							{
								printf("La recaudacion se dio de alta con exito!!\n");
								printf("Lista de recaudaciones actualizada");
								rec_imprimirArray(arrayRec, QTY_RECAUDACION);
							}
						}
						else
						{
							printf("No se encontro el ID ingresado.\n");
						}
					}


					printf("\n***************************************\n");
					break;
				case 5:
					printf("\n***************************************\n");
					rec_imprimirArray(arrayRec, QTY_RECAUDACION);
					if(!utn_getNumero(&auxID,"\nIngrese idRcaudacion:","\nError",1,1000,2))
					{
						rec_listarIdRecaudacion(arrayRec, QTY_RECAUDACION, auxID);
						auxIndice = rec_buscarId(arrayRec, QTY_RECAUDACION, auxID);

						if(auxIndice>=0)
						{
							if(!rec_modificarRefinanciar(arrayRec, QTY_RECAUDACION, auxIndice))
							{
								printf("La recaudacion se modifico con exito.!!\n");
								printf("Lista de recaudacion actualizada");
								rec_imprimirArray(arrayRec, QTY_RECAUDACION);
							}

						}
						else
						{
							printf("No se encontro el ID ingresado.\n");
						}

					}
					printf("\n***************************************\n");
					break;
				case 6:
					printf("\n***************************************\n");
					rec_imprimirArray(arrayRec, QTY_RECAUDACION);
					if(!utn_getNumero(&auxID,"\nIngrese idRcaudacion:","\nError",1,1000,2))
					{
						rec_listarIdRecaudacion(arrayRec, QTY_RECAUDACION, auxID);
						auxIndice = rec_buscarId(arrayRec, QTY_RECAUDACION, auxID);//Valido Id

						if(auxIndice>=0)
						{
							if(!rec_modificarSaldado(arrayRec, QTY_RECAUDACION, auxIndice))
							{
								printf("La recaudacion se modifico con exito.!!\n");
								printf("Lista de recaudacion actualizada");
								rec_imprimirArray(arrayRec, QTY_RECAUDACION);
							}
						}
						else
						{
							printf("No se encontro el ID ingresado.\n");
						}

					}
					printf("\n***************************************\n");
					break;
				case 7:
					printf("\n***************************************\n");
					/*
					printf("Contribuyente");
					con_imprimirArray(arrayCon, QTY_CONTRIBUYENTE);
					printf("\nRecaudacion");
					rec_imprimirArray(arrayRec, QTY_RECAUDACION);
					*/

					rec_listarcontribuyenteRecaudacion(arrayCon, QTY_CONTRIBUYENTE, arrayRec, QTY_RECAUDACION);

					printf("\n***************************************\n");
					break;
				case 8:
					printf("\n***************************************\n");

					rec_listarRecaudacionSaldadas(arrayRec, QTY_RECAUDACION, arrayCon, QTY_CONTRIBUYENTE, auxEstado);

					printf("\n***************************************\n");
					break;
				case 9://Informes
					printf("\n***************************************\n");
					do
					{
						Informes();
						if(!utn_getNumero(   &optionMenu,"\nElija una Opcion del Menu[1-5]: ","\nError",1,5,2))
						{
							switch(optionInfo)
							{
								case 1 :
									info_ContribuyenteRefinanciar(arrayRec, QTY_RECAUDACION, arrayCon, QTY_CONTRIBUYENTE, auxID);
									break;
								case 2 :
									info_RecaudaciobSaldada(arrayRec, QTY_RECAUDACION, arrayCon, QTY_CONTRIBUYENTE, auxID);
									break;
								case 3:
									info_ContribuyenteTipo(arrayRec, QTY_RECAUDACION, arrayCon, QTY_CONTRIBUYENTE, auxID);
									break;
								case 4:
									info_ContribuyenteFebrero(arrayRec, QTY_RECAUDACION, arrayCon,QTY_CONTRIBUYENTE, auxID);
									break;
								case 5:
									break;
										default:
										printf("\nOpcion no valida");

							}
						}
					}while(optionInfo!=5);
					printf("\n***************************************\n");
					break;

				case 10:
					break;
						default:
						printf("\nOpcion no valida");
			}
		}
	}while(optionMenu!=10);
	return EXIT_SUCCESS;
}
