#ifndef Decompression_H
#define Decompression_H

#ifdef _WIN32

/* You should define ADD_EXPORTS *only* when building the DLL. */
#ifdef ADD_EXPORTS
#define ADDAPI __declspec(dllexport)
#else
#define ADDAPI __declspec(dllimport)
#endif

/* Define calling convention in one place, for convenience. */
#define ADDCALL __cdecl

#else /* _WIN32 not defined. */

/* Define with no value on non-Windows OSes. */
#define ADDAPI
#define ADDCALL

#endif


#include "Dictionary.h"
#include "Stream.h"
#include "Utility.h"

ADDAPI void ADDCALL  LZ78_Decompressor(char *infilename, char *outfilename, int dictSize, int mode);
void LZ78_Decompression_Fixed(InStream *in, OutStream *out, Dictionary *dictionary, char *infilename, char *outfilename, int dictSize);
void LZ78_Decompression_Variable(InStream *in, OutStream *out, Dictionary *dictionary, char *infilename, char *outfilename, int dictSize);
int AddDataToDictionary(Dictionary *dictionary, unsigned int index, unsigned int data);
void Decompression(OutStream *out, unsigned int index, unsigned int data, Dictionary *dictionary);
unsigned int getVariableIndex(Dictionary *dictionary);

#endif // Decompression_H
