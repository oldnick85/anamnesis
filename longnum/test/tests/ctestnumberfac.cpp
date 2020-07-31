#include "ctestnumberfac.h"

bool CTestNumberFac::TestNumbers(const uint64 i, const uint64 j, sTestPerformanceAspect &prf)
{
    uint64 f = 0;
    switch (j)
    {
    case 0:     f = 1;                          break;
    case 1:     f = 1;                          break;
    case 2:     f = 2 ;                         break;
    case 3:     f = 6 ;                         break;
    case 4:     f = 24 ;                        break;
    case 5:     f = 120 ;                       break;
    case 6:     f = 720 ;                       break;
    case 7:     f = 5040 ;                      break;
    case 8:     f = 40320 ;                     break;
    case 9:     f = 362880 ;                    break;
    case 10:    f = 3628800 ;                   break;
    case 11:    f = 39916800 ;                  break;
    case 12:    f = 479001600 ;                 break;
    case 13:    f = 6227020800 ;                break;
    case 14:    f = 87178291200 ;               break;
    case 15:    f = 1307674368000 ;             break;
    case 16:    f = 20922789888000 ;            break;
    case 17:    f = 355687428096000 ;           break;
    case 18:    f = 6402373705728000 ;          break;
    case 19:    f = 121645100408832000 ;        break;
    case 20:    f = 2432902008176640000 ;       break;
    }

    prf.Inc();
    if (not (i == f))
    {
        printf("ERROR factorial %lu; %lu;\n", i, f);
        return false;
    }

    return true;
}

bool CTestNumberFac::Test(sTestPerformance &test_perf)
{
    printf("==== Testing factorial ====\n");
    test_perf.test_name = "FACTORIAL";

    printf("= low\n");
    test_perf.perfomance.emplace_back();
    sTestPerformanceAspect &perf_div = test_perf.perfomance.back();
    perf_div.name = "factorial low";
    perf_div.Start();
    for (uint64 i = 0; i < 20; ++i)
    {
        CNumber fac = CNumber(i).Factorial();
        if (not TestNumbers(fac.ToUint64(), i, perf_div))
        {
            perf_div.End();
            return false;
        }
    }
    perf_div.End();

    return true;
}
