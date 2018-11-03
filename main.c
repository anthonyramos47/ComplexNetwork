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
#include <math.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "functions.h"

/*
 *
 */
int main(int argc, char** argv) {

    /*Definicion de parametros globales*/
    //int K = 10, N= 40, numReds = 1, numConx=1;
    //float q=0.01; //q aun no estamos usando revisar las funciones superRed
    int T = 1000;
    int N = 50;
    int K = 1;
    int numReds = 1;
    // float actRed1, actRed2;
    //float deltaz, deltap, p1, p2;
    //srand(time(NULL));
    //float *sigmaVector;
    //float *zVector;
    FILE *values;

    srand(12);


    Red red1 = {0, N, K, 0.8, 0.4};
    float areas[ ] = {0.2161438641853612,0.017135961255624787,0.12910119999432873,0.04732631809463028,0.03856153472851655,0.4289769593978548,0.06325096809621523,0.735744372749664,0.05199651040738076,0.08666731200137802,0.03651391180839847,0.06406420203342938,0.08829984838934857,0.08673960288909009,0.09371824855072637,0.06021667359111928,0.43530514365282125,0.05750948982258523,0.1479708982047825,1.,0.5345786600082096,0.2285330496606817,0.6351377999907001,0.047014748490233293,0.10378446408989174,0.07832954634011552,0.04062107876019696,0.09006546530875985,0.09909331709398843,0.42022570982171165,0.1631746464036335,0.09523413746594873,0.13503361522732601,0.6765115462811824,0.19261357347109906,0.06319579658974298,0.08257406948934752,0.1341149388394604,0.4015320415081946,0.09465759812475742,0.385807949533644,0.3813215168753152,0.11571747415713927,0.09163974370325054,0.09799398349689716,0.38542890810426,0.7649951129266509,0.1613282673415262,0.36327041723060444,0.1438449720749867};

    inicializarRedPlaga(&red1, areas, 1);
//    asignarNodosYVecinos(&red1, numReds);
    // asignarAreas(&red1, areas);
    inicializarPlaga(&red1);
    actualizarRedPlaga(&red1, 1, T);
    printf("End\n");

    //for (deltaz = 0; deltaz <= -4  ; deltaz = deltaz - 1){


        // p1  = exp(-2.5)/ (1 + exp(-2.5));
        // p2  = exp(-1.8)/ (1 + exp(-1.8));
//        GHWS(30, 1000, 4, 1000, 1);

        // Red redM = {0,N,4,0.4,0.5};
        // inicializarRed(&redM);
        // cableadoInicial(&redM, 1);
        // recablearRed(&redM, 1);
        // generarEImprimirMatrizAdyacente(&redM, 1);
        // inicializarEstadosRed(&redM);
        // actualizarRed(&redM, 1, 100);
// ------------------------TEST FOR SIAM------------------------------------ //
  //       sigmaVector = malloc(30*sizeof(float));
  //       zVector = malloc(30*sizeof(float));
  //       values = fopen("values.dat","w");
  //       GHWS(30, 10000, 4, 1000, 1, sigmaVector, zVector);
  //       int contg = 0;
  //       for (int g = 10 ; g < 30; g++){
  //         int contz = 0;
  //         for (float dz = 0.5; dz > 0.001; dz /= 2){
  //           float z = zVector[g];
  //           float r = sigmaVector[g]/K;
  //           float z1 = z + dz;
  //           float z2 = z - dz;
  //           float p1 = exp(z1)/ (1 + exp(z1));
  //           float p2 =  exp(z2)/ (1 + exp(z2));
  //           printf("%f %f\n", p1, p2);
  //           Red red1 = {0,N,K,p2,r};
  //           Red red2 = {1,N,K,p1,r};
  //           inicializarRed(&red1);
  //           inicializarRed(&red2);
  //           inicializarMuestra(&red1, numReds);
  //           inicializarMuestra(&red2, numReds);
  //           recablearDosRedes(&red1,&red2,numConx,numReds,q);
  //           //printf("Pase Recableado\n");
  //           actividadRedes(&red1, &red2, numReds, T, contg, contz);
	// //          printf("Pase Actividad\n");
  //           liberarMemoria(&red1);
  //           liberarMemoria(&red2);
  //           fprintf(values, "%d %d %f %f %f\n",contg, contz, z, sigmaVector[g], dz  );
  //           contz += 1;
  //         }
  //         contg += 1;
  //       }
  //
  //       fflush(values);
  //       fclose(values);
// ------------------------TEST FOR SIAM------------------------------------ //

        // Red red1 = {0,N,K,p-deltap,r};
        // Red red2 = {1,N,K,p+deltap,r};
        // Red red1 = {0, N, K, 0.8, 0.4};
        // Red red2 = {1,N,K,0.9,0.8};

        //Inicializo las redes
//         inicializarRed(&red1);
//         inicializarRed(&red2);
//         printf("Putos todos");
//         inicializarMuestra(&red1, numReds);
// //        inicializarRedMuerta(&red1);
//
//         //actRed1 = actividadMuestra(&red1, T);
//         //printf("Actividad Red 1: %f \n", actRed1);
//
//
//
//
//         inicializarMuestra(&red2, numReds);
//         generarEImprimirMatrizAdyacente(&red1, numReds);
//         //printf("Actividad Red 2: %f \n", actRed2);
//         recablearDosRedes(&red1,&red2,numConx,numReds,q);
//         //generarEImprimirMatrizAdyacente(&red2, numReds);
//
//         actividadRedes(&red1, &red2, numReds, T, 1, 2);

 //   }
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
