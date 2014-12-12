#include "unity.h"
#include "Decompression.h"
#include "Dictionary.h"
#include "mock_Stream.h"
#include <assert.h>


void setUp(void)
{
    
}

void tearDown(void)
{

}



/*test case when dictionary is not full, and no merging of data occur
 *
 *  Given input = 1a1b
 */
void test_AddDataToDictionary_given_1a_1b_and_size_is_larger_than_data_written_should_add_into_dictionary_correctly()
{
    int value;
    Dictionary *dict = initDictionary(10);
    
    value = AddDataToDictionary(dict, 1 , (unsigned int)('a')   );
    TEST_ASSERT_EQUAL(1, value);
    TEST_ASSERT_EQUAL(1, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);     TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    TEST_ASSERT_EQUAL_STRING("" ,dict->Entry[1].data);     TEST_ASSERT_EQUAL(0 ,dict->Entry[1].entrySize);

    
    value = AddDataToDictionary(dict, 1 , (unsigned int)('b')   );
    TEST_ASSERT_EQUAL(1, value);
    TEST_ASSERT_EQUAL(2, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);     TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    TEST_ASSERT_EQUAL_STRING("b" ,dict->Entry[1].data);     TEST_ASSERT_EQUAL(1 ,dict->Entry[1].entrySize);
}




/*test case when dictionary is not full, and merging of data occur
 *
 *  Given input = 1a2b
 */
void test_AddDataToDictionary_given_1a_2b_3c_and_size_is_larger_than_data_written_should_add_into_dictionary_correctly()
{
    int value;
    Dictionary *dict = initDictionary(10);
    
    value = AddDataToDictionary(dict, 1 , (unsigned int)('a')   );
    TEST_ASSERT_EQUAL(1, value);
    TEST_ASSERT_EQUAL(1, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);     TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    TEST_ASSERT_EQUAL_STRING("" ,dict->Entry[1].data);     TEST_ASSERT_EQUAL(0 ,dict->Entry[1].entrySize);

   
    value = AddDataToDictionary(dict, 2 , (unsigned int)('b')   );
    TEST_ASSERT_EQUAL(1, value);
    TEST_ASSERT_EQUAL(2, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);     TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    TEST_ASSERT_EQUAL_STRING("ab" ,dict->Entry[1].data);    TEST_ASSERT_EQUAL(2 ,dict->Entry[1].entrySize);
    
    value = AddDataToDictionary(dict, 3 , (unsigned int)('c')   );
    TEST_ASSERT_EQUAL(1, value);
    TEST_ASSERT_EQUAL(3, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);     TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    TEST_ASSERT_EQUAL_STRING("ab" ,dict->Entry[1].data);    TEST_ASSERT_EQUAL(2 ,dict->Entry[1].entrySize);
    TEST_ASSERT_EQUAL_STRING("abc" ,dict->Entry[2].data);    TEST_ASSERT_EQUAL(3 ,dict->Entry[2].entrySize);
}




/*test case when dictionary is full, and try to add into dictionary
 *
 *  Given input = 1a2b
 */
void test_AddDataToDictionary_given_1a_2b_and_size_is_smaller_than_data_written_should_not_add_into_dictionary_correctly()
{
    int value;
    Dictionary *dict = initDictionary(1);
    
    value = AddDataToDictionary(dict, 1 , (unsigned int)('a')   );
    TEST_ASSERT_EQUAL(1, value);
    TEST_ASSERT_EQUAL(1, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);     TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);

   
    value = AddDataToDictionary(dict, 2 , (unsigned int)('b')   );
    TEST_ASSERT_EQUAL(0, value);
    
    //Expect the whole dictionary stay the same as before
    TEST_ASSERT_EQUAL(1, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);     TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);

}


//test case when dictionary is not full for decompression when index contain all zeroes only
void test_Decompression_given_1a1b1c_and_when_dictionary_is_not_full_should_decompress_correctly_into_abc()
{
    int value;
    OutStream out;
    Dictionary *dict = initDictionary(10);

    //create dictionary 
    value = AddDataToDictionary(dict, 1 , (unsigned int)('a')   );
    assert(value != 0);
    value = AddDataToDictionary(dict, 1 , (unsigned int)('b')   );
    assert(value != 0);
    value = AddDataToDictionary(dict, 1 , (unsigned int)('c')   );
    assert(value != 0);

    
    //create test fixture
    streamWriteBits_Expect(&out, (unsigned int)('a'), 8);           //expect a here
    streamWriteBits_Expect(&out, (unsigned int)('b'), 8);           //expect b here
    streamWriteBits_Expect(&out, (unsigned int)('c'), 8);           //expect c here
    
    //run
    Decompression(&out, 1 , (unsigned int)('a'), dict);
    Decompression(&out, 1 , (unsigned int)('b'), dict);
    Decompression(&out, 1 , (unsigned int)('c'), dict);
}



//test case when dictionary is not full for decompression when index not only zero
void test_Decompression_given_1a2b3c_and_when_dictionary_is_not_full_should_decompress_correctly_into_aababc()
{
    int value;
    OutStream out;
    Dictionary *dict = initDictionary(10);

    //create dictionary 
    value = AddDataToDictionary(dict, 1 , (unsigned int)('a')   );
    assert(value != 0);
    value = AddDataToDictionary(dict, 2 , (unsigned int)('b')   );
    assert(value != 0);
    value = AddDataToDictionary(dict, 3 , (unsigned int)('c')   );
    assert(value != 0);

    
    //create test fixture
    
    //expect a here
    streamWriteBits_Expect(&out, (unsigned int)('a'), 8); 
    
    //expect ab here
    streamWriteBits_Expect(&out, (unsigned int)('a'), 8);           
    streamWriteBits_Expect(&out, (unsigned int)('b'), 8); 
    
    //expect abcc here
    streamWriteBits_Expect(&out, (unsigned int)('a'), 8);           
    streamWriteBits_Expect(&out, (unsigned int)('b'), 8); 
    streamWriteBits_Expect(&out, (unsigned int)('c'), 8);     

    
    //run
    Decompression(&out, 1 , (unsigned int)('a'), dict);
    Decompression(&out, 2 , (unsigned int)('b'), dict);
    Decompression(&out, 3 , (unsigned int)('c'), dict);
}



// test case when dictionary is not needed to be refresh and all index is only 1
void test_LZ78_Decompression_Fixed_given_input_1a1b1c_and_size_of_10_should_decompress_into_abc()
{
    int dictSize = 10;
    char *infilename = "anyfile_in.txt";
    char *outfilename = "anyfile_out.txt";
    Dictionary *dict;
    InStream in;
    OutStream out;
    
    // create test fixture
    initInStream_ExpectAndReturn(&in);
    initOutStream_ExpectAndReturn(&out);
    openInStream_ExpectAndReturn(infilename, "rb+" , &in, &in);                       
    openOutStream_ExpectAndReturn(outfilename, "wb+" , &out, &out);
    streamReadBits_ExpectAndReturn(&in, 16, 1);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 8, (unsigned int)('a') );
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamWriteBits_Expect(&out, (unsigned int)('a') , 8 );
    streamReadBits_ExpectAndReturn(&in, 16, 1);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 8, (unsigned int)('b') );
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamWriteBits_Expect(&out, (unsigned int)('b') , 8 );
    streamReadBits_ExpectAndReturn(&in, 16, 1);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 8, (unsigned int)('c') );
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamWriteBits_Expect(&out, (unsigned int)('c') , 8 );
    streamReadBits_ExpectAndReturn(&in, 16, EOF);
    checkEndOfFile_ExpectAndReturn(&in, 1);
    closeInStream_ExpectAndReturn(&in, &in);
    closeOutStream_ExpectAndReturn(&out , &out);
    freeInStream_Expect(&in);
    freeOutStream_Expect(&out);

    
    LZ78_Decompression_Fixed(&in, &out, dict, infilename, outfilename, dictSize);
}



// test case when dictionary is not needed to be refresh and the index is not only 1
void test_LZ78_Decompression_Fixed_given_input_1a2b3c_and_size_of_10_should_decompress_into_abc()
{
    int dictSize = 10;
    char *infilename = "anyfile_in.txt";
    char *outfilename = "anyfile_out.txt";
    Dictionary *dict;
    InStream in;
    OutStream out;
    
    // create test fixture
    initInStream_ExpectAndReturn(&in);
    initOutStream_ExpectAndReturn(&out);
    openInStream_ExpectAndReturn(infilename, "rb+" , &in, &in);                       
    openOutStream_ExpectAndReturn(outfilename, "wb+" , &out, &out);
    streamReadBits_ExpectAndReturn(&in, 16, 1);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 8, (unsigned int)('a') );
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamWriteBits_Expect(&out, (unsigned int)('a') , 8 );            //expect a
    streamReadBits_ExpectAndReturn(&in, 16, 2);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 8, (unsigned int)('b') );
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamWriteBits_Expect(&out, (unsigned int)('a') , 8 );             //expect ab
    streamWriteBits_Expect(&out, (unsigned int)('b') , 8 );
    streamReadBits_ExpectAndReturn(&in, 16, 3);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 8, (unsigned int)('c') );
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamWriteBits_Expect(&out, (unsigned int)('a') , 8 );             //expect abc
    streamWriteBits_Expect(&out, (unsigned int)('b') , 8 );
    streamWriteBits_Expect(&out, (unsigned int)('c') , 8 );
    streamReadBits_ExpectAndReturn(&in, 16, EOF);
    checkEndOfFile_ExpectAndReturn(&in, 1);
    closeInStream_ExpectAndReturn(&in, &in);
    closeOutStream_ExpectAndReturn(&out , &out);
    freeInStream_Expect(&in);
    freeOutStream_Expect(&out);

    
    LZ78_Decompression_Fixed(&in, &out, dict, infilename, outfilename, dictSize);
}





// test case when dictionary is needed to be refresh 
void test_LZ78_Decompression_Fixed_given_input_1a1b1c_and_size_of_1_should_decompress_into_abc()
{
    int dictSize = 1;
    char *infilename = "anyfile_in.txt";
    char *outfilename = "anyfile_out.txt";
    Dictionary *dict;
    InStream in;
    OutStream out;
    
    // create test fixture
    initInStream_ExpectAndReturn(&in);
    initOutStream_ExpectAndReturn(&out);
    openInStream_ExpectAndReturn(infilename, "rb+" , &in, &in);                       
    openOutStream_ExpectAndReturn(outfilename, "wb+" , &out, &out); 
    streamReadBits_ExpectAndReturn(&in, 16, 1);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 8, (unsigned int)('a') );
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamWriteBits_Expect(&out, (unsigned int)('a') , 8 );            //expect a
    streamReadBits_ExpectAndReturn(&in, 16, 1);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 8, (unsigned int)('b') );
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamWriteBits_Expect(&out, (unsigned int)('b') , 8 );             //expect b
    streamReadBits_ExpectAndReturn(&in, 16, 1);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 8, (unsigned int)('c') );       
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamWriteBits_Expect(&out, (unsigned int)('c') , 8 );             //expect c
    streamReadBits_ExpectAndReturn(&in, 16, EOF);
    checkEndOfFile_ExpectAndReturn(&in, 1);
    closeInStream_ExpectAndReturn(&in, &in);
    closeOutStream_ExpectAndReturn(&out , &out);
    freeInStream_Expect(&in);
    freeOutStream_Expect(&out);

    
    LZ78_Decompression_Fixed(&in, &out, dict, infilename, outfilename, dictSize);
}


void test_getVariableIndex_given_0_should_return_1()
{
    int numberofbits;
    
    //initialize dictionary
    Dictionary *dict = initDictionary(10);
    dict->currentIndex = 0;
    
    numberofbits = getVariableIndex(dict);
    TEST_ASSERT_EQUAL(1 , numberofbits);
}



void test_getVariableIndex_given_1_should_return_2()
{
    int numberofbits;
    
    //initialize dictionary
    Dictionary *dict = initDictionary(10);
    dict->currentIndex = 1;
    
    numberofbits = getVariableIndex(dict);
    TEST_ASSERT_EQUAL(2 , numberofbits);
}

void test_getVariableIndex_given_2_should_return_2()
{
    int numberofbits;
    
    //initialize dictionary
    Dictionary *dict = initDictionary(10);
    dict->currentIndex = 2;
    
    numberofbits = getVariableIndex(dict);
    TEST_ASSERT_EQUAL(2 , numberofbits);
}

void test_getVariableIndex_given_5_should_return_3()
{
    int numberofbits;
    
    //initialize dictionary
    Dictionary *dict = initDictionary(10);
    dict->currentIndex = 5;
    
    numberofbits = getVariableIndex(dict);
    TEST_ASSERT_EQUAL(3 , numberofbits);
}


void test_getVariableIndex_given_4096_should_return_13()
{
    int numberofbits;
    
    //initialize dictionary
    Dictionary *dict = initDictionary(10);
    dict->currentIndex = 4095;
    
    numberofbits = getVariableIndex(dict);
    TEST_ASSERT_EQUAL(13 , numberofbits);
}



// test case when dictionary is not needed to be refresh, index is only 1
void test_LZ78_Decompression_Variable_given_input_1a1b_and_size_of_10_should_decompress_into_ab()
{
    int dictSize = 10;
    char *infilename = "anyfile_in.txt";
    char *outfilename = "anyfile_out.txt";
    Dictionary *dict;
    InStream in;
    OutStream out;
    
    // create test fixture
    initInStream_ExpectAndReturn(&in);
    initOutStream_ExpectAndReturn(&out);
    openInStream_ExpectAndReturn(infilename, "rb+" , &in, &in);                       
    openOutStream_ExpectAndReturn(outfilename, "wb+" , &out, &out); 
    streamReadBits_ExpectAndReturn(&in, 1, 1);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 8, (unsigned int)('a') );
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamWriteBits_Expect(&out, (unsigned int)('a') , 8 );            //expect a
    streamReadBits_ExpectAndReturn(&in, 2, 2);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 8, (unsigned int)('b') );
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamWriteBits_Expect(&out, (unsigned int)('a') , 8 );             //expect a
    streamWriteBits_Expect(&out, (unsigned int)('b') , 8 );             //expect b
    streamReadBits_ExpectAndReturn(&in, 2, 2);
    checkEndOfFile_ExpectAndReturn(&in, EOF);
    closeInStream_ExpectAndReturn(&in, &in);
    closeOutStream_ExpectAndReturn(&out , &out);
    freeInStream_Expect(&in);
    freeOutStream_Expect(&out);    
    
    LZ78_Decompression_Variable(&in, &out, dict, infilename, outfilename, dictSize);
}


// test case when dictionary is not needed to be refresh, index is not only 1
void test_LZ78_Decompression_Variable_given_input_1a2b2_and_size_of_10_should_decompress_into_aaba()
{
    int dictSize = 10;
    char *infilename = "anyfile_in.txt";
    char *outfilename = "anyfile_out.txt";
    Dictionary *dict;
    InStream in;
    OutStream out;
    
    // create test fixture
    initInStream_ExpectAndReturn(&in);
    initOutStream_ExpectAndReturn(&out);
    openInStream_ExpectAndReturn(infilename, "rb+" , &in, &in);                       
    openOutStream_ExpectAndReturn(outfilename, "wb+" , &out, &out); 
    streamReadBits_ExpectAndReturn(&in, 1, 1);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 8, (unsigned int)('a') );
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamWriteBits_Expect(&out, (unsigned int)('a') , 8 );            //expect a
    streamReadBits_ExpectAndReturn(&in, 2, 2);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 8, (unsigned int)('b') );
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamWriteBits_Expect(&out, (unsigned int)('a') , 8 );             //expect a
    streamWriteBits_Expect(&out, (unsigned int)('b') , 8 );             //expect b
    streamReadBits_ExpectAndReturn(&in, 2, 2);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 8, EOF); 
    checkEndOfFile_ExpectAndReturn(&in, 1);
    streamWriteBits_Expect(&out, (unsigned int)('a') , 8 );             //expect a    
    closeInStream_ExpectAndReturn(&in, &in);
    closeOutStream_ExpectAndReturn(&out , &out);
    freeInStream_Expect(&in);
    freeOutStream_Expect(&out);    
    
    LZ78_Decompression_Variable(&in, &out, dict, infilename, outfilename, dictSize);
}



// test case when dictionary is needed to be refresh 
void test_LZ78_Decompression_Variable_given_input_1a2b1b_and_size_of_2_should_decompress_into_aabb()
{
    int dictSize = 2;
    char *infilename = "anyfile_in.txt";
    char *outfilename = "anyfile_out.txt";
    Dictionary *dict;
    InStream in;
    OutStream out;
    
    // create test fixture
    initInStream_ExpectAndReturn(&in);
    initOutStream_ExpectAndReturn(&out);
    openInStream_ExpectAndReturn(infilename, "rb+" , &in, &in);                       
    openOutStream_ExpectAndReturn(outfilename, "wb+" , &out, &out); 
    streamReadBits_ExpectAndReturn(&in, 1, 1);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 8, (unsigned int)('a') );
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamWriteBits_Expect(&out, (unsigned int)('a') , 8 );            //expect a
    streamReadBits_ExpectAndReturn(&in, 2, 2);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 8, (unsigned int)('b') );
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamWriteBits_Expect(&out, (unsigned int)('a') , 8 );             //expect a
    streamWriteBits_Expect(&out, (unsigned int)('b') , 8 );             //expect b
    streamReadBits_ExpectAndReturn(&in, 1, 1);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 8, (unsigned int)('b') );       
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamWriteBits_Expect(&out, (unsigned int)('b') , 8 );             //expect b
    streamReadBits_ExpectAndReturn(&in, 2, EOF);
    checkEndOfFile_ExpectAndReturn(&in, 1);
    closeInStream_ExpectAndReturn(&in, &in);
    closeOutStream_ExpectAndReturn(&out , &out);
    freeInStream_Expect(&in);
    freeOutStream_Expect(&out);
    
    LZ78_Decompression_Variable(&in, &out, dict, infilename, outfilename, dictSize);
}