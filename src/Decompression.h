#ifndef Decompression_H
#define Decompression_H


#include "Dictionary.h"
#include "Stream.h"


void addDataToDictionary(Dictionary *dictionary, unsigned int data, unsigned int index);
int AddDataToDictionary(Dictionary *dictionary, unsigned int index, unsigned int data);
void Decompression(OutStream *out, unsigned int index, unsigned int data, Dictionary *dictionary);






#endif // Decompression_H
