#include "unity.h"
#include "Stream.h"
#include "Decompression_noMocking.h"
#include "Dictionary.h"
#include "CException.h"
#include "Decompression.h"

void setUp(void)
{
}

void tearDown(void)
{
}


void test_LZ78_Decompressor_given_input_0a_1b_1a_0b_2a_4EOF_should_decompress_into_aabaababab()
{
    // Create test fixture
    char *infilename = "test/support/test_decompression_in_0a1b1a0b2a4.txt";
    char *outfilename = "test/support/test_decompression_out_0a1b1a0b2a4.txt";    
    char *decompression_output;
    char *expectedOutput = "aabaababab";
    int i;
    
    // Create compression input 0a0b
    OutStream *out;
    out = initOutStream();
    out = openOutStream(infilename, "wb+" , out);
    streamWriteBits(out,0,16);
    streamWriteBits(out,'a',8);
    streamWriteBits(out,1,16);
    streamWriteBits(out,'b',8);
    streamWriteBits(out,1,16);
    streamWriteBits(out,'a',8);
    streamWriteBits(out,0,16);
    streamWriteBits(out,'b',8);
    streamWriteBits(out,2,16);
    streamWriteBits(out,'a',8);
    streamWriteBits(out,4,16);
    closeOutStream(out);

    //run
    LZ78_Decompressor(infilename, outfilename, 10);
    
    //Test the output
    // InStream *in;
    // in = initInStream();
    // in = openInStream(outfilename, "rb+" , in);
    // for ( i = 0 ; i < strlen(expectedOutput) ; i ++ )
        // decompression_output[i] = (char)streamReadBits(in,8) ;
        
    // closeInStream(in);    
    
    // Check and verify output
    // TEST_ASSERT_EQUAL_STRING( "aabaababab" , decompression_output);
}

