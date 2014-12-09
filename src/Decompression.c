#include "Dictionary.h"
#include "Stream.h"
#include "Decompression.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

void Decompression(OutStream *out, unsigned int index, unsigned int data, Dictionary *dictionary)
{
    int signedIndex = (int)index;
    int i;
    char *string;
    char *convertedData = (char *)(&data);           //typecast the int type data to char type
    
    if( signedIndex-1 < 0)                                      //if index is 0
        streamWriteBits(out, data, 8);
    else                                                        //if index is not 0
    {   
        string = strdup(dictionary->Entry[signedIndex-1].data);
        strcat(string, convertedData);                                   //combined the string with the data
        for(i=0; i < strlen(string); i++)
            streamWriteBits(out, (unsigned int)(string[i]), 8);
    }

}




/*
 * Add data into the dictionary
 *
 * Input :            
 *
 *					
 *
 * Return:
 *            1     dictionary is not full and data is written successfully
 *            0     dictionary has already full and data is not written into dictionary
 *          
 */
int AddDataToDictionary(Dictionary *dictionary, unsigned int index, unsigned int data)
{
    int signedIndex = (int)index;                    //to change the unsigned index into signed index
    char *convertedData = (char *)(&data);           //typecast the int type data to char type
    char *string;
    
    if( (signedIndex-1) < 0)
    {
        if( addEntryData(dictionary, convertedData) == 0)    
            return 0;
    }
    else
    {
        string = strdup(dictionary->Entry[signedIndex-1].data);
        strcat(string, convertedData);
        if( addEntryData(dictionary, string) == 0)
            return 0;
    }
}

