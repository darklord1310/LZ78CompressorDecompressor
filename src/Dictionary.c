#include "Dictionary.h"
#include "stdlib.h"
#include "malloc.h"
#include <string.h>
#include "stdio.h"

/*
 * Initialize the dictionary
 *
 * Input :
 *					dictSize is the size of the dictionary
 *
 */
Dictionary *initDictionary(int dictSize)
{
    int i ;
    
    Dictionary *dict;
    dict = malloc(sizeof(Dictionary));
    dict->Entry = calloc( dictSize, sizeof(DictionaryEntry) );
    
    for(i = 0 ; i < dictSize ; i ++ )
       dict->Entry[i].data = calloc( 1024, sizeof(char) );
    
    dict->dictionarySize = dictSize;
    dict->currentIndex = 0;
    
    return dict;
}


/* *
 *  Add data to the current empty/available DictionaryEntry
 *
 * Return 1 if data has been successfully added
 * Return 0 if data is not added due to full dictionary
 */
int addEntryData(Dictionary *dictionary, char *EntryDataToAdd)
{
    int index = dictionary->currentIndex ;
    
    if( !isDictionaryFull(dictionary) )
    {
        strcpy(dictionary->Entry[index].data , EntryDataToAdd);
        dictionary->Entry[index].entrySize = getSizeOfString(EntryDataToAdd);
        dictionary->currentIndex++;
        
        return 1 ;
    }
    else
        return 0 ;
}


/**
 *  Check if the dictionary is full based on currentIndex
 *
 * Return 1 if dictionary is full
 * Return 0 if dictionary is not full
 */
int isDictionaryFull(Dictionary *dictionary)
{
    if( dictionary->currentIndex >= dictionary->dictionarySize )
        return 1 ;
    else    
        return 0 ;

}

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


void refreshDictionaryEntryData(Dictionary *dictionary,int dictSize)
{
    int i  ;
    
    for ( i = 0 ; i < dictSize ; i ++ )    
    {    
        free(&(dictionary->Entry[i].data));
        dictionary->Entry[i].data = calloc( 1024, sizeof(char) );
    }
}

void destroyDictionary(Dictionary *dictionary,int dictSize)
{
    int i  ;
    
    for ( i = 0 ; i < dictSize ; i ++ )  
    {
        free(&(dictionary->Entry[i].data));
    }
    
    free(dictionary->Entry);
    free(dictionary);

}

