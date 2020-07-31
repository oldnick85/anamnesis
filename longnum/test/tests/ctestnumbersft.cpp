#include "ctestnumbersft.h"

bool CTestNumberSft::TestNumbers(const uint64 i, const uint sh, sTestPerformanceAspect &prf)
{
    CNumber a(i);
    CNumber s;

    s = a << sh;
    prf.Inc();
    uint64 k = s.ToUint64();
    uint64 rs = i << sh;
    if (not (rs == k))
    {
        printf("ERROR %lu << %u\n", i, sh);
        return false;
    }

    s = a >> sh;
    prf.Inc();
    k = s.ToUint64();
    rs = i >> sh;
    if (not (rs == k))
    {
        printf("ERROR %lu << %u\n", i, sh);
        return false;
    }
    return true;
}

bool CTestNumberSft::Test(sTestPerformance &test_perf)
{
    printf("==== Testing shift ====\n");
    test_perf.test_name = "SFT";

    printf("= low\n");
    test_perf.perfomance.emplace_back();
    sTestPerformanceAspect &perf_sft = test_perf.perfomance.back();
    perf_sft.name = "shift low";
    perf_sft.Start();
    for (uint64 i = 0; i < TEST_MAX_COUNT*TEST_MAX_COUNT; ++i)
    {
        for (uint sh = 0; sh < 8; ++sh)
        {
            if (not TestNumbers(i, sh, perf_sft))
            {
                perf_sft.End();
                return false;
            }
            perf_sft.Inc();
        }
        if ((i % (TEST_MAX_COUNT*TEST_MAX_COUNT/10)) == 0)
            printf("done %02lu%%\n", i*100/(TEST_MAX_COUNT*TEST_MAX_COUNT));
    }
    perf_sft.End();

    printf("= rnd32\n");
    test_perf.perfomance.emplace_back();
    sTestPerformanceAspect &perf_sft_rnd32 = test_perf.perfomance.back();
    perf_sft_rnd32.name = "shift random32";
    perf_sft_rnd32.Start();
    for (uint64 ic = 0; ic < TEST_MAX_COUNT*TEST_MAX_COUNT; ++ic)
    {
        if (not TestNumbers(Random32(), 1, perf_sft_rnd32))
        {
            perf_sft_rnd32.End();
            return false;
        }
        perf_sft_rnd32.Inc();

        if ((ic % (TEST_MAX_COUNT*TEST_MAX_COUNT/10)) == 0)
            printf("done %02lu%%\n", ic*100/(TEST_MAX_COUNT*TEST_MAX_COUNT));
    }
    perf_sft_rnd32.End();

    printf("= rnd64\n");
    test_perf.perfomance.emplace_back();
    sTestPerformanceAspect &perf_sft_rnd64 = test_perf.perfomance.back();
    perf_sft_rnd64.name = "shift random64";
    perf_sft_rnd64.Start();
    for (uint64 ic = 0; ic < TEST_MAX_COUNT*TEST_MAX_COUNT; ++ic)
    {
        if (not TestNumbers(Random64()/2, 1, perf_sft_rnd64))
        {
            perf_sft_rnd64.End();
            return false;
        }
        perf_sft_rnd64.Inc();

        if ((ic % (TEST_MAX_COUNT*TEST_MAX_COUNT/10)) == 0)
            printf("done %02lu%%\n", ic*100/(TEST_MAX_COUNT*TEST_MAX_COUNT));
    }
    perf_sft_rnd64.End();

    return true;
}
