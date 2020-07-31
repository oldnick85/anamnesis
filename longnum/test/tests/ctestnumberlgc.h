#ifndef CTESTLOGIC_H
#define CTESTLOGIC_H

#include "ctestcase.h"

/**
 * @brief CTestNumberLgc - тестирование логических функций
 */
class CTestNumberLgc
		: public CTestCase
{
public:
	CTestNumberLgc() = default;

	virtual bool Test(sTestPerformance &test_perf) override final;
private:
    bool TestNumbers(const uint64 i, const uint64 j, sTestPerformanceAspect &prf);
};

#endif // CTESTLOGIC_H
