#ifndef CTRMENCCOMBINE_H
#define CTRMENCCOMBINE_H

#include "common.h"
#include "ctrmio.h"

/*!
 * \brief CTrmEncCombine - терминал установки комбинатора
 */
class CTrmEncCombine
        : public ITrmEncCombine
        , public IStateMashine
        , private CTrmIO
{
public:
    /*!
     * \brief CTrmEncCombine - конструктор терминала установки комбинатора
     * \param setgen - генератор множества
     */
    CTrmEncCombine(ITrmEncSetgenPtr setgen);
    // IStateMashine
    virtual void Begin() override final;
    // ITrmCombine
    virtual ICombinePtr GetCombine() const override final;
    /*!
     * \brief Valid - предикат валидности
     * \return валидность
     */
    Result_t Valid() const;
private:
    ITrmEncCombinePtr   m_trm_combine = nullptr;
    ITrmEncSetgenPtr    m_setgen;
};

using CTrmEncCombinePtr = std::shared_ptr<CTrmEncCombine>;

#endif // CTRMENCCOMBINE_H
