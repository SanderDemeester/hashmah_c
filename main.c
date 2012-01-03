#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"


int main(int argc, char *arch[]){
  hashmap *m = (hashmap*) malloc(sizeof(hashmap));
  
  m->fp_init_hashmap = init_hashmap;
  m->fp_init_hashmap(m);
  printf("%d \n",m->hashmap_parameter->current_loadfactor);
  printf("%d \n",m->hashmap_parameter->capaciteit);
  
  return 0;
}
