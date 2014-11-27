#include "Compression.h"
#include "Dictionary.h"
#include "Stream.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void LZ78_Compressor(char *inputBuffer, char *outputBuffer, Dictionary *dictionary)
{   
    int i = 0,j = strlen(inputBuffer);
    char *inputString ;
    
    if(isDictionaryEmpty(dictionary)) // if dictionary is empty
    {
        if(addEntryData(dictionary, &inputBuffer[i])); // directly add it into dictionary
            LZ78_Output(&inputBuffer[i],outputBuffer,0); // output 0X where X = character in inputBuffer
    }    
    
    /*else    
    {
       
       
        
    }*/

}


void LZ78_Output(char *inputString,char *outputBuffer,int index)
{
    char charIndex[5] ;
    
    itoa(index,charIndex,10); // convert integer type of index to character
    strcat(outputBuffer,charIndex); // append index to buffer
    strcat(outputBuffer,inputString); // append inputString to buffer
}

/* *
 *  Compare data in the dictionary with input
 *
 * Return index of match entry if found
 * Return -1 if not found
 */
int compare_DictionaryData(char *inputString,Dictionary *dictionary)
{
    int i ;
    
    for ( i = 0 ; i < (dictionary->currentIndex) ; i ++ )
    {
        if (strcmp(inputString,(dictionary->Entry[i].data)) == 0)
            return i ;
    }

    return (-1);
}

/* *
 *  Merge data in the selected index of dictionaryEntry with input
 *
 * 
 */ 
void merge_InputDataDictionaryData(char *inputString,char *outputString,Dictionary *dictionary,int index)
{
    strcpy(outputString,inputString);
    strcat(outputString,dictionary->Entry[index].data);
}