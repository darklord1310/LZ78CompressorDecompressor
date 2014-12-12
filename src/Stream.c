#include "Stream.h"
#include <malloc.h>
#include <string.h>
#include <CException.h>

/*  Initialise InStream
 *
 *  Output : return initialised InStream
 */
InStream *initInStream()
{
    InStream *in;
    in = malloc(sizeof(InStream));
    in->byteToRead = 0;
    in->bitIndex = 8;

    return in;
}

/*  Initialise OutStream
 *
 *  Output : return initialised OutStream
 */
OutStream *initOutStream()
{
    OutStream *out;
    out = malloc(sizeof(OutStream));
    out->byteToWrite = 0;
    out->bitIndex = 0;

    return out;
}

/*  Free InStream
 *
 * Input : in is the InStream to be freed
 */
void freeInStream(InStream *in)
{
    free(in);
}

/*  Free OutStream
 *
 *  Input : out is the OutStream to be freed
 */
void freeOutStream(OutStream *out)
{
    free(out);
}

/*  Open selected file in selected mode for InStream
 *
 *  Input : filename    : filename is the name of the file to be opened
 *          mode        : mode is the file operation mode 
 *          in          : in is the InStream that going to open the file
 */
InStream *openInStream(char *filename, char *mode, InStream *in)
{
    in->file = fopen( filename, mode);
    if( in->file == NULL)
        Throw(ERR_FAILED_TO_OPEN);
    else
        in->filename = filename;

    return in;
}


/*  Open selected file in selected mode for OutStream
 *
 *  Input : filename    : filename is the name of the file to be opened
 *          mode        : mode is the file operation mode 
 *          out         : out is the OutStream that going to open the file
 */
OutStream *openOutStream(char *filename, char *mode, OutStream *out)
{
    out->file = fopen( filename, mode);
    out->filename = filename;

    return out;
}

/*  Close file in OutStream
 *
 *  Input :  out         : out is the OutStream containing the file to be close
 */
OutStream *closeOutStream(OutStream *out)
{
    if (out->bitIndex != 0)
        streamFlush(out);
        
    fclose(out->file);
}

/*  Close file in InStream
 *
 *  Input : in          : in is the InStream containing the file to be close
 */
InStream *closeInStream(InStream *in)
{
    fclose(in->file);
}

/*  Read 1 bit of data from InStream byteToRead
 *
 *  Input : in          : in is the InStream containing the bit to read
 *
 *  Output: return 1 if the bit is 1
 *          return 0 if the bit is 0
 */
unsigned int streamReadBit(InStream *in)
{
    int bitTest ;
    
    bitTest = in->byteToRead & (1 << in->bitIndex) ; //read lSB first
    in -> bitIndex ++ ;
    
    if (bitTest != 0 )
        return 1 ; 
    else 
        return 0 ;
}

/*  Read multiple bits of data from InStream
 *
 *  Input : in          : in is the InStream containing the bits to read
 *          bitSize     : bitSize is the amount of bits to be read          
 *
 *  Output: return read data 
 */
unsigned int streamReadBits(InStream *in, int bitSize)
{
    unsigned int dataRead = 0, bitRead = 0 ,i ;
    
    for ( i = 0 ; i < bitSize ; i ++)
    {
        if (in->bitIndex == 8 ) //fully extracted 1 byte
        {
            if (in->file != NULL)
				fread(&(in->byteToRead),1,1,in->file); //read new byte
            
			in->bitIndex = 0 ;
        }
        
        bitRead = streamReadBit(in);
        dataRead = dataRead | bitRead << i;
    }
    return dataRead ;
}

/*  Write 1 bit of data to OutStream byteToWrite
 *
 *  Input : out          : out is the OutStream that will write the bit to byteToWrite
 *
 */
void streamWriteBit(OutStream *out,int bitToWrite)
{
    out->byteToWrite |= (bitToWrite << out->bitIndex) ; //write lSB first
    out->bitIndex ++ ;
}

/*  Write multiple bits of data to OutStream byteToWrite
 *
 *  Input : out          : out is the OutStream that will write bits to byteToWrite
 *          value        : value is the value to be written 
 *          bitSize      : bitSize is the number of bits for the value to be written 
 *
 */
void streamWriteBits(OutStream *out,unsigned int value,int bitSize)
{
    int bitToWrite, i ,j ;
    
    for ( i = 0 ; i < bitSize ; i ++) //write value to buffer
    {
        if (out->bitIndex == 8)
            streamFlush(out);

        bitToWrite = value & (1 << i ) ;
        
        if (bitToWrite != 0 )
            bitToWrite = 1 ;
        else 
            bitToWrite = 0 ;
            
        streamWriteBit(out,bitToWrite);
    }
}    
    
/*  Flush byteToWrite in OutStream
 *
 *  Input : out          : out is the OutStream that contains the byteToWrite to be flushed
 */ 
void streamFlush(OutStream *out)
{
    int n;
    n = fwrite(&(out->byteToWrite),1,1,out->file);
    
    out->byteToWrite = 0;
    out->bitIndex = 0 ;
}

/* Check end of file(EOF)for the current file
 *
 * Input : in           : in is the InStream containing the file to be checked
 *
 * Output : return 1 if end of file is encountered
 *          return 0 if end of file is not encountered
 */
int checkEndOfFile(InStream *in)
{
    int result ;
    result = feof (in->file) ;
       
    if (result != 0)
        return 1;
    else 
        return 0;
}

