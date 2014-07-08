#ifndef TimerH
#define TimerH

class Timer {
private:
	float time;
public:
	Timer();
	void Update(float dt);
	void Restart();
	float Get();
};

#endif