set(CMAKE_ASM_VASM_SOURCE_FILE_EXTENSIONS asm)

if(NOT CMAKE_ASM_VASM_COMPILE_OBJECT)
  set(CMAKE_ASM_VASM_COMPILE_OBJECT "<CMAKE_ASM_VASM_COMPILER> <INCLUDES> -phxass -Fhunk -quiet -no-opt -o <OBJECT> <SOURCE>")
endif()

set(ASM_DIALECT "_VASM")
include(CMakeASMInformation)
set(ASM_DIALECT)