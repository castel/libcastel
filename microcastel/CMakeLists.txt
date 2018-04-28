cmake_minimum_required(VERSION 2.8)

find_package(LLVM)
find_package (Threads)

file(GLOB_RECURSE MICROCASTEL_STATIC_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cc")
set(MICROCASTEL_SOURCES ${MICROCASTEL_STATIC_SOURCES})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/includes")

message(STATUS ${LLVM_CONFIG_EXECUTABLE})
message(STATUS ${LLVM_LIBRARIES_CODEGEN})

add_executable(microcastel ${MICROCASTEL_HEADERS} ${MICROCASTEL_SOURCES})
target_link_libraries(microcastel CastelCompile CastelParse ${LLVM_LIBRARIES_CODEGEN} ${CMAKE_THREAD_LIBS_INIT})
set_property(TARGET microcastel APPEND_STRING PROPERTY COMPILE_FLAGS "${LLVM_CXX_FLAGS}")
set_property(TARGET microcastel APPEND_STRING PROPERTY LINK_FLAGS "${LLVM_LINK_FLAGS}")
add_dependencies(microcastel CastelParse CastelCompile)
