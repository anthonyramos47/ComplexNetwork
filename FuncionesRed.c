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

//extern int N;
extern nodo red[];

void cableadoInicial(int K){
  int i,j;
  /* function that create the initial ordered connections of the network
  putting for each node half of the neighbors to the rigth and half to the left
   */
  for(i=0;i<N;++i){
    for(j=-K/2; j<0; ++j){
      red[i].cnx[(K/2)+j]=((N+(i+j))%N);
      red[i].cnx[(K/2)-j-1]=((i-j)%N);
    }
  }
}

void inicializarRed(int K){
  int i;
  /*
  With this procedure we put all the properties of each node and also we
  allocate the memory that each node requier for the vector of conections With
  their neighbors
  */
  for(i=0;i<N;++i) {
    red[i].cnx=malloc(K*sizeof(int)); // asignación de memoria inicial
    red[i].k=K;
  }
}

void sumarLink(int i,int new){
  ++red[new].k;
  red[new].cnx=realloc(red[new].cnx,red[new].k*sizeof(int));
  red[new].cnx[red[new].k-1]=i;
}

void quitarLink(int i){
  --red[i].k;
   red[i].cnx=realloc(red[i].cnx,red[i].k*sizeof(int));
}

void recableadoRed(float probRecableado, int K){
  int i, j, nuevo, indiceVecino, cont;

  for(i=N-1;i>=0;--i){
    for(j=0;j<K/2;++j){
      if(prob()<probRecableado){
      	nuevo = nuevoNodo(i);
      	sumarLink(i, nuevo);
      	indiceVecino = encontrarVecino(i,red[i].cnx[j]);
      	swap(red[i].cnx[j], indiceVecino);
      	quitarLink(red[i].cnx[j]);
      	red[i].cnx[j]=nuevo;
      }
      else{++cont;}
    }
  }

}

int encontrarVecino(int i, int j){
  int k;
  for(k=0;k<red[j].k;++k)if(red[j].cnx[k]==i) break;
  return(k);
}

int nuevoNodo(int i){
  int ver, j, nodo;
  bool booleano = false;
  while(!booleano){
    nodo = rand()%N;
    if(nodo != i){
      for(j=0;j<red[i].k;++j){if(nodo ==red[i].cnx[j]) break;}
      if(j == red[i].k) booleano = true;
    }
  }
  return(nodo);
}

void imprimirRed(){
  int i;
  for(i=0; i<N; ++i){
    printf("Nodo :%i \t ActividadActual: %i \t ActividadAntigua: %i \n",i, red[i].estadoActual, red[i].estadoAntiguo );
  }

}

float prob(void){
  return ((float)rand()/RAND_MAX);
}
