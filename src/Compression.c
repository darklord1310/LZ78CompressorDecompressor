#include "Compression.h"
#include "Dictionary.h"
#include "Stream.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void LZ78_Compressor(char *inputBuffer, char *outputBuffer, Dictionary *dictionary)
{   
    int i = 0,j = strlen(inputBuffer), returnedIndex, saveIndex, stringLength, inputState ;
    char dataString[1024] = {} ;
   
    while ( i < j )
    {
        memset(dataString,0,1024); //clear string to 0
        strncpy(dataString,&inputBuffer[i],1);//read 1 character from inputBuffer and copy to dataString
          
        if(isDictionaryEmpty(dictionary)) // if dictionary is empty
        {
            addEntryData(dictionary, dataString); // directly add it into dictionary
            LZ78_Output(dataString,outputBuffer,0); // output 0X where X = character in inputBuffer
        }       
        else
        {
            returnedIndex = compare_DictionaryData(dataString,dictionary); //check is there any matched data in dictionaryEntry
            if ( returnedIndex >= 0 ) // if true
            {
                saveIndex = returnedIndex ; // store the index of first match in dictionaryEntry

                while(returnedIndex != -1)
                {
                    i ++ ;  // read next character 
                    stringLength = strlen(dataString);
                    dataString[stringLength] = inputBuffer[i]; //add next character to dataString
                    
                    returnedIndex = compare_DictionaryData(dataString,dictionary); //check again is there any matched data
                    
                    if (returnedIndex != -1 )    
                        saveIndex = returnedIndex ; // store the index of last match in dictionaryEntry
                }
                
                if(addEntryData(dictionary,dataString)) // add dataString into dictionary
                {
                    saveIndex ++ ; //increment saveIndex as dictionaryEntry starts from 0 instead of 1
                    memset(dataString,0,1024); //clear string to 0
                    strncpy(dataString,&inputBuffer[i],1); //read character from inputBuffer again
                    LZ78_Output(dataString,outputBuffer,saveIndex); // produce output (dictionaryIndex+1)(X) *without ()
                }
            }
            else // no matched data
            {
                if(addEntryData(dictionary,dataString))
                    LZ78_Output(dataString,outputBuffer,0); 
            }
        }
    
        i ++;
    }
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
void merge_InputDataDictionaryData(char *inputString,Dictionary *dictionary,int index)
{
    strcat(inputString,dictionary->Entry[index].data);
}

