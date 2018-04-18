/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "functions.h"

/*
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
} */

void actualizarEstadoNodo(Red* red, int indice, int numReds, float probActivarse){ 
    /* Funcion  que actualiza el estado del nodo. Siguiendo la sigueinte
     dinamica. 0, denota apagado; 1, denota suceptible; 2 denota activo.
     Si el nodo esta en estado 0 pasa a estado 1
     Si el nodo esta en estado 1, con probabilidad r y si alguno de sus vecinos
     esta activo. Entonces pasa a estado 2. Sino permanece en estado 1
     Si el nodo esta en estado 2 pasa a estado 0*/
  Nodo* nodos = red -> nodos;  
  int estadoNodo = nodos[indice].estadoAntiguo;
  float proba = prob();
  //printf("Nodo Activo : %i \t probabilidadActivarse : %i \n",algunVecinoActivo(nodo), prob()< probActivarse );
  switch(estadoNodo){
  case 0: nodos[indice].estadoActual = 1; break;
  case 1: if(algunVecinoActivo(red, indice, numReds) && (proba < probActivarse))
          {nodos[indice].estadoActual = 2;
          }
          break;
  case 2: nodos[indice].estadoActual = 0; break;
  }
}

bool algunVecinoActivo(Red* red, int indice, int numReds){
  /* Funcion que determina si exista al menos un vecino
   * activo en el nodo que se especifica
   */
  int i;
  bool encontrado = false;
  Nodo* nodos = red -> nodos;
  int clase = red -> id;
  i = 0;
  while (!encontrado & i < nodos[indice].k){
    if (nodos[((nodos[indice].cnx[i]) - clase)/ numReds].estadoAntiguo == 2){
      encontrado = true;
    }
    i += 1;
  }
  return(encontrado);
}

// FUNCIONES PARA EL RECABLEADO ENTRE REDES //

void actualizarEstadoNodoRedes(Red* red, Red* red2, int indice, int numReds, float probActivarse){ 
    /* Funcion  que actualiza el estado del nodo. Siguiendo la sigueinte
     dinamica. 0, denota apagado; 1, denota suceptible; 2 denota activo.
     Si el nodo esta en estado 0 pasa a estado 1
     Si el nodo esta en estado 1, con probabilidad r y si alguno de sus vecinos
     esta activo. Entonces pasa a estado 2. Sino permanece en estado 1
     Si el nodo esta en estado 2 pasa a estado 0*/
  Nodo* nodos = red -> nodos;  
  int estadoNodo = nodos[indice].estadoAntiguo;
  float proba = prob();
  //printf("Nodo Activo : %i \t probabilidadActivarse : %i \n",algunVecinoActivo(nodo), prob()< probActivarse );
  switch(estadoNodo){
  case 0: nodos[indice].estadoActual = 1; break;
  case 1: if(algunVecinoActivoRedes(red, red2, indice, numReds) && (proba < probActivarse))
          {nodos[indice].estadoActual = 2;
          }
          break;
  case 2: nodos[indice].estadoActual = 0; break;
  }
}


bool algunVecinoActivoRedes(Red* red, Red* red2,int indice, int numReds){
  /* Funcion que determina si exista al menos un vecino
   * activo en el nodo que se especifica red corresponde a la red donde estamos
   * actualizando los estados
   */
  int i;
  bool encontrado = false;
  Nodo* nodos1 = red -> nodos;
  Nodo* nodos2 = red -> nodos;
  int clase1 = red -> id;
  int clase2 = red2 -> id;
  i = 0;
  while (!encontrado & i < nodos1[indice].k){
      if (nodos1[indice].cnx[i]%numReds == clase1){
        if (nodos1[((nodos1[indice].cnx[i]) - clase1)/ numReds].estadoAntiguo == 2){
          encontrado = true;
        }
      }
      else{
          if (nodos2[((nodos1[indice].cnx[i]) - clase2)/ numReds].estadoAntiguo == 2){
          encontrado = true;
          }
      }
    i += 1;
  }
  return(encontrado);
}

//Funcion Super Red
void actividadRedes(Red* red, Red* red2, int numReds, float T){
  /*Funcion que mide la actividad de determinada Muestra
   */
  float actividad1, actividad2;
  int paso;
  FILE *fileRed1, *fileRed2;
  FILE *activos1, *activos2, *suceptibles1, *suceptibles2;
  inicializarEstadosRed(red);
  inicializarEstadosRed(red2);
  fileRed1 = fopen("ActividadRed1","w");
  fileRed2 = fopen("ActividadRed2","w");
  //imprimirRed();
  activos1 = fopen("activos.dat","w");
  suceptibles1 = fopen("suceptibles.dat","w");
  
  activos2 = fopen("activos2.dat","w");
  suceptibles2 = fopen("suceptibles2.dat","w");
  
  for(paso = 0; paso < T; ++paso){
      
        actualizarRedPaso(red, red2, numReds, activos1, suceptibles1);
        actualizarRedPaso(red2, red, numReds, activos2, suceptibles2);
        
        correccionEstadosRed(red);
        correccionEstadosRed(red2);
        
        actividad1 = actividadRed(red);
        actividad2 = actividadRed(red2);
        fprintf(fileRed1,"%d \t %f\n", paso, actividad1);
        fprintf(fileRed2,"%d \t %f\n", paso, actividad2);
        
  }
  fclose(fileRed1);
  fclose(fileRed2);
  // liberarMemoria();
}

void actualizarRedPaso(Red* red, Red* red2, int numReds, FILE *activos, FILE *suceptibles){
  /* Funcion que actualiza la red 
   */
  int i;
  int N = red -> N;
  float r = red -> r;
  int id = red -> id;
  
  
  for(i=0;i<N;++i){
    actualizarEstadoNodoRedes(red, red2, i, numReds, r);
    colorearNodo(red, i, activos, suceptibles);
    //printf("Nodo %i: %i\n",i, nodos[i].estadoAntiguo );
    }
  fprintf(activos, "\n");
  fprintf(suceptibles, "\n");
}



// FUNCIONES PARA EL RECABLEADO ENTRE REDES //


void actualizarRed(Red* red, int numReds, int T){
  /* Funcion que actualiza la red por T pasos
   */
  int pasos, i;
  int N = red -> N;
  float r = red -> r;
  for(pasos=0; pasos<T; ++pasos){
    for(i=0;i<N;++i){
      actualizarEstadoNodo(red, i, numReds, r);
      //printf("Nodo %i: %i\n",i, nodos[i].estadoAntiguo );
      }
    correccionEstadosRed(red);
  }
}

void correccionEstadosRed(Red* red){
  /*Funcion que corrige los estados de la red*/
    
  int i;
  Nodo* nodos = red -> nodos;
  int N = red -> N;
  for(i=0;i<N;++i){
      nodos[i].estadoAntiguo = nodos[i].estadoActual;
  }
}



void inicializarMuestra(Red* red, int numReds){
  /* Funcion que inicializa, cablea y recablea una red */
    
  inicializarRed(red);
  cableadoInicial(red, numReds);
  recablearRed(red, numReds);
}

float actividadRed(Red* red){
  /* Funcion que mide la actividad de la red al contar 
   * cuantos nodos activos hay y dividirlo para el numero
   * total de nodos */
    
  int i, Activos = 0;
  int N = red -> N;
  Nodo* nodos = red -> nodos; 
  
  for(i=0;i<N;++i){
      if(nodos[i].estadoActual==2){ 
        Activos += 1;
        }
  }
  return((float)Activos/N);
}

void inicializarEstadosRed(Red* red){
  /* Funcion que asigna estados de manera aleatoria a la red*/
    
  int i;
  int N = red -> N;
  Nodo* nodos = red -> nodos;
  for(i=0; i<N; ++i) {
  nodos[i].estadoAntiguo=rand()%3;
  nodos[i].estadoActual = nodos[i].estadoAntiguo;
  //printf("Nodo %i: %i\n",i, nodos[i].estadoAntiguo );
  }
}

float actividadMuestra(Red* red, int numReds, float T){
  /*Funcion que mide la actividad de determinada Muestra
   */
  float actividad;
  inicializarEstadosRed(red);
  //imprimirRed();
  actualizarRed(red, numReds, T);
  actividad = actividadRed(red);
  return(actividad);
  // liberarMemoria();
}




void liberarMemoria(Red* red){
  /* Funcion que limpia las conexiones de los nodos*/
  int i;
  int N = red -> N;
  Nodo* nodos = red -> nodos;
  for(i=0;i<N;++i) free(nodos[i].cnx);
}

void imprimir(Red* red, int i){
   /* Funcion que imprime las conexiones de un nodo i
   */
  int j;
  Nodo* nodos = red -> nodos;
  
  printf("Nodo: %i\t",i );
  for(j=0;j<nodos[i].k;++j) printf( "\t%d",nodos[i].cnx[j]); printf("\n");
}




void colorearNodo(Red* red, int i, FILE *fileActives, FILE *fileSuceptibles){
    Nodo* nodos = red -> nodos;
    int N = red -> N;
    
  if(nodos[i].estadoActual==2){
    fprintf(fileActives,"%d->Green ",i+1);
  }
  else if(nodos[i].estadoActual==2 && i==N-1){
    fprintf(fileActives, "%d->Green",i+1 );
  }
  else if(nodos[i].estadoActual==1 && i==N-1) {
    fprintf(fileSuceptibles, "%d->Red",i+1 );
  }
  else if(nodos[i].estadoActual==1){
    fprintf(fileSuceptibles, "%d->Red ",i+1 );
  }
}


void generarEImprimirMatrizAdyacente(Red* red, int numReds){
  int N = red -> N;
  Nodo* nodos = red -> nodos;
  int matriz[N][N];
  
  int k, m;
  for (k = 0; k<N; k++)
    {
    for (m = 0; m<N; m++)
        matriz[k][m] = 0;
    }
  
  int clase = red -> id;
  FILE *MatrizAdyacente;

  for (int i = 0; i<N; i++){
      for(int j =0; j < nodos[i].k; j++){
          matriz[i][(nodos[i].cnx[j] - clase) / (numReds)] = 1;
     }
  }
  
  MatrizAdyacente = fopen("MatrizAdyacente.dat","w");

  for(int i = 0; i<N; i++){
    for(int j = 0; j<N; j++) fprintf(MatrizAdyacente, "%d ", matriz[i][j]);
    fprintf(MatrizAdyacente, "\n");

  }

  fflush(MatrizAdyacente);
  fclose(MatrizAdyacente);
}
