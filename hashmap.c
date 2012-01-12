#include "hashmap.h"
static unsigned int cal_hash(char *key);
static int expaned_array(hashmap *hashmap);
static int kwadratische_peiling(int hash, int i);
static void* recu_search(hashmap *hashmap, char *key, int pos);

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
  
  if(!strcmp(hashmap->elementArray[cal_hash(key) % hashmap->capaciteit]->key,key)){
      return (void*)hashmap->elementArray[cal_hash(key) % hashmap->capaciteit]->value;
  }else{
    return recu_search(hashmap,key,1);
  }

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
  m->array_position = (int*) malloc(sizeof(int)*DEFAULT_SIZE);
  for(;i < DEFAULT_SIZE; i++)
    m->array_position[i] = 0;
  m->elementArray = (hashMapElement**) calloc(DEFAULT_SIZE*sizeof(hashMapElement),sizeof(hashMapElement*));
  for(i=0; i <= DEFAULT_SIZE; i++)
    m->elementArray[i] = (hashMapElement*) malloc(sizeof(hashMapElement));
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
  int i;
  
  hashMapElement **old_elementArray = calloc(hashmap->number_of_elements,sizeof(hashMapElement*));
  hashMapElement **new_elementArray;
  int* new_aantal_pos;

  for(i = 0; i < hashmap->capaciteit;i++){
    old_elementArray[i] = malloc(sizeof(hashMapElement));
    if(hashmap->array_position[i] == 1)
      *old_elementArray[i] = *hashmap->elementArray[i];
  }
  

  new_elementArray = (hashMapElement*) realloc(hashmap->elementArray, (hashmap->capaciteit*2)*sizeof(hashMapElement*));
  new_aantal_pos = (int*) realloc(hashmap->array_position, (hashmap->capaciteit*2)*sizeof(int));
  hashmap->elementArray = new_elementArray;
  
  for(i=0; i < (hashmap->capaciteit*2);i++){
    hashmap->elementArray[i] = (hashMapElement*) calloc(1,sizeof(hashMapElement*));
    new_aantal_pos[i] = 0;
  }

  for(i=0; i < hashmap->capaciteit; i++){
    printf("%d \n",i);
    if(hashmap->array_position[i] == 1){
      if(new_aantal_pos[cal_hash(old_elementArray[i]->key) % (hashmap->capaciteit*2)] == 0){
	new_aantal_pos[cal_hash(old_elementArray[i]->key) % (hashmap->capaciteit*2)] = 1;
	*hashmap->elementArray[cal_hash(old_elementArray[i]->key) % (hashmap->capaciteit*2)] = *old_elementArray[i];
      }
    }
  }
  hashmap->capaciteit = hashmap->capaciteit*2;
  hashmap->array_position = new_aantal_pos;

  /*FREE*/
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
static void* recu_search(hashmap *hashmap, char *key, int pos){
  if(!strcmp(hashmap->elementArray[kwadratische_peiling(cal_hash(key),pos)]->value,key))
    return (void*) hashmap->elementArray[kwadratische_peiling(cal_hash(key),pos)]->value;
  else
    return recu_search(hashmap,key,pos++);
}
