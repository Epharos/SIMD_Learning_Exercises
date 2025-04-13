#pragma once

class Exercise
{
public:
	virtual void ProcessAll() = 0;
	virtual double ProcessScalar() = 0;
	virtual double ProcessSSE() = 0;
	virtual double ProcessAVX() = 0;
};