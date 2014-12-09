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
 *  Given input = 0a0b
 */
void test_AddDataToDictionary_given_0a_0b_and_size_is_larger_than_data_written_should_add_into_dictionary_correctly()
{
    int value;
    Dictionary *dict = initDictionary(10);
    
    value = AddDataToDictionary(dict, 0 , (unsigned int)('a')   );
    TEST_ASSERT_EQUAL(1, value);
    TEST_ASSERT_EQUAL(1, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);     TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    TEST_ASSERT_EQUAL_STRING("" ,dict->Entry[1].data);     TEST_ASSERT_EQUAL(0 ,dict->Entry[1].entrySize);

    
    value = AddDataToDictionary(dict, 0 , (unsigned int)('b')   );
    TEST_ASSERT_EQUAL(1, value);
    TEST_ASSERT_EQUAL(2, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);     TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    TEST_ASSERT_EQUAL_STRING("b" ,dict->Entry[1].data);     TEST_ASSERT_EQUAL(1 ,dict->Entry[1].entrySize);
}




/*test case when dictionary is not full, and merging of data occur
 *
 *  Given input = 0a1b
 */
void test_AddDataToDictionary_given_0a_1b_and_size_is_larger_than_data_written_should_add_into_dictionary_correctly()
{
    int value;
    Dictionary *dict = initDictionary(10);
    
    value = AddDataToDictionary(dict, 0 , (unsigned int)('a')   );
    TEST_ASSERT_EQUAL(1, value);
    TEST_ASSERT_EQUAL(1, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);     TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    TEST_ASSERT_EQUAL_STRING("" ,dict->Entry[1].data);     TEST_ASSERT_EQUAL(0 ,dict->Entry[1].entrySize);

   
    value = AddDataToDictionary(dict, 1 , (unsigned int)('b')   );
    TEST_ASSERT_EQUAL(1, value);
    TEST_ASSERT_EQUAL(2, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);     TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    TEST_ASSERT_EQUAL_STRING("ab" ,dict->Entry[1].data);    TEST_ASSERT_EQUAL(2 ,dict->Entry[1].entrySize);
}




/*test case when dictionary is full, and try to add into dictionary
 *
 *  Given input = 0a0b
 */
void test_AddDataToDictionary_given_0a_0b_and_size_is_smaller_than_data_written_should_not_add_into_dictionary_correctly()
{
    int value;
    Dictionary *dict = initDictionary(1);
    
    value = AddDataToDictionary(dict, 0 , (unsigned int)('a')   );
    TEST_ASSERT_EQUAL(1, value);
    TEST_ASSERT_EQUAL(1, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);     TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);

   
    value = AddDataToDictionary(dict, 1 , (unsigned int)('b')   );
    TEST_ASSERT_EQUAL(0, value);
    
    //Expect the whole dictionary stay the same as before
    TEST_ASSERT_EQUAL(1, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);     TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);

}


//test case when dictionary is not full for decompression when index contain all zeroes only
void test_Decompression_given_0a0b0c_and_when_dictionary_is_not_full_should_decompress_correctly_into_abc()
{
    int value;
    OutStream out;
    Dictionary *dict = initDictionary(10);

    //create dictionary 
    value = AddDataToDictionary(dict, 0 , (unsigned int)('a')   );
    assert(value != 0);
    value = AddDataToDictionary(dict, 0 , (unsigned int)('b')   );
    assert(value != 0);
    value = AddDataToDictionary(dict, 0 , (unsigned int)('c')   );
    assert(value != 0);

    
    //create test fixture
    streamWriteBits_Expect(&out, (unsigned int)('a'), 8);           //expect a here
    streamWriteBits_Expect(&out, (unsigned int)('b'), 8);           //expect b here
    streamWriteBits_Expect(&out, (unsigned int)('c'), 8);           //expect c here
    
    //run
    Decompression(&out, 0 , (unsigned int)('a'), dict);
    Decompression(&out, 0 , (unsigned int)('b'), dict);
    Decompression(&out, 0 , (unsigned int)('c'), dict);
}



//test case when dictionary is not full for decompression when index not only zero
void test_Decompression_given_0a1b2c_and_when_dictionary_is_not_full_should_decompress_correctly_into_aababc()
{
    int value;
    OutStream out;
    Dictionary *dict = initDictionary(10);

    //create dictionary 
    value = AddDataToDictionary(dict, 0 , (unsigned int)('a')   );
    assert(value != 0);
    value = AddDataToDictionary(dict, 1 , (unsigned int)('b')   );
    assert(value != 0);
    value = AddDataToDictionary(dict, 2 , (unsigned int)('c')   );
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
    Decompression(&out, 0 , (unsigned int)('a'), dict);
    Decompression(&out, 1 , (unsigned int)('b'), dict);
    Decompression(&out, 2 , (unsigned int)('c'), dict);
}








/*
 * Given data = 01100001    (97)
 *
 *      Dictionary
 *      0.  a
 *
 */
 /*
void xtest_addDataToDictionary_given_binary_97_should_write_a_into_dictionary_entry0()
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
 /*
void xtest_addDataToDictionary_given_data1_and_data2_when_write_data2_should_merge_a_and_b_together_and_write_into_dictionary_entry1()
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
 /*
void xtest_addDataToDictionary_given_data1_data_2_and_data3_when_write_data3_should_merge_ab_and_c_together_and_write_into_dictionary_entry2()
{
    Dictionary *dict = initDictionary(3);
        
    addDataToDictionary(dict, 97, 0);
    addDataToDictionary(dict, 98, 1);
    addDataToDictionary(dict, 99, 2);
    TEST_ASSERT_EQUAL(3, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("abc" ,dict->Entry[2].data);
    TEST_ASSERT_EQUAL(3 ,dict->Entry[2].entrySize);
    
    destroyDictionary(dict,3);
}




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
 /*
void xtest_rebuildDictionaryForDecompression_given_dictionary_size_3_is_larger_than_data_written_should_rebuild_accordingly_and_currentIndex_is_1_and_should_return_neg_1(void)
{
    //Create test fixture
    int status;
	InStream in;	
    Dictionary *dict = initDictionary(3);    
    int lastDecompressPosition = -1;

	//Mock
    streamReadBits_ExpectAndReturn(&in, 16, 0);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 8, 97);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 16, EOF);
    checkEndOfFile_ExpectAndReturn(&in, 1);

	//Run
    // status = rebuildDictionaryForDecompression(dict, &in, &lastDecompressPosition);
    // TEST_ASSERT_EQUAL(-1, status);
    // TEST_ASSERT_EQUAL(1, dict->currentIndex);
    // TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);
    // TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    
    // destroyDictionary(dict,3);
}




/* Try to write 0a0b but only 0a is written into dictionary because dictionary has already full
 * Given input = 0a0b
 * In binary   = 00000000 00000000      01100001     00000000 00000000      01100010
 *               |               |      |      |     |               |      |      |
 *                   16bits              8bits            16bits             8bits
 *                      0                  a                0                  b
 *      Dictionary
 *      0.  a
 *
 */
 /*
void xtest_rebuildDictionaryForDecompression_given_dictionary_size_1_is_smaller_than_data_written_should_rebuild_accordingly_and_currentIndex_is_1_and_should_return_neg_1(void)
{
    //Create test fixture
    int status;
	InStream in;	
    Dictionary *dict = initDictionary(1);    
    int lastDecompressPosition = -1;

	//Mock
    streamReadBits_ExpectAndReturn(&in, 16, 0);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 8, 97);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    getPositionInFile_ExpectAndReturn(&in, 3);
    streamReadBits_ExpectAndReturn(&in, 16, 0);
    checkEndOfFile_ExpectAndReturn(&in, 0);


	//Run
    // status = rebuildDictionaryForDecompression(dict, &in, &lastDecompressPosition);
    // TEST_ASSERT_EQUAL(1, dict->currentIndex);
    // TEST_ASSERT_EQUAL(3, status);                           //dictionary is already full and it stop at the 3rd bytes
    // TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);
    // TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    
    destroyDictionary(dict,3);
}





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
 /*
void xtest_rebuildDictionaryForDecompression_given_dictionary_size_10_is_larger_than_data_written_should_rebuild_accordingly_currentIndex_is_3_and_should_return_neg_1(void)
{
    // Create test fixture
	InStream in;	
    int status;
    int lastDecompressPosition = -1;
    Dictionary *dict = initDictionary(10);    

	// Mock
    streamReadBits_ExpectAndReturn(&in, 16, 0);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamReadBits_ExpectAndReturn(&in, 8, 100);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamReadBits_ExpectAndReturn(&in, 16, 0x0100);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamReadBits_ExpectAndReturn(&in, 8, 65);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamReadBits_ExpectAndReturn(&in, 16, 0x0200);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamReadBits_ExpectAndReturn(&in, 8, 98);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamReadBits_ExpectAndReturn(&in, 16, 0x0200);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamReadBits_ExpectAndReturn(&in, 8, EOF);
    checkEndOfFile_ExpectAndReturn(&in, 1);

	// Run
    // status = rebuildDictionaryForDecompression(dict, &in, &lastDecompressPosition);
    // TEST_ASSERT_EQUAL(3, dict->currentIndex);
    // TEST_ASSERT_EQUAL(-1, status);                                      //dictionary is not full
    // TEST_ASSERT_EQUAL_STRING("d" ,dict->Entry[0].data);
    // TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    // TEST_ASSERT_EQUAL_STRING("dA" ,dict->Entry[1].data);
    // TEST_ASSERT_EQUAL(2 ,dict->Entry[1].entrySize);
    // TEST_ASSERT_EQUAL_STRING("dAb" ,dict->Entry[2].data);
    // TEST_ASSERT_EQUAL(3 ,dict->Entry[2].entrySize);

    
    destroyDictionary(dict,2);
}


/*
 *      Dictionary
 *      0.  a
 *
 */
 /*
void xtest_Decompression_given_0a_should_write_a()
{
    // Create test fixture
	InStream in;	
    OutStream out;
    Dictionary *dict = initDictionary(10);
    dict->Entry[0].data = strdup("a");
    dict->Entry[0].entrySize = 1;


    // Mock
    streamReadBits_ExpectAndReturn(&in, 16, 0);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamReadBits_ExpectAndReturn(&in, 8, 97);
    checkEndOfFile_ExpectAndReturn(&in, 0);
    streamWriteBits_Expect(&out, (unsigned int)('a'), 8);            //expect a here
    streamReadBits_ExpectAndReturn(&in, 16, EOF);
    checkEndOfFile_ExpectAndReturn(&in, 1);
    
    // run
    // Decompression(&in, &out, dict);
}



/*
 *      Dictionary
 *      0.  A
 *      1.  AA
 *      2.  AAA
 *
 */
 /*
void xtest_Decompression_given_0A_1A_2A_3EOF_should_write_A_AA_AAA_AAA()
{
    // Create test fixture
	InStream in;	
    OutStream out;
    Dictionary *dict = initDictionary(10);
    dict->Entry[0].data = strdup("A");
    dict->Entry[0].entrySize = 1;
    dict->Entry[1].data = strdup("AA");
    dict->Entry[1].entrySize = 2;
    dict->Entry[2].data = strdup("AAA");
    dict->Entry[2].entrySize = 3;


    // Mock
    streamReadBits_ExpectAndReturn(&in, 16, 0);                     //read index 0
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamReadBits_ExpectAndReturn(&in, 8, 65);                     //read A
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamWriteBits_Expect(&out, (unsigned int)('A'), 8);           //expect A here
    
    streamReadBits_ExpectAndReturn(&in, 16, 0x0100);                     //read index 1
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamReadBits_ExpectAndReturn(&in, 8, 65);                     //read A
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamWriteBits_Expect(&out, (unsigned int)('A'), 8);           //expect A here
    streamWriteBits_Expect(&out, (unsigned int)('A'), 8);           //expect A here
    
    streamReadBits_ExpectAndReturn(&in, 16, 0x0200);                     //read index 2
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamReadBits_ExpectAndReturn(&in, 8, 65);                     //read A
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamWriteBits_Expect(&out, (unsigned int)('A'), 8);           //expect A here
    streamWriteBits_Expect(&out, (unsigned int)('A'), 8);           //expect A here
    streamWriteBits_Expect(&out, (unsigned int)('A'), 8);           //expect A here
    
    streamReadBits_ExpectAndReturn(&in, 16, 0x0300);                     //read index 3
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamReadBits_ExpectAndReturn(&in, 8, EOF);                     //read EOF
    checkEndOfFile_ExpectAndReturn(&in, 1);                          //eof reached
    
    streamWriteBits_Expect(&out, (unsigned int)('A'), 8);           //expect A here
    streamWriteBits_Expect(&out, (unsigned int)('A'), 8);           //expect A here
    streamWriteBits_Expect(&out, (unsigned int)('A'), 8);           //expect A here
    
    
    // run
    // Decompression(&in, &out, dict);
}





/*
 *      Dictionary
 *      0.  a
 *      1.  b
 *      2.  ab
 *      3.  aa
 *
 */
 /*
void xtest_Decompression_given_0a_0b_1b_1a_2EOF_should_write_a_b_ab_aa_b()
{
    // Create test fixture
	InStream in;	
    OutStream out;
    Dictionary *dict = initDictionary(10);
    dict->Entry[0].data = strdup("a");
    dict->Entry[0].entrySize = 1;
    dict->Entry[1].data = strdup("b");
    dict->Entry[1].entrySize = 1;
    dict->Entry[2].data = strdup("ab");
    dict->Entry[2].entrySize = 2;
    dict->Entry[3].data = strdup("aa");
    dict->Entry[3].entrySize = 2;


    // Mock
    streamReadBits_ExpectAndReturn(&in, 16, 0);                     //read index 0
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamReadBits_ExpectAndReturn(&in, 8, 97);                     //read a
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamWriteBits_Expect(&out, (unsigned int)('a'), 8);           //expect a here
    
    streamReadBits_ExpectAndReturn(&in, 16, 0);                     //read index 0
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamReadBits_ExpectAndReturn(&in, 8, 98);                     //read b
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamWriteBits_Expect(&out, (unsigned int)('b'), 8);           //expect b here
    
    streamReadBits_ExpectAndReturn(&in, 16, 0x0100);                     //read index 1
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamReadBits_ExpectAndReturn(&in, 8, 98);                     //read b
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamWriteBits_Expect(&out, (unsigned int)('a'), 8);           //expect a here
    streamWriteBits_Expect(&out, (unsigned int)('b'), 8);           //expect b here
    
    streamReadBits_ExpectAndReturn(&in, 16, 0x0100);                     //read index 1
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamReadBits_ExpectAndReturn(&in, 8, 97);                     //read a
    checkEndOfFile_ExpectAndReturn(&in, 0);                         
    
    streamWriteBits_Expect(&out, (unsigned int)('a'), 8);           //expect a here
    streamWriteBits_Expect(&out, (unsigned int)('a'), 8);           //expect a here

    streamReadBits_ExpectAndReturn(&in, 16, 0x0200);                     //read index 2
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamReadBits_ExpectAndReturn(&in, 8, EOF);                     //read EOF
    checkEndOfFile_ExpectAndReturn(&in, 1); 
    
    streamWriteBits_Expect(&out, (unsigned int)('b'), 8);           //expect b here



    // run
    // Decompression(&in, &out, dict);

}




/*
 * Test for control word like carriage return, line feed
 * CR = carriage return = 13 , 0x0D
 * LF = line feed  = 10 0x0A
 */
 /*
void xtest_Decompression_given_input_0CR_0LF_2A_should_output_CR_LF_LF_A()
{
    // Create test fixture
	InStream in;	
    OutStream out;
    Dictionary *dict = initDictionary(10);
    dict->Entry[0].data = strdup("\r");
    dict->Entry[0].entrySize = 1;
    dict->Entry[1].data = strdup("\n");
    dict->Entry[1].entrySize = 1;
    dict->Entry[2].data = strdup("\nA");
    dict->Entry[2].entrySize = 2;

    
    // Mock
    streamReadBits_ExpectAndReturn(&in, 16, 0);                     //read index 0
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamReadBits_ExpectAndReturn(&in, 8, 13);                     //read CR
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamWriteBits_Expect(&out, (unsigned int)('\r'), 8);           //expect CR here
    
    streamReadBits_ExpectAndReturn(&in, 16, 0);                     //read index 0
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamReadBits_ExpectAndReturn(&in, 8, 10);                     //read LF
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamWriteBits_Expect(&out, (unsigned int)('\n'), 8);           //expect LF here
    
    streamReadBits_ExpectAndReturn(&in, 16, 0x0200);                     //read index 2
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamReadBits_ExpectAndReturn(&in, 8, 65);                     //read A
    checkEndOfFile_ExpectAndReturn(&in, 0);
    
    streamWriteBits_Expect(&out, (unsigned int)('\n'), 8);          //expect LF here
    streamWriteBits_Expect(&out, (unsigned int)('A'), 8);           //expect A here
    
    streamReadBits_ExpectAndReturn(&in, 16, EOF);                   //read EOF
    checkEndOfFile_ExpectAndReturn(&in, 1); 

    // run
    // Decompression(&in, &out, dict);
}
*/







