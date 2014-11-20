#include "Dictionary.h"
#include "stdlib.h"
#include "malloc.h"
#include <string.h>


/*
 * Initialize the dictionary
 *
 * Input :
 *					dictSize is the size of the dictionary
 *
 */
Dictionary *initDictionary(int dictSize)
{
    Dictionary *dict;
    dict = malloc(sizeof(Dictionary));
    dict->Entry = calloc( dictSize, sizeof(DictionaryEntry) );
    dict->Entry->data = calloc( 1024, sizeof(char *) );
    dict->dictionarySize = dictSize;
    dict->currentIndex = 0;
    
    return dict;
}




// void destroyDictionary(Dictionary *dictionary,int dictSize)
// {
    // int i;
    
    // for ( i = 0 ; i < dictSize ; i ++ )
        // free(dictionary->Entry[i]);
            
// }


// char *addEntry(Dictionary *dict, char *EntryToAdd)
// {
    // if( dict->currentIndex != dict->dictionarySize )
    // {
        // strcpy(dict->Entry[dict->currentIndex]->data , "abc");
        // dict->Entry[dict->currentIndex]->entrySize = getSizeOfString(EntryToAdd);
        // dict->currentIndex++;
    // }
    
    // return EntryToAdd;
// }




int getSizeOfString(char *string)
{
	int j=0,length=0;
	
	while ( string[j] != '\0')
	{
		length++;
		j++;
	}
    
	return length;
}





