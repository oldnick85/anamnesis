#ifndef CTESTMUL_H
#define CTESTMUL_H

#include "ctestcase.h"

/**
 * @brief CTestNumberMul - тестирование функций умножения
 */
class CTestNumberMul
		: public CTestCase
{
public:
	CTestNumberMul() = default;

	virtual bool Test(sTestPerformance &test_perf) override final;
private:
    bool TestNumbers(const uint64 i, const uint64 j, sTestPerformanceAspect &prf);
};

#endif // CTESTMUL_H
