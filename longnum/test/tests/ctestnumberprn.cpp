#include "ctestnumberprn.h"

bool CTestNumberPrn::Test(sTestPerformance &test_perf)
{
    printf("==== Testing print ====\n");
    test_perf.test_name = "PRINT";

    printf("= low\n");
	test_perf.perfomance.emplace_back();
	sTestPerformanceAspect &perf_uint = test_perf.perfomance.back();
	perf_uint.name = "uint->CNumber->uint";
	perf_uint.Start();
    for (uint64 i = 0; i < TEST_MAX_COUNT*TEST_MAX_COUNT; ++i)
	{
		CNumber a(i);
		auto x = a.ToUint64();
		perf_uint.Inc();
		if (i != x)
		{
            printf("ERROR %lu to %lu\n", i, x);
			perf_uint.End();
			return false;
		}
	}
	perf_uint.End();

    printf("= rnd32\n");
    test_perf.perfomance.emplace_back();
    sTestPerformanceAspect &perf_uint_rnd32 = test_perf.perfomance.back();
    perf_uint_rnd32.name = "uint->CNumber->uint rnd32";
    perf_uint_rnd32.Start();
    for (uint64 i = 0; i < TEST_MAX_COUNT*TEST_MAX_COUNT; ++i)
    {
        uint64 v = Random32();
        CNumber a(v);
        auto x = a.ToUint64();
        if (v != x)
        {
            printf("ERROR %lu to %lu\n", i, x);
            perf_uint_rnd32.End();
            return false;
        }
        perf_uint_rnd32.Inc();
    }
    perf_uint_rnd32.End();

    printf("= rnd64\n");
    test_perf.perfomance.emplace_back();
    sTestPerformanceAspect &perf_uint_rnd64 = test_perf.perfomance.back();
    perf_uint_rnd64.name = "uint->CNumber->uint rnd32";
    perf_uint_rnd64.Start();
    for (uint64 i = 0; i < TEST_MAX_COUNT*TEST_MAX_COUNT; ++i)
    {
        uint64 v = Random64();
        CNumber a(v);
        auto x = a.ToUint64();
        if (v != x)
        {
            printf("ERROR %lu to %lu\n", i, x);
            perf_uint_rnd64.End();
            return false;
        }
        perf_uint_rnd64.Inc();
    }
    perf_uint_rnd64.End();

	CNumber v0(0b0);
	auto v0str = v0.PrintBin();
	if (v0str != "0")
	{
        printf("ERROR %s != 0\n", v0str.c_str());
		return false;
	}

	CNumber v1(0b101010);
	auto v1str = v1.PrintBin();
	if (v1str != "101010")
	{
        printf("ERROR %s != 101010\n", v1str.c_str());
		return false;
	}

	CNumber v2(0b110110101);
	auto v2str = v2.PrintBin();
	if (v2str != "110110101")
	{
        printf("ERROR %s != 110110101\n", v2str.c_str());
		return false;
	}

	CNumber v3(0b111111111111);
	auto v3str = v3.PrintBin();
	if (v3str != "111111111111")
	{
        printf("ERROR %s != 111111111111\n", v3str.c_str());
		return false;
	}

    CNumber v4(12345);
    auto v4str = v4.PrintDec();
    if (v4str != "12345")
    {
        printf("ERROR %s != 12345\n", v4str.c_str());
        return false;
    }

    CNumber v5(0);
    auto v5str = v5.PrintDec();
    if (v5str != "0")
    {
        printf("ERROR %s != 0\n", v5str.c_str());
        return false;
    }

    CNumber v6(0x12345);
    auto v6str = v6.PrintHex();
    if (v6str != "12345")
    {
        printf("ERROR %s != 12345\n", v6str.c_str());
        return false;
    }

    CNumber v7(0x0);
    auto v7str = v5.PrintHex();
    if (v7str != "0")
    {
        printf("ERROR %s != 0\n", v7str.c_str());
        return false;
    }

	return true;
}
