#include <stdbool.h>
#include <stdlib.h>
#include "structs.h"




int generarNodoAleatorio(int indiceConvertido, int N, int numReds, int clase, Nodo nodo){
  int j, numNodo;
  bool encontrado = false;
  while(!encontrado){
    numNodo = (rand()%N)*numReds+clase;
    if(numNodo != indiceConvertido){
      for(j=0;j<nodo.k;++j){
          if(numNodo ==nodo.cnx[j]){
              encontrado = true;
              break;
          }
      }
      if(j == nodo.k) encontrado = true;
    }
  }
  return(numNodo-clase)/numReds; //Regresa la posicion del nodo de en arreglo de nodos
}

void sumarLink(int indiceConvertido ,Nodo* nodoNuevo){
    nodoNuevo -> k += 1;
    nodoNuevo -> cnx=realloc(nodoNuevo -> cnx,(nodoNuevo -> k)*sizeof(int));
    nodoNuevo -> cnx[(nodoNuevo -> k)-1]=indiceConvertido;
}

int encontrarEnVecino(int indiceConvertidoActual, Nodo nodo){
  int k;
  for(k=0;k<nodo.k;++k)if(nodo.cnx[k]==indiceConvertidoActual) break;
  return(k);
}

void swapYQuitarLink(Nodo* nodo, int viejaConexion){
    //Swap
    int last = (nodo -> k)-1;
    (nodo->cnx)[viejaConexion]=(nodo->cnx)[last];
    
    //Quitar
    (nodo->k) -= 1;
    nodo -> cnx=realloc(nodo->cnx,(nodo->k)*sizeof(int));
  
}


