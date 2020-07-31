#include "ctestnumbermul.h"

bool CTestNumberMul::TestNumbers(const uint64 i, const uint64 j, sTestPerformanceAspect &prf)
{
    CNumber a(i);
    CNumber b(j);

    CNumber m = a * b;
    prf.Inc();
    if (not ((i * j) == m.ToUint64()))
    {
        printf("ERROR %lu * %lu\n", i, j);
        return false;
    }

    return true;
}

bool CTestNumberMul::Test(sTestPerformance &test_perf)
{
    printf("==== Testing mul ====\n");
	test_perf.test_name = "MUL";

    printf("= low\n");
	test_perf.perfomance.emplace_back();
	sTestPerformanceAspect &perf_mul = test_perf.perfomance.back();
	perf_mul.name = "multiplication low";
	perf_mul.Start();
	for (uint64 i = 0; i < TEST_MAX_COUNT; ++i)
	{
		for (uint64 j = 0; j < TEST_MAX_COUNT; ++j)
		{
            if (not TestNumbers(i, j, perf_mul))
			{
				perf_mul.End();
				return false;
			}
		}
		if ((i % (TEST_MAX_COUNT/10)) == 0)
			printf("done %02lu%%\n", i*100/TEST_MAX_COUNT);
	}
	perf_mul.End();

    printf("= rnd32\n");
    test_perf.perfomance.emplace_back();
    sTestPerformanceAspect &perf_mul_rnd32 = test_perf.perfomance.back();
    perf_mul_rnd32.name = "multiplication random32";
    perf_mul_rnd32.Start();
    for (uint64 ic = 0; ic < TEST_MAX_COUNT*TEST_MAX_COUNT; ++ic)
    {
        if (not TestNumbers(Random32(), Random32(), perf_mul_rnd32))
        {
            perf_mul_rnd32.End();
            return false;
        }

        if ((ic % (TEST_MAX_COUNT*TEST_MAX_COUNT/10)) == 0)
            printf("done %02lu%%\n", ic*100/(TEST_MAX_COUNT*TEST_MAX_COUNT));
    }
    perf_mul_rnd32.End();

	return true;
}
