#pragma once

class Timer
{
public:
	void Start();
	int Read();
	int Stop();

private:
	void UpdateDeltaTime();

protected:
	int GetCurrentTime();

	int StartTime = 0;
	int DeltaTime = 0;
	bool Stopped = false;
};

