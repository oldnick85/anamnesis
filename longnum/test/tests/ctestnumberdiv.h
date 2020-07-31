#ifndef CTESTDIV_H
#define CTESTDIV_H

#include "ctestcase.h"

/**
 * @brief CTestNumberDiv -  - тестирование функций деления
 */
class CTestNumberDiv
        : public CTestCase
{
public:
	CTestNumberDiv() = default;

    virtual bool Test(sTestPerformance &test_perf) override final;
private:
    bool TestNumbers(const uint64 i, const uint64 j, sTestPerformanceAspect &prf);
};


#endif // CTESTDIV_H
