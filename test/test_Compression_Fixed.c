#include "unity.h"
#include <string.h>
#include "Dictionary.h"
#include "Compression.h"
#include "mock_Stream.h"
#include "Utility.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_compare_DictionaryData_given_input_AA_bytesToCompare_2_and_dictionaryEntry5_contains_AA_should_return_5()
{
    Dictionary *dict = initDictionary(10);

    addEntryData(dict, "aA",2);
    addEntryData(dict, "Aa",2);
    addEntryData(dict, "bB",2);
    addEntryData(dict, "Bb",2);
    addEntryData(dict, "cC",2);
    addEntryData(dict, "AA",2);
    addEntryData(dict, "AA",2);
    addEntryData(dict, "a",2);

    TEST_ASSERT_EQUAL(5,compare_DictionaryData("AA",dict,2));
    destroyDictionary(dict,10);
}

void test_compare_DictionaryData_given_input_cCC_bytesToCompare_3_and_dictionary_doesnt_contains_CCC_should_return_minus_1()
{
    Dictionary *dict = initDictionary(10);

    addEntryData(dict, "aA",2);
    addEntryData(dict, "Aa",2);
    addEntryData(dict, "bB",2);
    addEntryData(dict, "Bb",2);
    addEntryData(dict, "cC",2);
    addEntryData(dict, "AA",2);
    addEntryData(dict, "AA",2);
    addEntryData(dict, "a",2);

    TEST_ASSERT_EQUAL(-1,compare_DictionaryData("cCC",dict,3));
    destroyDictionary(dict,10);
}

void test_LZ78_Output_Fixed_mode_given_outputByte_A_index_10_EOFstate_0_should_output_10_16bit_A()
{
    Dictionary dict ;
    OutStream out ;

    streamWriteBits_Expect(&out,10,16);
    streamWriteBits_Expect(&out,'A',8);

    LZ78_Output(&dict,&out,'A',10,0,Fixed);
}

void test_LZ78_Output_Fixed_mode_given_outputByte_A_index_10_EOFstate_1_should_output_10()
{
    Dictionary dict ;
    OutStream out ;

    streamWriteBits_Expect(&out,10,16);

    LZ78_Output(&dict,&out,'A',10,1,Fixed);
}

void test_LZ78_Output_Variable_mode_given_outputByte_A_index_3_EOFstate_0_dict_index_7_should_output_3_3bits_A()
{
    Dictionary dict ;
    OutStream out ;

    dict.currentIndex = 7 ;
    streamWriteBits_Expect(&out,10,3);
    streamWriteBits_Expect(&out,'A',8);

    LZ78_Output(&dict,&out,'A',10,0,Variable);
}


void test_copy_DictionaryDataInputData_given_Hello_dictionary_index_5_contains_World_should_return_HelloWorld()
{
    char outputString[100] = "Hello" ;
    Dictionary *dict = initDictionary(10);
    dict->Entry[5].data = "World" ;
    dict->Entry[5].entrySize = 5 ;

   copy_DictionaryDataInputData(outputString,dict,5);

    TEST_ASSERT_EQUAL_STRING("World",outputString);
}

void test_findLastMatchEntry_given_readByte_contain_A_input_AB_dictionary_contains_A_AA_respectively_should_return_index_1_byte_B_string_AAB()
{
    char dataString[1024] ;
    char readByte[2] = "A";
    int returnedIndex = 0,EOFstate = 0 , result ,dataStringSize;

    Dictionary *dict = initDictionary(10);
    InStream in ;

    dict->Entry[0].data = "A" ;
    dict->Entry[0].entrySize = 1;
    dict->Entry[1].data = "AA" ;
    dict->Entry[1].entrySize = 2;
    dict->currentIndex = 2 ;

    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,'B');
    checkEndOfFile_ExpectAndReturn(&in,0);

    result = findLastMatchEntry(dict,&in,dataString,&dataStringSize,readByte,returnedIndex, &EOFstate);

    TEST_ASSERT_EQUAL(1,result);
    TEST_ASSERT_EQUAL('B',readByte[0]);
    TEST_ASSERT_EQUAL(0,EOFstate);
    TEST_ASSERT_EQUAL_STRING("AAB",dataString);
    TEST_ASSERT_EQUAL(3,dataStringSize);

    destroyDictionary(dict,10);
}

void test_findLastMatchEntry_given_readByte_contain_A_input_empty_dictionary_contains_A_AA_respectively_should_return_index_0_EOFstate_1()
{
    char dataString[1024] ;
    char readByte[2] = "A";
    int returnedIndex = 0,EOFstate = 0 , result,dataStringSize;

    Dictionary *dict = initDictionary(10);
    InStream in ;

    dict->Entry[0].data = "A" ;
    dict->Entry[0].entrySize = 1;
    dict->Entry[1].data = "AA" ;
    dict->Entry[1].entrySize = 2;
    dict->currentIndex = 2 ;

    streamReadBits_ExpectAndReturn(&in,8,EOF);
    checkEndOfFile_ExpectAndReturn(&in,1);

    result = findLastMatchEntry(dict,&in,dataString,&dataStringSize,readByte,returnedIndex, &EOFstate);

    TEST_ASSERT_EQUAL(0,result);
    TEST_ASSERT_EQUAL(EOF,readByte[0]);
    TEST_ASSERT_EQUAL(1,EOFstate);
    TEST_ASSERT_EQUAL_STRING("A",dataString);
    TEST_ASSERT_EQUAL(1,dataStringSize);

    destroyDictionary(dict,10);
}

/* Fixed mode LZ78_Compressor */
/* Fixed mode LZ78_Compressor */

void test_LZ78_Compressor_given_input_A_should_output_1A()
{
    Dictionary *dict = initDictionary(10);
    InStream in ;
    OutStream out ;

    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,1,16);
    streamWriteBits_Expect(&out,'A',8);

    streamReadBits_ExpectAndReturn(&in,8,EOF);
    checkEndOfFile_ExpectAndReturn(&in,1);

    LZ78_Compressor(dict,&in,&out,Fixed);

    TEST_ASSERT_EQUAL_STRING("A",dict->Entry[0].data);
    destroyDictionary(dict,10);
}

void test_LZ78_Compressor_given_input_AAAAAAAAA_should_output_1A_2A_3A_4()
{
    Dictionary *dict = initDictionary(10);
    InStream in ;
    OutStream out ;

    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,1,16);
    streamWriteBits_Expect(&out,'A',8);

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
    streamWriteBits_Expect(&out,3,16);
    streamWriteBits_Expect(&out,'A',8);

    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,EOF);
    checkEndOfFile_ExpectAndReturn(&in,1);
    streamWriteBits_Expect(&out,4,16);

    LZ78_Compressor(dict,&in,&out,Fixed);

    TEST_ASSERT_EQUAL_STRING("A",dict->Entry[0].data);
    TEST_ASSERT_EQUAL_STRING("AA",dict->Entry[1].data);
    TEST_ASSERT_EQUAL_STRING("AAA",dict->Entry[2].data);

    destroyDictionary(dict,10);
}

void test_LZ78_Compressor_given_input_space_A_space_B_should_output_1space_1A_2B()
{
    Dictionary *dict = initDictionary(10);
    InStream in ;
    OutStream out ;

    streamReadBits_ExpectAndReturn(&in,8,32);
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,1,16);
    streamWriteBits_Expect(&out,32,8);

    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,1,16);
    streamWriteBits_Expect(&out,'A',8);

    streamReadBits_ExpectAndReturn(&in,8,32);
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,'B');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,2,16);
    streamWriteBits_Expect(&out,'B',8);

    streamReadBits_ExpectAndReturn(&in,8,EOF);
    checkEndOfFile_ExpectAndReturn(&in,1);
    
    LZ78_Compressor(dict,&in,&out,Fixed);

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
    streamWriteBits_Expect(&out,1,16);
    streamWriteBits_Expect(&out,'A',8);

    /*Dictionary Entry 0*/
    streamReadBits_ExpectAndReturn(&in,8,'B');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,1,16);
    streamWriteBits_Expect(&out,'B',8);

    /*Dictionary Entry 1*/
    streamReadBits_ExpectAndReturn(&in,8,'C');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,1,16);
    streamWriteBits_Expect(&out,'C',8);

    /*Dictionary Entry 2*/
    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,1,16);
    streamWriteBits_Expect(&out,'A',8);

    /*Dictionary Entry 3*/
    streamReadBits_ExpectAndReturn(&in,8,'B');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,'C');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,2,16);
    streamWriteBits_Expect(&out,'C',8);

    streamReadBits_ExpectAndReturn(&in,8,EOF);
    checkEndOfFile_ExpectAndReturn(&in,1);
    
    LZ78_Compressor(dict,&in,&out,Fixed);

    TEST_ASSERT_EQUAL_STRING("B",dict->Entry[0].data);
    TEST_ASSERT_EQUAL_STRING("C",dict->Entry[1].data);
    TEST_ASSERT_EQUAL_STRING("A",dict->Entry[2].data);
    TEST_ASSERT_EQUAL_STRING("BC",dict->Entry[3].data);
    TEST_ASSERT_EQUAL(4,dict->currentIndex);

    destroyDictionary(dict,4096);
}



/* CR = carriage return = 13 , 0x0D
 * LF = line feed  = 10, 0x0A
 */
void test_LZ78_Compressor_given_input_CR_LF_LF_A_should_output_1CR_1LF_3A()
{
    Dictionary *dict = initDictionary(10);
    InStream in ;
    OutStream out ;

    streamReadBits_ExpectAndReturn(&in,8,13);
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,1,16);
    streamWriteBits_Expect(&out,'\r',8);

    streamReadBits_ExpectAndReturn(&in,8,10);
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,1,16);
    streamWriteBits_Expect(&out,'\n',8);

    streamReadBits_ExpectAndReturn(&in,8,10);
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,'A');
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,3,16);
    streamWriteBits_Expect(&out,'A',8);

    streamReadBits_ExpectAndReturn(&in,8,EOF);
    checkEndOfFile_ExpectAndReturn(&in,1);
    
    LZ78_Compressor(dict,&in,&out,Fixed);

    TEST_ASSERT_EQUAL(0x0D,*dict->Entry[0].data);
    TEST_ASSERT_EQUAL(0x0A,*dict->Entry[1].data);
    TEST_ASSERT_EQUAL(0X0A,*dict->Entry[2].data);
    TEST_ASSERT_EQUAL('A',dict->Entry[2].data[1]);

    destroyDictionary(dict,10);
}


void test_LZ78_Compressor_given_9x_NULL_should_return_1NULL_2NULL_3NULL_4()
{
    Dictionary *dict = initDictionary(10);
    InStream in ;
    OutStream out ;
    char dataString1[1] = {} , dataString2[2] = {} , dataString3[3] = {} ;
    
    /*Dictionary Entry 0 will Contains 0 EntrySize : 1*/
    streamReadBits_ExpectAndReturn(&in,8,0);
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,1,16);
    streamWriteBits_Expect(&out,0,8);

    /*Dictionary Entry 1 will Contains 00 EntrySize : 2*/
    streamReadBits_ExpectAndReturn(&in,8,0);
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,0);
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,2,16);
    streamWriteBits_Expect(&out,0,8);

    /*Dictionary Entry 2 will Contains 000 EntrySize : 3*/
    streamReadBits_ExpectAndReturn(&in,8,0);
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,0);
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,0);
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamWriteBits_Expect(&out,3,16);
    streamWriteBits_Expect(&out,0,8);

    streamReadBits_ExpectAndReturn(&in,8,0);
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,0);
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,0);
    checkEndOfFile_ExpectAndReturn(&in,0);
    streamReadBits_ExpectAndReturn(&in,8,EOF);
    checkEndOfFile_ExpectAndReturn(&in,1);
    streamWriteBits_Expect(&out,4,16);

    LZ78_Compressor(dict,&in,&out,Fixed);

    
    TEST_ASSERT_EQUAL(1,dict->Entry[0].entrySize);
    TEST_ASSERT_EQUAL(0,memcmp(dataString1,(dict->Entry[0].data),1));
    
    TEST_ASSERT_EQUAL(2,dict->Entry[1].entrySize);
    TEST_ASSERT_EQUAL(0,memcmp(dataString2,(dict->Entry[1].data),2));
    
    TEST_ASSERT_EQUAL(3,dict->Entry[2].entrySize);
    TEST_ASSERT_EQUAL(0,memcmp(dataString3,(dict->Entry[0].data),3));
    
    destroyDictionary(dict,10);    
}