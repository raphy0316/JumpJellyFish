#include "pch.h"
#include "Timer.h"
#include "World.h"


Timer::Timer() : active_(false)
{
	OnTick = []() {};
	OnFinished = []() {};

	World::GetInstance().GetTimers()->push_back(this);
}


Timer::~Timer()
{
	vector<Timer*> *timers = World::GetInstance().GetTimers();
	timers->erase(remove(timers->begin(), timers->end(), this), timers->end());
}

void Timer::Update(float dt)
{
	if (!active_) return;

	duration_.first += dt;
	if (duration_.first > duration_.second) {
		OnTick();
		duration_.first = 0;
		if (++count_.first >= count_.second) {
			active_ = false;
			OnFinished();
		}
	}
}

void Timer::Start()
{
	active_ = true;
}

void Timer::Stop()
{
	active_ = false;
}

void Timer::Reset(float duration, int count, bool auto_start)
{
	active_ = auto_start;
	this->duration_ = pair<float, float>(0.0f, duration);
	this->count_ = pair<int, int>(0, count);
}