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


void testing()
{
    //Create test fixture
    unsigned int storage[10] = {};
    // InStream *in = initInStream();                                              //init InStream
    // storage[0] = streamReadBits(in,16) ;
    // storage[1] = streamReadBits(in,8) ;
    // storage[2] = streamReadBits(in,16) ;
    // storage[3] = streamReadBits(in,8) ;
    // closeInStream(in);
        
    // int position = getPositionInFile(in);
  
    // TEST_ASSERT_EQUAL(1, storage[2]);
    // TEST_ASSERT_EQUAL((int)('a'), storage[1]);
    // TEST_ASSERT_EQUAL(1, storage[2]);
    // TEST_ASSERT_EQUAL((int)('b'), storage[3]);
    // TEST_ASSERT_EQUAL('a', storage[1]);

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

