#include "ctestnumbercmp.h"

bool CTestNumberCmp::TestNumbers(const uint64 i, const uint64 j, sTestPerformanceAspect &prf)
{
    CNumber a(i);
    CNumber b(j);

    bool cmp_g = (a > b);
    prf.Inc();
    if (not ((i > j) == cmp_g))
    {
        printf("ERROR %lu > %lu\n", i, j);
        return false;
    }

    bool cmp_l = (a < b);
    prf.Inc();
    if (not ((i < j) == cmp_l))
    {
        printf("ERROR %lu < %lu\n", i, j);
        return false;
    }

    bool cmp_eg = (a >= b);
    prf.Inc();
    if (not ((i >= j) == cmp_eg))
    {
        printf("ERROR %lu >= %lu\n", i, j);
        return false;
    }

    bool cmp_el = (a <= b);
    prf.Inc();
    if (not ((i <= j) == cmp_el))
    {
        printf("ERROR %lu <= %lu\n", i, j);
        return false;
    }

    bool cmp_eq = (a == b);
    prf.Inc();
    if (not ((i == j) == cmp_eq))
    {
        printf("ERROR %lu == %lu\n", i, j);
        return false;
    }

    bool cmp_neq = (a != b);
    prf.Inc();
    if (not ((i != j) == cmp_neq))
    {
        printf("ERROR %lu != %lu\n", i, j);
        return false;
    }
    return true;
}

bool CTestNumberCmp::Test(sTestPerformance &test_perf)
{
    printf("==== Testing compare ====\n");
    test_perf.test_name = "COMPARE";

    printf("= low\n");
    test_perf.perfomance.emplace_back();
    sTestPerformanceAspect &perf_cmp = test_perf.perfomance.back();
    perf_cmp.name = "comparison low";
    perf_cmp.Start();
    for (uint64 i = 0; i < TEST_MAX_COUNT; ++i)
    {
        for (uint64 j = 0; j < TEST_MAX_COUNT; ++j)
        {
            if (not TestNumbers(i, j, perf_cmp))
            {
                perf_cmp.End();
                return false;
            }
        }
        if ((i % (TEST_MAX_COUNT/10)) == 0)
            printf("done %02lu%%\n", i*100/TEST_MAX_COUNT);
    }
    perf_cmp.End();

    printf("= rnd32\n");
    test_perf.perfomance.emplace_back();
    sTestPerformanceAspect &perf_cmp_rnd32 = test_perf.perfomance.back();
    perf_cmp_rnd32.name = "comparison random32";
    perf_cmp_rnd32.Start();
    for (uint64 ic = 0; ic < TEST_MAX_COUNT*TEST_MAX_COUNT; ++ic)
    {
        if (not TestNumbers(Random32(), Random32(), perf_cmp_rnd32))
        {
            perf_cmp_rnd32.End();
            return false;
        }
        if ((ic % (TEST_MAX_COUNT*TEST_MAX_COUNT/10)) == 0)
            printf("done %02lu%%\n", ic*100/(TEST_MAX_COUNT*TEST_MAX_COUNT));
    }
    perf_cmp_rnd32.End();

    printf("= rnd64\n");
    test_perf.perfomance.emplace_back();
    sTestPerformanceAspect &perf_cmp_rnd64 = test_perf.perfomance.back();
    perf_cmp_rnd64.name = "comparison random64";
    perf_cmp_rnd64.Start();
    for (uint64 ic = 0; ic < TEST_MAX_COUNT*TEST_MAX_COUNT; ++ic)
    {
        if (not TestNumbers(Random64(), Random64(), perf_cmp_rnd64))
        {
            perf_cmp_rnd64.End();
            return false;
        }
        if ((ic % (TEST_MAX_COUNT*TEST_MAX_COUNT/10)) == 0)
            printf("done %02lu%%\n", ic*100/(TEST_MAX_COUNT*TEST_MAX_COUNT));
    }
    perf_cmp_rnd64.End();

    return true;
}
