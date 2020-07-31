#ifndef CTESTDIGITNUMBERSTR_H
#define CTESTDIGITNUMBERSTR_H

#include "ctestcase.h"

/*!
 * \brief CTestCombPermutation - тест комбинатора перестановок
 */
class CTestCombPermutation
        : public CTestCase
{
public:
    CTestCombPermutation() = default;
    virtual ~CTestCombPermutation() override = default;
    // CTestCase
	virtual bool Test(sTestPerformance &test_perf) override final;
private:
    bool TestPerm(const uint64 n, const uint64 k, const Sampling_t perm_set, const uint64 base, const uint64 value);
};

#endif // CTESTDIGITNUMBERSTR_H
