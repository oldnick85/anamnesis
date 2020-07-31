#include "cargparser.h"

CArgParser::CArgParser(const int argc, char **argv)
{
    Parse(argc, argv);
}

void CArgParser::Parse(const int argc, char **argv)
{
    for (int i = 0; i < argc; ++i)
    {
        std::string token = argv[i];
        const bool is_arg = (not token.empty()) and (token[0] == '-');
        if ((not is_arg) and (m_arguments.empty()))
        {
            m_arguments.push_back(sArgument(""));
        }
        if (is_arg)
        {
            m_arguments.push_back(sArgument(token));
        }
        else
        {
            m_arguments.back().parameters.push_back(token);
        }
    }
}

const std::vector<CArgParser::sArgument> &CArgParser::GetArguments() const
{
    return m_arguments;
}

bool CArgParser::CheckArgument(const std::string &arg) const
{
    return std::any_of(m_arguments.begin(), m_arguments.end(),
                       [arg](const sArgument& a){return (a.argument == arg);});
}

bool CArgParser::CheckArgument(const std::vector<std::string>& args) const
{
    return std::any_of(args.begin(), args.end(),
                       [this](const std::string &arg){return CheckArgument(arg);});
}
