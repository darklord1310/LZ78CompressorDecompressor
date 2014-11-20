#include "Dictionary.h"
#include "stdlib.h"
#include "malloc.h"



/*
 * Initialize the dictionary
 *
 *Input :
 *					dictSize is the size of the dictionary
 *
 */
Dictionary *initDictionary(int dictSize)
{
    Dictionary *dict;
    dict = malloc(sizeof(Dictionary));
    dict->Entry = calloc( dictSize, sizeof(DictionaryEntry) );
    dict->dictionarySize = dictSize;
    dict->currentIndex = 0;
    
    return dict;
}





// void destroyDictionary(Dictionary *dictionary,int dictSize)
// {
    // int i  ;
    
    // for ( i = 0 ; i < dictSize ; i ++ )
        // free(&dictionary[i]);
// }


char *addEntry(Dictionary *dict, char *EntryToAdd)
{


}


