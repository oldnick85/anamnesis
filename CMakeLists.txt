cmake_minimum_required(VERSION 3.13)

project(anamnesis VERSION 0.0.1)
include(CTest)

include_directories("common")
include_directories("include")
configure_file(common/version.h.in common/version.h)

include(CMakeProcParam.txt)
include(CMakeCompileOptions.txt)

include_directories(longnum)
add_subdirectory(longnum)

include_directories(select)
add_subdirectory(select)

include_directories(cmdlnargs)
add_subdirectory(cmdlnargs)

include_directories(resources)
add_subdirectory(resources)

include_directories(anamnesis_trm)
add_subdirectory(anamnesis_trm)

include_directories(anamnesis_gui_qt)
add_subdirectory(anamnesis_gui_qt)

include(CMakeDoc.txt)

install(TARGETS anamnesis_trm anamnesis_gui_qt
    RUNTIME DESTINATION "/opt/anamnesis/" CONFIGURATIONS Release
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE)
