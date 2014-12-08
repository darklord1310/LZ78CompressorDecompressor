#include "unity.h"
#include "Stream.h"
#include "CException.h"

void setUp(void)
{
}

void tearDown(void)
{
}


void test_initInStream_should_malloc_correctly(void)
{
    InStream *in = initInStream();
    TEST_ASSERT_NOT_NULL(in);
	TEST_ASSERT_EQUAL(8, in->bitIndex);
	TEST_ASSERT_EQUAL(0, in->byteToRead);
    freeInStream(in);
}


void test_initOutStream_should_malloc_correctly(void)
{
    OutStream *out = initOutStream();
    TEST_ASSERT_NOT_NULL(out);
	TEST_ASSERT_EQUAL(0, out->bitIndex);
	TEST_ASSERT_EQUAL(0, out->byteToWrite);
    freeOutStream(out);
}


void test_openInStream_open_a_text_file_available_should_not_throw_error(void)
{
    CEXCEPTION_T ERR;
    
    InStream *in = initInStream();
    
    Try
	{
        in = openInStream("test/support/test_in.txt", "rb" , in);
        TEST_ASSERT_NOT_NULL(in);
        TEST_ASSERT_NOT_NULL(in->file);
        TEST_ASSERT_EQUAL("test/support/test_in.txt", in->filename);
    }
    Catch(ERR){
        TEST_ASSERT_EQUAL(ERR_FAILED_TO_OPEN, ERR);
		TEST_FAIL_MESSAGE("File not exist!");
    }
    closeInStream(in);
    freeInStream(in);
}


// abc is not existed
void test_openInStream_open_a_text_file_unavailable_should_throw_error(void)
{
    CEXCEPTION_T ERR;
    
    InStream *in = initInStream();
    
    Try
	{
        in = openInStream("test/support/abc.txt", "rb" , in);
        TEST_FAIL_MESSAGE("Expected file to be opened");

    }
    Catch(ERR){
        TEST_ASSERT_EQUAL(ERR_FAILED_TO_OPEN, ERR);
		printf("File not exist!\n");
    }
    freeInStream(in);
}



void test_openOutStream_should_open_file_successfully(void)
{
    OutStream *out = initOutStream();
    
    out = openOutStream("test/support/zzz.txt", "rb" , out);
    TEST_ASSERT_NOT_NULL(out);
    TEST_ASSERT_NOT_NULL(out->file);
    TEST_ASSERT_EQUAL("test/support/zzz.txt", out->filename);
    closeOutStream(out);
    freeOutStream(out);

}

void test_streamWriteBit_1time_given_input_1_should_write_1_to_byteToWrite_and_increment_bitIndex_to_1()
{
    OutStream *out = initOutStream();
    
    TEST_ASSERT_EQUAL(0,out->byteToWrite);
    TEST_ASSERT_EQUAL(0,out->bitIndex);
    
    streamWriteBit(out,1);
    
    TEST_ASSERT_EQUAL(1,out->byteToWrite);
    TEST_ASSERT_EQUAL(1,out->bitIndex);
    
    freeOutStream(out);
}

void test_streamWriteBit_2time_given_input_1_0_byteToWrite_should_contain_01_and_increment_bitIndex_to_2()
{
    OutStream *out = initOutStream();
    
    TEST_ASSERT_EQUAL(0,out->byteToWrite);
    TEST_ASSERT_EQUAL(0,out->bitIndex);
    
    streamWriteBit(out,1);
    
    TEST_ASSERT_EQUAL(1,out->byteToWrite);
    TEST_ASSERT_EQUAL(1,out->bitIndex);
    
    streamWriteBit(out,0);
    
    TEST_ASSERT_EQUAL(1,out->byteToWrite);
    TEST_ASSERT_EQUAL(2,out->bitIndex);
    
    freeOutStream(out);
}

void test_streamWriteBit_3time_given_input_1_0_1_should_write_1_0_1_to_byteToWrite_and_increment_bitIndex_to_3()
{
    OutStream *out = initOutStream();
    
    TEST_ASSERT_EQUAL(0,out->byteToWrite);
    TEST_ASSERT_EQUAL(0,out->bitIndex);
    
    streamWriteBit(out,1);
    
    TEST_ASSERT_EQUAL(1,out->byteToWrite);
    TEST_ASSERT_EQUAL(1,out->bitIndex);
    
    streamWriteBit(out,0);
    
    TEST_ASSERT_EQUAL(1,out->byteToWrite);
    TEST_ASSERT_EQUAL(2,out->bitIndex);
    
    streamWriteBit(out,1);
    
    TEST_ASSERT_EQUAL(5,out->byteToWrite);
    TEST_ASSERT_EQUAL(3,out->bitIndex);
       
    freeOutStream(out);
}

void test_streamWriteBits_given_value_8_bitSize_3_should_write_0_to_byteToWrite_return_bitIndex_3()
{
    OutStream *out = initOutStream();
    
    streamWriteBits(out,8,3);

    TEST_ASSERT_EQUAL(0,out->byteToWrite);
    TEST_ASSERT_EQUAL(3,out->bitIndex);
    
    freeOutStream(out);
    
}

void test_streamWriteBits_given_value_8_bitSize_4_should_write_8_to_byteToWrite_return_bitIndex_4()
{
    OutStream *out = initOutStream();
    
    streamWriteBits(out,8,4);

    TEST_ASSERT_EQUAL(8,out->byteToWrite);
    TEST_ASSERT_EQUAL(4,out->bitIndex);
    
    freeOutStream(out);
}

void test_streamWriteBits_given_A_bitSize_8_should_flush_A_during_closeOutStream()
{
    OutStream *out = initOutStream();
    
    out = openOutStream("test/support/test_streamWriteBits.txt", "wb" , out);
    
    streamWriteBits(out,'A',8);
    
    TEST_ASSERT_EQUAL('A',out->byteToWrite);
    TEST_ASSERT_EQUAL(8,out->bitIndex);
    
    closeOutStream(out);
   
    TEST_ASSERT_EQUAL(0,out->byteToWrite);
    TEST_ASSERT_EQUAL(0,out->bitIndex);
    
    freeOutStream(out);
}


void test_streamWriteBits_given_ABCDEFGH_bitSize_64_should_flush_ABCDEFGH()
{
    char *string = "ABCDEFGH" ;
    
    int i ;
    OutStream *out = initOutStream();
    
    out = openOutStream("test/support/test_streamWriteBits_1.txt", "wb" , out);

    for( i = 0 ; i < strlen(string) ; i ++ )
        streamWriteBits(out,string[i],8);

    closeOutStream(out);
    
    TEST_ASSERT_EQUAL(0,out->byteToWrite);
    TEST_ASSERT_EQUAL(0,out->bitIndex);
    
    freeOutStream(out);
}

void test_streamReadBit_given_byteToRead_3_bitIndex_0_should_return_1_and_increment_bitIndex()
{
    InStream * in = initInStream();
    in->byteToRead = 3 ;
    TEST_ASSERT_EQUAL(1,streamReadBit(in));
    TEST_ASSERT_EQUAL(1,in->bitIndex);
    
    freeInStream(in);
}

void test_streamReadBit_given_byteToRead_3_bitIndex_4_should_return_0_and_increment_bitIndex()
{
    InStream * in = initInStream();
    in->byteToRead = 3 ;
    in->bitIndex = 4 ;
    TEST_ASSERT_EQUAL(0,streamReadBit(in));
    TEST_ASSERT_EQUAL(5,in->bitIndex);
    
    freeInStream(in);
}

void test_streamReadBits_given_byteToRead_20_bitSize_4_should_return_4()
{
    InStream *in = initInStream();
    in->byteToRead = 20 ;
    TEST_ASSERT_EQUAL(4,streamReadBits(in,4));
    TEST_ASSERT_EQUAL(4,in->bitIndex);
    
    freeInStream(in);
}

void test_streamReadBits_given_byteToRead_20_bitSize_5_should_return_20()
{
    InStream *in = initInStream();
    in->byteToRead = 20 ;
    TEST_ASSERT_EQUAL(20,streamReadBits(in,5));
    TEST_ASSERT_EQUAL(5,in->bitIndex);
    
    freeInStream(in);
}

void test_streamReadBits_given_bitSize_64_storageType_string_should_extract_data_from_the_file()
{
    char storage[10] = {};
    int i ;
    InStream *in = initInStream();
    in = openInStream("test/support/test_streamReadBits.txt", "rb" , in);

    for ( i = 0 ; i < 8 ; i ++ )
        storage[i] = (char)streamReadBits(in,8) ;
    
    TEST_ASSERT_EQUAL_STRING("ABCDEFGH",storage);
    closeInStream(in);
    freeInStream(in);
}

void test_streamReadBits_given_bitSize_16_storageType_int_should_extract_data_from_the_file()
{
    int storage;
    int i ;
    
    InStream *in = initInStream();
    in = openInStream("test/support/test_streamReadBits.txt", "rb" , in);

    storage = streamReadBits(in,16) ;
    
    TEST_ASSERT_EQUAL(0x4241,storage); /*Text file in little endian format*/
    closeInStream(in);
    freeInStream(in);
}



void test_getPositionInFile_after_read_6_byte_should_point_to_6()
{
    //Create test fixture
    unsigned int storage[10] = {};
    InStream *in = initInStream();                                              //init InStream
    in = openInStream("test/support/LZ78decompressor_in_0a1b1a0b2a4.txt", "rb" , in);
    storage[0] = streamReadBits(in,16) ;
    storage[1] = streamReadBits(in,8) ;
    storage[2] = streamReadBits(in,16) ;
    storage[3] = streamReadBits(in,8) ;

        
    int position = getPositionInFile(in);
    TEST_ASSERT_EQUAL(6, position);
    closeInStream(in);
}