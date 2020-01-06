#pragma once

struct klaster
{
	point center;
	std::vector<point> k_points{};

	klaster(const point &center) : center(center) {};
};