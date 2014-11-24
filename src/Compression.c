#include "Compression.h"
#include "Dictionary.h"
#include "Stream.h"
#include <string.h>
#include <stdio.h>


/* *
 *  Compare data in the dictionary with input
 *
 * Return index of match entry if found
 * Return -1 if not found
 */
int compare_DictionaryData(char *input,Dictionary *dictionary)
{
    int i ;
    
    for ( i = 0 ; i < (dictionary->currentIndex) ; i ++ )
    {
        if (strcmp(input,(dictionary->Entry[i].data)) == 0)
            return i ;
    }

    return (-1);
}

/* *
 *  Merge data in the selected index of dictionaryEntry with input
 *
 * 
 */
void merge_InputDataDictionaryData(char *input,char *output,Dictionary *dictionary,int Index)
{
    strcpy(output,input);
    strcat(output,dictionary->Entry[Index].data);
}