#ifndef CTESTCASKET_H
#define CTESTCASKET_H

#include "ctestcase.h"

/*!
 * \brief CTestCasket - тест кодирования и раскодирования пароля
 */
class CTestCasket
        : public CTestCase
{
public:
    CTestCasket() = default;

    virtual bool Test(sTestPerformance &test_perf) override final;
private:
    bool TestEncDecPerm(sTestPerformanceAspect &perf);
    bool TestEncDecComb(sTestPerformanceAspect &perf);
    bool TestEncDecBug(sTestPerformanceAspect &perf);
    bool TestEncDecRandom(sTestPerformanceAspect &perf);

    Pass_t RandomPassSymbols(const uint size);
    Pass_t RandomPass(const uint size, const Pass_t &symbols);
    Sampling_t RandomPermutation(const uint n, const uint k);
    void ShufflePermutation(Sampling_t &permutation);
    std::list<std::string> RandomSetgenVariants(const uint k);

    std::mt19937    m_generator;

    struct sTestCasketCombine
    {
        std::string Print() const
        {
            std::string s;

            s.append("type: ");
            switch (type)
            {
            case enCombineType::ctNone:         s.append("NONE");   break;
            case enCombineType::ctPermutation:  s.append("PERM");   break;
            case enCombineType::ctCombination:  s.append("COMB");   break;
            }

            s.append("; val:");
            for (const auto v : values)
            {
                s.append(" ");
                s.append(std::to_string(v));
            }
            s.append("; var: ");
            for (const auto &v : setgen_variants)
            {
                s.append(" ");
                s.append(v);
            }
            return s;
        }

        enCombineType           type = enCombineType::ctNone;
        Sampling_t              values;
        std::list<std::string>  setgen_variants;
    };

    struct sTestCasket
    {
        std::string Print() const
        {
            std::string s;
            s.append("pass: ");
            for (const auto v : pass)
            {
                s.append(" ");
                s += static_cast<char>(v);
            }
            s.append("\nsymbols: ");
            for (const auto v : symbols)
            {
                s.append(" ");
                s += static_cast<char>(v);
            }
            for (const auto &c : combines)
            {
                s.append("\n");
                s.append(c.Print());
            }
            return s;
        }

        Pass_t                              pass;
        Pass_t                              symbols;
        std::vector<sTestCasketCombine>     combines;
    };
    sTestCasket RandomCasket(const uint permutations_count, const uint combinations_count,
                             const uint pass_symbols_min, const uint pass_symbols_max,
                             const uint pass_size_min, const uint pass_size_max,
                             const uint n_min, const uint n_max, const uint k_min, const uint k_max);
    bool TestEncodeCasket(const sTestCasket &test_casket, std::string &encoded_json);
    bool TestDecodeCasket(const sTestCasket &test_casket, const std::string &encoded_json);
};

#endif // CTESTCASKET_H
