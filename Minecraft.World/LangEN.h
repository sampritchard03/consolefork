#pragma once
#include <unordered_map>

// ITEM NAMES

constexpr int ID_PLANKS_BLACK = 5000;
constexpr int ID_PLANKS_RED = 5001;
constexpr int ID_PLANKS_GREEN = 5002;
constexpr int ID_PLANKS_BROWN = 5003;
constexpr int ID_PLANKS_BLUE = 5004;
constexpr int ID_PLANKS_PURPLE = 5005;
constexpr int ID_PLANKS_CYAN = 5006;
constexpr int ID_PLANKS_SILVER = 5007;
constexpr int ID_PLANKS_GRAY = 5008;
constexpr int ID_PLANKS_PINK = 5009;
constexpr int ID_PLANKS_LIME = 5010;
constexpr int ID_PLANKS_YELLOW = 5011;
constexpr int ID_PLANKS_LIGHTBLUE = 5012;
constexpr int ID_PLANKS_MAGENTA = 5013;
constexpr int ID_PLANKS_ORANGE = 5014;
constexpr int ID_PLANKS_WHITE = 5015;
constexpr int ID_LIZARD_TAIL = 5016;

// ITEM DESCRIPTIONS
constexpr int DESC_PLANKS = 5100;
constexpr int DESC_PLANKS_COLORED = 5101;
constexpr int DESC_LIZARD_TAIL = 5102;

// ENTITY NAMES
constexpr int ID_LIZARD = 5200;
constexpr int ID_BIRD = 5201;

//ENTITY DESCRIPTIONS
constexpr int DESC_LIZARD = 5300;
constexpr int DESC_BIRD = 5301;

extern const std::unordered_map<int, const wchar_t*> g_names;