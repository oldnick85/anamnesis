#include "ctestcasket.h"

#include <random>
#include <algorithm>
#include <array>
#include <numeric>

using namespace std::chrono;

#define TEST_ASSERT(asrt, msg) do{if (not (asrt)) {printf(msg); return false;}}while(0)

bool CTestCasket::Test(sTestPerformance &test_perf)
{
    unsigned long seed = static_cast<unsigned long>(duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count());
    m_generator.seed(seed);

    printf("==== Testing casket ====\n");
    test_perf.test_name = "CASKET";
    printf("= \n");

    test_perf.perfomance.emplace_back();
    sTestPerformanceAspect &perf_enc_dec = test_perf.perfomance.back();
    perf_enc_dec.name = "encode-decode";
    perf_enc_dec.Start();
    //if (not TestEncDecBug(perf_enc_dec)) {perf_enc_dec.End(); return false;}
    if (not TestEncDecPerm(perf_enc_dec)) {perf_enc_dec.End(); return false;}
    if (not TestEncDecComb(perf_enc_dec)) {perf_enc_dec.End(); return false;}
    if (not TestEncDecRandom(perf_enc_dec)) {perf_enc_dec.End(); return false;}
    perf_enc_dec.End();
    return true;
}

bool CTestCasket::TestEncDecPerm(sTestPerformanceAspect &perf)
{
    bool res = true;

    sTestCasket test_casket;
    test_casket.symbols = Pass_t({'0', '1', '2', '3'});
    test_casket.pass = Pass_t({'1', '3', '1', '0', '2', '2'});
    sTestCasketCombine test_combine;
    test_combine.type = enCombineType::ctPermutation;
    test_combine.setgen_variants = {"v1", "v2", "v3", "v4", "v5", "v6", "v7"};
    test_combine.values = {4, 1, 2, 3, 0};
    test_casket.combines.push_back(test_combine);

    std::string encoded_json;
    res = TestEncodeCasket(test_casket, encoded_json);
    TEST_ASSERT(res, "casket encode error\n");

    res = TestDecodeCasket(test_casket, encoded_json);
    TEST_ASSERT(res, "casket decode error\n");

    perf.Increment();
    return true;
}

bool CTestCasket::TestEncDecComb(sTestPerformanceAspect &perf)
{
    bool res = true;

    sTestCasket test_casket;
    test_casket.symbols = Pass_t({'0', '1', '2', '3'});
    test_casket.pass = Pass_t({'1', '3', '1', '0', '2', '2'});
    sTestCasketCombine test_combine;
    test_combine.type = enCombineType::ctCombination;
    test_combine.setgen_variants = {"v1", "v2", "v3", "v4", "v5", "v6", "v7"};
    test_combine.values = {4, 1, 2, 3, 0};
    test_casket.combines.push_back(test_combine);

    std::string encoded_json;
    res = TestEncodeCasket(test_casket, encoded_json);
    TEST_ASSERT(res, "casket encode error\n");

    res = TestDecodeCasket(test_casket, encoded_json);
    TEST_ASSERT(res, "casket decode error\n");

    perf.Increment();
    return true;
}

bool CTestCasket::TestEncDecBug(sTestPerformanceAspect &perf)
{
    bool res = true;

    sTestCasket test_casket;
    test_casket.symbols = Pass_t({'P', 'G', 'P', 'f', '2'});
    test_casket.pass = Pass_t({'P', 'i', 'f', 'n', 'G', 'e', '2', ']', 'p', 'z', 'g', '$'});
    sTestCasketCombine test_combine;

    test_combine.type = enCombineType::ctPermutation;
    test_combine.setgen_variants = {"v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8"};
    test_combine.values = {2, 0, 1, 4, 5, 7};
    test_casket.combines.push_back(test_combine);

    test_combine.type = enCombineType::ctPermutation;
    test_combine.setgen_variants = {"v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7"};
    test_combine.values = {5, 0, 6, 7, 4, 3};
    test_casket.combines.push_back(test_combine);

    test_combine.type = enCombineType::ctPermutation;
    test_combine.setgen_variants = {"v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7"};
    test_combine.values = {6, 0, 1, 7};
    test_casket.combines.push_back(test_combine);

    test_combine.type = enCombineType::ctCombination;
    test_combine.setgen_variants = {"v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9"};
    test_combine.values = {7, 1, 8, 6};
    test_casket.combines.push_back(test_combine);

    test_combine.type = enCombineType::ctPermutation;
    test_combine.setgen_variants = {"v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8"};
    test_combine.values = {8, 5, 7, 6, 4};
    test_casket.combines.push_back(test_combine);

    test_combine.type = enCombineType::ctCombination;
    test_combine.setgen_variants = {"v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7"};
    test_combine.values = {2, 7, 5, 6, 3};
    test_casket.combines.push_back(test_combine);

    test_combine.type = enCombineType::ctPermutation;
    test_combine.setgen_variants = {"v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7"};
    test_combine.values = {4, 7, 0, 6, 1};
    test_casket.combines.push_back(test_combine);

    test_combine.type = enCombineType::ctCombination;
    test_combine.setgen_variants = {"v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7"};
    test_combine.values = {3, 4, 2, 7, 5};
    test_casket.combines.push_back(test_combine);

    std::string encoded_json;
    res = TestEncodeCasket(test_casket, encoded_json);
    TEST_ASSERT(res, "casket encode error\n");

    res = TestDecodeCasket(test_casket, encoded_json);
    TEST_ASSERT(res, "casket decode error\n");

    perf.Increment();
    return true;
}

bool CTestCasket::TestEncDecRandom(sTestPerformanceAspect &perf)
{
    bool res = false;

    for (uint i = 0; i < TEST_MAX_COUNT*10; ++i)
    {
        sTestCasket test_casket = RandomCasket(5, 3, 10, 12, 4, 8, 8, 10, 4, 6);

        std::string encoded_json;
        res = TestEncodeCasket(test_casket, encoded_json);
        if (not res) {printf("%s\n", test_casket.Print().c_str());}
        TEST_ASSERT(res, "casket encode error\n");

        res = TestDecodeCasket(test_casket, encoded_json);
        if (not res) {printf("%s\n", test_casket.Print().c_str());}
        TEST_ASSERT(res, "casket decode error\n");

        perf.Increment();
    }
    return true;
}

Pass_t CTestCasket::RandomPassSymbols(const uint size)
{
    std::string symbols_all = "abcdefghijklmnopqrstuvwxyz"
                              "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                              "0123456789-_ "
                              "!@#$%^&*+=\"'\\|/.,:;~`?"
                              "(){}[]<>";
    std::vector<uint> symb_ind;
    symb_ind.resize(symbols_all.size());
    std::iota(symb_ind.begin(), symb_ind.end(), 0);

    std::shuffle(symb_ind.begin(), symb_ind.end(), m_generator);

    Pass_t symbols;
    for (size_t i = 0; i < size; ++i)
    {
        auto ind = symb_ind[i];
        symbols.push_back(static_cast<PassSymbol_t>(symbols_all[ind]));
    }

    return symbols;
}

Pass_t CTestCasket::RandomPass(const uint size, const Pass_t &symbols)
{
    Pass_t pass;
    pass.resize(size);
    std::uniform_int_distribution<size_t> dis(0, symbols.size()-1);
    for (auto &pass_symbol : pass)
    {
        auto ind = dis(m_generator);
        pass_symbol = symbols[ind];
    }
    return pass;
}

Sampling_t CTestCasket::RandomPermutation(const uint n, const uint k)
{
    Sampling_t permutation;

    permutation.resize(n);
    std::iota(permutation.begin(), permutation.end(), 0);
    std::shuffle(permutation.begin(), permutation.end(), m_generator);

    permutation.resize(k);
    return permutation;
}

void CTestCasket::ShufflePermutation(Sampling_t &permutation)
{
    auto seed = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
    std::mt19937 generator(static_cast<uint>(seed));
    std::shuffle(permutation.begin(), permutation.end(), generator);
}

std::list<std::string> CTestCasket::RandomSetgenVariants(const uint k)
{
    std::list<std::string> setgen_variants;
    for (uint i = 0; i < k; ++i)
        setgen_variants.push_back(std::to_string(i));
    return setgen_variants;
}

CTestCasket::sTestCasket CTestCasket::RandomCasket(const uint permutations_count, const uint combinations_count,
                                                   const uint pass_symbols_min, const uint pass_symbols_max,
                                                   const uint pass_size_min, const uint pass_size_max,
                                                   const uint n_min, const uint n_max, const uint k_min, const uint k_max)
{
    sTestCasket test_casket;

    auto seed = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
    std::mt19937 generator(static_cast<uint>(seed));

    std::uniform_int_distribution<uint> dis_symb(pass_symbols_min, pass_symbols_max);
    uint symbols_size = dis_symb(generator);
    test_casket.symbols = RandomPassSymbols(symbols_size);

    std::uniform_int_distribution<uint> dis_pass(pass_size_min, pass_size_max);
    uint pass_size = dis_pass(generator);
    test_casket.pass = RandomPass(pass_size, test_casket.symbols);

    for (uint i = 0; i < permutations_count; ++i)
    {
        sTestCasketCombine test_casket_combine;
        test_casket_combine.type = enCombineType::ctPermutation;
        std::uniform_int_distribution<uint> dis_n(n_min, n_max);
        uint n = dis_n(m_generator);
        std::uniform_int_distribution<uint> dis_k(k_min, k_max);
        uint k = dis_k(m_generator);
        test_casket_combine.values = RandomPermutation(n, k);
        test_casket_combine.setgen_variants = RandomSetgenVariants(n);
        test_casket.combines.push_back(test_casket_combine);
    }
    for (uint i = 0; i < combinations_count; ++i)
    {
        sTestCasketCombine test_casket_combine;
        test_casket_combine.type = enCombineType::ctCombination;
        std::uniform_int_distribution<uint> dis_n(n_min, n_max);
        uint n = dis_n(m_generator);
        std::uniform_int_distribution<uint> dis_k(k_min, k_max);
        uint k = dis_k(m_generator);
        test_casket_combine.values = RandomPermutation(n, k);
        test_casket_combine.setgen_variants = RandomSetgenVariants(n);
        test_casket.combines.push_back(test_casket_combine);
    }
    std::shuffle(test_casket.combines.begin(), test_casket.combines.end(), m_generator);

    return test_casket;
}

bool CTestCasket::TestEncodeCasket(const sTestCasket &test_casket, std::string &encoded_json)
{
    Result_t res;

    auto cskt_enc = CCasketPtr(new CCasket());

    auto pass_enc = CPassPtr(new CPass());
    res = pass_enc->SetSymbols(test_casket.symbols);
    TEST_ASSERT(res.OK(), "set pass symbols error\n");
    res = pass_enc->SetPassword(test_casket.pass);
    TEST_ASSERT(res.OK(), "set pass error\n");
    cskt_enc->SetPass(pass_enc);

    std::list<CSetCombPtr> encoding_setcombs;
    for (auto &combine : test_casket.combines)
    {
        auto encoding_setcomb = CSetCombPtr(new CSetComb());
        encoding_setcomb->SetDescription("foo");

        auto encoding_setgen = CSetgenSinglePtr(new CSetgenSingle());
        encoding_setgen->SetDescription("foo");
        encoding_setgen->SetVariants(combine.setgen_variants);
        encoding_setcomb->SetSetgen(encoding_setgen);

        switch (combine.type)
        {
        case enCombineType::ctNone:
        {
            break;
        }
        case enCombineType::ctPermutation:
        {
            auto encoding_combine = CCombinePermutationPtr(new CCombinePermutation());
            Result_t r;
            r = encoding_combine->SetParameters(combine.setgen_variants.size());
            TEST_ASSERT(r.OK(), "set casket parameters error\n");
            r = encoding_combine->SetPermutation(combine.values);
            TEST_ASSERT(r.OK(), "set casket permutation error\n");
            encoding_setcomb->SetCombine(encoding_combine);
            TEST_ASSERT(encoding_setcomb->Valid(enPurpose::pEncode).OK(), "casket setcomb valid error\n");

            encoding_setcombs.push_back(encoding_setcomb);
            break;
        }
        case enCombineType::ctCombination:
        {
            auto encoding_combine = CCombineCombinationPtr(new CCombineCombination());
            Result_t r;
            r = encoding_combine->SetParameters(combine.setgen_variants.size());
            TEST_ASSERT(r.OK(), "set casket parameters error\n");
            r = encoding_combine->SetCombination(combine.values);
            TEST_ASSERT(r.OK(), "set casket permutation error\n");
            encoding_setcomb->SetCombine(encoding_combine);
            TEST_ASSERT(encoding_setcomb->Valid(enPurpose::pEncode).OK(), "casket setcomb valid error\n");

            encoding_setcombs.push_back(encoding_setcomb);
            break;
        }
        }

    }

    cskt_enc->SetSetcombs(encoding_setcombs);

    TEST_ASSERT(cskt_enc->Valid(enPurpose::pEncode).OK(), "casket valid error\n");

    res = cskt_enc->KeyholeFromPass();
    TEST_ASSERT(res.OK(), "make casket keyhole error\n");

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    cskt_enc->toJSON().Accept(writer);
    encoded_json = buffer.GetString();
    return true;
}

bool CTestCasket::TestDecodeCasket(const sTestCasket &test_casket, const std::string &encoded_json)
{
    bool res = false;

    auto cskt_dec = CCasketPtr(new CCasket());
    rapidjson::Document doc;
    doc.Parse(encoded_json);
    res = cskt_dec->fromJSON(doc);
    TEST_ASSERT(res, "casket json parsing error\n");

    auto decoding_setcombs = cskt_dec->GetSetcombs();
    TEST_ASSERT(decoding_setcombs.size() == test_casket.combines.size(), "casket setcombs size error\n");

    for (size_t i = 0; i < test_casket.combines.size(); ++i)
    {
        auto decoding_setcomb = decoding_setcombs.front();
        decoding_setcombs.pop_front();
        auto decoding_combine = decoding_setcomb->GetCombine();

        auto test_casket_combine = test_casket.combines[i];
        TEST_ASSERT(decoding_combine->GetType() == test_casket_combine.type, "casket combine type error\n");

        switch (decoding_combine->GetType())
        {
        case enCombineType::ctNone:
        {
            TEST_ASSERT(false, "combine type none\n");
            break;
        }
        case enCombineType::ctPermutation:
        {
            CCombinePermutation* decoding_combine_permutation = dynamic_cast<CCombinePermutation*>(decoding_combine.get());
            auto r = decoding_combine_permutation->SetPermutation(test_casket_combine.values);
            TEST_ASSERT(r.OK(), "casket set permutation error\n");
            break;
        }
        case enCombineType::ctCombination:
        {
            CCombineCombination* decoding_combine_permutation = dynamic_cast<CCombineCombination*>(decoding_combine.get());
            auto values = test_casket_combine.values;
            ShufflePermutation(values);
            auto r = decoding_combine_permutation->SetCombination(values);
            TEST_ASSERT(r.OK(), "casket set combination error\n");
            break;
        }
        }

    }

    auto r = cskt_dec->PassFromKeyhole();
    TEST_ASSERT(r.OK(), "make casket password error\n");

    auto decoded_pass = cskt_dec->GetPass()->GetPassword();
    TEST_ASSERT(decoded_pass == test_casket.pass, "password match error\n");

    return true;
}
