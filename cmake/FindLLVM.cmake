set(LLVM_CONFIG_NAMES
    llvm-config-3.9 llvm-config39
    llvm-config-3.8 llvm-config38
    llvm-config-3.7 llvm-config37
)

find_program(LLVM_CONFIG_EXECUTABLE
    DOC "llvm-config executable"
    NAMES ${LLVM_CONFIG_NAMES}
)

execute_process(
    COMMAND "${LLVM_CONFIG_EXECUTABLE}" --bindir
    COMMAND tr "\n" " "
    OUTPUT_VARIABLE LLVM_BIN_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND "${LLVM_CONFIG_EXECUTABLE}" --cppflags
    COMMAND tr "\n" " "
    OUTPUT_VARIABLE LLVM_CXX_FLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND "${LLVM_CONFIG_EXECUTABLE}" --ldflags
    COMMAND tr "\n" " "
    OUTPUT_VARIABLE LLVM_LINK_FLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND "${LLVM_CONFIG_EXECUTABLE}" --libs codegen --system-libs
    COMMAND tr "\n" " "
    OUTPUT_VARIABLE LLVM_LIBRARIES_CODEGEN
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND "${LLVM_CONFIG_EXECUTABLE}" --libs all --system-libs
    COMMAND tr "\n" " "
    OUTPUT_VARIABLE LLVM_LIBRARIES_ALL
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(LLVM_LLC "${LLVM_BIN_DIR}/llc")
