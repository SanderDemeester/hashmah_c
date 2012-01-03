#ifndef _hashmap
#define _hashmap

#define DEFAULT_SIZE 10
#define LOAD_FACTOR 0.75

typedef struct hashMapElement{
  int word;
}hashMapElement;

typedef struct hashmapP{
  hashMapElement *elementArray;
  int array_position[DEFAULT_SIZE];
  int number_of_elements;
  int capaciteit;
  float current_loadfactor;
}hashmapP;

typedef struct hashmap{
  hashmapP *hashmap_parameter;
  int (*fp_addElement)(char *,int,hashmapP*); //0 for succes, -1 for fail
  int (*fp_removeElement)(int); //0 for success, -1 for fail
  void (*fp_clean_up)(); //vrijmaken van geheugen
  void (*fp_init_hashmap)(struct hashmap *); //init van de hashmap
}hashmap;

int addElement(char *,int,hashmapP*);
int removeElement(int);
void clean_up();
void init_hashmap(hashmap*);
#endif
