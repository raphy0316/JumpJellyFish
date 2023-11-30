#pragma once
#include "Define.h"

class Timer
{
public:
	Timer();
	~Timer();

	void Update(float dt);

	void Start();
	void Stop();
	void Reset(float duration = 0, int cout = 0, bool auto_start = true);

	function<void()> OnTick;
	function<void()> OnFinished;

	bool GetIsActive() { return active_; }

private:

	pair<float, float> duration_;
	pair<int, int> count_;

	bool active_;
};

