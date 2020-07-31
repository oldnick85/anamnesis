#include "ctestcombinecombination.h"

bool CTestCombineCombination::Test(sTestPerformance &test_perf)
{
    printf("==== Testing combinations ====\n");
    test_perf.test_name = "COMBINATIONS";

    printf("= \n");
    test_perf.perfomance.emplace_back();
    sTestPerformanceAspect &perf_div = test_perf.perfomance.back();
    perf_div.name = "";
    perf_div.Start();
    if (not TestComb(7, 3, {0, 1, 2}, 35, 34)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {0, 1, 3}, 35, 33)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {0, 1, 4}, 35, 32)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {0, 1, 5}, 35, 31)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {0, 1, 6}, 35, 30)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {0, 2, 3}, 35, 29)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {0, 2, 4}, 35, 28)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {0, 2, 5}, 35, 27)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {0, 2, 6}, 35, 26)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {0, 3, 4}, 35, 25)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {0, 3, 5}, 35, 24)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {0, 3, 6}, 35, 23)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {0, 4, 5}, 35, 22)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {0, 4, 6}, 35, 21)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {0, 5, 6}, 35, 20)) {perf_div.End(); return false;}

    if (not TestComb(7, 3, {1, 2, 3}, 35, 19)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {1, 2, 4}, 35, 18)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {1, 2, 5}, 35, 17)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {1, 2, 6}, 35, 16)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {1, 3, 4}, 35, 15)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {1, 3, 5}, 35, 14)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {1, 3, 6}, 35, 13)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {1, 4, 5}, 35, 12)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {1, 4, 6}, 35, 11)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {1, 5, 6}, 35, 10)) {perf_div.End(); return false;}

    if (not TestComb(7, 3, {2, 3, 4}, 35, 9)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {2, 3, 5}, 35, 8)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {2, 3, 6}, 35, 7)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {2, 4, 5}, 35, 6)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {2, 4, 6}, 35, 5)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {2, 5, 6}, 35, 4)) {perf_div.End(); return false;}

    if (not TestComb(7, 3, {3, 4, 5}, 35, 3)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {3, 4, 6}, 35, 2)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {3, 5, 6}, 35, 1)) {perf_div.End(); return false;}

    if (not TestComb(7, 3, {4, 5, 6}, 35, 0)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {6, 4, 5}, 35, 0)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {5, 6, 4}, 35, 0)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {5, 4, 6}, 35, 0)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {4, 6, 5}, 35, 0)) {perf_div.End(); return false;}
    if (not TestComb(7, 3, {6, 5, 4}, 35, 0)) {perf_div.End(); return false;}

    perf_div.End();

    return true;
}

bool CTestCombineCombination::TestComb(const uint64 n, const uint64 k, const Sampling_t comb_set, const uint64 base, const uint64 value)
{
    CCombineCombination comb;
    Result_t res;
    res = comb.SetParameters(n, k);
    if (res.ERROR())
    {
        printf("set parameters n=%lu, k=%lu error\n", n, k);
        return false;
    }
    res = comb.SetCombination(comb_set);
    if (res.ERROR())
    {
        printf("set permutation error\n");
        return false;
    }
    CNumber b = comb.VariantsCount();
    CNumber v = comb.Value();
    if (b != base)
    {
        printf("base (%s == %lu) mismatch\n", b.PrintDec().c_str(), base);
        return false;
    }
    if (v != value)
    {
        printf("value (%s == %lu) mismatch\n", v.PrintDec().c_str(), value);
        return false;
    }
    return true;
}
