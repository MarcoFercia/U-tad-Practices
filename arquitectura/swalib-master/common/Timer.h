#pragma once

#include "stdafx.h"






class m_Timer
{

public:

	LARGE_INTEGER Currenttime;
	LARGE_INTEGER Previoustime;
	LARGE_INTEGER Frequency;
	float elapsed = 0;


	const float fixedtick =1.f/60.f;
	float tiemposobranteelapsed = 0.f;

	float totaltime = 0.f;
	float timelogic = 0.f;
	float fps = 0.f;





	m_Timer();
	void initSlots();
	bool ProcessSlot();
};