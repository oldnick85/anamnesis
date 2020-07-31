#include "ctestsetgensingle.h"

bool CTestSetgenSingle::Test(sTestPerformance &test_perf)
{
    printf("==== Testing single set generator ====\n");
    test_perf.test_name = "SINGLE_GENERATORS";

    printf("= \n");
    test_perf.perfomance.emplace_back();
    sTestPerformanceAspect &perf_div = test_perf.perfomance.back();
    perf_div.name = "";
    perf_div.Start();
    if (not TestSetgenSingle()) {perf_div.End(); return false;}
    perf_div.End();

    return true;
}

bool CTestSetgenSingle::TestSetgenSingle()
{
    CSetgenSingle setgen;
    Result_t res;

    std::string var1 = "var1";
    res = setgen.AddVariant(var1);
    if (res.ERROR())
    {
        printf("add variant %s error", var1.c_str());
        return false;
    }
    res = setgen.AddVariant(var1);
    if (res.OK())
    {
        printf("add same variant %s error", var1.c_str());
        return false;
    }

    std::string var2 = "var2";
    res = setgen.AddVariant(var2);
    if (res.ERROR())
    {
        printf("add variant %s error", var2.c_str());
        return false;
    }
    res = setgen.AddVariant(var2);
    if (res.OK())
    {
        printf("add same variant %s error", var2.c_str());
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
