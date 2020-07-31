#ifndef CARGPARSER_H
#define CARGPARSER_H

#include <memory>
#include <vector>
#include <algorithm>

/*!
 * \~english \brief CArgParser - command line arguments parser
 * \~russian \brief CArgParser - парсер аргументов командной строки
 */
class CArgParser
{
public:
    /*!
     * \brief sArgument - структура аргумента командной строки
     */
    struct sArgument
    {
        /*!
         * \brief sArgument - конструктор структуры аргумента командной строки
         * \param[in] arg - аргумент командной строки
         * \param[in] prm - параметры аргумента командной строки
         */
        sArgument(const std::string &arg, const std::vector<std::string> &prm = {}) {argument = arg; parameters = prm;}
        std::string                 argument;       ///< аргумент
        std::vector<std::string>    parameters;     ///< параметры аргумента
    };

    CArgParser() = default;
    /*!
     * \brief CArgParser - конструктор парсера аргументов командной строки
     * \param[in] argc - количество аргументов командной строки
     * \param[in] argv - массив указателей на аргументы командной строки
     */
    CArgParser(const int argc, char **argv);
    /*!
     * \brief Parse - парсинг аргументов командной строки
     * \param[in] argc - количество аргументов командной строки
     * \param[in] argv - массив указателей на аргументы командной строки
     */
    void Parse(const int argc, char **argv);
    /*!
     * \brief GetArguments - получить список аргументов
     * \return список аргументов
     */
    const std::vector<sArgument>& GetArguments() const;
    /*!
     * \brief CheckArgument - проверить наличие аргумента
     * \param[in] arg - имя аргумента
     * \return наличие аргумента
     */
    bool CheckArgument(const std::string& arg) const;
    /*!
     * \brief CheckArguments - проверить наличие хотя бы одного из аргументов
     * \param[in] args - имена аргументов
     * \return наличие одного из аргументов
     */
    bool CheckArgument(const std::vector<std::string>& args) const;
protected:
private:
    std::vector<sArgument>    m_arguments;
};
using CArgParserPtr = std::shared_ptr<CArgParser>;

#endif // CARGPARSER_H
