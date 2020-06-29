#pragma once
#include <chrono> // �ð� ���̺귯��

class Timer
{
public:
	Timer() noexcept;
	float Mark() noexcept;
	float Peek() const noexcept;
private:
	std::chrono::steady_clock::time_point last;
};