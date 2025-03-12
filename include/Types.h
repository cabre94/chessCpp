#pragma once

#include <cstdint>
#include <string>

namespace chess {

// using Position = std::string;

// using PlayerID = uint32_t;

// constexpr PlayerID WHITE = 0;
// constexpr PlayerID BLACK = 1;

// Enum class para restringir PlayerID
// enum class PlayerID : uint8_t { WHITE = 0, BLACK = 1 };

// using PlayerID = uint32_t;

// constexpr PlayerID WHITE = 0;
// constexpr PlayerID BLACK = 1;

// Enum para PlayerID
enum PlayerID : uint32_t { WHITE = 0, BLACK = 1, MAX_NUM_PLAYERS };

} // namespace chess