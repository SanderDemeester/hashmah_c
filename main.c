#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

void iterate(hashmap* hashmap);

int main(int argc, char *arch[]){
  hashmap *m = (hashmap*) malloc(sizeof(hashmap));
  
  m->fp_init_hashmap = init_hashmap;
  m->fp_init_hashmap(m);

  printf("%d \n",m->fp_addElement("sander",3,m));
  printf("%d \n",m->fp_addElement("sander",6,m));
  printf("%d \n",m->fp_getElement("sander",m));
  iterate(m);
  return 0;
}

void iterate(hashmap *hashmap){
  int i = 0;
  for(;i <= hashmap->capaciteit; i++)
    printf("%d \n",hashmap->array_position[i]);
}
    
