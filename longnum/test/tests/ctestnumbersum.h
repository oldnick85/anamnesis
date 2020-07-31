#ifndef CTESTSUM_H
#define CTESTSUM_H

#include "ctestcase.h"

/**
 * @brief CTestNumberSum - тестирование функций сложения
 */
class CTestNumberSum
		: public CTestCase
{
public:
	CTestNumberSum() = default;
	virtual bool Test(sTestPerformance &test_perf) override final;
private:
    bool TestNumbers(const uint64 i, const uint64 j, sTestPerformanceAspect &prf);
};

#endif // CTESTSUM_H
