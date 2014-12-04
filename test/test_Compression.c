#include "unity.h"
#include <string.h>
#include "Dictionary.h"
#include "Compression.h"
#include "mock_Stream.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_compare_DictionaryData_given_input_AA_and_dictionaryEntry5_contains_AA_should_return_5()
{
    Dictionary *dict = initDictionary(10);
    
    addEntryData(dict, "aA");
    addEntryData(dict, "Aa");
    addEntryData(dict, "bB");
    addEntryData(dict, "Bb");
    addEntryData(dict, "cC");
    addEntryData(dict, "AA");
    addEntryData(dict, "AA");
    addEntryData(dict, "a");
    
    TEST_ASSERT_EQUAL(5,compare_DictionaryData("AA",dict));
    destroyDictionary(dict,10);
}

void test_compare_DictionaryData_given_input_CCC_and_dictionary_doesnt_contains_CCC_should_return_minus_1()
{
    Dictionary *dict = initDictionary(10);
    
    addEntryData(dict, "aA");
    addEntryData(dict, "Aa");
    addEntryData(dict, "bB");
    addEntryData(dict, "Bb");
    addEntryData(dict, "cC");
    addEntryData(dict, "AA");
    addEntryData(dict, "AA");
    addEntryData(dict, "a");
    
    TEST_ASSERT_EQUAL(-1,compare_DictionaryData("CCC",dict));
    destroyDictionary(dict,10);
}


void test_LZ78_Compressor_given_input_A_should_output_0A()
{
    Dictionary *dict = initDictionary(10);
    InStream in ; 
    OutStream out ;
    
    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,0,16);
    streamWriteBits_Expect(&out,'A',8);
    
    streamReadBits_ExpectAndReturn(&in,8,EOF);
    checkEndOfFile_ExpectAndReturn(&in,1);
    
    LZ78_Compressor(dict,&in,&out);

    TEST_ASSERT_EQUAL_STRING("A",dict->Entry[0].data);
    destroyDictionary(dict,10);
}

void test_LZ78_Compressor_given_input_AAAAAAAAA_should_output_0A_1A_2A_3EOF()
{
    Dictionary *dict = initDictionary(10);
    InStream in ; 
    OutStream out ;
    
    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,0,16);
    streamWriteBits_Expect(&out,'A',8);
    
    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,1,16);
    streamWriteBits_Expect(&out,'A',8);
    
    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,2,16);
    streamWriteBits_Expect(&out,'A',8);
    
    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,EOF);
    checkEndOfFile_ExpectAndReturn(&in,1);
    streamWriteBits_Expect(&out,3,16);
    
    LZ78_Compressor(dict,&in,&out);

    TEST_ASSERT_EQUAL_STRING("A",dict->Entry[0].data);
    TEST_ASSERT_EQUAL_STRING("AA",dict->Entry[1].data);
    TEST_ASSERT_EQUAL_STRING("AAA",dict->Entry[2].data);
    
    destroyDictionary(dict,10);
}

void test_LZ78_Compressor_given_input_space_A_space_B_should_output_0space_0A_1B()
{
    Dictionary *dict = initDictionary(10);
    InStream in ; 
    OutStream out ;

    streamReadBits_ExpectAndReturn(&in,8,32);
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,0,16);
    streamWriteBits_Expect(&out,32,8);
    
    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,0,16);
    streamWriteBits_Expect(&out,'A',8);

    streamReadBits_ExpectAndReturn(&in,8,32);
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,'B');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,1,16);
    streamWriteBits_Expect(&out,'B',8);
    
    streamReadBits_ExpectAndReturn(&in,8,EOF);
    checkEndOfFile_ExpectAndReturn(&in,1);
    
    LZ78_Compressor(dict,&in,&out);

    TEST_ASSERT_EQUAL(32,dict->Entry[0].data[0]);
    TEST_ASSERT_EQUAL_STRING("A",dict->Entry[1].data);
    TEST_ASSERT_EQUAL_STRING(" B",dict->Entry[2].data);
    
    destroyDictionary(dict,10);
}

void test_LZ78_Compressor_dictionaryIndex_4095_input_ABCABC_should_refresh_dictionary_and_add()
{
    Dictionary *dict = initDictionary(4096);
    dict->currentIndex = 4095;
    InStream in ; 
    OutStream out ;

     /*Dictionary Entry 4095*/
    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,0,16);
    streamWriteBits_Expect(&out,'A',8);
    
    /*Dictionary Entry 0*/
    streamReadBits_ExpectAndReturn(&in,8,'B');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,0,16);
    streamWriteBits_Expect(&out,'B',8);
    
    /*Dictionary Entry 1*/
    streamReadBits_ExpectAndReturn(&in,8,'C');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,0,16);
    streamWriteBits_Expect(&out,'C',8);

    /*Dictionary Entry 2*/
    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,0,16);
    streamWriteBits_Expect(&out,'A',8);
    
    /*Dictionary Entry 3*/
    streamReadBits_ExpectAndReturn(&in,8,'B');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,'C');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,1,16);
    streamWriteBits_Expect(&out,'C',8);
    
    streamReadBits_ExpectAndReturn(&in,8,EOF);
    checkEndOfFile_ExpectAndReturn(&in,1);
    
    LZ78_Compressor(dict,&in,&out);
 
    TEST_ASSERT_EQUAL_STRING("B",dict->Entry[0].data);
    TEST_ASSERT_EQUAL_STRING("C",dict->Entry[1].data);
    TEST_ASSERT_EQUAL_STRING("A",dict->Entry[2].data);
    TEST_ASSERT_EQUAL_STRING("BC",dict->Entry[3].data);
    TEST_ASSERT_EQUAL(4,dict->currentIndex);
    
    destroyDictionary(dict,4096);
}



/* CR = carriage return = 13 , 0x0D
 * LF = line feed  = 10 0x0A
 */
void test_LZ78_Compressor_given_input_CR_LF_LF_A_should_output_0CR_0LF_2A()
{
    Dictionary *dict = initDictionary(10);
    InStream in ; 
    OutStream out ;

    streamReadBits_ExpectAndReturn(&in,8,13);
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,0,16);
    streamWriteBits_Expect(&out,'\r',8);
    
    streamReadBits_ExpectAndReturn(&in,8,10);
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,0,16);
    streamWriteBits_Expect(&out,'\n',8);

    streamReadBits_ExpectAndReturn(&in,8,10);
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,2,16);
    streamWriteBits_Expect(&out,'A',8);
    
    streamReadBits_ExpectAndReturn(&in,8,EOF);
    checkEndOfFile_ExpectAndReturn(&in,1);
    
    LZ78_Compressor(dict,&in,&out);
 
    TEST_ASSERT_EQUAL(0x0D,*dict->Entry[0].data);
    TEST_ASSERT_EQUAL(0x0A,*dict->Entry[1].data);
    TEST_ASSERT_EQUAL(0X0A,*dict->Entry[2].data);
    TEST_ASSERT_EQUAL('A',dict->Entry[2].data[1]);
    
    destroyDictionary(dict,10);
}

