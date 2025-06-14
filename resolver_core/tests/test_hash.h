#pragma once
#include <glm/glm.hpp>
#include <maths/hashs.h>
#include <stdio.h>
void test_hash() {
	glm::vec2 v0(600, 0);
	glm::vec2 v1(900, 750);
	glm::vec2 v2(450, 1020);
	glm::vec2 v3(0, 0);

	std::vector<glm::vec2> p0{ v0, v1, v2, v3 };
	std::vector<glm::vec2> p1{ v2, v3, v0, v1 };

	auto r0 = vertices_hasher()(p0);
	auto r1 = vertices_hasher()(p1);
	bool equal = r0 == r1;
	std::cout << std::to_string(equal) << std::endl;
}