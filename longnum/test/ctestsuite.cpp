#include <cstring>

#include "ctestsuite.h"
#include "tests/ctestnumberprn.h"
#include "tests/ctestnumbercmp.h"
#include "tests/ctestnumbersum.h"
#include "tests/ctestnumbersub.h"
#include "tests/ctestnumbermul.h"
#include "tests/ctestnumberdiv.h"
#include "tests/ctestnumberlgc.h"
#include "tests/ctestnumbersft.h"
#include "tests/ctestnumberfac.h"
#include "tests/ctestdigitnumberstr.h"

bool CTestSuite::ProcArgument(const char* arg)
{
    bool test_ok = true;
	CTestCase* tst = nullptr;
	if      (strcmp(arg, "number_sum") == 0)		tst = new CTestNumberSum();
	else if (strcmp(arg, "number_sub") == 0)		tst = new CTestNumberSub();
	else if (strcmp(arg, "number_prn") == 0)		tst = new CTestNumberPrn();
	else if (strcmp(arg, "number_cmp") == 0)		tst = new CTestNumberCmp();
	else if (strcmp(arg, "number_mul") == 0)		tst = new CTestNumberMul();
	else if (strcmp(arg, "number_div") == 0)		tst = new CTestNumberDiv();
	else if (strcmp(arg, "number_lgc") == 0)		tst = new CTestNumberLgc();
	else if (strcmp(arg, "number_sft") == 0)		tst = new CTestNumberSft();
	else if (strcmp(arg, "number_fac") == 0)		tst = new CTestNumberFac();
	else if (strcmp(arg, "digitnumber_str") == 0)	tst = new CTestDigitNumberStr();
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
    return test_ok;
}
