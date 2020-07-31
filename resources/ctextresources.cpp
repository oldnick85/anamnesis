#include "ctextresources.h"

using namespace TRM_TXT_RES;

CTextResources::CTextResources()
{
#if defined ANAMNESIS_DEFAULT_LANGUAGE_RU
    m_lang = TRM_TXT_RES::lRU;
#elif defined ANAMNESIS_DEFAULT_LANGUAGE_EN
    m_lang = TRM_TXT_RES::lEN;
#else
    m_lang = TRM_TXT_RES::lRU;
#endif
    Init();
}

std::string CTextResources::operator()(const enStringId str_id) const
{
    std::string s;
    const Strings_t &str = m_strings[m_lang];
    if (not str[str_id].empty())
        s = str[str_id];
    else
        s = m_strings[TRM_TXT_RES::lEN][str_id];
    return s;
}

void CTextResources::Init()
{
    {
        Strings_t &strings_en = m_strings[lEN];
        strings_en[siHorisontalSeparator]               = "================================================================";
        strings_en[siOK]                                = "OK";
        strings_en[siCancel]                        	= "Cancel";
        strings_en[siExit]                              = "Exit";
        strings_en[siAbort]                             = "Abort";
        strings_en[siError]                             = "Error";
        strings_en[siDone]                              = "Done";
        strings_en[siNotSet]                            = "not set";
        strings_en[siOtherVariant]                      = "Other variant";
        strings_en[siQueryNextStep]                     = "Choose next action";
        strings_en[siVariantsCount]                     = "Variants count";
        strings_en[siNoDescription]                     = "No description";
        strings_en[siBit]                               = "bit";
        strings_en[siInputVectorInt]                    = "Enter one or more numbers separated by spaces";
        strings_en[siBank]                              = "bank";
        strings_en[siTotal]                             = "total";
        strings_en[siSave]                              = "Save";
        strings_en[siEnthropy]                          = "Enthropy";
        strings_en[siOpenFile]                          = "Open file";
        strings_en[siNext]                              = "Next";
        strings_en[siNextQuestion]                      = "Next question";
        strings_en[siAnswerAllQuestions]                = "Answer all questions";
        strings_en[siFileNotOpened]                     = "File is not opened";
        strings_en[siQuestionsCount]                    = "Questions count";

        strings_en[siResultOK]                          = "OK";
        strings_en[siResultError]                       = "Unknown error";
        strings_en[siResultIncorrectIndex]              = "Incorrect index";
        strings_en[siResultVarInList]                   = "Variant in list";
        strings_en[siResultComb_N_less_K]               = "Set size is too big";
        strings_en[siResultCombSize_neq_K]              = "Combination set size mismatch";
        strings_en[siResultCombSize_gr_N]               = "Combination set is too big";
        strings_en[siResultCombVal_geq_N]               = "Incorrect value in set";
        strings_en[siResultCombValDuplicate]            = "Duplicated value in set";
        strings_en[siResultSymbDuplicate]               = "Allowed in password symbols duplicate";
        strings_en[siResultPassWrongSymbol]             = "Pass has incorrect symbol";
        strings_en[siResultPerm_N_0]                    = "Zero permutation size";
        strings_en[siResultComb_N_0]                    = "Zero combination size";
        strings_en[siResultPassNoSymbSet]               = "Symbols set for password is not determined";
        strings_en[siResultPassNoPassword]              = "Password is not set";
        strings_en[siResultNoSetcomb]                   = "No setcomb";
        strings_en[siResultNoDescription]               = "No description";
        strings_en[siResultNoPassword]                  = "No password";
        strings_en[siResultNoSetgen]                    = "No set generator";
        strings_en[siResultNoCombine]                   = "No combinator";
        strings_en[siResultNoVariants]                  = "No variants";
        strings_en[siResultNoVariantsInBank]            = "No variants in bank";
        strings_en[siResultNoPermutation]               = "No permutation";
        strings_en[siResultNoCombination]               = "No combination";
        strings_en[siResultEmptyString]                 = "Empty string";
        strings_en[siResultNoDelimeter]                 = "No delimeter";
        strings_en[siResultNoValueInToken]              = "No value in token";
        strings_en[siResultNotUniqueVariants]           = "Duplicate variants";
        strings_en[siResultNotUniqueVariantsInBank]     = "Duplicate variants in bank";

        strings_en[siSetgenSingle]                      = "Single";
        strings_en[siSetgenDouble]                      = "Double";
        strings_en[siCombinePermut]                     = "Permutation";
        strings_en[siCombineCombination]                = "Combination";

        strings_en[siMainDescription]                = "This is program for password encryption.\n";
        strings_en[siMainQuestion]                   = "What do you want";
        strings_en[siMainEncodePass]                 = "Encode password";
        strings_en[siMainRestorePass]                = "Restore encoded password";

        strings_en[siEncodeStatus]                   = "Encoding status";
        strings_en[siEncodeStatusQuestions]          = "Questions";
        strings_en[siEncodeStatusPass]               = "Password";

        strings_en[siEncodeQuery]                    = "Password encode";
        strings_en[siEncodeQueryAnew]                = "Anew password encode";
        strings_en[siEncodeQueryAdd]                 = "Add question";
        strings_en[siEncodeQueryShowQstns]           = "Show all added questions";
        strings_en[siEncodeQuerySetPass]             = "Set password";
        strings_en[siEncodeQuerySave]                = "Save encoded password";
        strings_en[siEncodeAddError]                 = "Question is not added";
        strings_en[siEncodeErrorNoPass]              = "No password is set";
        strings_en[siEncodeAddQuestDesc]             = "Set question description";

        strings_en[siCombineChoose]                  = "Choose combinator";

        strings_en[siSetgenChoose]                   = "Choose variants set";
        strings_en[siSetgenShow]                     = "Show variants";
        strings_en[siSetgenSingleQuery]              = "Set single variants generator";
        strings_en[siSetgenSingleQueryAnew]          = "Anew variants";
        strings_en[siSetgenSingleQueryAdd]           = "Add variant";
        strings_en[siSetgenSingleQueryDel]           = "Delete variant";
        strings_en[siSetgenSingleSampleHint]         = "one integer";

        strings_en[siSetgenDoubleQuery]              = "Set single variants generator";
        strings_en[siSetgenDoubleQueryAnew]          = "Anew variants";
        strings_en[siSetgenDoubleQueryAddFirst]      = "Add first variant";
        strings_en[siSetgenDoubleQueryAddSecond]     = "Add second variant";
        strings_en[siSetgenDoubleQueryDelFirst]      = "Delete first variant";
        strings_en[siSetgenDoubleQueryDelSecond]     = "Delete second variant";
        strings_en[siSetgenDoubleSampleHint]         = "pair of integers";

        strings_en[siSetgenQuerySetDesc]             = "Set description";
        strings_en[siSetgenAddError]                 = "Incorrect variant";
        strings_en[siSetgenNotValid]                 = "Set generator is not valid";

        strings_en[siCombinePermutSetPerm]           = "Set permutation";
        strings_en[siCombinePermutSetPermErr]        = "Incorrect permutation";
        strings_en[siCombinePermutGetPerm]           = "Input permutation";
        strings_en[siCombinePermutHint]              = "separated by spaces values, each of which represents";

        strings_en[siCombineCombinationGetComb]      = "Input combination";

        strings_en[siPassCurSymbSet]                 = "Current symbols set";
        strings_en[siPassSymbQuery]                  = "Select allowed symbols for password";
        strings_en[siPassSymbDigits]                 = "Digits";
        strings_en[siPassSymbLower]                  = "Lower case";
        strings_en[siPassSymbUpper]                  = "Upper case";
        strings_en[siPassSymbBraces]                 = "Braces";
        strings_en[siPassPassQuery]                  = "Set password";
        strings_en[siPassPassError]                  = "Password error";
        strings_en[siPassResult]                     = "Decoded password";

        strings_en[siSaveFileEnterName]              = "Enter file name to save";
        strings_en[siOpenFileEnterName]              = "Enter file name to open";
        strings_en[siOpenFileNoName]                 = "No file name";
        strings_en[siOpenFileNoFile]                 = "No file";
        strings_en[siOpenFileContentErr]             = "Incorrect file format";
        strings_en[siOpenFileJsonErr]                = "Incorrect file content";
    }
    {
        Strings_t &strings_ru = m_strings[lRU];
        strings_ru[siHorisontalSeparator]               = "================================================================";
        strings_ru[siOK]                                = "OK";
        strings_ru[siCancel]                            = "Отмена";
        strings_ru[siExit]                              = "Выход";
        strings_ru[siAbort]                             = "Прервать";
        strings_ru[siError]                             = "Ошибка";
        strings_ru[siDone]                              = "Готово";
        strings_ru[siNotSet]                            = "не установлен";
        strings_ru[siOtherVariant]                      = "Другой вариант";
        strings_ru[siQueryNextStep]                     = "Выберите следующее действие";
        strings_ru[siVariantsCount]                     = "Количество вариантов";
        strings_ru[siNoDescription]                     = "Нет описания";
        strings_ru[siBit]                               = "бит";
        strings_ru[siInputVectorInt]                    = "Введите одно или несколько чисел разделённых пробелами";
        strings_ru[siBank]                              = "банк";
        strings_ru[siTotal]                             = "всего";
        strings_ru[siSave]                              = "Сохранить";
        strings_ru[siEnthropy]                          = "Энтропия";
        strings_ru[siOpenFile]                          = "Открыть файл";
        strings_ru[siNext]                              = "Дальше";
        strings_ru[siNextQuestion]                      = "Следующий вопрос";
        strings_ru[siAnswerAllQuestions]                = "Необходимо ответить на все вопросы";
        strings_ru[siFileNotOpened]                     = "Файл не открыт";
        strings_ru[siQuestionsCount]                    = "Количество вопросов";

        strings_ru[siResultOK]                          = "OK";
        strings_ru[siResultError]                       = "Неизвестная ошибка";
        strings_ru[siResultIncorrectIndex]              = "Неверный индекс";
        strings_ru[siResultVarInList]                   = "Вариант уже в списке";
        strings_ru[siResultComb_N_less_K]               = "Размер набора слишком большой";
        strings_ru[siResultCombSize_neq_K]              = "Неподходящий размер набора";
        strings_ru[siResultCombSize_gr_N]               = "Набор слишком большой";
        strings_ru[siResultCombVal_geq_N]               = "Неверное значение в наборе";
        strings_ru[siResultCombValDuplicate]            = "Повторяющееся значение в наборе";
        strings_ru[siResultSymbDuplicate]               = "Разрешенные в пароле символы имеют повторы";
        strings_ru[siResultPassWrongSymbol]             = "Пароль содержит неверный символ";
        strings_ru[siResultPerm_N_0]                    = "Нулевой размер перестановки";
        strings_ru[siResultComb_N_0]                    = "Нулевой размер комбинации";
        strings_ru[siResultPassNoSymbSet]               = "Набор символов для пароля не задан";
        strings_ru[siResultPassNoPassword]              = "Пароль не задан";
        strings_ru[siResultNoSetcomb]                   = "Вопрос не задан";
        strings_ru[siResultNoDescription]               = "Нет описания";
        strings_ru[siResultNoPassword]                  = "Нет пароля";
        strings_ru[siResultNoSetgen]                    = "Нет генератора множества";
        strings_ru[siResultNoCombine]                   = "Нет комбинатора";
        strings_ru[siResultNoVariants]                  = "Нет вариантов";
        strings_ru[siResultNoVariantsInBank]            = "Нет вариантов в банке";
        strings_ru[siResultNoPermutation]               = "Нет перестановки";
        strings_ru[siResultNoCombination]               = "Нет комбинации";
        strings_ru[siResultEmptyString]                 = "Пустая строка";
        strings_ru[siResultNoDelimeter]                 = "Не найден разделитель";
        strings_ru[siResultNoValueInToken]              = "Нет значения в токене";
        strings_ru[siResultNotUniqueVariants]           = "Повторяющиеся варианты";
        strings_ru[siResultNotUniqueVariantsInBank]     = "Повторяющиеся варианты в банке";

        strings_ru[siSetgenSingle]                      = "Одиночный";
        strings_ru[siSetgenDouble]                      = "Двойной";
        strings_ru[siCombinePermut]                     = "Перестановка";
        strings_ru[siCombineCombination]                = "Сочетание";

        strings_ru[siMainDescription]                = "Это программа для кодирования пароля.\n";
        strings_ru[siMainQuestion]                   = "Что вы хотите";
        strings_ru[siMainEncodePass]                 = "Закодировать пароль";
        strings_ru[siMainRestorePass]                = "Декодировать пароль";

        strings_ru[siEncodeStatus]                   = "Статус кодирования";
        strings_ru[siEncodeStatusQuestions]          = "Вопросы";
        strings_ru[siEncodeStatusPass]               = "Пароль";

        strings_ru[siEncodeQuery]                    = "Кодирование пароля";
        strings_ru[siEncodeQueryAnew]                = "Кодировать заново";
        strings_ru[siEncodeQueryAdd]                 = "Добавить вопрос";
        strings_ru[siEncodeQueryShowQstns]           = "Показать все добавленные вопросы";
        strings_ru[siEncodeQuerySetPass]             = "Задать пароль";
        strings_ru[siEncodeQuerySave]                = "Сохранить закодированный пароль";
        strings_ru[siEncodeAddError]                 = "Вопрос не был добавлен";
        strings_ru[siEncodeErrorNoPass]              = "Пароль не задан";
        strings_ru[siEncodeAddQuestDesc]             = "Введите описание вопроса";

        strings_ru[siCombineChoose]                  = "Выберите комбинатор";

        strings_ru[siSetgenChoose]                   = "Выберите генератор вариантов";
        strings_ru[siSetgenShow]                     = "Показать варианты";
        strings_ru[siSetgenSingleQuery]              = "Задать одиночный генератор вариантов";
        strings_ru[siSetgenSingleQueryAnew]          = "Задать варианты заново";
        strings_ru[siSetgenSingleQueryAdd]           = "Добавить вариант";
        strings_ru[siSetgenSingleQueryDel]           = "Удалить вариант";
        strings_ru[siSetgenSingleSampleHint]         = "одно целое число";

        strings_ru[siSetgenDoubleQuery]              = "Задать двойной генератор вариантов";
        strings_ru[siSetgenDoubleQueryAnew]          = "Задать варианты заново";
        strings_ru[siSetgenDoubleQueryAddFirst]      = "Добавить первый вариант";
        strings_ru[siSetgenDoubleQueryAddSecond]     = "Добавить второй вариант";
        strings_ru[siSetgenDoubleQueryDelFirst]      = "Удалить первый вариант";
        strings_ru[siSetgenDoubleQueryDelSecond]     = "Удалить второй вариант";
        strings_ru[siSetgenDoubleSampleHint]         = "Пара целых чисел";

        strings_ru[siSetgenQuerySetDesc]             = "Задать описание";
        strings_ru[siSetgenAddError]                 = "Некорректный вариант";
        strings_ru[siSetgenNotValid]                 = "Генератор не определён";

        strings_ru[siCombinePermutSetPerm]           = "Задать перестановку";
        strings_ru[siCombinePermutSetPermErr]        = "Неверная перестановка";
        strings_ru[siCombinePermutGetPerm]           = "Введите перестановку";
        strings_ru[siCombinePermutHint]              = "разделённые пробелами значения, каждое из которых есть";

        strings_ru[siCombineCombinationGetComb]      = "Введите сочетание";

        strings_ru[siPassCurSymbSet]                 = "Текущий набор символов";
        strings_ru[siPassSymbQuery]                  = "Выберите разрешенные символы для пароля";
        strings_ru[siPassSymbDigits]                 = "Цифры";
        strings_ru[siPassSymbLower]                  = "Строчные латинские буквы";
        strings_ru[siPassSymbUpper]                  = "Прописные латинские буквы";
        strings_ru[siPassSymbBraces]                 = "Скобки";
        strings_ru[siPassPassQuery]                  = "Введите пароль";
        strings_ru[siPassPassError]                  = "Ошибка пароля";
        strings_ru[siPassResult]                     = "Декодирован пароль";

        strings_ru[siSaveFileEnterName]              = "Введите имя файла для сохранения";
        strings_ru[siOpenFileEnterName]              = "Введите имя файла для открытия";
        strings_ru[siOpenFileNoName]                 = "Имя файла не задано";
        strings_ru[siOpenFileNoFile]                 = "Файл не найден";
        strings_ru[siOpenFileContentErr]             = "Неверное содержимое файла";
        strings_ru[siOpenFileJsonErr]                = "Некорректные данные";
    }
}

std::string CTextResources::PrintProgramName() const
{
    char s[256];
    snprintf(s, sizeof(s), "ANAMNESIS %s", CVersion().Print().c_str());
    return s;
}
