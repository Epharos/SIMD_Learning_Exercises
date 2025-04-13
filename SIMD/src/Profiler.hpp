#pragma once

#include <iostream>
#include <chrono>
#include <string>

class Profiler
{
private:
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;

	std::string name;

	double* counterRef;

public:
	Profiler(const std::string& _name, double* _ref = nullptr)
	{
		name = _name;
		counterRef = _ref;
		start = std::chrono::high_resolution_clock::now();
	}

	~Profiler()
	{
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = end - start;
		if(counterRef) *counterRef = elapsed.count() * 1000; // Convert to milliseconds
		std::cout << name << " - " << elapsed.count() * 1000 << " ms" << std::endl;
	}
};