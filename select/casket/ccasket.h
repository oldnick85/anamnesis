#ifndef CCASKET_H
#define CCASKET_H

#include "result/result.h"
#include "pass/cpass.h"
#include "variant/csetcomb.h"

/*!
 * \brief CCasket - класс, хранящий полный набор для кодирования и декодирования пароля
 */
class CCasket
        : public ISerializible
{
public:
    CCasket() = default;

    /*!
     * \brief SetPass - установить пароль
     * \param[in] pass - пароль
     */
    void SetPass(const CPassPtr pass);
    /*!
     * \brief GetPass - получить пароль
     * \return класс с паролем
     */
    CPassPtr GetPass();
    /*!
     * \brief SetSetcombs - задать список связок генераторов и комбинаторов
     * \param[in] setcombs
     */
    void SetSetcombs(const std::list<CSetCombPtr> &setcombs);
    /*!
     * \brief GetSetcombs - получить список связок генераторов и комбинаторов
     * \return список связок генераторов и комбинаторов
     */
    std::list<CSetCombPtr> &GetSetcombs();

    virtual rapidjson::Document toJSON() const override final;
    virtual bool fromJSON(const rapidjson::Value& doc) override final;
    /*!
     * \brief Valid - предикат валидности
     * \return валидность
     */
    Result_t Valid(const enPurpose purpose) const;
    /*!
     * \brief VariantsCount - общее количество комбинаций
     * \return общее количество комбинаций
     */
    CNumber VariantsCount() const;
    /*!
     * \brief KeyholeFromPass - сформировать замочную скважину для раскодирования пароля
     * \return успех формирования
     */
    Result_t KeyholeFromPass();
    /*!
     * \brief PassFromKeyhole - декодировать пароль по замочной скважине
     * \return успех декодирования
     */
    Result_t PassFromKeyhole();
    /*!
     * \brief SaveFileJSON - сохранить в файл формата JSON
     * \param[in] fname - полное имя файла
     * \return результат сохранения
     */
    Result_t SaveFileJSON(const std::string &fname);
    /*!
     * \brief LoadFileJSON - загрузить из файла формата JSON
     * \param[in] fname - полное имя файла
     * \return результат загрузки
     */
    Result_t LoadFileJSON(const std::string &fname);
private:
    rapidjson::Document toJSON_pass() const;
    rapidjson::Document toJSON_setcombs() const;
    bool fromJSON_setcombs(const rapidjson::Value& doc);

    CNumber GenerateKey(CNumber quest_value);
    CNumber QuestionsValue();

    CPassPtr                m_pass;
    std::list<CSetCombPtr>  m_setcombs;

    CNumber                 m_keyhole;
};

using CCasketPtr = std::shared_ptr<CCasket>;

#endif // CCASKET_H
