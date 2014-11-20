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

    if ((((in)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)17);;};

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((in->bitIndex)), (((void *)0)), (_U_UINT)18, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((in->byteToRead)), (((void *)0)), (_U_UINT)19, UNITY_DISPLAY_STYLE_INT);

    freeInStream(in);

}





void test_initOutStream_should_malloc_correctly(void)

{

    OutStream *out = initOutStream();

    if ((((out)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)27);;};

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((out->bitIndex)), (((void *)0)), (_U_UINT)28, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((out->byteToWrite)), (((void *)0)), (_U_UINT)29, UNITY_DISPLAY_STYLE_INT);

    freeOutStream(out);

}





void test_openInStream_open_a_text_file_available_should_not_throw_error(void)

{

    unsigned int ERR;



    InStream *in = initInStream();



    { jmp_buf *PrevFrame, NewFrame; unsigned int MY_ID = (0); PrevFrame = CExceptionFrames[(0)].pFrame; CExceptionFrames[MY_ID].pFrame = (jmp_buf*)(&NewFrame); CExceptionFrames[MY_ID].Exception = (0x5A5A5A5A); if (_setjmp(NewFrame) == 0) { if (&PrevFrame)

 {

        in = openInStream("test/support/test_in.txt", "rb" , in);

        if ((((in)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)43);;};

        if ((((in->file)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)44);;};

        UnityAssertEqualNumber((_U_SINT)(("test/support/test_in.txt")), (_U_SINT)((in->filename)), (((void *)0)), (_U_UINT)45, UNITY_DISPLAY_STYLE_INT);

    }

    else { } CExceptionFrames[MY_ID].Exception = (0x5A5A5A5A); } else { ERR = CExceptionFrames[MY_ID].Exception; ERR=ERR; } CExceptionFrames[MY_ID].pFrame = PrevFrame; } if (CExceptionFrames[(0)].Exception != (0x5A5A5A5A)){

        UnityAssertEqualNumber((_U_SINT)((ERR_FAILED_TO_OPEN)), (_U_SINT)((ERR)), (((void *)0)), (_U_UINT)48, UNITY_DISPLAY_STYLE_INT);

  printf("File not exist!\n");

    }



    freeInStream(in);

}







void test_openInStream_open_a_text_file_unavailable_should_throw_error(void)

{

    unsigned int ERR;



    InStream *in = initInStream();



    { jmp_buf *PrevFrame, NewFrame; unsigned int MY_ID = (0); PrevFrame = CExceptionFrames[(0)].pFrame; CExceptionFrames[MY_ID].pFrame = (jmp_buf*)(&NewFrame); CExceptionFrames[MY_ID].Exception = (0x5A5A5A5A); if (_setjmp(NewFrame) == 0) { if (&PrevFrame)

 {

        in = openInStream("test/support/abc.txt", "rb" , in);



    }

    else { } CExceptionFrames[MY_ID].Exception = (0x5A5A5A5A); } else { ERR = CExceptionFrames[MY_ID].Exception; ERR=ERR; } CExceptionFrames[MY_ID].pFrame = PrevFrame; } if (CExceptionFrames[(0)].Exception != (0x5A5A5A5A)){

        UnityAssertEqualNumber((_U_SINT)((ERR_FAILED_TO_OPEN)), (_U_SINT)((ERR)), (((void *)0)), (_U_UINT)69, UNITY_DISPLAY_STYLE_INT);

  printf("File not exist!\n");

    }



    freeInStream(in);

}







void test_openOutStream_should_open_file_successfully(void)

{

    OutStream *out = initOutStream();



    out = openOutStream("test/support/zzz.txt", "rb" , out);

    if ((((out)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)83);;};

    if ((((out->file)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)84);;};

    UnityAssertEqualNumber((_U_SINT)(("test/support/zzz.txt")), (_U_SINT)((out->filename)), (((void *)0)), (_U_UINT)85, UNITY_DISPLAY_STYLE_INT);

    freeOutStream(out);



}
