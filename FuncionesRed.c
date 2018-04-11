#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "functions.h"



void imprimirRed(Red* red, int numReds){
  int N = red -> N; //invocamos al numero de nodos de la red
  int clase = red -> id; //invocamos a la clase de la red
  Nodo* nodos = red -> nodos; //invocamos al arreglo de nodos de la red
  
  printf("\n Red %d:\n", clase);
  for(int i = 0; i < N; i++){
    //modificamos la variable "i" para convertirla en el indice correcto 
    //respecto al numero de redes y a la propia red
    printf("Nodo %d: ",i*numReds+clase);
    for(int j=0;j<nodos[i].k;j++){
        printf( " -> %d",nodos[i].cnx[j]); 
    }
    printf("--!\n");
  }
}

/*
With this procedure we put all the properties of each node and also we
allocate the memory that each node requier for the vector of conections With
their neighbors
*/
void inicializarRed(Red* red){
    //invocamos al numero de cordinacion (numero de vecinos promedio) de la red
    int K = red -> K; 
    int N = red -> N; //invocamos al numero de nodos de la red
  
    //asignamos memoria a los nodos de la red
    Nodo* nodos = malloc(N*sizeof(Nodo)); 
                                                            
  for(int i=0;i<N;++i) {
      //asignamos memoria al arreglo de conexiones de cada nodo
      nodos[i].cnx = malloc(K*sizeof(int)); 
      nodos[i].k = K;
  }
  red -> nodos = nodos;
}

  /* function that create the initial ordered connections of the network
  putting for each node half of the neighbors to the rigth and half to the left
  */
void cableadoInicial(Red* red, int numReds){
    int N = red -> N;
    int K = red -> K;
    //obtenemos el id de la red que corresponde a la clase modulo a la que 
    //corresponde
    int clase = red -> id; 
    Nodo* nodos = red -> nodos; //invocamos a los nodos de la red
    for(int i=0;i<N;++i){
        for(int j=-K/2; j<0; ++j){
            //asignamos los valores de las conexiones de los K vecinos mas 
            //proximos. K/2 estan en direccion antohoraria y los restantes K/2 
            //en direccion horaria. Los valores estan convertidos a notacion 
            //modular
            nodos[i].cnx[(K/2)+j]=((N+(i+j))%N)*numReds+clase;
            nodos[i].cnx[(K/2)-j-1]=((i-j)%N)*numReds+clase;
      }
    }
}

void recablearRed(Red* red, int numReds){
    
    //Obtenemos los parametros de la red
    int N = red -> N;
    int K = red -> K;
    float probRec = red -> p;
    int clase = red -> id;
    Nodo* nodos = red -> nodos;;
    //--
    
    //Son variables auxiliares
    int nuevo, idxViejoM, idxActualM, idxViejoP;

    //Iteramos sobre cada nodo
    for(int i= N-1;i>=0;--i){
        //Iteramos sobre la mitad de las conexiones de los nodos
        for(int j=0;j<K/2;++j){
            if(prob()<probRec){ //Preguntamos si el nodo se recableará
                //Convertimos el indice "i" al respectivo valor modular
                idxActualM = i*numReds+clase;
                //Se obtiene el indice posicional del nodo nuevo
                nuevo = generarNodoAleatorio(idxActualM, N, numReds, clase, nodos[i]);
                //Añade el indice modular actual al nuevo nodo
                sumarLink(idxActualM, &nodos[nuevo]);
                //Obtenemos el indice posicional del vecino j
                idxViejoP = (nodos[i].cnx[j] - clase)/numReds;
                //Dados dos nodos i y j, se halla el indice posicional donde se 
                //encuentra el nodo i en el arreglo de conexiones del nodo j 
                idxViejoM = encontrarEnVecino(i,nodos[idxViejoP]);
                //Corrige el arreglo de conexiones del nodo j
                swapYQuitarLink(&nodos[idxViejoP], idxViejoM);
                //Se asigna la nueva conexion al nodos i
                nodos[i].cnx[j]=nuevo*numReds+clase;
            }
        }
    }
}

void recablearNodo(){
    
}





/*
 
 void recablearRed(Red* red, int numReds){
    
    //Obtenemos los parametros de la red
    int N = red -> N;
    int K = red -> K;
    float probRec = red -> p;
    int clase = red -> id;
    Nodo* nodos = red -> nodos;;
    //--
    
    //Son variables auxiliares
    int nuevo, indiceVecino, idxActual, posicionVecino;

    //Iteramos sobre cada nodo
    for(int i= N-1;i>=0;--i){
        //Iteramos sobre la mitad de las conexiones de los nodos
        for(int j=0;j<K/2;++j){
            if(prob()<probRec){ //Preguntamos si el nodo se recableará
                //Convertimos el indice "i" al respectivo valor modular 
                idxActual = i*numReds+clase;
                
                recablearNodo(idxActual)
            }
        }
    }
}

void recablearNodo(int idxActual, int idxViejo, int idxNuevo, Nodo* nodoActual, Nodo* nodoViejo, Nodo* nodoNuevo){
    //Se obtiene el indice posicional del nodo nuevo
    nuevo = generarNodoAleatorio(idxActual, N, numReds, clase, nodos[i]);
    //Añade el indice modular actual al nuevo nodo
    sumarLink(idxActual, &nodos[nuevo]);
    //Obtenemos el indice posicional del vecino j
    posicionVecino = (nodos[i].cnx[j] - clase)/numReds;
    //Dados dos nodos i y j, se halla el indice posicional donde se 
    //encuentra el nodo i en el arreglo de conexiones del nodo j 
    indiceVecino = encontrarEnVecino(i,nodos[posicionVecino]);
    //Corrige el arreglo de conexiones del nodo j
    swapYQuitarLink(&nodos[posicionVecino], indiceVecino);
    //Se asigna la nueva conexion al nodos i
    nodos[i].cnx[j]=nuevo*numReds+clase;
}
 
 
 */