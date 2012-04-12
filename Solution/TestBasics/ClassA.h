#pragma once

class ClassB;

class ClassA
{
public:
	ClassA(void);
	~ClassA(void);
	void Initialise(void);

private:
	ClassB* b;
};

