#include "ctestnumbersub.h"

bool CTestNumberSub::TestNumbers(const uint64 i, const uint64 j)
{
    CNumber a(i);
    CNumber b(j);
    CNumber s = a - b;
    uint64 k = s.ToUint64();
    uint64 rs = (i > j) ? i - j : 0;
    if (not (rs == k))
    {
        printf("ERROR %lu + %lu\n", i, j);
        return false;
    }
    return true;
}

bool CTestNumberSub::Test(sTestPerformance &test_perf)
{
    printf("==== Testing sub ====\n");
    test_perf.test_name = "SUB";

    printf("= low\n");
    test_perf.perfomance.emplace_back();
    sTestPerformanceAspect &perf_sum = test_perf.perfomance.back();
    perf_sum.name = "substitute low";
    perf_sum.Start();
    for (uint64 i = 0; i < TEST_MAX_COUNT; ++i)
    {
        for (uint64 j = 0; j < TEST_MAX_COUNT; ++j)
        {
            if (not TestNumbers(i, j))
            {
                perf_sum.End();
                return false;
            }
            perf_sum.Inc();
        }
        if ((i % (TEST_MAX_COUNT/10)) == 0)
            printf("done %02lu%%\n", i*100/TEST_MAX_COUNT);
    }
    perf_sum.End();

    printf("= rnd32\n");
    test_perf.perfomance.emplace_back();
    sTestPerformanceAspect &perf_sum_rnd32 = test_perf.perfomance.back();
    perf_sum_rnd32.name = "substitute random32";
    perf_sum_rnd32.Start();
    for (uint64 ic = 0; ic < TEST_MAX_COUNT*TEST_MAX_COUNT; ++ic)
    {
        if (not TestNumbers(Random32(), Random32()))
        {
            perf_sum_rnd32.End();
            return false;
        }
        perf_sum_rnd32.Inc();

        if ((ic % (TEST_MAX_COUNT*TEST_MAX_COUNT/10)) == 0)
            printf("done %02lu%%\n", ic*100/(TEST_MAX_COUNT*TEST_MAX_COUNT));
    }
    perf_sum_rnd32.End();

    printf("= rnd64\n");
    test_perf.perfomance.emplace_back();
    sTestPerformanceAspect &perf_sum_rnd64 = test_perf.perfomance.back();
    perf_sum_rnd64.name = "substitute random64";
    perf_sum_rnd64.Start();
    for (uint64 ic = 0; ic < TEST_MAX_COUNT*TEST_MAX_COUNT; ++ic)
    {
        if (not TestNumbers(Random64(), Random64()))
        {
            perf_sum_rnd64.End();
            return false;
        }
        perf_sum_rnd64.Inc();

        if ((ic % (TEST_MAX_COUNT*TEST_MAX_COUNT/10)) == 0)
            printf("done %02lu%%\n", ic*100/(TEST_MAX_COUNT*TEST_MAX_COUNT));
    }
    perf_sum_rnd64.End();

    return true;
}
