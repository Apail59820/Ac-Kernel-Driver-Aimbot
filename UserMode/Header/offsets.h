#pragma once
#include <cstddef>
#include <cstdint>

constexpr ::std::ptrdiff_t BaseAddress = 0x00400000;
constexpr ::std::ptrdiff_t PlayerBase = 0x50F4F4;

constexpr ::std::ptrdiff_t PlayerXPosOffset = 0x04;
constexpr ::std::ptrdiff_t PlayerYPosOffset = 0x08;
constexpr ::std::ptrdiff_t PlayerZPosOffset = 0x0C;


constexpr ::std::ptrdiff_t PlayerYawOffset = 0x40;
constexpr ::std::ptrdiff_t PlayerPitchOffset = 0x44;
constexpr ::std::ptrdiff_t PlayerRollOffset = 0x48;

constexpr ::std::ptrdiff_t EntityBase = BaseAddress + 0x110D90;