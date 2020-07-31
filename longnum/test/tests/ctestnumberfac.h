#ifndef CTESTFAC_H
#define CTESTFAC_H

#include "ctestcase.h"

/**
 * @brief CTestNumberFac -  - тестирование комбинаторных функций
 */
class CTestNumberFac
		: public CTestCase
{
public:
	CTestNumberFac() = default;

    virtual bool Test(sTestPerformance &test_perf) override final;
private:
    bool TestNumbers(const uint64 i, const uint64 j, sTestPerformanceAspect &prf);
};

#endif // CTESTFAC_H
