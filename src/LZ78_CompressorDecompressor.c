#include "LZ78_CompressorDecompressor.h"
#include <string.h>
#include "malloc.h"

void LZ78_CompressorDecompressor(char *InfileName,char *OutfileName,int dictSize,int mode)
{
	char *CompressedfileName ;
    CompressedfileName = calloc(strlen(InfileName)+4,sizeof(char));    
	renameCompressedFile(InfileName,CompressedfileName);
    
	InStream *in = initInStream();
    OutStream *out = initOutStream();
    Dictionary *dictionary = initDictionary(dictSize);
	
	in = openInStream(InfileName, "rb" , in);
    out = openOutStream(CompressedfileName, "wb" , out);

	LZ78_Compressor(dictionary,in,out,mode);
	
	closeInStream(in);
    closeOutStream(out);
    freeInStream(in);
    freeOutStream(out);
    destroyDictionary(dictionary,dictSize);
	
	LZ78_Decompressor(CompressedfileName,OutfileName,dictSize,mode);
    free(CompressedfileName);
}

