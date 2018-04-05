/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "structs.h"
#include "functions.h"

extern nodo red[];

float criticalProbAct(int K, float probRecableado, int T){
  int n,maxNumberOfBisections;
  float minOfInterval,maxOfInterval,minOfProbAct,maxOfProbAct,critProbAct,Fmin,F,Fmax;

  inicializarMuestra(K, probRecableado);

  maxNumberOfBisections = 9;         // para cada r nuevas condiciones iniciales y nuevo cableado
  minOfInterval = 1;
  maxOfInterval = 5;
  minOfProbAct = minOfInterval/K;
  maxOfProbAct = maxOfInterval/K;
  Fmin = actividadMuestra(minOfProbAct, T);
  Fmax = actividadMuestra(maxOfProbAct, T);
  //printf("Fmin = %f \t Fmax = %f\n", Fmin, Fmax );
  for(n = 0; n < maxNumberOfBisections; ++n){ // resolucion en rc
    critProbAct = 0.5*(minOfProbAct + maxOfProbAct);
    F=actividadMuestra(critProbAct, T);
    if((F*Fmax) == 0){ minOfProbAct=critProbAct; Fmin = F; } else{ maxOfProbAct = critProbAct; Fmax = F; }
  }
  return(critProbAct);
  liberarMemoria();
}

void actualizarEstadoNodo(int nodo,float probActivarse){
  int estadoNodo = red[nodo].estadoAntiguo;
  float proba = prob();
  //printf("Nodo Activo : %i \t probabilidadActivarse : %i \n",algunVecinoActivo(nodo), prob()< probActivarse );
  switch(estadoNodo){
  case 0: red[nodo].estadoActual = 1; break;
  case 1: if(algunVecinoActivo(nodo)&&(proba < probActivarse))
          {red[nodo].estadoActual = 2;
          }
          break;
  case 2: red[nodo].estadoActual = 0; break;
  }
}

void actualizarRed(float probActivarse, int T){
  int pasos, i;

  for(pasos=0; pasos<T; ++pasos){
    for(i=0;i<N;++i){
      actualizarEstadoNodo(i,probActivarse);
      }
    correccionEstadosRed();
  }
}

bool algunVecinoActivo(int nodo){
  int i;
  bool encontrado = false;

  while (!encontrado & i < red[nodo].k){
    if (red[red[nodo].cnx[i]].estadoAntiguo == 2){
      encontrado = true;
    }
    i += 1;
  }
  return(encontrado);
}

void inicializarMuestra(int K, float probRecableado){
  inicializarRed(K);
  cableadoInicial(K);
  recableadoRed(probRecableado, K);
}

float actividadRed(void){
  int i, Activos = 0;
  for(i=0;i<N;++i) if(red[i].estadoActual==2) ++Activos;
  return((float)Activos/N);
}

void inicializarEstadosRed(){
  int i;
  for(i=0; i<N; ++i) {
  red[i].estadoAntiguo=rand()%3;
  red[i].estadoActual = red[i].estadoAntiguo;
  //printf("Nodo %i: %i\n",i, red[i].estadoAntiguo );
  }
}

float actividadMuestra(float probActivarse, float T){
  float actividad;
  inicializarEstadosRed();
  //imprimirRed();
  actualizarRed(probActivarse, T);
  actividad = actividadRed();
  return(actividad);
  // liberarMemoria();
}

void correccionEstadosRed( void ){
  int i;
  for(i=0;i<N;++i){
      red[i].estadoAntiguo = red[i].estadoActual;
  }
}