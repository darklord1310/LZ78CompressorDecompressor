#ifndef Utility_H
#define Utility_H


#include "Stream.h"

typedef enum { Fixed,
               Variable    
             } Mode;
             
int determineNumberOfBitsRequired(int value,int dictionaryIndex);
void renameCompressedFile(char *InfileName,char *CompressedName,int mode);
int verifyDecompressedFile(char *infilename1, char *infilename2);


#endif // Utility_H
