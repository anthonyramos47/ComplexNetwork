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


void swap(int i, int j){
  int aux,last=red[i].k-1;
  aux=red[i].cnx[last];
  red[i].cnx[last]=red[i].cnx[j];
  red[i].cnx[j]=aux;
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