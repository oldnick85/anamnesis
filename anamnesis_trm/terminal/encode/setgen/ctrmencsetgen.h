#ifndef CTRMENCSETGEN_H
#define CTRMENCSETGEN_H

#include "common.h"
#include "ctrmio.h"

/*!
 * \brief CTrmEncSetgen - терминал установки пароля для кодирования
 */
class CTrmEncSetgen
        : public ITrmEncSetgen
        , public IStateMashine
        , private CTrmIO
{
public:
    CTrmEncSetgen() = default;
    // IStateMashine
    virtual void Begin() override final;
    // ITrmEncSetgen
    virtual ISetgenPtr GetSetgen() override final;
    virtual Result_t Valid() const override final;
    virtual std::string SampleHint() const override final;
    // ITrmSetgen
    virtual Result_t ParseSample(const std::string &str, uint64 &value) const override;
private:
    ITrmEncSetgenPtr    m_trm_setgen = nullptr;
};

using CTrmEncSetgenPtr = std::shared_ptr<CTrmEncSetgen>;

#endif // CTRMENCSETGEN_H
