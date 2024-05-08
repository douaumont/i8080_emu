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

#pragma once

#include <array>
#include <bitset>
#include <cstdint>
#include <utility>
#include <memory>
#include "register.hpp"

class i8080cpu
{
    enum Registers : std::size_t
    {   
        B = 0,
        C,
        D,
        E,
        H,
        L,
        M,
        A
    };

    std::array<std::unique_ptr<Register>, 8> m_registers;

public:
    i8080cpu();
    void TestStart();
};