#ifndef CTESTSETGENSINGLE_H
#define CTESTSETGENSINGLE_H

#include "ctestcase.h"

/*!
 * \brief CTestSetgenSingle - тест одиночного генератора
 */
class CTestSetgenSingle
        : public CTestCase
{
public:
    CTestSetgenSingle() = default;
    // CTestCase
    virtual bool Test(sTestPerformance &test_perf) override final;
private:
    bool TestSetgenSingle();
};

#endif // CTESTSETGENSINGLE_H
