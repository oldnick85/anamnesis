cmake_minimum_required(VERSION 3.13)
project(anamnesis_trm)
message("\nBEGIN " ${PROJECT_NAME})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(TERMINAL_DIR terminal)
set(TERMINAL_ENCODE_DIR ${TERMINAL_DIR}/encode)
set(TERMINAL_ENCODE_SETGEN_DIR ${TERMINAL_ENCODE_DIR}/setgen)
set(TERMINAL_ENCODE_COMBINE_DIR ${TERMINAL_ENCODE_DIR}/combine)
set(TERMINAL_DECODE_DIR ${TERMINAL_DIR}/decode)
set(TERMINAL_DECODE_SETGEN_DIR ${TERMINAL_DECODE_DIR}/setgen)
set(TERMINAL_DECODE_COMBINE_DIR ${TERMINAL_DECODE_DIR}/combine)
set(TERMINAL_IO_DIR ${TERMINAL_DIR}/io)
set(SELECT_DIR select)
set(HEADERS_ANAMNESIS_TRM
    common.h
    ${TERMINAL_DIR}/ctrmmain.h
    ${TERMINAL_IO_DIR}/ctrmio.h
    ${TERMINAL_IO_DIR}/ctrmio_setgensingle.h
    ${TERMINAL_IO_DIR}/ctrmio_setgendouble.h
    ${TERMINAL_IO_DIR}/ctrmio_combine.h
    ${TERMINAL_ENCODE_DIR}/ctrmencode.h
    ${TERMINAL_ENCODE_DIR}/ctrmencpass.h
    ${TERMINAL_ENCODE_SETGEN_DIR}/ctrmencsetgen.h
    ${TERMINAL_ENCODE_SETGEN_DIR}/ctrmencsetgensingle.h
    ${TERMINAL_ENCODE_SETGEN_DIR}/ctrmencsetgendouble.h
    ${TERMINAL_ENCODE_COMBINE_DIR}/ctrmenccombine.h
    ${TERMINAL_ENCODE_COMBINE_DIR}/ctrmenccombinepermut.h
    ${TERMINAL_ENCODE_COMBINE_DIR}/ctrmenccombinecombination.h
    ${TERMINAL_ENCODE_DIR}/ctrmencquestion.h
    ${TERMINAL_DECODE_DIR}/ctrmdecode.h
    ${TERMINAL_DECODE_DIR}/ctrmdecquestion.h
    ${TERMINAL_DECODE_SETGEN_DIR}/ctrmdecsetgen.h
    ${TERMINAL_DECODE_SETGEN_DIR}/ctrmdecsetgensingle.h
    ${TERMINAL_DECODE_SETGEN_DIR}/ctrmdecsetgendouble.h
    ${TERMINAL_DECODE_COMBINE_DIR}/ctrmdeccombine.h
    ${TERMINAL_DECODE_COMBINE_DIR}/ctrmdeccombinepermut.h
    ${TERMINAL_DECODE_COMBINE_DIR}/ctrmdeccombinecombination.h
    )
set(SOURCE_ANAMNESIS_TRM
    main.cpp
    ${TERMINAL_DIR}/ctrmmain.cpp
    ${TERMINAL_IO_DIR}/ctrmio.cpp
    ${TERMINAL_IO_DIR}/ctrmio_setgensingle.cpp
    ${TERMINAL_IO_DIR}/ctrmio_setgendouble.cpp
    ${TERMINAL_IO_DIR}/ctrmio_combine.cpp
    ${TERMINAL_ENCODE_DIR}/ctrmencode.cpp
    ${TERMINAL_ENCODE_DIR}/ctrmencpass.cpp
    ${TERMINAL_ENCODE_SETGEN_DIR}/ctrmencsetgen.cpp
    ${TERMINAL_ENCODE_SETGEN_DIR}/ctrmencsetgensingle.cpp
    ${TERMINAL_ENCODE_SETGEN_DIR}/ctrmencsetgendouble.cpp
    ${TERMINAL_ENCODE_COMBINE_DIR}/ctrmenccombine.cpp
    ${TERMINAL_ENCODE_COMBINE_DIR}/ctrmenccombinepermut.cpp
    ${TERMINAL_ENCODE_COMBINE_DIR}/ctrmenccombinecombination.cpp
    ${TERMINAL_ENCODE_DIR}/ctrmencquestion.cpp
    ${TERMINAL_DECODE_DIR}/ctrmdecode.cpp
    ${TERMINAL_DECODE_DIR}/ctrmdecquestion.cpp
    ${TERMINAL_DECODE_SETGEN_DIR}/ctrmdecsetgen.cpp
    ${TERMINAL_DECODE_SETGEN_DIR}/ctrmdecsetgensingle.cpp
    ${TERMINAL_DECODE_SETGEN_DIR}/ctrmdecsetgendouble.cpp
    ${TERMINAL_DECODE_COMBINE_DIR}/ctrmdeccombine.cpp
    ${TERMINAL_DECODE_COMBINE_DIR}/ctrmdeccombinepermut.cpp
    ${TERMINAL_DECODE_COMBINE_DIR}/ctrmdeccombinecombination.cpp
    )

add_executable(anamnesis_trm ${SOURCE_ANAMNESIS_TRM} ${HEADERS_ANAMNESIS_TRM})
target_link_libraries(anamnesis_trm longnum select cmdlnargs resources)
target_include_directories(anamnesis_trm PRIVATE terminal select terminal/io)

message("END " ${PROJECT_NAME} "\n")
