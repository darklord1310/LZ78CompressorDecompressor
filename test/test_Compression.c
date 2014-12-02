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
    streamWriteBits_Expect(&out,0,16);
    streamWriteBits_Expect(&out,'A',8);
    streamReadBits_ExpectAndReturn(&in,8,EOF);

    LZ78_Compressor(dict,&in,&out);

    TEST_ASSERT_EQUAL_STRING("A",dict->Entry[0].data);
    TEST_ASSERT_EQUAL_STRING("",dict->Entry[1].data);
    destroyDictionary(dict,10);
}

void test_LZ78_Compressor_given_input_AAAAAAAAA_should_output_0A_1A_2A_3EOF()
{
    Dictionary *dict = initDictionary(10);
    InStream in ; 
    OutStream out ;
    
    streamReadBits_ExpectAndReturn(&in,8,'A');
    streamWriteBits_Expect(&out,0,16);
    streamWriteBits_Expect(&out,'A',8);
    
    streamReadBits_ExpectAndReturn(&in,8,'A');
    streamReadBits_ExpectAndReturn(&in,8,'A');
    streamWriteBits_Expect(&out,1,16);
    streamWriteBits_Expect(&out,'A',8);
    
    streamReadBits_ExpectAndReturn(&in,8,'A');
    streamReadBits_ExpectAndReturn(&in,8,'A');
    streamReadBits_ExpectAndReturn(&in,8,'A');
    streamWriteBits_Expect(&out,2,16);
    streamWriteBits_Expect(&out,'A',8);
    
    streamReadBits_ExpectAndReturn(&in,8,'A');
    streamReadBits_ExpectAndReturn(&in,8,'A');
    streamReadBits_ExpectAndReturn(&in,8,'A');
    streamReadBits_ExpectAndReturn(&in,8,EOF);
    streamWriteBits_Expect(&out,3,16);
    streamWriteBits_Expect(&out,EOF,8);
    
    LZ78_Compressor(dict,&in,&out);

    TEST_ASSERT_EQUAL_STRING("A",dict->Entry[0].data);
    TEST_ASSERT_EQUAL_STRING("AA",dict->Entry[1].data);
    TEST_ASSERT_EQUAL_STRING("AAA",dict->Entry[2].data);
    TEST_ASSERT_EQUAL_STRING("",dict->Entry[3].data);
    
    destroyDictionary(dict,10);
}

void test_LZ78_Compressor_given_input_space_A_space_B_should_output_0space_0A_1B()
{

    Dictionary *dict = initDictionary(10);
    InStream in ; 
    OutStream out ;

    streamReadBits_ExpectAndReturn(&in,8,' ');
    streamWriteBits_Expect(&out,0,16);
    streamWriteBits_Expect(&out,' ',8);
    
    streamReadBits_ExpectAndReturn(&in,8,'A');
    streamWriteBits_Expect(&out,0,16);
    streamWriteBits_Expect(&out,'A',8);

    streamReadBits_ExpectAndReturn(&in,8,' ');
    streamReadBits_ExpectAndReturn(&in,8,'B');
    streamWriteBits_Expect(&out,1,16);
    streamWriteBits_Expect(&out,'B',8);
    
    streamReadBits_ExpectAndReturn(&in,8,EOF);
    
    LZ78_Compressor(dict,&in,&out);

    TEST_ASSERT_EQUAL_STRING(" ",dict->Entry[0].data);
    TEST_ASSERT_EQUAL_STRING("A",dict->Entry[1].data);
    TEST_ASSERT_EQUAL_STRING(" B",dict->Entry[2].data);
    TEST_ASSERT_EQUAL_STRING("",dict->Entry[3].data);
    
    destroyDictionary(dict,10);
}


/* CR = carriage return
 * LF = line feed  
 * EOL = end of line
 */
void test_LZ78_Compressor_given_input_CR_LF_EOL_EOL_A_should_output_0CR_0LF_1LF_3A()
{

    Dictionary *dict = initDictionary(10);
    InStream in ; 
    OutStream out ;

    streamReadBits_ExpectAndReturn(&in,8,'\r');
    streamWriteBits_Expect(&out,0,16);
    streamWriteBits_Expect(&out,'\r',8);
    
    streamReadBits_ExpectAndReturn(&in,8,'\n');
    streamWriteBits_Expect(&out,0,16);
    streamWriteBits_Expect(&out,'\n',8);

    streamReadBits_ExpectAndReturn(&in,8,'\r');
    streamReadBits_ExpectAndReturn(&in,8,'\n');
    streamWriteBits_Expect(&out,1,16);
    streamWriteBits_Expect(&out,'\n',8);
    
    streamReadBits_ExpectAndReturn(&in,8,'\r');
    streamReadBits_ExpectAndReturn(&in,8,'\n');
    streamReadBits_ExpectAndReturn(&in,8,'A');
    streamWriteBits_Expect(&out,3,16);
    streamWriteBits_Expect(&out,'A',8);
    
    streamReadBits_ExpectAndReturn(&in,8,EOF);
    
    LZ78_Compressor(dict,&in,&out);

    TEST_ASSERT_EQUAL_STRING("\r",dict->Entry[0].data);
    TEST_ASSERT_EQUAL_STRING("\n",dict->Entry[1].data);
    TEST_ASSERT_EQUAL_STRING("\r\n",dict->Entry[2].data);
    TEST_ASSERT_EQUAL_STRING("\r\nA",dict->Entry[3].data);
    
    destroyDictionary(dict,10);
}