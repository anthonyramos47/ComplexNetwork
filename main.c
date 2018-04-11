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
#include "structs.h"
#include "functions.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    /*Definicion de parametros globales*/
    int K = 4, N= 10, numReds = 1;
    float p = 0.5, r = 0.1;
    
    
    Red red1 = {0,N,K,p,r};
//    Red red2 = {1,N,K,p,r};
//    Red red3 = {2,N,K,p,r};

    
    inicializarRed(&red1);
//    inicializarRed(&red2);
//    inicializarRed(&red3);

    
    cableadoInicial(&red1,numReds);
//    cableadoInicial(&red2,numReds);
//    cableadoInicial(&red3,numReds);

    
    imprimirRed(&red1,numReds);
    
    printf("\n--------------------------------------\n");
    recablearRed(&red1,numReds);
    //recablearRed(&Red2, numReds);


    
    imprimirRed(&red1,numReds);
//    imprimirRed(&red2,numReds);
//    imprimirRed(&red3,numReds);

    
//    entrelazarRedes(&Red1,&Red2);
    
    return (EXIT_SUCCESS);
}

