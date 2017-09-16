# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 3.4.1)


#FFMpeg配置
#FFmpeg配置目录
set(distribution_DIR ${CMAKE_SOURCE_DIR}/../../../../src/main/jniLibs)
#配置编译的头文件

include_directories(src/main/jniLibs/include)
include_directories(src/main/jniLibs/other)

# 编解码(最重要的库)
add_library(
            avcodec-56
            SHARED
            IMPORTED)
set_target_properties(
            avcodec-56
            PROPERTIES IMPORTED_LOCATION
            ../../../../src/main/jniLibs/armeabi/libavcodec-56.so)
add_library(
            libavdevice-56
            SHARED
            IMPORTED)
set_target_properties(
            libavdevice-56
            PROPERTIES IMPORTED_LOCATION
            ../../../../src/main/jniLibs/armeabi/libavdevice-56.so)

# 滤镜特效处理库
add_library(
            avfilter-5
            SHARED
            IMPORTED)
set_target_properties(
            avfilter-5
            PROPERTIES IMPORTED_LOCATION
            ../../../../src/main/jniLibs/armeabi/libavfilter-5.so)

# 封装格式处理库
add_library(
            avformat-56
            SHARED
            IMPORTED)
set_target_properties(
            avformat-56
            PROPERTIES IMPORTED_LOCATION
            ../../../../src/main/jniLibs/armeabi/libavformat-56.so)

# 工具库(大部分库都需要这个库的支持)
add_library(
            avutil-54
            SHARED
            IMPORTED)
set_target_properties(
            avutil-54
            PROPERTIES IMPORTED_LOCATION
            ../../../../src/main/jniLibs/armeabi/libavutil-54.so)

# 音频采样数据格式转换库
add_library(
            swresample-1
            SHARED
            IMPORTED)
set_target_properties(
            swresample-1
            PROPERTIES IMPORTED_LOCATION
            ../../../../src/main/jniLibs/armeabi/libswresample-1.so)
add_library(
            libpostproc-53
            SHARED
            IMPORTED)
set_target_properties(
            libpostproc-53
            PROPERTIES IMPORTED_LOCATION
            ../../../../src/main/jniLibs/armeabi/libpostproc-53.so)

# 视频像素数据格式转换
add_library(
            swscale-3
            SHARED
            IMPORTED)
set_target_properties(
            swscale-3
            PROPERTIES IMPORTED_LOCATION
            ../../../../src/main/jniLibs/armeabi/libswscale-3.so)








#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
#判断编译器类型,如果是gcc编译器,则在编译选项中加入c++11支持
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
    message(STATUS "optional:-std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)



# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds it for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-ffmpeg

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             src/main/cpp/cmdutils.c
             #src/main/cpp/ffmpeg_filter.c
             src/main/cpp/ffmpeg_jni.cpp
             src/main/cpp/ffmpeg_mod.c
             src/main/cpp/ffmpeg_opt.c
            )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because system libraries are included in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib


              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )
 find_library( # Sets the name of the path variable.
              android-lib


              # Specifies the name of the NDK library that
              # you want CMake to locate.
              android)


# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in the
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-ffmpeg  avcodec-56 avfilter-5 avformat-56 avutil-54 swresample-1 libpostproc-53 swscale-3 libavdevice-56
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       ${android-lib})
