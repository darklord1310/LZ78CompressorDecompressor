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

void test_merge_InputDataDictionaryData_given_input_BBB_dictionaryEntry0_contains_AAA_should_return_BBBAAA()
{
    Dictionary *dict = initDictionary(10);
    char result[1024] ;
    
    addEntryData(dict, "AAA");
    addEntryData(dict, "CCC");
    
    merge_InputDataDictionaryData("BBB",result,dict,0);
    
    TEST_ASSERT_EQUAL_STRING("BBBAAA",result);
    destroyDictionary(dict,10);
}

void test_LZ78_Compressor_given_input_A_should_output_0A()
{
    Dictionary *dict = initDictionary(10);
    char output[10];
    
    LZ78_Compressor("A", output, dict);

    TEST_ASSERT_EQUAL_STRING("0A",output);
}