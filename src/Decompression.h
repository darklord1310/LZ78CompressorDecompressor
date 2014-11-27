#ifndef Decompression_H
#define Decompression_H


#include "Dictionary.h"
#include "Stream.h"


char convertIntToChar(unsigned int inputdata);
int addDataToDictionary(Dictionary *dictionary, unsigned int data, unsigned int index);



#endif // Decompression_H
