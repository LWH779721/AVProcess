cmake_minimum_required(VERSION 2.8) 

PROJECT(AVProcess)
 
INCLUDE_DIRECTORIES(../include) 
INCLUDE_DIRECTORIES(../wav/include)

AUX_SOURCE_DIRECTORY(. AVProcess)
AUX_SOURCE_DIRECTORY(wav WAV)

ADD_LIBRARY (AVProcess SHARED ${AVProcess} ${WAV})
