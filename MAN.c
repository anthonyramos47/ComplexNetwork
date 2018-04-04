#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>



#define N 1000 // numero de nodos

typedef struct{
  int  id;
  int estadoActual;
  int estadoAntiguo;
  int k; // número de elementos en cnx
  int *cnx; // conexiones
  int nulos;
} Node;

typedef struct{
  int id;
  //int N; //number of nodes
  Node* nodeList;
  //float p; //rewiring probability
  //int K; //number of starting neighbors (coordination number)
}Red;

// Fercho El Teorista de Numeros

 // arreglo global de nodos y sus conexiones

void inicializarRed(int);
void cableadoInicial(int);
void sumarLink(int, int);
void recableadoRed(float, int);
int nuevoNodo(int);
void liberarMemoria(void);
void imprimir(int);
float prob(void);
int encontrarVecino(int, int );
float critialProbAct(int, float, int);
void inicializarMuestra(int, float);
void actualizarRed(float, int);
void actualizarEstadoNodo(int, float);
bool algunVecinoActivo(int);
float actividadRed(void);
void swap(int, int);
void quitarLink(int);
void inicializarEstadosRed();
void correccionEstadosRed(void);
float actividadMuestra(float, float);
void imprimirRed();



//////////////////////   main   ///////////////////////

int main(){

}

/* -----------------------FUNCIONES-------------------------*/


void cableadoInicial(int K, Red* redEst){
  int i,j;
  /* function that create the initial ordered connections of the network
  putting for each node half of the neighbors to the rigth and half to the left
   */
  Node red[] = redEst -> nodeList;
  int class = redEst -> id;

  for(i=0;i<N;++i){
    for(j=-K/2; j<0; ++j){
      red[i].cnx[(K/2)+j]= red[((N+(i+j))%N)].id;
      red[i].cnx[(K/2)-j-1]= red[((i-j)%N)].id;

    }
  }
  redEst -> nodeList = red;
}

void inicializarRed(int K, Red* redEst){
  int i;
  /*
  With this procedure we put all the properties of each node and also we
  allocate the memory that each node requier for the vector of conections With
  their neighbors
  */
  int class = redEst -> id;
  Node red[] = redEst -> nodeList;

  for(i=0;i<N;++i) {
    red[i].id = i*NRed + class;
    red[i].cnx=malloc(K*sizeof(int)); // asignación de memoria inicial
    red[i].k=K;
  }
}

void sumarLink(int i,int new, Red* redEst){
  /*
  Beware new is the node that we add the node i
  */

  Node red[] = redEst -> nodeList;

  ++red[new].k;
  red[new].cnx=realloc(red[new].cnx,red[new].k*sizeof(int));
  red[new].cnx[red[new].k-1]= red[i].id;
}

void quitarLink(int i){
  --red[i].k;
   red[i].cnx=realloc(red[i].cnx,red[i].k*sizeof(int));
}

void swap(int i, int j){
  int aux,last=red[i].k-1;
  aux=red[i].cnx[last];
  red[i].cnx[last]=red[i].cnx[j];
  red[i].cnx[j]=aux;
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

void liberarMemoria(void){
  int i;
  for(i=0;i<N;++i) free(red[i].cnx);
}

void imprimir(int i){
  int j;
  printf("Nodo: %i\t",i );
  for(j=0;j<red[i].k;++j) printf( "\t%d",red[i].cnx[j]); printf("\n");
}

void imprimirRed(){
  int i;
  for(i=0; i<N; ++i){
    printf("Nodo :%i \t ActividadActual: %i \t ActividadAntigua: %i \n",i, red[i].estadoActual, red[i].estadoAntiguo );
  }

}

float prob(void){
  return((float)rand()/RAND_MAX);
}


float critialProbAct(int K, float probRecableado, int T){
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

void inicializarMuestra(int K, float probRecableado){
  inicializarRed(K);
  cableadoInicial(K);
  recableadoRed(probRecableado, K);
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

void actualizarRed(float probActivarse, int T){
  int pasos, i;

  for(pasos=0; pasos<T; ++pasos){
    for(i=0;i<N;++i){
      actualizarEstadoNodo(i,probActivarse);
      }
    correccionEstadosRed();
  }


}

void inicializarEstadosRed(){
  int i;
  for(i=0; i<N; ++i) {
  red[i].estadoAntiguo=rand()%3;
  red[i].estadoActual = red[i].estadoAntiguo;
  //printf("Nodo %i: %i\n",i, red[i].estadoAntiguo );
  }
}

void correccionEstadosRed( void ){
  int i;
  for(i=0;i<N;++i){
      red[i].estadoAntiguo = red[i].estadoActual;
  }
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

float actividadRed(void){
  int i, Activos = 0;
  for(i=0;i<N;++i) if(red[i].estadoActual==2) ++Activos;
  return((float)Activos/N);
}



/////////////////////////





/////////////////////////CLUSTER FUNCTIONS//////////////////////////////



/////FUTURE IMPLEMENTATION
// Red* generateCluster(int NRed, int N, int K, float p){
//   Red* cluster = malloc(Nred*sizeof(Red));
//   for(int i=0;i<NRed;i++){
//
//     (cluster+i)* = inicializarRed(N,K,p,i); //i es la clase i MOD NRed
//
//   }
//   return cluster;
//
// }
