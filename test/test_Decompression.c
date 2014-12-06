#include "unity.h"
#include "Decompression.h"
#include "Dictionary.h"
#include "mock_Stream.h"
#include "Decompression_noMocking.h"

void setUp(void)
{
    
}

void tearDown(void)
{

}




/*
 * Given data = 01100001    (97)
 *
 *      Dictionary
 *      0.  a
 *
 */
void test_addDataToDictionary_given_binary_97_should_write_a_into_dictionary_entry0()
{
    Dictionary *dict = initDictionary(3);
    
    addDataToDictionary(dict, 97, 0);
    
    TEST_ASSERT_EQUAL(1, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);
    TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    
    destroyDictionary(dict,3);
}



/*
 * Given data1 = 0a            
 *       data2 = 1b     
 *
 *      Dictionary
 *      0.  a
 *      1.  ab
 *
 */
void test_addDataToDictionary_given_data1_and_data2_when_write_data2_should_merge_a_and_b_together_and_write_into_dictionary_entry1()
{
    Dictionary *dict = initDictionary(3);
        
    addDataToDictionary(dict, 97, 0);
    TEST_ASSERT_EQUAL(1, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);
    TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    
    
    addDataToDictionary(dict, 98, 1);  
    TEST_ASSERT_EQUAL(2, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("ab" ,dict->Entry[1].data);
    TEST_ASSERT_EQUAL(2 ,dict->Entry[1].entrySize);
    
    destroyDictionary(dict,3);
}




/*
 * Given data1 = 0a            
 *       data2 = 1b
 *       data3 = 2c
 *
 *      Dictionary
 *      0.  a
 *      1.  ab
 *      2.  abc
 *
 */
// void test_addDataToDictionary_given_data1_data_2_and_data3_when_write_data3_should_merge_ab_and_c_together_and_write_into_dictionary_entry2()
// {
    // Dictionary *dict = initDictionary(3);
        
    // addDataToDictionary(dict, 97, 0);
    // addDataToDictionary(dict, 98, 1);
    // addDataToDictionary(dict, 99, 2);
    // TEST_ASSERT_EQUAL(3, dict->currentIndex);
    // TEST_ASSERT_EQUAL_STRING("abc" ,dict->Entry[2].data);
    // TEST_ASSERT_EQUAL(3 ,dict->Entry[2].entrySize);
    
    // destroyDictionary(dict,3);
// }




/*
 * Given input = 0a
 * In binary   = 00000000 00000000      01100001   
 *               |               |      |      |    
 *                   16bits              8bits            
 *                      0                  a              
 *      Dictionary
 *      0.  a
 *
 */
// void test_rebuildDictionaryForDecompression_given_dictionary_size_3_is_larger_than_data_written_should_rebuild_accordingly_and_currentIndex_is_1_and_should_return_0(void)
// {
    // Create test fixture
    // int status;
	// InStream in;	
    // Dictionary *dict = initDictionary(3);    

	// Mock
    // streamReadBits_ExpectAndReturn(&in, 16, 0);
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    // streamReadBits_ExpectAndReturn(&in, 8, 97);
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    // streamReadBits_ExpectAndReturn(&in, 16, EOF);
    // checkEndOfFile_ExpectAndReturn(&in, 1);

	// Run
    // status = rebuildDictionaryForDecompression(dict, &in);
    // TEST_ASSERT_EQUAL(0, status);
    // TEST_ASSERT_EQUAL(1, dict->currentIndex);
    // TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);
    // TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    
    // destroyDictionary(dict,3);
// }




/*
 * Given input = 0a0b
 * In binary   = 00000000 00000000      01100001     00000000 00000000      01100010
 *               |               |      |      |     |               |      |      |
 *                   16bits              8bits            16bits             8bits
 *                      0                  a                0                  b
 *      Dictionary
 *      0.  a
 *
 */
// void test_rebuildDictionaryForDecompression_given_dictionary_size_1_is_smaller_than_data_written_should_rebuild_accordingly_and_currentIndex_is_1_and_should_return_1(void)
// {
    // Create test fixture
    // int status;
	// InStream in;	
    // Dictionary *dict = initDictionary(1);    

	// Mock
    // streamReadBits_ExpectAndReturn(&in, 16, 0);
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    // streamReadBits_ExpectAndReturn(&in, 8, 97);
    // checkEndOfFile_ExpectAndReturn(&in, 0);


	// Run
    // status = rebuildDictionaryForDecompression(dict, &in);
    // TEST_ASSERT_EQUAL(1, dict->currentIndex);
    // TEST_ASSERT_EQUAL(1, status);
    // TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);
    // TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    
    // destroyDictionary(dict,3);
// }





/*
 * Given input = 0d1A2b2
 * In binary   = 00000000 00000000      01100100     00000000 00000001      01000001        00000000 00000010   01100010       00000000 00000010    
 *               |               |      |      |     |               |      |      |        |               |   |      |       |               |    
 *                   16bits              8bits            16bits             8bits                16bits         8bits              16bits          
 *                     0                   d                1                  A                   2               b                  2                
 *      Dictionary
 *      0.  d
 *      1.  dA
 *      2.  dAb
 *
 */
// void test_rebuildDictionaryForDecompression_given_dictionary_size_10_is_larger_than_data_written_should_rebuild_accordingly_currentIndex_is_3_and_should_return_0(void)
// {
    // Create test fixture
	// InStream in;	
    // int status;
    // Dictionary *dict = initDictionary(10);    

	// Mock
    // streamReadBits_ExpectAndReturn(&in, 16, 0);
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamReadBits_ExpectAndReturn(&in, 8, 100);
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamReadBits_ExpectAndReturn(&in, 16, 1);
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamReadBits_ExpectAndReturn(&in, 8, 65);
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamReadBits_ExpectAndReturn(&in, 16, 2);
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamReadBits_ExpectAndReturn(&in, 8, 98);
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamReadBits_ExpectAndReturn(&in, 16, 2);
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamReadBits_ExpectAndReturn(&in, 8, EOF);
    // checkEndOfFile_ExpectAndReturn(&in, 1);

	// Run
    // status = rebuildDictionaryForDecompression(dict, &in);
    // TEST_ASSERT_EQUAL(3, dict->currentIndex);
    // TEST_ASSERT_EQUAL(0, status);
    // TEST_ASSERT_EQUAL_STRING("d" ,dict->Entry[0].data);
    // TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    // TEST_ASSERT_EQUAL_STRING("dA" ,dict->Entry[1].data);
    // TEST_ASSERT_EQUAL(2 ,dict->Entry[1].entrySize);
    // TEST_ASSERT_EQUAL_STRING("dAb" ,dict->Entry[2].data);
    // TEST_ASSERT_EQUAL(3 ,dict->Entry[2].entrySize);

    
    // destroyDictionary(dict,2);
// }


/*
 *      Dictionary
 *      0.  a
 *
 */
// void test_Decompression_given_0a_should_write_a()
// {
    // Create test fixture
	// InStream in;	
    // OutStream out;
    // Dictionary *dict = initDictionary(10);
    // dict->Entry[0].data = strdup("a");
    // dict->Entry[0].entrySize = 1;


    // Mock
    // streamReadBits_ExpectAndReturn(&in, 16, 0);
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    // streamReadBits_ExpectAndReturn(&in, 8, 97);
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    // streamWriteBits_Expect(&out, (unsigned int)('a'), 8);            //expect a here
    // streamReadBits_ExpectAndReturn(&in, 16, EOF);
    // checkEndOfFile_ExpectAndReturn(&in, 1);
    
    // run
    // Decompression(&in, &out, dict);
// }



/*
 *      Dictionary
 *      0.  A
 *      1.  AA
 *      2.  AAA
 *
 */
// void test_Decompression_given_0A_1A_2A_3EOF_should_write_A_AA_AAA_AAA()
// {
    // Create test fixture
	// InStream in;	
    // OutStream out;
    // Dictionary *dict = initDictionary(10);
    // dict->Entry[0].data = strdup("A");
    // dict->Entry[0].entrySize = 1;
    // dict->Entry[1].data = strdup("AA");
    // dict->Entry[1].entrySize = 2;
    // dict->Entry[2].data = strdup("AAA");
    // dict->Entry[2].entrySize = 3;


    // Mock
    // streamReadBits_ExpectAndReturn(&in, 16, 0);                     //read index 0
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamReadBits_ExpectAndReturn(&in, 8, 65);                     //read A
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamWriteBits_Expect(&out, (unsigned int)('A'), 8);           //expect A here
    
    // streamReadBits_ExpectAndReturn(&in, 16, 1);                     //read index 1
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamReadBits_ExpectAndReturn(&in, 8, 65);                     //read A
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamWriteBits_Expect(&out, (unsigned int)('A'), 8);           //expect A here
    // streamWriteBits_Expect(&out, (unsigned int)('A'), 8);           //expect A here
    
    // streamReadBits_ExpectAndReturn(&in, 16, 2);                     //read index 2
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamReadBits_ExpectAndReturn(&in, 8, 65);                     //read A
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamWriteBits_Expect(&out, (unsigned int)('A'), 8);           //expect A here
    // streamWriteBits_Expect(&out, (unsigned int)('A'), 8);           //expect A here
    // streamWriteBits_Expect(&out, (unsigned int)('A'), 8);           //expect A here
    
    // streamReadBits_ExpectAndReturn(&in, 16, 3);                     //read index 3
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamReadBits_ExpectAndReturn(&in, 8, EOF);                     //read EOF
    // checkEndOfFile_ExpectAndReturn(&in, 1);                          //eof reached
    
    // streamWriteBits_Expect(&out, (unsigned int)('A'), 8);           //expect A here
    // streamWriteBits_Expect(&out, (unsigned int)('A'), 8);           //expect A here
    // streamWriteBits_Expect(&out, (unsigned int)('A'), 8);           //expect A here
    
    
    // run
    // Decompression(&in, &out, dict);
// }





/*
 *      Dictionary
 *      0.  a
 *      1.  b
 *      2.  ab
 *      3.  aa
 *
 */
// void test_Decompression_given_0a_0b_1b_1a_2EOF_should_write_a_b_ab_aa_b()
// {
    // Create test fixture
	// InStream in;	
    // OutStream out;
    // Dictionary *dict = initDictionary(10);
    // dict->Entry[0].data = strdup("a");
    // dict->Entry[0].entrySize = 1;
    // dict->Entry[1].data = strdup("b");
    // dict->Entry[1].entrySize = 1;
    // dict->Entry[2].data = strdup("ab");
    // dict->Entry[2].entrySize = 2;
    // dict->Entry[3].data = strdup("aa");
    // dict->Entry[3].entrySize = 2;


    // Mock
    // streamReadBits_ExpectAndReturn(&in, 16, 0);                     //read index 0
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamReadBits_ExpectAndReturn(&in, 8, 97);                     //read a
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamWriteBits_Expect(&out, (unsigned int)('a'), 8);           //expect a here
    
    // streamReadBits_ExpectAndReturn(&in, 16, 0);                     //read index 0
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamReadBits_ExpectAndReturn(&in, 8, 98);                     //read b
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamWriteBits_Expect(&out, (unsigned int)('b'), 8);           //expect b here
    
    // streamReadBits_ExpectAndReturn(&in, 16, 1);                     //read index 1
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamReadBits_ExpectAndReturn(&in, 8, 98);                     //read b
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamWriteBits_Expect(&out, (unsigned int)('a'), 8);           //expect a here
    // streamWriteBits_Expect(&out, (unsigned int)('b'), 8);           //expect b here
    
    // streamReadBits_ExpectAndReturn(&in, 16, 1);                     //read index 1
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamReadBits_ExpectAndReturn(&in, 8, 97);                     //read a
    // checkEndOfFile_ExpectAndReturn(&in, 0);                         
    
    // streamWriteBits_Expect(&out, (unsigned int)('a'), 8);           //expect a here
    // streamWriteBits_Expect(&out, (unsigned int)('a'), 8);           //expect a here

    // streamReadBits_ExpectAndReturn(&in, 16, 2);                     //read index 2
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamReadBits_ExpectAndReturn(&in, 8, EOF);                     //read EOF
    // checkEndOfFile_ExpectAndReturn(&in, 1); 
    
    // streamWriteBits_Expect(&out, (unsigned int)('b'), 8);           //expect b here



    // run
    // Decompression(&in, &out, dict);

// }




/*
 * Test for control word like carriage return, line feed
 * CR = carriage return = 13 , 0x0D
 * LF = line feed  = 10 0x0A
 */
// void xtest_Decompression_given_input_0CR_0LF_2A_should_output_CR_LF_LF_A()
// {
    // Create test fixture
	// InStream in;	
    // OutStream out;
    // Dictionary *dict = initDictionary(10);
    // dict->Entry[0].data = strdup("\r");
    // dict->Entry[0].entrySize = 1;
    // dict->Entry[1].data = strdup("\n");
    // dict->Entry[1].entrySize = 1;
    // dict->Entry[2].data = strdup("\nA");
    // dict->Entry[2].entrySize = 2;

    
    // Mock
    // streamReadBits_ExpectAndReturn(&in, 16, 0);                     //read index 0
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamReadBits_ExpectAndReturn(&in, 8, 13);                     //read CR
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamWriteBits_Expect(&out, (unsigned int)('\r'), 8);           //expect CR here
    
    // streamReadBits_ExpectAndReturn(&in, 16, 0);                     //read index 0
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamReadBits_ExpectAndReturn(&in, 8, 10);                     //read LF
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamWriteBits_Expect(&out, (unsigned int)('\n'), 8);           //expect LF here
    
    // streamReadBits_ExpectAndReturn(&in, 16, 2);                     //read index 2
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamReadBits_ExpectAndReturn(&in, 8, 65);                     //read A
    // checkEndOfFile_ExpectAndReturn(&in, 0);
    
    // streamWriteBits_Expect(&out, (unsigned int)('\n'), 8);          //expect LF here
    // streamWriteBits_Expect(&out, (unsigned int)('A'), 8);           //expect A here
    
    // streamReadBits_ExpectAndReturn(&in, 16, EOF);                   //read EOF
    // checkEndOfFile_ExpectAndReturn(&in, 1); 

    // run
    // Decompression(&in, &out, dict);
// }



void test_swapUpper16bitsWithLower16bits_given_0x0100_should_return_1()
{

    unsigned int value = 0x100;
    unsigned int convertedvalue = swapUpper16bitsWithLower16bits(value);


    TEST_ASSERT_EQUAL(1, convertedvalue);

}


void test_swapUpper16bitsWithLower16bits_given_0x0E00_should_return_14()
{

    unsigned int value = 0xe00;
    unsigned int convertedvalue = swapUpper16bitsWithLower16bits(value);


    TEST_ASSERT_EQUAL(14, convertedvalue);
}



