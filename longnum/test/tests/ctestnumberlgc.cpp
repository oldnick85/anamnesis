#include "ctestnumberlgc.h"

bool CTestNumberLgc::TestNumbers(const uint64 i, const uint64 j, sTestPerformanceAspect &prf)
{
	CNumber a(i);
	CNumber b(j);
    CNumber s;
    uint64 k;

    s = a ^ b;
    prf.Inc();
    k = s.ToUint64();
    if (not ((i ^ j) == k)) {printf("ERROR %lu ^ %lu = %lu\n", i, j, k); return false;}

    s = a & b;
    prf.Inc();
    k = s.ToUint64();
    if (not ((i & j) == k)) {printf("ERROR %lu & %lu = %lu\n", i, j, k); return false;}

    s = a | b;
    prf.Inc();
    k = s.ToUint64();
    if (not ((i | j) == k)) {printf("ERROR %lu | %lu = %lu\n", i, j, k); return false;}

	return true;
}

bool CTestNumberLgc::Test(sTestPerformance &test_perf)
{
    printf("==== Testing logic ====\n");
    test_perf.test_name = "LOGIC";

    printf("= low\n");
	test_perf.perfomance.emplace_back();
	sTestPerformanceAspect &perf_logic_low = test_perf.perfomance.back();
	perf_logic_low.name = "logic low";
	perf_logic_low.Start();
	for (uint64 i = 0; i < TEST_MAX_COUNT; ++i)
	{
        for (uint64 j = 2; j < TEST_MAX_COUNT; ++j)
		{
            if (not TestNumbers(i, j, perf_logic_low))
            {
                perf_logic_low.End();
                return false;
            }
		}
		if ((i % (TEST_MAX_COUNT/10)) == 0)
			printf("done %02lu%%\n", i*100/TEST_MAX_COUNT);
	}
	perf_logic_low.End();

    printf("= rnd32\n");
    test_perf.perfomance.emplace_back();
    sTestPerformanceAspect &perf_logic_rnd32 = test_perf.perfomance.back();
    perf_logic_rnd32.name = "logic random32";
    perf_logic_rnd32.Start();
    for (uint64 ic = 0; ic < TEST_MAX_COUNT*TEST_MAX_COUNT; ++ic)
    {
        if (not TestNumbers(Random32(), Random32(), perf_logic_rnd32))
        {
            perf_logic_rnd32.End();
            return false;
        }

        if ((ic % (TEST_MAX_COUNT*TEST_MAX_COUNT/10)) == 0)
            printf("done %02lu%%\n", ic*100/(TEST_MAX_COUNT*TEST_MAX_COUNT));
    }
    perf_logic_rnd32.End();

    printf("= rnd64\n");
    test_perf.perfomance.emplace_back();
    sTestPerformanceAspect &perf_logic_rnd64 = test_perf.perfomance.back();
    perf_logic_rnd64.name = "logic random64";
    perf_logic_rnd64.Start();
    for (uint64 ic = 0; ic < TEST_MAX_COUNT*TEST_MAX_COUNT; ++ic)
    {
        if (not TestNumbers(Random64(), Random64(), perf_logic_rnd64))
        {
            perf_logic_rnd64.End();
            return false;
        }

        if ((ic % (TEST_MAX_COUNT*TEST_MAX_COUNT/10)) == 0)
            printf("done %02lu%%\n", ic*100/(TEST_MAX_COUNT*TEST_MAX_COUNT));
    }
    perf_logic_rnd64.End();

	return true;
}
