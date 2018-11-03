#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <time.h>


#define N 2 // numero de nodos
#define SIZE 10
#define probLimp 0.5

typedef struct{
  int estadoActual;
  int estadoAntiguo;
  int k; // número de elementos en cnx
  int *cnx; // conexiones
  int nulos;
  float area;
  float poblacion;
  int pasoEvol;
} nodo;

nodo red[N]; // arreglo global de nodos y sus conexiones

void inicializarRed();
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
void actualizarEstadoNodo(int, float, int);
bool algunVecinoActivo(int);
float actividadRed(void);
void swap(int, int);
void quitarLink(int);
void inicializarEstadosRed();
void correccionEstadosRed(void);
float actividadMuestra(float, float);
void imprimirRed();
float funcionCrecimiento(int, int);
char** str_split(char*, const char);
void asignarVecinos(int nodo, int lista[]);
void asignarAreas(float lista[]);
void cureZone(int nodo);
void prevent();
void asignarNodosYVecinos();
int* str2array(char*,int) ;


//////////////////////   main   ///////////////////////

int main(){
  /* Program to Run a small wolrd network with the GH method with different
  probabilities of disorder from [0 - 1], several K, wich represents the number of neighbors for
  each node of the network , several T and
  for each (prob, K and T) it is run a max of 30 samples with this conditions
  and it is measure the activity of each network
   .*/

  int K, numMuestra, numMuestraMax, T, i, Kmax;
  float probRecableado, x, promCritialProbAct, z, probActivarse, activity, proba;

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

  FILE *archivoSalida, *archivoEntrada, *archivoArea;

  int arr[SIZE];



  time_t t;

  K = 4;
  T = 1000;

  probActivarse = 0.5;

  srand(time(NULL));
  //srand(30);


  /* while (!feof(archivoEntrada)){
  fgets(linea,sizeof(linea),archivoEntrada);
  MILISTA = str_split(linea," ");
  printf("%s\n", *MILISTA);
}  */

  asignarNodosYVecinos();  //Como la red es global no la pongo como parametro
  float areas[ ] = {0.2161438641853612,0.017135961255624787,0.12910119999432873,0.04732631809463028,0.03856153472851655,0.4289769593978548,0.06325096809621523,0.735744372749664,0.05199651040738076,0.08666731200137802,0.03651391180839847,0.06406420203342938,0.08829984838934857,0.08673960288909009,0.09371824855072637,0.06021667359111928,0.43530514365282125,0.05750948982258523,0.1479708982047825,1.,0.5345786600082096,0.2285330496606817,0.6351377999907001,0.047014748490233293,0.10378446408989174,0.07832954634011552,0.04062107876019696,0.09006546530875985,0.09909331709398843,0.42022570982171165,0.1631746464036335,0.09523413746594873,0.13503361522732601,0.6765115462811824,0.19261357347109906,0.06319579658974298,0.08257406948934752,0.1341149388394604,0.4015320415081946,0.09465759812475742,0.385807949533644,0.3813215168753152,0.11571747415713927,0.09163974370325054,0.09799398349689716,0.38542890810426,0.7649951129266509,0.1613282673415262,0.36327041723060444,0.1438449720749867};
  asignarAreas(areas);
  inicializarRed();
  imprimir(0);
  imprimir(1);
  activity = actividadMuestra(probActivarse, T);
  printf("%f \n",activity );

}

/* -----------------------FUNCIONES-------------------------*/

void asignarAreas(float lista[]){
  for (int i =0; i< N; i++){
    red[i].area = lista[i];
  }
}

void cureZone(int nodo) {
  red[nodo].estadoAntiguo = 0;
  red[nodo].estadoActual = 0;
  red[nodo].pasoEvol = 0;
  red[nodo].poblacion = 0;
}

void prevent(){

  //printf("proba: %f\n",proba  );
  for (int i =0; i< N; i++){
    float proba = prob();
    // printf("Proba: %f No entre\n",proba);
    if (proba < probLimp){
    //  printf("Proba: %f putos todos\n",proba);
    }
    if (red[i].estadoAntiguo = 1 && proba < probLimp){
      red[i].estadoAntiguo = 0;
    };
  }

}

void asignarVecinos(int nodo, int lista[]){

  for (int k =0; k< red[nodo].k; k++){
    red[nodo].cnx[k] = lista[k]-1;
  }
}


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

void inicializarRed(){
  int i;
  /*
  With this procedure we put all the properties of each node and also we
  allocate the memory that each node requier for the vector of conections With
  their neighbors
  */
  for(i=0;i<N;++i) {
    red[i].poblacion = 0.0;
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
  minOfInterval = 4;
  maxOfInterval = 100;
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
  int pasos, i, t;
//  imprimirRed();
  FILE *f, *su;
  f = fopen("activos.dat","w");
  su = fopen("suceptibles.dat","w");
  for(pasos=0; pasos<T; ++pasos){

    //if (pasos%50 == 0 && pasos != 0 && proba < probLimp ){
    if (pasos%10 == 0 && pasos > 50 ){
      prevent();
    }
    for(i=0;i<N;++i){
      if (red[i].estadoActual == 2){
        red[i].pasoEvol += 1;
        t = red[i].pasoEvol;
        red[i].poblacion = funcionCrecimiento(i, t);
      //  printf("%f\n",red[i].poblacion );
      //  printf("Entreee chugchaa %i\n Poblacion: %f \n", i, red[i].poblacion);
      }
      actualizarEstadoNodo(i, probActivarse, pasos);
      }
    //  printf("DESPUES DE LA ACTUALIZACION DE ESTADOS\n");
    //  imprimirRed();
      correccionEstadosRed();

    //  printf("Time: %i\n", pasos );
      for(i=0;i<N;++i){
          if (red[i].estadoActual == 2){
            fprintf(f, "%i ",i+1);
            }
          if (red[i].estadoActual ==1){
            fprintf(su, "%i ",i+1);
          }
      }
      fprintf(f, "\n");
      fprintf(su, "\n");
    //  printf("---------------DESPUEs DE LA CORRECCION--------------------\n");
  //    imprimirRed();
  //    printf("---------------*******************--------------------\n");

  }
  fclose(f);
  fclose(su);
}

void inicializarEstadosRed(){
  int i;
  for(i=0; i<N; ++i) {
  red[i].estadoAntiguo=0;
  red[i].estadoActual = red[i].estadoAntiguo;
  //printf("Nodo %i: %i\n",i, red[i].estadoAntiguo );
  }
  red[4].estadoAntiguo = 2;
  red[4].estadoActual = 2;
  red[6].estadoAntiguo = 2;
  red[6].estadoActual = 2;
}

void correccionEstadosRed( void ){
  int i;
  for(i=0;i<N;++i){
      red[i].estadoAntiguo = red[i].estadoActual;
  }
}

float funcionCrecimiento(int nodo, int t){
  float area = red[nodo].area;
  float funcion = (t*t)/2 - ((area * t*t*t )/30);
  return funcion;
}


void actualizarEstadoNodo(int nodo, float probActivarse, int t){
  int estadoNodo = red[nodo].estadoAntiguo;
  //float crecimiento = funcionCrecimiento(nodo, t);
  float maximoCrecimiento = funcionCrecimiento(nodo, (1/red[nodo].area));
  float proba = prob();
//  printf("Estado Antiguo:%i \t AlgunVec: %i\n", red[nodo].estadoAntiguo, algunVecinoActivo(nodo));
  switch(estadoNodo){
  case 0: if (proba < probActivarse){
            red[nodo].estadoActual = 1; break;
          }
  case 1: if(algunVecinoActivo(nodo))
          {red[nodo].estadoActual = 2;
  //          printf("Me ACTIVE HDP\n");
          break;
          }
  case 2:
  if (red[nodo].poblacion < -0.3){
        red[nodo].estadoActual = 0;
        red[nodo].pasoEvol = 0;
        red[nodo].poblacion = 0;}
          break;
  }
}

bool algunVecinoActivo(int nodo){
  int i;
  bool encontrado = false;

  while (!encontrado & i < red[nodo].k){
    //printf("%i\n",red[nodo].cnx[i]);
    if (red[red[nodo].cnx[i]].estadoAntiguo == 2 && red[red[nodo].cnx[i]].poblacion > funcionCrecimiento(red[nodo].cnx[i],(3/red[red[nodo].cnx[i]].area) )) {
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

void asignarNodosYVecinos(){
  int numVecinos; // numero de vecinos de un nodo
  int espacio = (N/2)*3;
  char strVecinos[espacio]; // string con los vecinos separado por comas
  int *vecinos; //array que contendra los vecinos temporales
  //Abro el archivo
  FILE *pf = fopen("Vecinos2.txt","r");
  //Empiezo a iterar por cada linea
  for(int nodo=0;nodo<N;nodo++){
    fscanf(pf, "%d %s", &numVecinos, strVecinos);
    vecinos = str2array(strVecinos,numVecinos); //convierto el string separado por comas a un array
    //Asigno los valores a la red
    red[nodo].k = numVecinos;
    red[nodo].cnx=malloc(numVecinos*sizeof(int));
    asignarVecinos(nodo, vecinos);
    free(vecinos);
  }
  fclose(pf);
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
