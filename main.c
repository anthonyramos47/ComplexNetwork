/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: zoso
 *
 * Created on 4 de abril de 2018, 17:16
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "functions.h"
#include "structs.h"

#define N 10 // numero de nodos

//int N = 1000;
nodo red[N];
/*
 *
 *  
 */
int main(int argc, char** argv) {
    
  /* Program to Run a small wolrd network with the GH method with different
  probabilities of disorder from [0 - 1], several K, wich represents the number of neighbors for
  each node of the network , several T and
  for each (prob, K and T) it is run a max of 30 samples with this conditions
  and it is measure the activity of each network
   .*/

  int K, numMuestra, numMuestraMax, T, i, Kmax;
  float probRecableado, x, promCritialProbAct, z, probActivarse;
  
  
  /*
  K ,- Numero de vecinos de cada nodo
  numMuestra ,- numero de la muestra
  numMuestraMax ,- Numero de Muestra Maximo
  T ,- Numero de pasos
  Kmax .- Numero de vecinos Maximo
  probRecableado ,- it is the probabability that a node to be reconected
  x ,- it is a variable that help us to extend the domain of probability from
  [  0 - 1 ] to [ 1 , +infinity ]
  z ,- it is a variable that help us to pas the probability from [1, infinity]
  to [- infinity, +infinity]
  critialProbAct, is the critical transmition probability that multiplied by the number
    of neighbors it gives the sigma or coupling of the network
  promCritialProbAct,- is the mean of the critical transmition probablity
  */

  char archivoDatos[99];
  // Chain of character that allow us to print several files

  FILE *archivoSalida;

  time_t t;

  numMuestraMax = 30;
  // The max of samples that we run in order to obtain a mean of the critical
  // probability of activation

  Kmax = 5;  // We define the maximum number of neighbors

  srand(t);


  for(T=100; T<120; T*=10){
    // We will run for three different maximum number of iterations 100, 1000, 10000

    for(K = 4; K < Kmax; K *= 2){
      // We also run for each maximum number of iterations different number of
      // neighbors 4,8,16,32

      sprintf(archivoDatos, "GHWS_sigmaVSz_N%d_K%d_M%d_T%d_.dat", N, K, numMuestraMax, T);
      archivoSalida=fopen(archivoDatos, "w");

      for(x = 10000; x > 0.00001; x /= 2){
        // This x value allow us to spread the probability from 0-1 to  -infinity to infinity

        probRecableado = x/(1+x);
        // This is a inverse function to obtain the probability given an x

        z = log(x); 
        //z=5;
        
        promCritialProbAct = 0;
        // We initialize the mean value of the critical probability of activation
        // this is realted with the sigma value wich is the CPA(critical probability of activation)
        // CPA * K = sigma, which is plotted

        for(numMuestra = 0; numMuestra < numMuestraMax; ++numMuestra){

          // In order to obtain a good value for the CPA we compute the mean
          // by running 30 samples of the network and computing the activity
          // for each one

          promCritialProbAct+=criticalProbAct(K,probRecableado,T);
        }

        promCritialProbAct /= numMuestraMax;
        fprintf(archivoSalida, "%f %f\n", z, K*promCritialProbAct);

      }

      fclose(archivoSalida);

    }
  }
    return (EXIT_SUCCESS);
}

