#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "functions.h"


void GHWS(int maxMuestra, int T, int K, int N, int numReds, float *sigma, float *zV){
  FILE *archivoSalida;
  char archivoDatos[99];
  float probRecableado, promCritialProbAct, x;

  sprintf(archivoDatos, "GHWS_N%d_K%d_T%d.dat", N, K, T);
  archivoSalida = fopen(archivoDatos,"w");
  int cont = 0;
  for(x = 10000; x > 0.00001; x /= 2){
    probRecableado = x/(1+x);
    float z = log(x);
    promCritialProbAct = runMuestras(maxMuestra, N, K, probRecableado, T, numReds);
    fprintf(archivoSalida, "%f %f\n", z, promCritialProbAct);
    zV[cont] = z;
    sigma[cont] = K*promCritialProbAct;
    printf("%f %f\n", zV[cont], sigma[cont] );
    cont += 1;
  }
  fclose(archivoSalida);
}


float runMuestras(int maxMuestra, int N, int K, float probRec, int T, int numReds){
  float promCritialProbAct = 0;

  for(int numMuestra = 0; numMuestra < maxMuestra; ++numMuestra){
    // In order to obtain a good value for the CPA we compute the mean
    // by running 30 samples of the network and computing the activity
    // for each one

    promCritialProbAct+=criticalProbAct(N, K, probRec, T, numReds);
  }

  promCritialProbAct /= maxMuestra;
  return promCritialProbAct;
}

// crear funcion para modificar probabilidad de activacion

void cambiarProbAct(Red* red, float r){
  red -> r = r;
}


float criticalProbAct(int N, int K, float probRecableado, int T, int numReds){
  int n,maxNumberOfBisections;
  float minOfInterval,maxOfInterval,minOfProbAct,maxOfProbAct,critProbAct,Fmin,F,Fmax;

  maxNumberOfBisections = 9;         // para cada r nuevas condiciones iniciales y nuevo cableado
  minOfInterval = 1;
  maxOfInterval = 5;
  minOfProbAct = minOfInterval/K;
  maxOfProbAct = maxOfInterval/K;
  Red red = {0, N, K, probRecableado, 0};
  inicializarMuestra(&red, numReds);
  cambiarProbAct(&red, minOfProbAct);
  Fmin = actividadMuestra(&red, numReds, T);
  cambiarProbAct(&red, maxOfProbAct);
  Fmax = actividadMuestra(&red, numReds, T);
  //printf("Fmin = %f \t Fmax = %f\n", Fmin, Fmax );
  for(n = 0; n < maxNumberOfBisections; ++n){ // resolucion en rc
    critProbAct = 0.5*(minOfProbAct + maxOfProbAct);
    cambiarProbAct(&red, critProbAct);
    F=actividadMuestra(&red, numReds, T);
    if((F*Fmax) == 0){ minOfProbAct=critProbAct; Fmin = F; } else{ maxOfProbAct = critProbAct; Fmax = F; }
  }
  return(critProbAct);
  liberarMemoria(&red);
}
