#ifndef CTESTCMP_H
#define CTESTCMP_H

#include "ctestcase.h"

/**
 * @brief CTestNumberCmp - тестирование функций сравнения
 */
class CTestNumberCmp
        : public CTestCase
{
public:
	CTestNumberCmp() = default;
    virtual bool Test(sTestPerformance &test_perf) override final;
private:
    bool TestNumbers(const uint64 i, const uint64 j, sTestPerformanceAspect &prf);
};

#endif // CTESTCMP_H
