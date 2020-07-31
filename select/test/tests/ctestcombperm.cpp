#include "ctestcombperm.h"

bool CTestCombPermutation::Test(sTestPerformance &test_perf)
{
    printf("==== Testing permutations ====\n");
	test_perf.test_name = "PERMUTATIONS";

	printf("= \n");
	test_perf.perfomance.emplace_back();
	sTestPerformanceAspect &perf_div = test_perf.perfomance.back();
	perf_div.name = "";
	perf_div.Start();
    if (not TestPerm(4, 4, {0, 1, 2, 3}, 24, 0)) {perf_div.End(); return false;}
    if (not TestPerm(4, 4, {1, 3, 0, 2}, 24, 10)) {perf_div.End(); return false;}
    if (not TestPerm(4, 4, {3, 2, 1, 0}, 24, 23)) {perf_div.End(); return false;}

    if (not TestPerm(5, 3, {0, 1, 2}, 60, 0)) {perf_div.End(); return false;}
    if (not TestPerm(5, 3, {0, 1, 3}, 60, 1)) {perf_div.End(); return false;}
    if (not TestPerm(5, 3, {4, 3, 2}, 60, 59)) {perf_div.End(); return false;}
	perf_div.End();

	return true;
}

bool CTestCombPermutation::TestPerm(const uint64 n, const uint64 k, const Sampling_t perm_set, const uint64 base, const uint64 value)
{
    CCombinePermutation perm;
    Result_t res;
    res = perm.SetParameters(n, k);
    if (res.ERROR())
    {
        printf("set parameters n=%lu, k=%lu error", n, k);
        return false;
    }
    res = perm.SetPermutation(perm_set);
    if (res.ERROR())
    {
        printf("set permutation error");
        return false;
    }
    CNumber b = perm.VariantsCount();
    CNumber v = perm.Value();
    if (b != base)
    {
        printf("base (%s == %lu) mismatch", b.PrintDec().c_str(), base);
        return false;
    }
    if (v != value)
    {
        printf("value (%s == %lu) mismatch", v.PrintDec().c_str(), value);
        return false;
    }
    return true;
}
