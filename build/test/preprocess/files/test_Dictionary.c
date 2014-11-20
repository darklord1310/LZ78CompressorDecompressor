#include "unity.h"
#include "Dictionary.h"


void setUp(void)

{

}



void tearDown(void)

{

}



void test_initDictionary_with_size_of_3_should_return_dictionary_with_size_of_3()

{

 Dictionary *dict = initDictionary(3);



    if ((((dict)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)16);;};

    if ((((dict->Entry)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)17);;};

    if ((((dict->Entry->data)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)18);;};

    UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((dict->dictionarySize)), (((void *)0)), (_U_UINT)19, UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((dict->currentIndex)), (((void *)0)), (_U_UINT)20, UNITY_DISPLAY_STYLE_INT);

}







void test_getSizeOfString_given_string_abc_should_return_3()

{

    int length = getSizeOfString("abc");





    UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((length)), (((void *)0)), (_U_UINT)30, UNITY_DISPLAY_STYLE_INT);

}





void test_getSizeOfString_given_empty_string_should_return_0()

{

    int length = getSizeOfString("");



    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((length)), (((void *)0)), (_U_UINT)38, UNITY_DISPLAY_STYLE_INT);

}
