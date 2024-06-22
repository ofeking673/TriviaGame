#pragma once
#include <vector>

class Buffer
{
public:
	Buffer() = default;
	~Buffer() = default;
	std::vector<unsigned char> data;
};