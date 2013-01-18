cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE PARSE_STATIC_HEADERS_ORIGIN "${CMAKE_CURRENT_SOURCE_DIR}/includes/*.hh" "${CMAKE_CURRENT_SOURCE_DIR}/includes/*.def")
string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" PARSE_STATIC_HEADERS "${PARSE_STATIC_HEADERS_ORIGIN}")
file(GLOB_RECURSE PARSE_STATIC_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cc")
set(PARSE_GENERATED_HEADERS "${CMAKE_BINARY_DIR}/includes/castel/lex/MangledLexemeTypes.hh")
set(PARSE_GENERATED_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/temporary/sources/lex/Lexer.cc")
set(PARSE_HEADERS ${PARSE_STATIC_HEADERS};${PARSE_GENERATED_HEADERS})
set(PARSE_SOURCES ${PARSE_STATIC_SOURCES};${PARSE_GENERATED_SOURCES})

foreach(HEADER ${PARSE_STATIC_HEADERS})
    file(RELATIVE_PATH RELATIVE_HEADER "${CMAKE_BINARY_DIR}" "${HEADER}")
    set(SOURCE_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/${RELATIVE_HEADER}")
    set(BINARY_HEADER "${CMAKE_BINARY_DIR}/${RELATIVE_HEADER}")
    get_filename_component(BINARY_PATH "${BINARY_HEADER}" PATH)
    add_custom_command(OUTPUT
        "${CMAKE_BINARY_DIR}/${RELATIVE_HEADER}"
        COMMAND mkdir -p "${BINARY_PATH}"
        COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/${RELATIVE_HEADER}" "${CMAKE_BINARY_DIR}/${RELATIVE_HEADER}"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${RELATIVE_HEADER}")
endforeach(HEADER)

add_custom_command(OUTPUT
    "${CMAKE_BINARY_DIR}/includes/castel/lex/MangledLexemeTypes.hh"
    "${CMAKE_CURRENT_BINARY_DIR}/temporary/sources/parse/lemon-parser.cc"
    COMMAND lemon "${CMAKE_CURRENT_SOURCE_DIR}/sources/parse/lemon-parser.lm"
    COMMAND rm "${CMAKE_CURRENT_SOURCE_DIR}/sources/parse/lemon-parser.out"
    COMMAND mkdir -p "${CMAKE_BINARY_DIR}/includes/castel/lex/"
    COMMAND mv "${CMAKE_CURRENT_SOURCE_DIR}/sources/parse/lemon-parser.h" "${CMAKE_BINARY_DIR}/includes/castel/lex/MangledLexemeTypes.hh"
    COMMAND mkdir -p "${CMAKE_CURRENT_BINARY_DIR}/temporary/sources/parse/"
    COMMAND mv "${CMAKE_CURRENT_SOURCE_DIR}/sources/parse/lemon-parser.c" "${CMAKE_CURRENT_BINARY_DIR}/temporary/sources/parse/lemon-parser.cc"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/sources/parse/lemon-parser.lm")

add_custom_command(OUTPUT
    "${CMAKE_CURRENT_BINARY_DIR}/temporary/sources/lex/Lexer.cc"
    COMMAND mkdir -p "${CMAKE_CURRENT_BINARY_DIR}/temporary/sources/lex/"
    COMMAND ragel -C -o "${CMAKE_CURRENT_BINARY_DIR}/temporary/sources/lex/Lexer.cc" "${CMAKE_CURRENT_SOURCE_DIR}/sources/lex/Lexer.rl"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/sources/lex/Lexer.rl")

include_directories(BEFORE "${CMAKE_CURRENT_BINARY_DIR}/temporary")

add_library(CastelParse STATIC ${PARSE_HEADERS} ${PARSE_SOURCES})
