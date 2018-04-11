#include <stdbool.h>

#include "structs.h"

void recablearDosRedes(Red* red1, Red* red2, int numCnxs, int numReds, int N){
    int rndNods = {7,37,47,31,13,131,141,83,139,151,2};
    int indiceConvertido2, idxNodoR1_P, idxNodoR2_P, kNodoRed2, kNodoRed1, idxNodoRecablearR1_P, idxNodoR1_M, idxNodoR2_M, idxNodoRecablearR1_M ;
    int posicionRecablearNodoR1;
    // La _P denota indices posicionales y _M indices modulares
    Nodo* nodos2 = red2 -> nodos; // obtenemos los nodos de la red 2
    Nodo* nodos1 = red1 -> nodos; // obtenemos los nodos de la red 1
    int claseR1 = red1 -> id;
    int claseR2 = red2 -> id;
    for (int i = 0; i < numCnxs; i++){
        idxNodoR1_P = rndNods[i]; // elejimos un nodo aleatorio de la red 1
        idxNodoR1_M = idxNodoR1_P*numReds + claseR1; // Modularizamos el nodo posicional de la red1
        
        // Obtenemos de manera aleatoria y verificando que no se encuentre en nodo de la red 1, la posicion de un nodo de la red 2
        idxNodoR2_P = generarNodoAleatorioRedes(nodos1, red2, numReds, idxNodoR1_P, N); 
        // Modularizamos el nodo de la red 2
        idxNodoR2_M = idxNodoR2_P * numReds + claseR2; 
        
        kNodoRed2 = nodos2[idxNodoR2_P].k + 1; // obtenemos el k a preservar de la red 2
        idxNodoRecablearR1_P = generarNodoAleatorio( idxNodoR1_M, N, numReds, claseR1, nodos1[idxNodoR1_P]); // obtenemos un nodo aleatorio a recablear de la red1
        idxNodoRecablearR1_M = idxNodoRecablearR1_P * numReds + claseR1 ; // Modularizamos el indice del nodo a recablear
        posicionRecablearNodoR1 = encontrarEnVecino(idxNodoRecablearR1_M, nodos1[idxNodoR1_P]);
        kNodoRed1 = nodos1[(nodos1[idxNodoRecablearR1_P]-claseR1)/ numReds].k - 1 ; // obtenemos el k a preservar de la red 1
        
        // recableamos estos nodos
        recablearNodo(idxNodoR1_M, idxNodoR1_P, idxNodoR2_M, posicionRecablearNodoR1, &nodos2[idxNodoR2_P], &nodos1[idxNodoRecablearR1_P], &nodos1[idxNodoR1_P]);                 
    }       
} 


int generarNodoAleatorio(int indiceConvertido, int N, int numReds, int clase, Nodo nodo){
  int j, numNodo;
  bool encontrado = false;
  while(!encontrado){
    numNodo = (rand()%N)*numReds+clase;
    if(numNodo != indiceConvertido){
      for(j=0;j<nodo.k;++j){
          if(numNodo ==nodo.cnx[j]) {
             break;
          }
      }
      if(j == nodo.k) encontrado = true;
    }
  }
  return(numNodo-clase)/numReds; //Regresa la posicion del nodo de en arreglo de nodos
}



void correccionRecableado(int k1, int k2, Red* red1, Red* red2, int N, int numReds, int idxExcluidoR1_P, int idxExcluidoR2_P){
    int idxNodoR1_P, idxAuxR2_P, idxRecableadoR2_P, idxNodoR2_P, idxNodoR1_M, idxNodoR2_M, idxRecableadoR2_M, indicesR2, idxAuxR2_M ;
    int posicionRecableadoR2;
    
    Nodo* nodos1 = red1 -> nodos;
    Nodo* nodos2 = red2 -> nodos;
    
    int clase1 = red1 -> id;
    int clase2 = red2 -> id;
    // Obtenemos la posicion del nodo que conserva k de la red 1
    idxNodoR1_P = generarNodoK(k1, red1, N, idxExcluidoR1_P);
    // Modularizamos el nodo que conserva k en la red 1
    idxNodoR1_M = idxNodoR1_P * numReds + clase1;
    
    // Obtenemos la posicion del nodo que conserva k de la red 2
    idxRecableadoR2_P = generarNodoK(k2, red2, N, idxExcluidoR2_P); 
    // Modularizamos la posicion del nodo que conserva k de la red 2
    idxRecableadoR2_M = idxAuxR2_P * numReds + clase2;
    
    /* Obtenemos el indice modular del nodo que tiene como vecino 
     * el nodo que conserva k de la red 2 */
    idxNodoR2_M = indiceAleatorioConexion(red2, idxRecablearR2_P, numReds);
    // Obetenemos la posicion del nodo que tienee como vecino el nodo que conserva
    // k de la red 2
    idxNodoR2_P = encontrarEnVecino();
    
    // Denotemos como NR2 al nodo a recablear (conserva k en red 2), entonces
    // obtenemos la posicion de NR2 en el nodo que lo tiene como vecino
    posicionRecableadoR2 =  encontrarEnVecino(idxAuxR2_M, nodos2[idxNodoR2_P]);
    
      
    recablearNodo(idxNodoR2_M, idxNodoR2_P, idxNodoR1_M, posicionRecableadoR2, &nodos1[idxNodoR1_P], &nodos2[idxRecableadoR2_P], &nodos2[idxNodoR2_P]);                 
    
}



void recablearNodo(int idxActualM, int idxElimP, int idxNuevoM, int idxNodoRecaP, Nodo* nuevoNodo, Nodo* viejoNodo, Nodo nodoRecablear){
                //Añade el indice modular actual al nuevo nodo
                sumarLink(idxActualM, nuevoNodo);
                //Corrige el arreglo de conexiones del nodo j
                swapYQuitarLink(viejoNodo, idxElimP);
                //Se asigna la nueva conexion al nodo i
                nodoRecablear.cnx[idxNodoRecaP]=idxNuevoM;
}

int encontrarEnVecino(int indiceConvertidoActual, Nodo nodo){
  int k;
  for(k=0;k<nodo.k;++k)if(nodo.cnx[k]==indiceConvertidoActual) break;
  return(k);
}

int indiceAleatorioConexion(Red* red, int idxNodo, int numReds){
    int maxIdx, rndIdx, idxAleatorio;
    
    int clase = red -> id;
    Nodo* nodos = red -> nodos;
    maxIdx = nodos.k; // obtenemos un maximo indice de vecinos del nodo
   
    // generamos un indice aleatorio que indica la posicion del vecino del nodo
    // en el arreglo de conexciones
    rndIdx = rand()%maxIdx ;
    
    idxAleatorio = nodos.cnx[rndIdx]; //Obtenemos le indice modular de la conexion
    
    return idxAleatorio;
    
    
}


int generarNodoK(int k1, Nodo* nodos, int N, int idxNodoExcluido){
    int i;
    bool encontrado = false;
    while(i < N && !encontrado){
        if(nodos[i].k == k1 && i!= idxNodoExcluido){
            encontrado = true;
        }
        else{
            i +=1;
        }   
    }
    if (!encontrado){
        i = idxNodoExcluido;
    }
    return i;
}


int generarNodoAleatorioRedes(Nodo* nodos1, Red* red2, int numReds, int idxNodo, int N){
  int j, numNodo_M;
  bool encontrado = false;
  int clase = red2 -> id;
  Nodo* nodo1 = nodos1[idxNodo] ;
  while(!encontrado){
    numNodo_M = (rand()%N)*numReds+clase;
    if (!estaEnNodo(nodo1, numNodo_M)){
        encontrado = true;
    }
  }
  return(numNodo_M-clase)/numReds; //Regresa la posicion del nodo de en arreglo de nodos
}


bool estaEnNodo(Nodo* nodo, int nuevoVecino){
    int j;
    bool encontrado = false;
    while(j< nodo.k && !encontrado){
        if(nuevoVecino == nodo->cnx[j]){
            encontrado = true;
        }
        j += 1;
    }
    return encontrado; 
}

