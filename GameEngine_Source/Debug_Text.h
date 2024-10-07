#pragma once
#include "CommonInclude.h"

template<typename T>
static void Print_Text(HDC hdc, const std::wstring& text, T explain, Vector2 pos)
{
	wchar_t str[100] = L"";
	if constexpr (std::is_same<T, float>::value)
	{
		swprintf_s(str, 100, L"%s: %f", text.c_str(), explain);
	}
	else if constexpr (std::is_same<T, int>::value)
	{
		swprintf_s(str, 100, L"%s: %d", text.c_str(), explain);
	}
	else if constexpr (std::is_same<T, bool>::value)
	{
		swprintf_s(str, 100, L"%s: %s", text.c_str(), explain ? L"true" : L"false");
	}
	else
	{
		swprintf_s(str, 100, L"%s: %s", text.c_str(), explain);
	}
	int len = wcsnlen_s(str, 100);
	TextOut(hdc, pos.x, pos.y, str, len);
}
static void Print_Text(HDC hdc, const std::wstring& text,  Vector2 pos)
{
	wchar_t str[100] = L"";
	swprintf_s(str, 100, L"%s", text.c_str());
	int len = wcsnlen_s(str, 100);
	TextOut(hdc, pos.x, pos.y, str, len);
}
