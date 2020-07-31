cmake_minimum_required(VERSION 3.13)
project(anamnesis_gui_qt VERSION 0.0.1)
message("\nBEGIN " ${PROJECT_NAME})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#find_package (Qt5Widgets)
#find_package (Qt5Declarative)
#include_directories(${Qt5Widgets_INCLUDE_DIRS})
#include_directories(${Qt5Declarative_INCLUDE_DIRS})

find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
include (${QT_USE_FILE})

ADD_DEFINITIONS(${QT_DEFINITIONS})

set(GUI_DIR gui)
set(ENCODE_DIR ${GUI_DIR}/encode)
set(ENCODE_SETGEN_DIR ${ENCODE_DIR}/setgen)
set(ENCODE_COMBINE_DIR ${ENCODE_DIR}/combine)
set(DECODE_DIR ${GUI_DIR}/decode)
set(WIDGETS_DIR ${GUI_DIR}/widgets)
set(HEADERS_ANAMNESIS_GUI
    ${GUI_DIR}/cguiqtmain.h
    ${GUI_DIR}/cguiqtcommon.h
    ${ENCODE_DIR}/cguiqtencode.h
    ${ENCODE_DIR}/cguiqtencpass.h
    ${ENCODE_DIR}/cguiqtencquestion.h
    ${ENCODE_COMBINE_DIR}/cguiqtenccombine.h
    ${ENCODE_COMBINE_DIR}/cguiqtenccombinecombination.h
    ${ENCODE_COMBINE_DIR}/cguiqtenccombinepermutation.h
    ${ENCODE_SETGEN_DIR}/cguiqtencsetgen.h
    ${ENCODE_SETGEN_DIR}/cguiqtencsetgensingle.h
    ${ENCODE_SETGEN_DIR}/cguiqtencsetgendouble.h
    ${DECODE_DIR}/cguiqtdecode.h
    ${DECODE_DIR}/cguiqtdecquestion.h
    ${WIDGETS_DIR}/cguiqtsetgenelement.h
    ${WIDGETS_DIR}/cguiqtsetgenelementsingle.h
    ${WIDGETS_DIR}/cguiqtsetgenelementdouble.h
    common.h
    )
set(SOURCE_ANAMNESIS_GUI
    ${GUI_DIR}/cguiqtmain.cpp
    ${GUI_DIR}/cguiqtcommon.cpp
    ${ENCODE_DIR}/cguiqtencode.cpp
    ${ENCODE_DIR}/cguiqtencpass.cpp
    ${ENCODE_DIR}/cguiqtencquestion.cpp
    ${ENCODE_COMBINE_DIR}/cguiqtenccombine.cpp
    ${ENCODE_COMBINE_DIR}/cguiqtenccombinecombination.cpp
    ${ENCODE_COMBINE_DIR}/cguiqtenccombinepermutation.cpp
    ${ENCODE_SETGEN_DIR}/cguiqtencsetgen.cpp
    ${ENCODE_SETGEN_DIR}/cguiqtencsetgensingle.cpp
    ${ENCODE_SETGEN_DIR}/cguiqtencsetgendouble.cpp
    ${DECODE_DIR}/cguiqtdecode.cpp
    ${DECODE_DIR}/cguiqtdecquestion.cpp
    ${WIDGETS_DIR}/cguiqtsetgenelement.cpp
    ${WIDGETS_DIR}/cguiqtsetgenelementsingle.cpp
    ${WIDGETS_DIR}/cguiqtsetgenelementdouble.cpp
    main.cpp
    )
message(${SOURCE_ANAMNESIS_GUI})
add_executable(anamnesis_gui_qt ${SOURCE_ANAMNESIS_GUI} ${HEADERS_ANAMNESIS_GUI})
target_link_libraries (anamnesis_gui_qt longnum select resources ${QT_LIBRARIES})

message("END " ${PROJECT_NAME} "\n")
