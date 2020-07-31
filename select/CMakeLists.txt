cmake_minimum_required(VERSION 3.13)
project(select)
message("\nBEGIN " ${PROJECT_NAME})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(PASS_DIR pass)
set(COMBINE_DIR combine)
set(SETGEN_DIR setgen)
set(VARIANT_DIR variant)
set(CASKET_DIR casket)
set(RESULT_DIR result)

set(SOURCE_QUESTIONS
    ${PASS_DIR}/cpass.cpp
    ${SETGEN_DIR}/csetgensingle.cpp
    ${SETGEN_DIR}/csetgendouble.cpp
    ${COMBINE_DIR}/ccombinepermutation.cpp
    ${COMBINE_DIR}/ccombinecombination.cpp
    ${VARIANT_DIR}/csetcomb.cpp
    ${CASKET_DIR}/ccasket.cpp)
set(HEADERS_QUESTIONS
    select_common.h
    ${PASS_DIR}/cpass.h
    ${SETGEN_DIR}/csetgensingle.h
    ${SETGEN_DIR}/csetgendouble.h
    ${COMBINE_DIR}/ccombinepermutation.h
    ${COMBINE_DIR}/ccombinecombination.h
    ${VARIANT_DIR}/csetcomb.h
    ${CASKET_DIR}/ccasket.h
    ${RESULT_DIR}/result.h)

add_library(select STATIC ${SOURCE_QUESTIONS} ${HEADERS_QUESTIONS})
target_link_libraries(select longnum)
target_include_directories(select PRIVATE combine setgen)

set(TEST_DIR test)
set(TESTS_DIR test/tests)
set(HEADERS_TEST
    ${TEST_DIR}/test_common.h
    ${TEST_DIR}/ctestsuite.h
    ${TEST_DIR}/ctestcase.h
    ${TESTS_DIR}/ctestcombperm.h
    ${TESTS_DIR}/ctestcombinecombination.h
    ${TESTS_DIR}/ctestsetgensingle.h
    ${TESTS_DIR}/ctestsetgendouble.h
    ${TESTS_DIR}/ctestjson.h
    ${TESTS_DIR}/ctestcasket.h
    )
set(SOURCE_TEST
    ${TEST_DIR}/main.cpp
    ${TEST_DIR}/ctestsuite.cpp
    ${TEST_DIR}/ctestcase.cpp
    ${TESTS_DIR}/ctestcombperm.cpp
    ${TESTS_DIR}/ctestcombinecombination.cpp
    ${TESTS_DIR}/ctestsetgensingle.cpp
    ${TESTS_DIR}/ctestsetgendouble.cpp
    ${TESTS_DIR}/ctestjson.cpp
    ${TESTS_DIR}/ctestcasket.cpp
    )

add_executable(select_test ${SOURCE_TEST} ${HEADERS_TEST})
target_link_libraries(select_test select)
target_include_directories(select_test PRIVATE combine setgen casket test test/tests)

if(BUILD_TESTING)
    message("ADDING TESTS FOR " ${PROJECT_NAME})
    # Установить поведение тестов:
    set(TEST_TIMEOUT 1000)

    add_test(NAME TestSelectCombPermut	    COMMAND select_test comb_permutation)
    add_test(NAME TestSelectCombCombination COMMAND select_test comb_combination)
    add_test(NAME TestSelectSetgSingle	    COMMAND select_test setg_single)
    add_test(NAME TestSelectSetgDouble	    COMMAND select_test setg_double)
    add_test(NAME TestSelectJSON	    COMMAND select_test json)
    add_test(NAME TestSelectCasket	    COMMAND select_test casket)

    set_tests_properties(
	TestSelectCombPermut
	TestSelectJSON
	PROPERTIES TIMEOUT ${TEST_TIMEOUT})

endif()

message("END " ${PROJECT_NAME} "\n")
