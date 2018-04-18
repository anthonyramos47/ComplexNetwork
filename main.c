/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ferynando7
 *
 * Created on April 10, 2018, 1:42 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "functions.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    /*Definicion de parametros globales*/
    int K = 16, N= 1000, numReds = 2,numConx=2;
    float p = 0.08, r = 0.1 ,q=0.01; //q aun no estamos usando revisar las funciones superRed
    int T = 2000;
    float actRed1, actRed2;
    
    //srand(time(NULL));
    
    srand(300);
    
    Red red1 = {0,N,K,p,r};
    Red red2 = {1,N,K,p,r};

    //Inicializo las redes
    /* inicializarRed(&red1); */
    /*inicializarRed(&red2); */
    
    inicializarMuestra(&red1, numReds);
    //actRed1 = actividadMuestra(&red1, T);
    //printf("Actividad Red 1: %f \n", actRed1);
    
    generarEImprimirMatrizAdyacente(&red1, numReds);
    
    
    inicializarMuestra(&red2, numReds);
    //actRed2 = actividadMuestra(&red2, T);
    //printf("Actividad Red 2: %f \n", actRed2);
    recablearDosRedes(&red1,&red2,numConx,numReds,q);
    //generarEImprimirMatrizAdyacente(&red2, numReds);
    
    actividadRedes(&red1, &red2, numReds, T);
    //imprimirRed(&red1,numReds);
    
    //imprimirRed(&red2,numReds);
    /*
    printf("\n--------------------------------------\n");
    printf("\nCABLEADO INICIAL\n");
    
    //Realizo el cableado inicial
    cableadoInicial(&red1,numReds);
    cableadoInicial(&red2,numReds);
    imprimirRed(&red1,numReds);
    imprimirRed(&red2,numReds);

    printf("\n--------------------------------------\n");
    printf("\nRECABLEADO POR SEPARADO\n");
    
    //Recableo ambas redes por separado
    recablearRed(&red1,numReds);
    recablearRed(&red2, numReds);
    imprimirRed(&red1,numReds);
    imprimirRed(&red2,numReds);
    
    printf("\n--------------------------------------\n");
    printf("\nRECABLEADO DE AMBAS REDES\n");

    recablearDosRedes(&red1,&red2,numConx,numReds,q);
    imprimirRed(&red1,numReds);
    imprimirRed(&red2,numReds); */ 
    
        
    return (EXIT_SUCCESS);
}

