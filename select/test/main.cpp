#include <cstring>
#include "ctestsuite.h"

int main(int argc, char **argv)
{
    CTestSuite tst;
    //tst.ProcArgument("casket");
    printf("arguments count %d\n", argc);
    for (int arg_i = 1; arg_i < argc; ++arg_i)
	{
        printf("argument %s\n", argv[arg_i]);
        auto test_ok = tst.ProcArgument(argv[arg_i]);
        if (not test_ok)
            return 1;
	}
    printf("program end\n");
	return 0;
}
