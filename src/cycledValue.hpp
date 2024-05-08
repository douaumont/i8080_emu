#pragma once

#include <cstdint>

using Cycles = std::int32_t;

/**
 * @brief Some non-void value which took some time in cycles to be produced by some operation
 * 
 * @tparam ValueType The type of the value
 */
template<typename ValueType>
struct CycledValue
{
    ValueType value;
    Cycles cycles;
};

/**
 * @brief This struct is returned when some operation doesn't yield any value but takes some time to execute
 * 
 * @tparam  
 */
template<>
struct CycledValue<void>
{
    Cycles cycles;
};