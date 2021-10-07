#include "Player.h"

void Player::init()
{
	this->update();
}

void Player::update()
{
	m_Position.x = m_Driver.ReadVirtualMemory<float>(m_ProcessId, m_Address + PlayerXPosOffset, sizeof(float));
	m_Position.y = m_Driver.ReadVirtualMemory<float>(m_ProcessId, m_Address + PlayerYPosOffset, sizeof(float));
	m_Position.z = m_Driver.ReadVirtualMemory<float>(m_ProcessId, m_Address + PlayerZPosOffset, sizeof(float));
}

Player::~Player()
{
	// std::cout << "Player instance destroyed." << std::endl;
}

void Player::aimAt(const float _yaw, const float _pitch)
{
	m_Driver.WriteVirtualMemory<float>(m_ProcessId, m_Address + PlayerYawOffset, _yaw ,sizeof(float));
	m_Driver.WriteVirtualMemory<float>(m_ProcessId, m_Address + PlayerPitchOffset, _pitch, sizeof(float));
}