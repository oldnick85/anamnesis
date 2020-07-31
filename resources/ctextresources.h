#ifndef CTEXTRESOURCES_H
#define CTEXTRESOURCES_H

#include <string>
#include <array>
#include "../common/version.h"

namespace TRM_TXT_RES {

enum enLanguage : uint
{
	lEN			= 0,
	lRU			= 1,

	sLastLanguage,
};

enum enStringId : uint
{
    siNone		= 0,
    siHorisontalSeparator,
    siOK,
    siCancel,
    siExit,
    siAbort,
    siError,
    siDone,
    siNotSet,
    siOtherVariant,
    siQueryNextStep,
    siVariantsCount,
    siNoDescription,
    siBit,
    siInputVectorInt,
    siBank,
    siTotal,
    siSave,
    siEnthropy,
    siOpenFile,
    siNext,
    siNextQuestion,
    siAnswerAllQuestions,
    siFileNotOpened,
    siQuestionsCount,

    siResultOK,
    siResultError,
    siResultIncorrectIndex,
    siResultVarInList,
    siResultComb_N_less_K,
    siResultCombSize_neq_K,
    siResultCombSize_gr_N,
    siResultCombVal_geq_N,
    siResultCombValDuplicate,
    siResultSymbDuplicate,
    siResultPassWrongSymbol,
    siResultPerm_N_0,
    siResultComb_N_0,
    siResultPassNoSymbSet,
    siResultPassNoPassword,
    siResultNoSetcomb,
    siResultNoDescription,
    siResultNoPassword,
    siResultNoSetgen,
    siResultNoCombine,
    siResultNoVariants,
    siResultNoVariantsInBank,
    siResultNoPermutation,
    siResultNoCombination,
    siResultEmptyString,
    siResultNoDelimeter,
    siResultNoValueInToken,
    siResultNotUniqueVariants,
    siResultNotUniqueVariantsInBank,

    siSetgenSingle,
    siSetgenDouble,
    siCombinePermut,
    siCombineCombination,

    siMainDescription,
    siMainQuestion,
    siMainEncodePass,
    siMainRestorePass,

    siEncodeStatus,
    siEncodeStatusQuestions,
    siEncodeStatusPass,

    siEncodeQuery,
    siEncodeQueryAnew,
    siEncodeQueryAdd,
    siEncodeQueryShowQstns,
    siEncodeQuerySetPass,
    siEncodeQuerySave,
    siEncodeAddError,
    siEncodeErrorNoPass,
    siEncodeAddQuestDesc,

    siCombineChoose,

    siSetgenChoose,
    siSetgenShow,
    siSetgenSingleQuery,
    siSetgenSingleQueryAnew,
    siSetgenSingleQueryAdd,
    siSetgenSingleQueryDel,
    siSetgenSingleSampleHint,

    siSetgenDoubleQuery,
    siSetgenDoubleQueryAnew,
    siSetgenDoubleQueryAddFirst,
    siSetgenDoubleQueryAddSecond,
    siSetgenDoubleQueryDelFirst,
    siSetgenDoubleQueryDelSecond,
    siSetgenDoubleSampleHint,

    siSetgenQuerySetDesc,
    siSetgenAddError,
    siSetgenNotValid,

    siPassCurSymbSet,
    siPassSymbQuery,
    siPassSymbDigits,
    siPassSymbLower,
    siPassSymbUpper,
    siPassSymbBraces,
    siPassPassQuery,
    siPassPassError,
    siPassResult,

    siCombinePermutSetPerm,
    siCombinePermutSetPermErr,
    siCombinePermutGetPerm,
    siCombinePermutHint,

    siCombineCombinationGetComb,

    siSaveFileEnterName,
    siOpenFileEnterName,
    siOpenFileNoName,
    siOpenFileNoFile,
    siOpenFileContentErr,
    siOpenFileJsonErr,

    siLastStringId,
};

} // namespace TRM_TXT_RES

/*!
 * \brief CTextResources - строки для выводы в терминал
 */
class CTextResources
{
public:
	CTextResources();

    /*!
     * \brief SetLanguage - установить текущий язык вывода
     * \param[in] lang - язык вывода
     */
	void SetLanguage(const TRM_TXT_RES::enLanguage lang) {m_lang = lang;}
    /*!
     * \brief String - получить строку по идентификатору
     * \param[in] str_id - идентификатор строки
     * \return строка
     */
    std::string operator()(const TRM_TXT_RES::enStringId str_id) const;
    /*!
     * \brief PrintProgramName - получить имя программы
     * \return имя программы
     */
    std::string PrintProgramName() const;
private:
	void Init();

    TRM_TXT_RES::enLanguage		m_lang;

    using Strings_t = std::array<std::string, TRM_TXT_RES::siLastStringId>;
	using Languages_t = std::array<Strings_t, TRM_TXT_RES::sLastLanguage>;
	Languages_t					m_strings;
};

static CTextResources text;

#endif // CTEXTRESOURCES_H
