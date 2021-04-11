project(RunTests)

# (1) Look for installed version of CppUTest
if(DEFINED ENV{CPPUTEST_HOME})
    message(STATUS "Using CppUTest home: $ENV{CPPUTEST_HOME}")
    set(CPPUTEST_INCLUDE_DIRS $ENV{CPPUTEST_HOME}/include)
    set(CPPUTEST_LIBRARIES $ENV{CPPUTEST_HOME}/lib)
    set(CPPUTEST_LDFLAGS CppUTest CppUTestExt)
else()
    find_package(PkgConfig REQUIRED)
    pkg_search_module(CPPUTEST REQUIRED cpputest>=3.8)
    message(STATUS "Found CppUTest version ${CPPUTEST_VERSION}")
endif()

include_directories(include)

add_executable(RunTests 
    src/ArraysTests.cpp
    src/PrimitivesTests.cpp
    src/StringsTests.cpp
    src/LinkedListsTests.cpp
    src/DynamicProgrammingTests.cpp
    src/DesignTests.cpp
    src/TreesTests.cpp
    src/RecursionTests.cpp
    src/test.cpp
    src/StackTests.cpp
    src/QueueTests.cpp
)

target_link_libraries(RunTests Arrays Primitives Strings LinkedLists DynamicProgramming Design Trees Recursion Stacks ${CPPUTEST_LDFLAGS})

target_compile_features(RunTests PRIVATE cxx_std_17)