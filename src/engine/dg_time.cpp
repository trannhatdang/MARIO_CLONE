#include "engine/dg_time.h"

float deltaTime = 0.016667f;
std::chrono::time_point<std::chrono::system_clock> start_point;


void DGTime_recordDeltaTime()
{
	start_point = std::chrono::system_clock::now();
}

void DGTime_stopRecordDeltaTime()
{
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - start_point);
	deltaTime = duration.count() / 1000000000.0;
}

float DGTime_deltaTime()
{
	return deltaTime;
}

float DGTime_fixedDeltaTime()
{
	return 0.016667f;
}
