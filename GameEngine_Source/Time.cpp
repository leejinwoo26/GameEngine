#include "Time.h"
#include "Debug_Text.h"

namespace GE
{
	LARGE_INTEGER Time::CpuFrequency = {};
	LARGE_INTEGER Time::PrevFrequency = {};
	LARGE_INTEGER Time::CurrentFrequency = {};
	float Time::DeltaTimeValue = 0.f;

	void Time::Initialize()
	{
		QueryPerformanceFrequency(&CpuFrequency);
		QueryPerformanceCounter(&PrevFrequency);
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&CurrentFrequency);
		float diffrentFrequency = static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart);
		DeltaTimeValue = diffrentFrequency / static_cast<float>(CpuFrequency.QuadPart);
		PrevFrequency.QuadPart = CurrentFrequency.QuadPart;
	}
	void Time::Render(HDC hdc)
	{
		static float time = 0.f;
		time += DeltaTimeValue;
		float fps = 1.f / DeltaTimeValue;

		wchar_t str[50] = L"";

		swprintf_s(str, 50, L"Time : %f", fps);
		int len = wcsnlen_s(str, 50);

		TextOut(hdc, 0, 0, str, len);
	}
}
