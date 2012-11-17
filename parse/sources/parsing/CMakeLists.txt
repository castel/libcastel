add_custom_command(OUTPUT
    ${CMAKE_BINARY_DIR}/sources/parse/Lexer.cc
    COMMAND ${RAGEL} -C -o ${CMAKE_BINARY_DIR}/sources/parse/Lexer.cc Lexer.rl
    DEPENDS sources/parse/Lexer.rl
)

add_custom_command(OUTPUT
  includes/
)

add_library(CastelParse

  )
