#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "functions.h"


void asignarAreas(Nodo* nodos, int N, float lista[]){
  for (int i = 0; i < N; i ++){
    nodos[i].area = lista[i];
  }
}


void asignarVecinos(Nodo* nodos, int indice, int clase, int lista[], int numReds){
  int j;
  // Se asginan los vecinos correspondientes a un nodo
  for (j = 0; j < nodos[indice].k; j++){
    nodos[indice].cnx[j] = (lista[j]-1)*numReds + clase;
  }
}


void inicializarRedPlaga(Red* red, float areas[], int numReds){
    //invocamos al numero de cordinacion (numero de vecinos promedio) de la red
    int N = red -> N; //invocamos al numero de nodos de la red
    int clase = red -> id;
    //asignamos memoria a los nodos de la red
    Nodo* nodos = malloc(N*sizeof(Nodo));
    asignarAreas(nodos, N, areas);
    asignarNodosYVecinos(nodos, numReds, clase, N);
  for(int i=0;i<N;++i) {
      //asignamos memoria al arreglo de conexiones de cada nodo
      nodos[i].poblacion = 0.0;
      nodos[i].poblacionCrit = funcionCrecimiento(nodos, i, (1/nodos[i].area));
      printf("Nodo %d, PopCrit =%f\n", i, nodos[i].poblacionCrit );
  }
  red -> nodos = nodos;
}



void asignarNodosYVecinos(Nodo* nodos, int numReds, int clase, int N){
  int numVecinos; // numero de vecinos de un nodo
  int espacio = (N/2)*3;
  char strVecinos[espacio]; // string con los vecinos separado por comas
  int *vecinos; //array que contendra los vecinos temporales
  //Abro el archivo
  // printf("Abriendo el archivo");
  FILE *pf = fopen("Vecinos2.txt","r");
  // printf("abri el archivos");
  //Empiezo a iterar por cada linea
  for(int nodo=0; nodo<N; nodo++){

    //printf("Estoy en el nodo %d\n", nodo);
    fscanf(pf, "%d %s", &numVecinos, strVecinos);
    vecinos = str2array(strVecinos,numVecinos); //convierto el string separado por comas a un array
    // //Asigno los valores a la red
    nodos[nodo].k = numVecinos;
    nodos[nodo].cnx=malloc(numVecinos*sizeof(int));
    asignarVecinos(nodos, nodo, clase, vecinos, numReds);
    free(vecinos);
  }
  fclose(pf);
}


void evolucionPoblacion(Red* red, int i){
  Nodo* nodos = red -> nodos;
  nodos[i].poblacion = funcionCrecimiento(nodos, i, nodos[i].pasoEvol);
  nodos[i].pasoEvol += 1;
}



void actualizarRedPlaga(Red* red, int numReds, int T){
  /* Funcion que actualiza la red por T pasos
   */
  FILE *activos, *suceptibles;
  activos = fopen("infected.dat","w");
  suceptibles = fopen("suceptiblesI.dat","w");
  int pasos, i, t;
  int N = red -> N;
  float r = red -> r;

  for(pasos=0; pasos<T; ++pasos){
    for(i=0;i<N;++i){
      evolucionPoblacion(red, i);
      actualizarEstadoPlaga(red, i, numReds, r);
      imprimirNodoPlaga(red, i, activos, suceptibles);
      //printf("Nodo %i: %i\n",i, nodos[i].estadoAntiguo );
      }
    fprintf(activos, "\n");
    fprintf(suceptibles, "\n");
    correccionEstadosRed(red);
  }
  fflush(activos);
  fclose(activos);
  fflush(suceptibles);
  fclose(suceptibles);
}

void imprimirNodoPlaga(Red* red, int i, FILE *fileActives, FILE *fileSuceptibles){
    Nodo* nodos = red -> nodos;
    int N = red -> N;

  if(nodos[i].estadoActual==2){
    fprintf(fileActives,"%d ",i+1);
  }
  else if(nodos[i].estadoActual==2 && i==N-1){
    fprintf(fileActives, "%d",i+1 );
  }
  else if(nodos[i].estadoActual==1 && i==N-1) {
    fprintf(fileSuceptibles, "%d",i+1 );
  }
  else if(nodos[i].estadoActual==1){
    fprintf(fileSuceptibles, "%d ",i+1 );
  }
}



void actualizarEstadoPlaga(Red* red, int indice, int numReds, float probActivarse){
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
  case 0: if (proba < probActivarse){
      nodos[indice].estadoActual = 1;
  }
  break;
  case 1: if(vecinoZonaInfectada(red, indice, numReds))
          {nodos[indice].estadoActual = 2;
          }
          break;
  case 2: if(nodos[indice].poblacion < -0.3){
    nodos[indice].estadoActual = 0;
    nodos[indice].pasoEvol = 0;
    nodos[indice].poblacion = 0;
  }
  break;
}
}



bool vecinoZonaInfectada(Red* red, int indice, int numReds){
  int i;
  bool encontrado = false;
  Nodo* nodos = red -> nodos;
  int clase = red -> id;
  i = 0;
  while (!encontrado & i < nodos[indice].k){
    if (nodos[((nodos[indice].cnx[i]) - clase)/ numReds].estadoAntiguo == 2 && nodos[((nodos[indice].cnx[i]) - clase)/ numReds].poblacion >  nodos[((nodos[indice].cnx[i]) - clase)/ numReds].poblacionCrit ){
      encontrado = true;
    }
    i += 1;
  }
  return(encontrado);

}




float funcionCrecimiento(Nodo* nodos,int indice, int t){
  float area = nodos[indice].area;
  float funcion = (t*t)/2 - ((area * t*t*t )/5);
  nodos -> poblacion = funcion;
}


void inicializarPlaga(Red* red){
    /* Funcion que asigna estados de manera aleatoria a la red*/

    int i;
    int N = red -> N;
    Nodo* nodos = red -> nodos;
    for(i=0; i<N; ++i) {
      nodos[i].estadoAntiguo=0;
      nodos[i].estadoActual = nodos[i].estadoAntiguo;
      //printf("Nodo %i: %i\n",i, nodos[i].estadoAntiguo );
    }
    nodos[0].estadoAntiguo = 2;
    nodos[0].estadoActual = nodos[0].estadoAntiguo;
}





int* str2array(char* strVecinos,int numVecinos){
  //Como los valores estan separados por comas hago un split por comas
  //y asignos los valoes al arreglo vecinos
  int * vecinos = malloc(numVecinos*sizeof(int));
  char *tokenVecino = strtok(strVecinos, ",");
  for(int i=0;i<numVecinos;i++){
      int numero = atoi(tokenVecino);
      vecinos[i] = numero;
      tokenVecino = strtok(NULL, ",");
    }
  return vecinos;
}
