#include <cstring>

#include "ctestsuite.h"
#include "ctestcombperm.h"
#include "ctestcombinecombination.h"
#include "ctestsetgensingle.h"
#include "ctestsetgendouble.h"
#include "ctestjson.h"
#include "ctestcasket.h"

bool CTestSuite::ProcArgument(const char* arg)
{
    bool test_ok = true;
    CTestCasePtr tst = nullptr;

    if      (strcmp(arg, "comb_permutation") == 0)	tst = CTestCasePtr(new CTestCombPermutation());
    if      (strcmp(arg, "comb_combination") == 0)	tst = CTestCasePtr(new CTestCombineCombination());
    if      (strcmp(arg, "setg_single") == 0)		tst = CTestCasePtr(new CTestSetgenSingle());
    if      (strcmp(arg, "setg_double") == 0)		tst = CTestCasePtr(new CTestSetgenDouble());
    if      (strcmp(arg, "json") == 0)              tst = CTestCasePtr(new CTestJSON());
    if      (strcmp(arg, "casket") == 0)            tst = CTestCasePtr(new CTestCasket());

    if (tst)
	{
		sTestPerformance test_perf;
		test_ok = tst->Test(test_perf);
        printf("%s==========================\n", test_perf.test_name.c_str());
        printf("==== TEST %s PERFOMANCE ====\n", test_perf.test_name.c_str());
		for (const sTestPerformanceAspect &tpa : test_perf.perfomance)
		{
            printf("= %s\n", tpa.Print().c_str());
		}
        printf("%s==========================\n", test_perf.test_name.c_str());
	}
    else
    {
        assert(tst);
    }
    return test_ok;
}
