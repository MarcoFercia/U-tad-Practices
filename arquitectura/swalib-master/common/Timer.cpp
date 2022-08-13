#include"Timer.h"



m_Timer Timer;


m_Timer::m_Timer()
{
	QueryPerformanceFrequency(&this->Frequency);
	QueryPerformanceCounter(&this->Previoustime);
}

void m_Timer::initSlots()
{
	QueryPerformanceCounter(&Currenttime);

	this->elapsed = (float(this->Currenttime.QuadPart - this->Previoustime.QuadPart) / float(this->Frequency.QuadPart));
	this->Previoustime = this->Currenttime;

	this->fps = 1.f / this->elapsed;
	this->totaltime += this->elapsed;

	this->elapsed += this->tiemposobranteelapsed;
	this->tiemposobranteelapsed = 0;

	if (this->elapsed >= 1.f / 15.f)
	{
		this->elapsed = 1.f / 15.f;
	}
}

bool m_Timer::ProcessSlot()
{
	bool temp = false;
	if (this->elapsed >= this->fixedtick)
	{
		this->timelogic += this->fixedtick;
		this->elapsed = this->elapsed - this->fixedtick;
		temp = true;
	}
	this->tiemposobranteelapsed = this->elapsed;



	return temp;
}
