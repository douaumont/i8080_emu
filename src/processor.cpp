/*
Intel 8080 CPU Emulator
Copyright (C) 2024  Artyom Makarov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <ranges>
#include <iostream>
#include <format>
#include "processor.hpp"

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

i8080cpu::i8080cpu()
    :
    m_registers()
{
    for (const auto reg : std::ranges::views::iota(std::size_t{0}, m_registers.size()))
    {
        if (reg != Registers::M)
        {
            m_registers[reg] = std::make_unique<Register>();
        }
        else
        {
            m_registers[reg] = std::make_unique<MemoryRefRegister>(m_registers[Registers::H].get(), m_registers[Registers::L].get());
        }
    }
}

void i8080cpu::TestStart()
{
    std::cout << "Write 0xAA to H\n";
    m_registers[Registers::H]->SetValue(std::byte{0xAA});
    std::cout << "Write 0x55 to L\n";
    m_registers[Registers::L]->SetValue(std::byte{0x55});
    std::cout << "Read from M\n" << std::to_integer<int>(m_registers[Registers::M]->GetValue());
}

i8080cpu::Register::Register()
    :
    m_value(std::byte{0})
{

}

std::byte i8080cpu::Register::GetValue() const
{
    return this->m_value;
}

void i8080cpu::Register::SetValue(std::byte value)
{
    this->m_value = value;
}

i8080cpu::MemoryRefRegister::MemoryRefRegister(Register::ConstPointer highPart, Register::ConstPointer lowPart)
    :
    m_highPart(highPart),
    m_lowPart(lowPart)
{

}

std::byte i8080cpu::MemoryRefRegister::GetValue() const
{
    const auto address = GetAddress();
    //read value from memory at `address`
    std::cout << std::format("Read from {}\n", address);
    return std::byte{0};
}

void i8080cpu::MemoryRefRegister::SetValue(std::byte value)
{
    const auto address = GetAddress();
    //write value to `address`
}

std::uint16_t i8080cpu::MemoryRefRegister::GetAddress() const
{
    return JoinParts(this->m_highPart->GetValue(), this->m_lowPart->GetValue());
}