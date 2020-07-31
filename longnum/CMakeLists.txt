cmake_minimum_required(VERSION 3.13)
project(long_numbers)
message("\nBEGIN " ${PROJECT_NAME})

set(SOURCE_LIB
    cnumber.cpp
    cdigitnumber.cpp)
set(HEADERS_LIB
    cnumber.h
    cdigitnumber.h)
add_library(longnum STATIC ${SOURCE_LIB} ${HEADERS_LIB})

set(TEST_DIR test)
set(TESTS_DIR tests)
set(HEADERS_TEST
    ${TEST_DIR}/test_common.h
    ${TEST_DIR}/ctestsuite.h
    ${TEST_DIR}/ctestcase.h
    ${TEST_DIR}/${TESTS_DIR}/ctestnumberprn.h
    ${TEST_DIR}/${TESTS_DIR}/ctestnumbercmp.h
    ${TEST_DIR}/${TESTS_DIR}/ctestnumbersum.h
    ${TEST_DIR}/${TESTS_DIR}/ctestnumbersub.h
    ${TEST_DIR}/${TESTS_DIR}/ctestnumbermul.h
    ${TEST_DIR}/${TESTS_DIR}/ctestnumberdiv.h
    ${TEST_DIR}/${TESTS_DIR}/ctestnumberlgc.h
    ${TEST_DIR}/${TESTS_DIR}/ctestnumbersft.h
    ${TEST_DIR}/${TESTS_DIR}/ctestnumberfac.h
    ${TEST_DIR}/${TESTS_DIR}/ctestdigitnumberstr.h)
set(SOURCE_TEST
    ${TEST_DIR}/main.cpp
    ${TEST_DIR}/ctestsuite.cpp
    ${TEST_DIR}/ctestcase.cpp
    ${TEST_DIR}/${TESTS_DIR}/ctestnumberprn.cpp
    ${TEST_DIR}/${TESTS_DIR}/ctestnumbercmp.cpp
    ${TEST_DIR}/${TESTS_DIR}/ctestnumbersum.cpp
    ${TEST_DIR}/${TESTS_DIR}/ctestnumbersub.cpp
    ${TEST_DIR}/${TESTS_DIR}/ctestnumbermul.cpp
    ${TEST_DIR}/${TESTS_DIR}/ctestnumberdiv.cpp
    ${TEST_DIR}/${TESTS_DIR}/ctestnumberlgc.cpp
    ${TEST_DIR}/${TESTS_DIR}/ctestnumbersft.cpp
    ${TEST_DIR}/${TESTS_DIR}/ctestnumberfac.cpp
    ${TEST_DIR}/${TESTS_DIR}/ctestdigitnumberstr.cpp)

add_executable(longnum_test ${SOURCE_TEST} ${HEADERS_TEST})
target_link_libraries(longnum_test longnum)
target_include_directories(longnum_test PRIVATE test)

if(BUILD_TESTING)
    message("ADDING TESTS FOR " ${PROJECT_NAME})
    # Установить поведение тестов:
    set(TEST_TIMEOUT 1000)

    add_test(NAME TestNumberPrint	    COMMAND longnum_test number_prn)
    add_test(NAME TestNumberCompare	    COMMAND longnum_test number_cmp)
    add_test(NAME TestNumberSummation	    COMMAND longnum_test number_sum)
    add_test(NAME TestNumberSubstitution    COMMAND longnum_test number_sub)
    add_test(NAME TestNumberMultiplication  COMMAND longnum_test number_mul)
    add_test(NAME TestNumberDivision	    COMMAND longnum_test number_div)
    add_test(NAME TestNumberLogic	    COMMAND longnum_test number_lgc)
    add_test(NAME TestNumberFactorial	    COMMAND longnum_test number_fac)
    add_test(NAME TestDigitNumberString	    COMMAND longnum_test digitnumber_str)

    set_tests_properties(
	TestNumberPrint
	TestNumberCompare
	TestNumberSummation
	TestNumberSubstitution
	TestNumberMultiplication
	TestNumberDivision
	TestNumberLogic
	TestNumberFactorial
	TestDigitNumberString
	PROPERTIES TIMEOUT ${TEST_TIMEOUT})

endif()

message("END " ${PROJECT_NAME} "\n")
