#ifndef CTESTCOMBINECOMBINATION_H
#define CTESTCOMBINECOMBINATION_H

#include "ctestcase.h"

/*!
 * \brief CTestCombineCombination - тест комбинатора сочетаний
 */
class CTestCombineCombination
        : public CTestCase
{
public:
    CTestCombineCombination() = default;
    // CTestCase
    virtual bool Test(sTestPerformance &test_perf) override final;
private:
    bool TestComb(const uint64 n, const uint64 k, const Sampling_t comb_set, const uint64 base, const uint64 value);
};

#endif // CTESTCOMBINECOMBINATION_H
