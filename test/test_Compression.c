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
    InStream *in ; 
    OutStream *out ;
    
    streamReadBits_ExpectAndReturn(in,8,'A');
    streamWriteBits_Expect(out,0,16);
    streamWriteBits_Expect(out,'A',8);
    streamReadBits_ExpectAndReturn(in,8,EOF);
    LZ78_Compressor(dict,in,out);

    
    TEST_ASSERT_EQUAL_STRING("A",dict->Entry[0].data);
    destroyDictionary(dict,10);
}

void xtest_LZ78_Compressor_given_input_AAB_should_output_0A1B()
{
    Dictionary *dict = initDictionary(10);
    char output[10];
    
    
    //LZ78_Compressor("AAB", output, dict);

    TEST_ASSERT_EQUAL_STRING("0A1B",output);
    TEST_ASSERT_EQUAL_STRING("A",dict->Entry[0].data);
    TEST_ASSERT_EQUAL_STRING("AB",dict->Entry[1].data);
    destroyDictionary(dict,10);

}

void xtest_LZ78_Compressor_given_input_AABAC_should_output_0A1B1C()
{
    Dictionary *dict = initDictionary(10);
    char output[10];
    
    
    //LZ78_Compressor("AABAC", output, dict);

    TEST_ASSERT_EQUAL_STRING("0A1B1C",output);
    TEST_ASSERT_EQUAL_STRING("A",dict->Entry[0].data);
    TEST_ASSERT_EQUAL_STRING("AB",dict->Entry[1].data);
    TEST_ASSERT_EQUAL_STRING("AC",dict->Entry[2].data);
    destroyDictionary(dict,10);

}