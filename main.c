#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"


int main(int argc, char *arch[]){
  hashmap *m = (hashmap*) malloc(sizeof(hashmap));
  
  m->fp_init_hashmap = init_hashmap;
  m->fp_init_hashmap(m);
  m->fp_addElement("sander",2,m->hashmap_parameter);
  return 0;
}
