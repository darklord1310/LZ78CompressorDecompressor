#include "unity.h"
#include <string.h>
#include "Dictionary.h"
#include "Compression.h"
#include "Stream.h"

void setUp(void)
{
}

void tearDown(void)
{
}

/*sampleText_forCompresssion -> AAAAAAAAA BBBBBBBBB
 * Fixed mode
 * Compressed output -> 0A1A2A3 0B5B6B7 
 *
 * 0000 0000 0000 0000 <- 16bit index for 0
 * 0100 0001           <- A
 * 0000 0000 0000 0001 <- 16bit index for 1
 * 0100 0001           <- A
 * 0000 0000 0000 0010 <- 16bit index for 2
 * 0100 0001           <- A
 * 0000 0000 0000 0011 <- 16bit index for 3
 * 0010 0000           <- Space
 * 0000 0000 0000 0000 <- 16bit index for 0
 * 0100 0010           <- B
 * 0000 0000 0000 0101 <- 16bit index for 5
 * 0100 0010           <- B
 * 0000 0000 0000 0110 <- 16bit index for 6
 * 0100 0010           <- B
 * 0000 0000 0000 0111 <- 16bit index for 7
 */


void test_LZ78_Compression_fixed_mode_given_input_file_sampleText_forCompresssion()
{
    InStream *in = initInStream();
    OutStream *out = initOutStream();
    Dictionary *dictionary = initDictionary(100);
    
    in = openInStream("test/support/sampleText_forCompresssion.txt", "rb" , in);
    out = openOutStream("test/support/sampleText_forCompresssion_Compressed_Fixed.txt", "wb" , out);
      
    LZ78_Compressor(dictionary,in,out,Fixed);
    
    TEST_ASSERT_EQUAL_STRING("A",dictionary->Entry[0].data);
    TEST_ASSERT_EQUAL_STRING("AA",dictionary->Entry[1].data);
    TEST_ASSERT_EQUAL_STRING("AAA",dictionary->Entry[2].data);
    TEST_ASSERT_EQUAL_STRING("AAA ",dictionary->Entry[3].data);
    TEST_ASSERT_EQUAL_STRING("B",dictionary->Entry[4].data);
    TEST_ASSERT_EQUAL_STRING("BB",dictionary->Entry[5].data);
    TEST_ASSERT_EQUAL_STRING("BBB",dictionary->Entry[6].data);
    TEST_ASSERT_EQUAL_STRING("",dictionary->Entry[7].data);
    
    closeInStream(in);
    closeOutStream(out);
    freeInStream(in);
    freeOutStream(out);
    destroyDictionary(dictionary,100);
}


/*sampleText_forCompresssion -> AAAAAAAAA BBBBBBBBB
 * Variable mode
 * Compressed output -> 0A1A2A3 0B5B6B7 
 * 
 *        
 * 1000 0010  <- bit 0 = index 0
 * 0000 0110  <- bit 1 = index 1
 * 0001 1001  <- bit 3,2 = index 2    
 * 0011 0100  <- bit 5,4 = index 3    
 * 0000 1000  <- bit 6 = index 0    
 * 1010 0001  <- bit 7 = index 5   
 * 0000 1010  <- bit 1,0 = index 5
 * 0101 1001  <- bit 4,3,2 = index 6
 * 1110 1000  <- bit 7,6,5 = index 7
 */

void test_LZ78_Compression_Variable_mode_given_input_file_sampleText_forCompresssion()
{
    InStream *in = initInStream();
    OutStream *out = initOutStream();
    Dictionary *dictionary = initDictionary(100);
    
    in = openInStream("test/support/sampleText_forCompresssion.txt", "rb" , in);
    out = openOutStream("test/support/sampleText_forCompresssion_Compressed_Variable.txt", "wb" , out);
      
    LZ78_Compressor(dictionary,in,out,Variable);
    
    TEST_ASSERT_EQUAL_STRING("A",dictionary->Entry[0].data);
    TEST_ASSERT_EQUAL_STRING("AA",dictionary->Entry[1].data);
    TEST_ASSERT_EQUAL_STRING("AAA",dictionary->Entry[2].data);
    TEST_ASSERT_EQUAL_STRING("AAA ",dictionary->Entry[3].data);
    TEST_ASSERT_EQUAL_STRING("B",dictionary->Entry[4].data);
    TEST_ASSERT_EQUAL_STRING("BB",dictionary->Entry[5].data);
    TEST_ASSERT_EQUAL_STRING("BBB",dictionary->Entry[6].data);
    TEST_ASSERT_EQUAL_STRING("",dictionary->Entry[7].data);
    
    closeInStream(in);
    closeOutStream(out);
    freeInStream(in);
    freeOutStream(out);
    destroyDictionary(dictionary,100);
}

/*sampleText_forCompresssion -> AAAAAAAAA BBBBBBBBBBC
 * Variable mode
 * Compressed output -> 0A1A2A3 0B5B6B7B0C
 * 
 *        
 * 1000 0010  <- bit 0 = index 0
 * 0000 0110  <- bit 1 = index 1
 * 0001 1001  <- bit 3,2 = index 2    
 * 0011 0100  <- bit 5,4 = index 3    
 * 0000 1000  <- bit 6 = index 0    
 * 1010 0001  <- bit 7 = index 5   
 * 0000 1010  <- bit 1,0 = index 5
 * 0101 1001  <- bit 4,3,2 = index 6
 * 1110 1000  <- bit 7,6,5 = index 7
 * 0100 0010  
 * 1000 0110  <- bit 0 = index 0
 *         0
 */

void test_LZ78_Compression_Variable_mode_given_input_file_sampleText_forCompresssion_2()
{
    InStream *in = initInStream();
    OutStream *out = initOutStream();
    Dictionary *dictionary = initDictionary(100);
    
    in = openInStream("test/support/sampleText_forCompresssion_2.txt", "rb" , in);
    out = openOutStream("test/support/sampleText_forCompresssion_Compressed_Variable_2.txt", "wb" , out);
      
    LZ78_Compressor(dictionary,in,out,Variable);
    
    TEST_ASSERT_EQUAL_STRING("A",dictionary->Entry[0].data);
    TEST_ASSERT_EQUAL_STRING("AA",dictionary->Entry[1].data);
    TEST_ASSERT_EQUAL_STRING("AAA",dictionary->Entry[2].data);
    TEST_ASSERT_EQUAL_STRING("AAA ",dictionary->Entry[3].data);
    TEST_ASSERT_EQUAL_STRING("B",dictionary->Entry[4].data);
    TEST_ASSERT_EQUAL_STRING("BB",dictionary->Entry[5].data);
    TEST_ASSERT_EQUAL_STRING("BBB",dictionary->Entry[6].data);
    TEST_ASSERT_EQUAL_STRING("BBBB",dictionary->Entry[7].data);
    TEST_ASSERT_EQUAL_STRING("C",dictionary->Entry[8].data);
    TEST_ASSERT_EQUAL_STRING("",dictionary->Entry[9].data);
    
    closeInStream(in);
    closeOutStream(out);
    freeInStream(in);
    freeOutStream(out);
    destroyDictionary(dictionary,100);
}

void test_LZ78_Compression_Variable_mode_given_input_file_README()
{
    InStream *in = initInStream();
    OutStream *out = initOutStream();
    Dictionary *dictionary = initDictionary(4096);
    
    in = openInStream("test/support/README", "rb" , in);
    out = openOutStream("test/support/README_Compressed_Variable", "wb" , out);
      
    LZ78_Compressor(dictionary,in,out,Variable);

    closeInStream(in);
    closeOutStream(out);
    freeInStream(in);
    freeOutStream(out);
    destroyDictionary(dictionary,4096);
}

void test_LZ78_Compression_Variable_mode_given_input_file_StringObject_o()
{
    InStream *in = initInStream();
    OutStream *out = initOutStream();
    Dictionary *dictionary = initDictionary(4096);
    
    in = openInStream("test/support/StringObject.o", "rb" , in);
    out = openOutStream("test/support/StringObject_Compressed_Variable.o", "wb" , out);
      
    LZ78_Compressor(dictionary,in,out,Variable);

    closeInStream(in);
    closeOutStream(out);
    freeInStream(in);
    freeOutStream(out);
    destroyDictionary(dictionary,4096);
}

void test_LZ78_Compression_Variable_mode_given_input_file_libjansson_4_dll_()
{
    InStream *in = initInStream();
    OutStream *out = initOutStream();
    Dictionary *dictionary = initDictionary(4096);
    
    in = openInStream("test/support/libjansson-4.dll", "rb" , in);
    out = openOutStream("test/support/libjansson-4_Compressed_Variable.dll", "wb" , out);
      
    LZ78_Compressor(dictionary,in,out,Variable);

    closeInStream(in);
    closeOutStream(out);
    freeInStream(in);
    freeOutStream(out);
    destroyDictionary(dictionary,4096);
}