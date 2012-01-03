#include "hashmap.h"
static unsigned int cal_hash(char *key);
static int expaned_array(hashmap *hashmap);
static int kwadratische_peiling(int hash, int i);

int addElement(char *key, int value,hashmap* hashmap){
  unsigned int hash = (cal_hash(key) % hashmap->capaciteit);
  if(hashmap->array_position[hash] == 0){
    hashmap->array_position[hash]=1;
    hashMapElement *e = (hashMapElement*) malloc(sizeof(hashMapElement));
    e->value = value;
    e->key = key;
    hashmap->elementArray[hash] = e;
    hashmap->number_of_elements++;
    hashmap->current_loadfactor = (double)hashmap->number_of_elements/(double)hashmap->capaciteit;
    printf("first state: %d \n",hash);
  }else{
    /*doe iets slims*/
    printf("%s \n","hash collision");
    unsigned int hash2 = hash;
    int i = 0;
    while(hashmap->array_position[hash2] != 0){
      if(strcmp(key,hashmap->elementArray[hash2]->key) == 0)
	 return -1;
	  hash2 = kwadratische_peiling(hash,i) %  hashmap->capaciteit;
	  i++;
    }
    printf("second state %d %d \n",hash2,i);
    hashMapElement *e = (hashMapElement*) malloc(sizeof(hashMapElement));
    e->value = value;
    e->key = key;
    hashmap->array_position[hash2] = 1;
    hashmap->elementArray[hash2] = e;
    hashmap->number_of_elements++;
    hashmap->current_loadfactor = (double)hashmap->number_of_elements/(double)hashmap->capaciteit;
  }
  if(hashmap->current_loadfactor >= LOAD_FACTOR)
    expaned_array(hashmap);
  
  return 0;
}
  

void* getElement(char *key,hashmap* hashmap){
  return (void*)hashmap->elementArray[cal_hash(key) % hashmap->capaciteit]->value;
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
  for(;i <= DEFAULT_SIZE; i++)
    m->array_position[i] = 0;
  m->elementArray = (hashMapElement**) calloc(DEFAULT_SIZE*sizeof(hashMapElement),sizeof(hashMapElement*));
  m->fp_addElement = addElement;
  m->fp_getElement = getElement;
  m->fp_removeElement = removeElement;
  m->fp_clean_up = clean_up;
  m->number_of_elements = 0;
  m->current_loadfactor = 0;
  m->capaciteit = DEFAULT_SIZE;
}

static int expaned_array(hashmap *hashmap){
  printf("%s \n","expanding van de array");
  int old_array_position[hashmap->capaciteit];
  int i = 0;
  hashMapElement** old_array = hashmap->elementArray;
  
  hashmap->capaciteit = hashmap->capaciteit*2;
  hashmap->elementArray = (hashMapElement**) realloc(hashmap->elementArray,hashmap->capaciteit * sizeof(hashMapElement*));
  hashmap->current_loadfactor = (double)hashmap->number_of_elements/(double)hashmap->capaciteit;

  for(; i <= hashmap->capaciteit/2;i++)
    old_array_position[i] = hashmap->array_position[i];
  for(;i <= hashmap->capaciteit; i++)
    hashmap->array_position[i] = 0;

  hashmap->number_of_elements = 0;
  for(i = 0; i <= (hashmap->capaciteit/2); i++){
    if(old_array_position == 1){
      /*recalculate the new hash values*/
      printf("%f \n",i);
      addElement(old_array[i]->key,old_array[i]->value,hashmap);
    }
  }
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
static int kwadratische_peiling(int hash, int i){
    return hash + (i << 1);
}
