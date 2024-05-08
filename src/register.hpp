#pragma once 

#include <cstddef>
#include <cstdint>
#include "cycledValue.hpp"

/**
 * @brief Default CPU register
 * 
 */
class Register
{
    std::byte m_value;
public:
    using ConstPointer = Register* const;
    Register();
    virtual ~Register() = default;

    virtual CycledValue<std::byte> GetValue() const;
    virtual CycledValue<void> SetValue(std::byte value);
};

/**
 * @brief Virtual register that references a memory cell via two other registers serving as address
 * 
 */
class MemoryRefRegister : public Register
{
    Register::ConstPointer m_highPart, m_lowPart;

    CycledValue<std::uint16_t> GetAddress() const;

public:
    MemoryRefRegister(Register::ConstPointer highPart, Register::ConstPointer lowPart);
    CycledValue<std::byte> GetValue() const override;
    CycledValue<void> SetValue(std::byte value) override;
};