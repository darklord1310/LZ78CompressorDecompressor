#include "Dictionary.h"
#include "stdlib.h"

Dictionary **initDictionary(int dictSize)
{
    int i  ;
    Dictionary **dictionary; 
    
    //allocate dictSize amount of pointers to Dictionary
    dictionary = (Dictionary**)calloc(dictSize,sizeof(Dictionary*));   
 
    //allocate dictSize amount of Dictionary
    for(i = 0; i< dictSize; i++)
        dictionary[i] = (Dictionary*)calloc(1,sizeof(Dictionary));
    
    return dictionary ;
}

void destroyDictionary(Dictionary **dictionary,int dictSize)
{
    int i  ;
    
    for ( i = 0 ; i < dictSize ; i ++ )    
        free(dictionary[i]);
    free(dictionary);
}