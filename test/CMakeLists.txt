cmake_minimum_required(VERSION 2.8) 

PROJECT(AVProcessTest)

INCLUDE_DIRECTORIES(../include) 

ADD_EXECUTABLE(test_demo test.c)  
TARGET_LINK_LIBRARIES(test_demo AVProcess)

ADD_EXECUTABLE(pcm_to_wav pcm_to_wav.c)  
TARGET_LINK_LIBRARIES(pcm_to_wav AVProcess)

ADD_EXECUTABLE(bmp_test bmp_test.c)  
TARGET_LINK_LIBRARIES(bmp_test AVProcess)

ADD_EXECUTABLE(yuv_test yuv_test.c)  
TARGET_LINK_LIBRARIES(yuv_test AVProcess)

#ADD_EXECUTABLE(aac_encode aac_encode.c)  
#TARGET_LINK_LIBRARIES(aac_encode faac)
