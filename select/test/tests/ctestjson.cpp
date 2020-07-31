#include "ctestjson.h"

bool CTestJSON::Test(sTestPerformance &test_perf)
{
    printf("==== Testing JSON ====\n");
    test_perf.test_name = "JSON";

    printf("= \n");
    test_perf.perfomance.emplace_back();
    sTestPerformanceAspect &perf_json = test_perf.perfomance.back();
    perf_json.name = "json";
    perf_json.Start();

    if (not TestCombinePermutation(perf_json)) {perf_json.End(); return false;}
    if (not TestSetgSingle(perf_json)) {perf_json.End(); return false;}
    if (not TestSetgDouble(perf_json)) {perf_json.End(); return false;}

    perf_json.End();

    return true;
}

bool CTestJSON::TestCombinePermutation(sTestPerformanceAspect &perf) const
{
    CCombinePermutation perm1;
    perm1.SetParameters(5, 3);
    perm1.SetPermutation({0, 1, 2});
    rapidjson::Document json_doc1 = perm1.toJSON();
    rapidjson::StringBuffer buffer1;
    rapidjson::Writer<rapidjson::StringBuffer> writer1(buffer1);
    json_doc1.Accept(writer1);
    std::string perm_json1 = buffer1.GetString();
    printf("JSON1=%s\n", perm_json1.c_str());

    CCombinePermutation perm2;
    rapidjson::Document json_doc2;
    json_doc2.Parse(perm_json1.c_str());
    if (not perm2.fromJSON(json_doc2))
    {
        printf("ERROR CCombinePermutation fromJSON\n");
        return false;
    }
    rapidjson::StringBuffer buffer2;
    rapidjson::Writer<rapidjson::StringBuffer> writer2(buffer2);
    json_doc2.Accept(writer2);
    std::string perm_json2 = buffer2.GetString();
    printf("JSON2=%s\n", perm_json2.c_str());
    perf.Increment();

    if ((perm1.GetParameterN() != perm2.GetParameterN()) or (perm1.GetParameterK() != perm2.GetParameterK()))
    {
        printf("ERROR CCombinePermutation JSON restore mismatch\n");
        return false;
    }

    if (not (perm_json1 == perm_json2))
    {
        printf("ERROR CCombinePermutation JSON strings mismatch\n");
        return false;
    }

    return true;
}

bool CTestJSON::TestSetgSingle(sTestPerformanceAspect &perf) const
{
    CSetgenSingle setgs1;
    setgs1.SetVariants({"var1", "var2", "var3"});
    rapidjson::Document json_doc1 = setgs1.toJSON();
    rapidjson::StringBuffer buffer1;
    rapidjson::Writer<rapidjson::StringBuffer> writer1(buffer1);
    json_doc1.Accept(writer1);
    std::string setgs_json1 = buffer1.GetString();
    printf("JSON1=%s\n", setgs_json1.c_str());

    CSetgenSingle setgs2;
    rapidjson::Document json_doc2;
    json_doc2.Parse(setgs_json1.c_str());
    if (not setgs2.fromJSON(json_doc2))
    {
        printf("ERROR CSetgenSingle fromJSON\n");
        return false;
    }
    rapidjson::StringBuffer buffer2;
    rapidjson::Writer<rapidjson::StringBuffer> writer2(buffer2);
    json_doc2.Accept(writer2);
    std::string setgs_json2 = buffer2.GetString();
    printf("JSON2=%s\n", setgs_json2.c_str());
    perf.Increment();

    if (not (setgs1 == setgs2))
    {
        printf("ERROR CSetgenSingle JSON restore mismatch\n");
        return false;
    }

    if (not (setgs_json1 == setgs_json2))
    {
        printf("ERROR CSetgenSingle JSON strings mismatch\n");
        return false;
    }
    return true;
}

bool CTestJSON::TestSetgDouble(sTestPerformanceAspect &perf) const
{
    CSetgenDouble setgs1;
    setgs1.SetVariants({"var1 f", "var2 f", "var3 f"}, CSetgenDouble::enVariantsBank::vbFirst);
    setgs1.SetVariants({"var1 s", "var2 s", "var3 s"}, CSetgenDouble::enVariantsBank::vbSecond);
    rapidjson::Document json_doc1 = setgs1.toJSON();
    rapidjson::StringBuffer buffer1;
    rapidjson::Writer<rapidjson::StringBuffer> writer1(buffer1);
    json_doc1.Accept(writer1);
    std::string setgs_json1 = buffer1.GetString();
    printf("JSON1=%s\n", setgs_json1.c_str());

    CSetgenDouble setgs2;
    rapidjson::Document json_doc2;
    json_doc2.Parse(setgs_json1.c_str());
    if (not setgs2.fromJSON(json_doc2))
    {
        printf("ERROR CSetgenDouble fromJSON\n");
        return false;
    }
    rapidjson::StringBuffer buffer2;
    rapidjson::Writer<rapidjson::StringBuffer> writer2(buffer2);
    json_doc2.Accept(writer2);
    std::string setgs_json2 = buffer2.GetString();
    printf("JSON2=%s\n", setgs_json2.c_str());
    perf.Increment();

    if (not (setgs1 == setgs2))
    {
        printf("ERROR CSetgenDouble JSON restore mismatch\n");
        return false;
    }

    if (not (setgs_json1 == setgs_json2))
    {
        printf("ERROR CSetgenDouble JSON strings mismatch\n");
        return false;
    }
    return true;
}
