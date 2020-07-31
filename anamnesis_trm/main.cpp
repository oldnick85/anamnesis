#include <cstring>
#include "../longnum/cnumber.h"
#include "common.h"
#include "ctrmmain.h"
#include "../common/version.h"
#include "../cmdlnargs/cargparser.h"

int main(int argc, char **argv)
{
    auto arg_parser = CArgParserPtr(new CArgParser(argc, argv));
    printf("%s\n", text.PrintProgramName().c_str());
    std::vector<std::string> help_args = {"-h", "--help"};
    if (arg_parser->CheckArgument(help_args))
    {
        printf("HELP\n");
        return 0;
    }
    CTrmMain trm;
    trm.Begin();
	return 0;
}
