# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

# 设置CMAKE_LIBRARY_OUTPUT_DIRECTORY指定输出路径必须在add_library命令之前调用
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../../release/libs/${ANDROID_ABI})
add_library( # Sets the name of the library.
        jni-reflect

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        JniReflect.cpp Transform.cpp)

# 对于静态库使用CMAKE_ARCHIVE_OUTPUT_DIRECTORY ref:https://stackoverflow.com/questions/36089291/why-cmake-library-output-directory-doesnt-work
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../../release/staticlibs/${ANDROID_ABI})
add_library( # Sets the name of the library.
        jni-reflect-static

        # Sets the library as a shared library.
        STATIC

        # Provides a relative path to your source file(s).
        JniReflect.cpp Transform.cpp)
set_target_properties(jni-reflect-static PROPERTIES OUTPUT_NAME "jni-reflect")
# 使得静态库与动态库同时存在
set_target_properties(jni-reflect-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(jni-reflect PROPERTIES CLEAN_DIRECT_OUTPUT 1)
# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        jni-reflect

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})