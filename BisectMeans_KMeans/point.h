#pragma once
//global
#include <random>

struct point
{
	uint16_t n;
	std::vector<uint32_t> v{};

	point() : n(0) {};
	point(uint16_t n) : n(n) {
		std::mt19937_64 random_generator;
		uint32_t seed = std::random_device{}();
		random_generator.seed(seed);
		v.reserve(n);
		for (uint16_t index = 0; index < n; ++index) {
			v.push_back(random_generator() % 10);
		}
	};

	bool operator==(const point & right) {
		return (n == right.n && v == right.v);
	};
};

