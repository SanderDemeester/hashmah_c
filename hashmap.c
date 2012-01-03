#ifndef _hashmap
#include "hashmap.h"
#endif
static unsigned int cal_hash(char *key);

int addElement(char *key, int value,hashmapP* hashmap_p){
  unsigned int hash = (cal_hash(key) % DEFAULT_SIZE);
  if(hashmap_p->array_position[hash] == 0){
    hashmap_p->array_position[hash]=1;
    hashMapElement e = {value};
    hashmap_p->elementArray[hash] = e;
    hashmap_p->number_of_elements++;
    hashmap_p->current_loadfactor = (hashmap_p->capaciteit/hashmap_p->number_of_elements);
    printf("load factor: %d \n",hashmap_p->current_loadfactor);
    if(hashmap_p->current_loadfactor >= LOAD_FACTOR)
      printf("%s \n","time for a rehash");
  }else{
    /*doe iets slims*/
    printf("%s \n","hash collision");
  }
  
  return 0;
}

int removeElement(int element){
  printf("%s \n","remove Element");
  return 0;
}

void clean_up(){
  printf("%s \n","clean up van de hashmap");
}

void init_hashmap(hashmap *m){
  int i = 0;
  printf("%s \n","init van de hashmap");
  m->hashmap_parameter = (hashmapP*) malloc(sizeof(hashmapP));
  for(;i <= DEFAULT_SIZE; i++)
    m->hashmap_parameter->array_position[i] = 0;
  m->hashmap_parameter->elementArray = (hashMapElement*) calloc(DEFAULT_SIZE*sizeof(hashMapElement),sizeof(hashMapElement));
  m->fp_addElement = addElement;
  m->fp_removeElement = removeElement;
  m->fp_clean_up = clean_up;
  m->hashmap_parameter->number_of_elements = 0;
  m->hashmap_parameter->current_loadfactor = 0;
  m->hashmap_parameter->capaciteit = DEFAULT_SIZE;
}

static int expaned_array(hashmap *hashmap){
}
static unsigned int cal_hash(char *value){
  unsigned int hash = 0;
  unsigned int i = 0;
  for(;i <= sizeof(value)/sizeof(char); i++){
    hash += value[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash;
}
