#include "register.hpp"

namespace
{
    std::uint16_t JoinParts(std::byte high, std::byte low)
    {
        std::uint16_t joined {0};
        joined |= std::to_integer<std::uint16_t>(high);
        joined <<= 8;
        joined |= std::to_integer<std::uint16_t>(low);
        return joined;
    }
}

Register::Register()
    :
    m_value(std::byte{0})
{

}

CycledValue<std::byte> Register::GetValue() const
{
    return {.value = this->m_value, .cycles = 1};
}

CycledValue<void> Register::SetValue(std::byte value)
{
    this->m_value = value;
    return {.cycles = 1};
}

MemoryRefRegister::MemoryRefRegister(Register::ConstPointer highPart, Register::ConstPointer lowPart)
    :
    m_highPart(highPart),
    m_lowPart(lowPart)
{

}

CycledValue<std::byte> MemoryRefRegister::GetValue() const
{
    const auto address = GetAddress();
    //read value from memory at `address`
    return {.value = std::byte{0}, .cycles = address.cycles + 1};
}

CycledValue<void> MemoryRefRegister::SetValue(std::byte value)
{
    const auto address = GetAddress();
    //write value to `address`
    
    return {.cycles = address.cycles + 1};
}

CycledValue<std::uint16_t> MemoryRefRegister::GetAddress() const
{
    const auto high = this->m_highPart->GetValue(), low = this->m_lowPart->GetValue();
    const auto cyclesTaken = high.cycles + low.cycles;
    return {.value = JoinParts(high.value, low.value), .cycles = cyclesTaken};
}