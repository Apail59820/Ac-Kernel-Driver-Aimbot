#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <tgmath.h>

#include "kernelinterface.h"
#include "offsets.h"

template <typename T>
struct Vector3 {
	T x, y, z;
};

struct Rotation {
	float yaw, pitch, roll;
};

class Player
{
public : 

	Player(KernelInterface& _Driver, ULONG _ProcessId) : m_Driver(_Driver), m_ProcessId(_ProcessId) { this->init(); }
	Player(::std::ptrdiff_t _Addr, KernelInterface& _Driver, ULONG _ProcessId) : m_Driver(_Driver), m_ProcessId(_ProcessId), m_Address(_Addr) { this->init(); }

	~Player();

	void init();

	void aimAt(const float _yaw, const float _pitch);

	void update();

	inline int getHealth() { return m_Driver.ReadVirtualMemory<int>(m_ProcessId, m_Address + 0xF8, sizeof(int)); }

	inline void set_Address(const ::std::ptrdiff_t _Addr) { this->m_Address = _Addr; }
	inline ::std::ptrdiff_t get_Address(void) const { return this->m_Address; }

	inline auto get_Position(void) const { return this->m_Position; }

	inline float get_Yaw(void) { return m_Driver.ReadVirtualMemory<float>(m_ProcessId, m_Address + PlayerYawOffset, sizeof(float)); }
	

private :

	KernelInterface& m_Driver;
	ULONG m_ProcessId;

	::std::ptrdiff_t m_Address;

	Vector3<float> m_Position;
	Rotation m_Rotation;
};



