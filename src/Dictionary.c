#include "Dictionary.h"
#include "stdlib.h"

Dictionary *initDictionary(int dictSize)
{
    Dictionary *dict = calloc(dictSize,sizeof(Dictionary));

    return dict ;
}

void destroyDictionary(Dictionary *dictionary,int dictSize)
{
    int i  ;
    
    for ( i = 0 ; i < dictSize ; i ++ )
        free(&dictionary[i]);

}