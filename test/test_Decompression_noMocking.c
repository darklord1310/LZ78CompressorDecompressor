#include "unity.h"
#include "Decompression.h"
#include "Stream.h"
#include "Decompression_noMocking.h"
#include "Dictionary.h"
#include "CException.h"

void setUp(void)
{
}

void tearDown(void)
{
}


void test_getPositionInFile_after_read_6_byte_should_point_to_6()
{
    //Create test fixture
    unsigned int storage[10] = {};
    InStream *in = initInStream();                                              //init InStream
    in = openInStream("test/support/test_decompression_in_0a1b1a0b2a4.txt", "rb" , in);
    storage[0] = streamReadBits(in,16) ;
    storage[1] = streamReadBits(in,8) ;
    storage[2] = streamReadBits(in,16) ;
    storage[3] = streamReadBits(in,8) ;

        
    int position = getPositionInFile(in);
    TEST_ASSERT_EQUAL(6, position);
    closeInStream(in);
}



void test_LZ78_Decompressor_given_input_0a_1b_1a_0b_2a_4EOF_should_decompress_into_aabaababab()
{
    // Create test fixture
    char *infilename = "test/support/test_decompression_in_0a1b1a0b2a4.txt";
    char *outfilename = "test/support/test_decompression_out_0a1b1a0b2a4.txt";    
    
    // Create compression input 0a0b
    // OutStream *out;
    // out = initOutStream();
    // out = openOutStream(infilename, "wb" , out);
    // streamWriteBits(out,0,16);
    // streamWriteBits(out,'a',8);
    // streamWriteBits(out,1,16);
    // streamWriteBits(out,'b',8);
    // streamWriteBits(out,1,16);
    // streamWriteBits(out,'a',8);
    // streamWriteBits(out,0,16);
    // streamWriteBits(out,'b',8);
    // streamWriteBits(out,2,16);
    // streamWriteBits(out,'a',8);
    // streamWriteBits(out,4,16);
    // closeOutStream(out);

    //run
    LZ78_Decompressor(infilename, outfilename, 10);
    // int status = rebuildDictionaryForDecompression(dictionary, in);
    // in = closeInStream(in);                                          //close input file
}

