#ifndef CTESTSFT_H
#define CTESTSFT_H

#include "ctestcase.h"

/**
 * @brief CTestNumberSft - тестирование функций сдвига
 */
class CTestNumberSft
        : public CTestCase
{
public:
	CTestNumberSft() = default;
    virtual bool Test(sTestPerformance &test_perf) override final;
private:
    bool TestNumbers(const uint64 i, const uint sh, sTestPerformanceAspect &prf);
};

#endif // CTESTSFT_H
