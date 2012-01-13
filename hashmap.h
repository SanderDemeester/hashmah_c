#ifndef _hashmap
#define _hashmap

#define DEFAULT_SIZE 10
#define LOAD_FACTOR 0.75

typedef struct hashMapElement{
  char *key;
  int value;
}hashMapElement;

typedef struct hashmap{
  hashMapElement **elementArray;
  int *array_position;
  int number_of_elements;
  int capaciteit;
  double current_loadfactor;
  int (*fp_addElement)(char *,int,struct hashmap *); //0 for succes, -1 for fail
  void*(*fp_getElement)(char *,struct hashmap *); 
  int (*fp_removeElement)(char *,struct hashmap*); //0 for success, -1 for fail
  void (*fp_clean_up)(); //vrijmaken van geheugen
  void (*fp_init_hashmap)(struct hashmap *); //init van de hashmap
}hashmap;


int addElement(char *,int,hashmap*);
void* getElement(char*,hashmap*);
int removeElement(char*,hashmap*);
void clean_up();
void init_hashmap(hashmap*);
#endif
