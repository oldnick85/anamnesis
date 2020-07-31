#ifndef CTRMDECSETGEN_H
#define CTRMDECSETGEN_H

#include "common.h"
#include "ctrmio.h"
#include "ctrmdecsetgensingle.h"
#include "ctrmdecsetgendouble.h"

/*!
 * \brief CTrmEncSetgen - терминал установки пароля для кодирования
 */
class CTrmDecSetgen
        : public ITrmDecSetgen
        , public IStateMashine
        , private CTrmIO
{
public:
    /*!
     * \brief CTrmDecSetgen - конструктор терминала обработки генератора для декодирования
     * \param[in] setgen - генератор
     */
    CTrmDecSetgen(ISetgenPtr setgen);
    // IStateMashine
    virtual void Begin() override final;
    // ITrmDecSetgen
    virtual ISetgenPtr GetSetgen() override final;
    virtual Result_t Valid() const override final;
    // ITrmSetgen
    virtual Result_t ParseSample(const std::string &str, uint64 &value) const override;
    virtual std::string SampleHint() const override;
private:
    ITrmDecSetgenPtr    m_trm_setgen = nullptr;
    ISetgenPtr          m_setgen = nullptr;
};

using CTrmDecSetgenPtr = std::shared_ptr<CTrmDecSetgen>;

#endif // CTRMDECSETGEN_H
