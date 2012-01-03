#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

void iterate(hashmap* hashmap);

int main(int argc, char *arch[]){
  hashmap *m = (hashmap*) malloc(sizeof(hashmap));
  
  m->fp_init_hashmap = init_hashmap;
  m->fp_init_hashmap(m);

  m->fp_addElement("sander",3,m);
  m->fp_addElement("sander",6,m);
  m->fp_addElement("jer232oen",7,m);
  m->fp_addElement("jersdfoen",7,m);
  m->fp_addElement("jesdfsqdroen",7,m);
  m->fp_addElement("jersdfsdoen",7,m);
  m->fp_addElement("jesdfsdfroen",7,m);
  m->fp_getElement("sander",m);
  return 0;
}

void iterate(hashmap *hashmap){
  int i = 0;
  for(;i <= hashmap->capaciteit; i++)
    printf("%d \n",hashmap->array_position[i]);
}
    
