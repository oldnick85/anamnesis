#ifndef CTESTSETGENDOUBLE_H
#define CTESTSETGENDOUBLE_H

#include "ctestcase.h"

/*!
 * \brief CTestSetgenSingle - тест одиночного генератора
 */
class CTestSetgenDouble
        : public CTestCase
{
public:
    CTestSetgenDouble() = default;
    // CTestCase
    virtual bool Test(sTestPerformance &test_perf) override final;
private:
    bool TestSetgenDouble();
};

#endif // CTESTSETGENDOUBLE_H
