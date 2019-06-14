#include "pch.h"
#include "Random.h"

namespace Random
{
	std::random_device rd;
	std::mt19937 mt(rd());

	// 0.0��x��1.0 �̏��������_������
	float Value()
	{
		return static_cast<float>(Rand(RAND_MAX)) / RAND_MAX;
	}

	// 0.0��x��max �̐��������_������
	int Rand(int max)
	{
		return mt() % (max + 1);
	}

	// 0.0��x��max �̏��������_������
	float Rand(float max)
	{
		return Value() * max;
	}

	// min��x��max �̐��������_������
	int Range(int min, int max)
	{
		if (max < min)
			std::swap(min, max);
		return Rand(max - min) + min;
	}

	// min��x��max �̏��������_������
	float Range(float min, float max)
	{
		if (max < min)
			std::swap(min, max);
		return Rand(max - min) + min;
	}
}
