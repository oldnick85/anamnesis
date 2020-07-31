#include "ctestcase.h"

CTestCase::CTestCase()
{
    m_rnd_gen = new std::mt19937(m_rd());
}

uint32 CTestCase::Random32()
{
    std::uniform_int_distribution<uint32> uid(0, ~static_cast<uint32>(0));
    return uid(*m_rnd_gen);
}

uint64 CTestCase::Random64()
{
    std::uniform_int_distribution<uint64> uid(0, ~static_cast<uint64>(0));
    return uid(*m_rnd_gen);
}
