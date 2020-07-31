#include "ctestsetgendouble.h"

bool CTestSetgenDouble::Test(sTestPerformance &test_perf)
{
    printf("==== Testing double set generator ====\n");
    test_perf.test_name = "DOUBLE_GENERATORS";

    printf("= \n");
    test_perf.perfomance.emplace_back();
    sTestPerformanceAspect &perf_div = test_perf.perfomance.back();
    perf_div.name = "";
    perf_div.Start();
    if (not TestSetgenDouble()) {perf_div.End(); return false;}
    perf_div.End();

    return true;
}

bool CTestSetgenDouble::TestSetgenDouble()
{
    CSetgenDouble setgen;

    std::string var1f = "var1f";
    Result_t res;
    res = setgen.AddVariant(var1f, CSetgenDouble::enVariantsBank::vbFirst);
    if (res.ERROR())
    {
        printf("add variant %s error", var1f.c_str());
        return false;
    }
    res = setgen.AddVariant(var1f, CSetgenDouble::enVariantsBank::vbFirst);
    if (res.OK())
    {
        printf("add same variant %s error", var1f.c_str());
        return false;
    }

    std::string var2f = "var2f";
    res = setgen.AddVariant(var2f, CSetgenDouble::enVariantsBank::vbSecond);
    if (res.ERROR())
    {
        printf("add variant %s error", var2f.c_str());
        return false;
    }
    res = setgen.AddVariant(var2f, CSetgenDouble::enVariantsBank::vbSecond);
    if (res.OK())
    {
        printf("add same variant %s error", var2f.c_str());
        return false;
    }

    std::string var1s = "var1s";
    res = setgen.AddVariant(var1s, CSetgenDouble::enVariantsBank::vbFirst);
    if (res.ERROR())
    {
        printf("add variant %s error", var1s.c_str());
        return false;
    }
    res = setgen.AddVariant(var1s, CSetgenDouble::enVariantsBank::vbFirst);
    if (res.OK())
    {
        printf("add same variant %s error", var1s.c_str());
        return false;
    }

    std::string var2s = "var2s";
    res = setgen.AddVariant(var2s, CSetgenDouble::enVariantsBank::vbSecond);
    if (res.ERROR())
    {
        printf("add variant %s error", var2s.c_str());
        return false;
    }
    res = setgen.AddVariant(var2s, CSetgenDouble::enVariantsBank::vbSecond);
    if (res.OK())
    {
        printf("add same variant %s error", var2s.c_str());
        return false;
    }

    std::string desc = "desc";
    setgen.SetDescription(desc);
    auto get_desc = setgen.GetDescription();
    if (desc != get_desc)
    {
        printf("set-get description %s -> %s error", desc.c_str(), get_desc.c_str());
        return false;
    }

    if ((setgen.Valid(enPurpose::pEncode).ERROR()) or (setgen.Valid(enPurpose::pDecode).ERROR()))
    {
        printf("setgen valid error");
        return false;
    }

    if (setgen.VariantsCount() == 0)
    {
        printf("setgen variants count error");
        return false;
    }

    return true;
}
