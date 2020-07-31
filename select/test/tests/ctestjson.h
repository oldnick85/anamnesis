#ifndef CTESTJSON_H
#define CTESTJSON_H

#include "ctestcase.h"

/*!
 * \brief CTestJSON - тест сохранения объектов в JSON
 */
class CTestJSON
        : public CTestCase
{
public:
    CTestJSON() = default;

    virtual bool Test(sTestPerformance &test_perf) override final;
private:
    bool TestCombinePermutation(sTestPerformanceAspect &perf) const;
    bool TestSetgSingle(sTestPerformanceAspect &perf) const;
    bool TestSetgDouble(sTestPerformanceAspect &perf) const;
};

#endif // CTESTJSON_H
