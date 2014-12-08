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



/*  Test for refresh dictionary with dicionary size 1
    This test is quite similar with the one in Decompression.c but
    this test is testing with some real input instead of mocking
    
    Test when dictionary full should refresh and place the value correctly
    
    Compression Input :     0a0b0c0d
    Dictionary Size   :     1
            
    Expected Dictionary
    
    First time
    0.  a
    
    2nd time
    0.  b
    
    3rd time
    0.  c
    
    4th time
    0.  d
    
 */
void xtest_rebuildDictionaryForDecompression_given_0a0b0c0d_and_dictionary_size_is_1_should_update_the_dictionary_correctly()
{
    //Create test fixture
    char *infilename = "test/support/finaldecompression_in1.txt";
    char *outfilename = "test/support/finaldecompression_out1.txt";    
    int status , lastDictionaryLocation = -1, dictSize = 1, lastDecompressPosition = 0;
    Dictionary *dict = initDictionary(dictSize);
    OutStream *out = initOutStream();
    InStream *in = initInStream();
    
    //Create compression input 0a0b
    out = openOutStream(infilename, "wb+" , out);
    streamWriteBits(out,0,16);
    streamWriteBits(out,'a',8);
    streamWriteBits(out,0,16);
    streamWriteBits(out,'b',8);
    streamWriteBits(out,0,16);
    streamWriteBits(out,'c',8);
    streamWriteBits(out,0,16);
    streamWriteBits(out,'d',8);
    closeOutStream(out);
    
    //Build dictionaryint 
    in = openInStream(infilename, "rb+" , in);
    status = finalrebuildDictionaryForDecompression(dict, in, &lastDecompressPosition, lastDictionaryLocation);
    
    //verify dictionary
    TEST_ASSERT_EQUAL(3 , status);
    TEST_ASSERT_EQUAL(0 , lastDecompressPosition);
    TEST_ASSERT_EQUAL_STRING( "a" , dict->Entry[0].data );
    TEST_ASSERT_EQUAL(1 , dict->Entry[0].entrySize);
    
    // rebuild dictionary
    // refreshDictionaryEntryData(dict, dictSize);
    // TEST_ASSERT_EQUAL(3 , lastDecompressPosition);
    // status = finalrebuildDictionaryForDecompression(dict, in, &lastDecompressPosition);

    
    //verify dictionary
    // TEST_ASSERT_EQUAL(6 , status);      
    // TEST_ASSERT_EQUAL_STRING( "b" , dict->Entry[0].data );
    // TEST_ASSERT_EQUAL(1 , dict->Entry[0].entrySize);
    
    //rebuild dictionary
    // refreshDictionaryEntryData(dict, dictSize);
    // TEST_ASSERT_EQUAL(6 , lastDecompressPosition);
    // status = finalrebuildDictionaryForDecompression(dict, in, &lastDecompressPosition);

 
    //verify dictionary
    // TEST_ASSERT_EQUAL(9 , status);      
    // TEST_ASSERT_EQUAL_STRING( "c" , dict->Entry[0].data );
    // TEST_ASSERT_EQUAL(1 , dict->Entry[0].entrySize);
    
    
    //rebuild dictionary
    // refreshDictionaryEntryData(dict, dictSize);
    // TEST_ASSERT_EQUAL(9 , lastDecompressPosition);
    // status = finalrebuildDictionaryForDecompression(dict, in, &lastDecompressPosition);

    
    //verify dictionary
    // TEST_ASSERT_EQUAL(-1 , status);      
    // TEST_ASSERT_EQUAL_STRING( "d" , dict->Entry[0].data );
    // TEST_ASSERT_EQUAL(1 , dict->Entry[0].entrySize);

}



/*  Test for refresh dictionary with dictionary size 3
    This test is quite similar with the one in Decompression.c but
    this test is testing with some real input instead of mocking
    
    Test when dictionary full should refresh and place the value correctly
    
    Compression Input :     0a0b0c0d
    Dictionary Size   :     3
            
    Expected Dictionary
    
    First time
    0.  a
    1.  b
    2.  c
    
    2nd time
    0.  d
    
 */
void xtest_rebuildDictionaryForDecompression_given_0a0b0c0d_and_dictionary_size_is_3_should_update_the_dictionary_correctly()
{
    //Create test fixture
    char *infilename = "test/support/finaldecompression_in1.txt";
    char *outfilename = "test/support/finaldecompression_out1.txt";    
    int status , lastDecompressPosition = -1;
    int dictSize = 3;
    Dictionary *dict = initDictionary(dictSize);
    OutStream *out = initOutStream();
    InStream *in = initInStream();
    
    //Create compression input 0a0b
    out = openOutStream(infilename, "wb+" , out);
    streamWriteBits(out,0,16);
    streamWriteBits(out,'a',8);
    streamWriteBits(out,0,16);
    streamWriteBits(out,'b',8);
    streamWriteBits(out,0,16);
    streamWriteBits(out,'c',8);
    streamWriteBits(out,0,16);
    streamWriteBits(out,'d',8);
    closeOutStream(out);
    
    //Build dictionary
    in = openInStream(infilename, "rb+" , in);
    status = rebuildDictionaryForDecompression(dict, in, &lastDecompressPosition);
    closeInStream(in);
    
    //verify dictionary
    TEST_ASSERT_EQUAL(9 , status);
    TEST_ASSERT_EQUAL_STRING( "a" , dict->Entry[0].data );
    TEST_ASSERT_EQUAL(1 , dict->Entry[0].entrySize);
    TEST_ASSERT_EQUAL_STRING( "b" , dict->Entry[1].data );
    TEST_ASSERT_EQUAL(1 , dict->Entry[1].entrySize);
    TEST_ASSERT_EQUAL_STRING( "c" , dict->Entry[2].data );
    TEST_ASSERT_EQUAL(1 , dict->Entry[2].entrySize);
    
    //rebuild dictionary
    in = openInStream(infilename, "rb+" , in);
    refreshDictionaryEntryData(dict, dictSize);
    TEST_ASSERT_EQUAL(9 , lastDecompressPosition);
    status = rebuildDictionaryForDecompression(dict, in, &lastDecompressPosition);
    closeInStream(in);
    
    //verify dictionary
    TEST_ASSERT_EQUAL(-1 , status);      
    TEST_ASSERT_EQUAL_STRING( "d" , dict->Entry[0].data );
    TEST_ASSERT_EQUAL(1 , dict->Entry[0].entrySize);
    
}


/*  Test for dictionary no refresh
    This test is quite similar with the one in Decompression.c but
    this test is testing with some real input instead of mocking
    
    Input             :     wabba wabba
    Compression Input :     0w0a0b3a0space1a3b2
    Dictionary Size   :     
            
    Expected Dictionary
    
    0.  w
    1.  a
    2.  b
    3.  ba
    4.  space
    5   wa
    6.  bb
    
 */
void xtest_rebuildDictionaryForDecompression_given_0w0a0b3a0space1a3b2_and_dictionary_size_is_10_should_update_the_dictionary_correctly()
{
    //Create test fixture
    char *infilename = "test/support/finaldecompression_in2.txt";
    char *outfilename = "test/support/finaldecompression_out2.txt";    
    int status , lastDecompressPosition = -1;
    int dictSize = 10;
    Dictionary *dict = initDictionary(dictSize);
    OutStream *out = initOutStream();
    InStream *in = initInStream();
    
    //Create compression input 0a0b
    out = openOutStream(infilename, "wb+" , out);
    streamWriteBits(out,0,16);  streamWriteBits(out,'w',8);
    streamWriteBits(out,0,16);  streamWriteBits(out,'a',8);
    streamWriteBits(out,0,16);  streamWriteBits(out,'b',8);
    streamWriteBits(out,3,16);  streamWriteBits(out,'a',8);
    streamWriteBits(out,0,16);  streamWriteBits(out,' ',8);
    streamWriteBits(out,1,16);  streamWriteBits(out,'a',8);
    streamWriteBits(out,3,16);  streamWriteBits(out,'b',8);
    streamWriteBits(out,2,16);
    closeOutStream(out);
    
    //Build dictionary
    in = openInStream(infilename, "rb+" , in);
    status = rebuildDictionaryForDecompression(dict, in, &lastDecompressPosition);
    closeInStream(in);
    
    //verify dictionary
    TEST_ASSERT_EQUAL(-1 , status);
    TEST_ASSERT_EQUAL_STRING( "w" , dict->Entry[0].data );  TEST_ASSERT_EQUAL(1 , dict->Entry[0].entrySize);   
    TEST_ASSERT_EQUAL_STRING( "a" , dict->Entry[1].data );  TEST_ASSERT_EQUAL(1 , dict->Entry[1].entrySize);
    TEST_ASSERT_EQUAL_STRING( "b" , dict->Entry[2].data );  TEST_ASSERT_EQUAL(1 , dict->Entry[2].entrySize);
    TEST_ASSERT_EQUAL_STRING( "ba" , dict->Entry[3].data );  TEST_ASSERT_EQUAL(2 , dict->Entry[3].entrySize);
    TEST_ASSERT_EQUAL_STRING( " " , dict->Entry[4].data );  TEST_ASSERT_EQUAL(1 , dict->Entry[4].entrySize);
    TEST_ASSERT_EQUAL_STRING( "wa" , dict->Entry[5].data );  TEST_ASSERT_EQUAL(2 , dict->Entry[5].entrySize);
    TEST_ASSERT_EQUAL_STRING( "bb" , dict->Entry[6].data );  TEST_ASSERT_EQUAL(2 , dict->Entry[6].entrySize);

}


void xtest_LZ78_Decompressor_given_input_0a_0b_0c_0d_dictionary_size_1_should_decompress_into_abcd()
{
    // Create test fixture
    char *infilename = "test/support/LZ78decompressor_in_0a0b0c0d.txt";
    char *outfilename = "test/support/LZ78decompressor_out_0a0b0c0d.txt";    
    char *decompression_output;
    char *expectedOutput = "aabaababab";


    // Create compression input 0a0b
    OutStream *out;
    out = initOutStream();
    out = openOutStream(infilename, "wb+" , out);
    streamWriteBits(out,0,16);
    streamWriteBits(out,'a',8);
    streamWriteBits(out,0,16);
    streamWriteBits(out,'b',8);
    streamWriteBits(out,0,16);
    streamWriteBits(out,'c',8);
    streamWriteBits(out,0,16);
    streamWriteBits(out,'d',8);
    closeOutStream(out);

    //run
    LZ78_Decompressor(infilename, outfilename, 1);


}

void xtest_LZ78_Decompressor_given_input_0a_1b_1a_0b_2a_4EOF_should_decompress_into_aabaababab()
{
    // Create test fixture
    char *infilename = "test/support/LZ78decompressor_in_0a1b1a0b2a4.txt";
    char *outfilename = "test/support/LZ78decompressor_out_0a1b1a0b2a4.txt";    
    char *decompression_output;
    char *expectedOutput = "aabaababab";
    unsigned int value;
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
    // for ( i = 0 ; i < strlen("aabaababab") ; i ++ )
        // decompression_output[i] = (char)streamReadBits(in,8) ;
        
    // closeInStream(in);    
    
    // Check and verify output
    // TEST_ASSERT_EQUAL_STRING( "aabaababab" , decompression_output);
}


void testing()
{
    char *infilename = "test/support/sampleText_forCompresssion_Compressed_Fixed.txt";
    char *outfilename = "test/support/testing_out.txt"; 
    LZ78_Decompressor(infilename, outfilename, 4096);






}