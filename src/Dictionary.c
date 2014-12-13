#include "Dictionary.h"
#include "stdlib.h"
#include "malloc.h"
#include <string.h>
#include "stdio.h"
#include <assert.h>

/*
 * Initialize the dictionary
 *
 * Input : dictSize         : dictSize is the size of the dictionary
 *
 */
Dictionary *initDictionary(int dictSize)
{
    int i ;
    
    Dictionary *dict;
    dict = malloc(sizeof(Dictionary));
    dict->Entry = calloc( dictSize, sizeof(DictionaryEntry) );
    
    for(i = 0 ; i < dictSize ; i ++ )
    {
        dict->Entry[i].data = calloc( 4096, sizeof(char) );
        dict->Entry[i].entrySize = 0 ;
    }
    dict->dictionarySize = dictSize;
    dict->currentIndex = 0;
    
    return dict;
}


/* *
 *  Add data to the current empty/available DictionaryEntry
 *
 * Input : dictionary       : dictionary is the pointer to dictionary to be added with data
 *         EntryDataToAdd   : EntryDataToAdd is the data to be added to the dictionary
 *
 *
 * Return 1 if data has been successfully added
 * Return 0 if data is not added due to full dictionary
 */
int addEntryData(Dictionary *dictionary, char *EntryDataToAdd,int size)
{
    int index = dictionary->currentIndex ;
    if( !isDictionaryFull(dictionary) )
    {
        memcpy(dictionary->Entry[index].data , EntryDataToAdd,size);
        dictionary->Entry[index].entrySize += size ;
        dictionary->currentIndex++;
        
        return 1 ;
    }
    else
        return 0 ;
}


/**
 *  Check if the dictionary is full based on currentIndex
 *
 * Input : dictionary       : dictionary is the pointer to dictionary to be checked
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

/**
 *  Check if the dictionary is empty if currentIndex = 0
 *
 * Input : dictionary       : dictionary is the pointer to dictionary to be checked
 *
 * Return 1 if dictionary is empty
 * Return 0 if dictionary is not empty
 */
int isDictionaryEmpty(Dictionary *dictionary)
{
    if( dictionary->currentIndex == 0 )
        return 1 ;
    else    
        return 0 ;
}

/**
 *  Get the length/size of the string
 *
 * Input : string       : string is the string to be checked
 *
 * Return length/size of the string
 */
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


/**
 *  Reset the data in the dictionary and currentIndex to 0
 *
 * Input : dictionary       : dictionary is the pointer to dictionary to be refreshed
 *         dictSize         : dictSize is the size of the created dictionary
 *
 */
void refreshDictionaryEntryData(Dictionary *dictionary,int dictSize)
{
    int i  ;
   
    assert(dictSize <= 4096);
    
    for ( i = 0 ; i < dictSize ; i ++ )
    {
        assert(i < 4096);
        memset (dictionary->Entry[i].data,0,4096);
        dictionary->Entry[i].entrySize = 0;
    }
    
    dictionary->currentIndex = 0;
}

/**
 *  Free dictionary
 *
 * Input : dictionary       : dictionary is the pointer to dictionary to be freed
 *         dictSize         : dictSize is the size of the created dictionary
 *
 */
void destroyDictionary(Dictionary *dictionary,int dictSize)
{
    int i  ;
    
    // for ( i = 0 ; i < usedSize ; i ++ )  
    // {
        // free(&(dictionary->Entry[i].data));
        // free(&(dictionary->Entry[i])); 
    // }  
    
    free(dictionary);
}

