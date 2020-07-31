#ifndef CTESTSUB_H
#define CTESTSUB_H

#include "ctestcase.h"

/**
 * @brief CTestNumberSub - тестирование функций вычитания
 */
class CTestNumberSub
        : public CTestCase
{
public:
	CTestNumberSub() = default;
    virtual bool Test(sTestPerformance &test_perf) override final;
private:
    bool TestNumbers(const uint64 i, const uint64 j);
};
#endif // CTESTSUB_H
