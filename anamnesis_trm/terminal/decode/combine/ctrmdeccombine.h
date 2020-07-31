#ifndef CTRMDECCOMBINE_H
#define CTRMDECCOMBINE_H

#include "common.h"
#include "ctrmio.h"
#include "ctrmdeccombinepermut.h"
#include "ctrmdeccombinecombination.h"

/*!
 * \brief CTrmDecCombine - терминал запроса комбинатора
 */
class CTrmDecCombine
        : public ITrmDecCombine
        , public IStateMashine
        , private CTrmIO
{
public:
    /*!
     * \brief CTrmDecCombine - конструктор терминала обработки комбинатора для декодирования
     * \param[in] combine - комбинатор
     * \param[in] trm_setgen - терминал генератора вариантов
     */
    CTrmDecCombine(ICombinePtr combine, ITrmDecSetgenPtr trm_setgen);
    // IStateMashine
    virtual void Begin() override final;
    // ITrmDecCombine
    virtual ICombinePtr GetCombine() const override;
    virtual bool Valid() const override;
private:
    ITrmDecCombinePtr   m_trm_combine = nullptr;
    ICombinePtr         m_combine = nullptr;
    ITrmDecSetgenPtr    m_trm_setgen = nullptr;
};
using CTrmDecCombinePtr = std::shared_ptr<CTrmDecCombine>;

#endif // CTRMDECCOMBINE_H
