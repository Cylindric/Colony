#include "ClassA.h"
#include "ClassB.h"

ClassA::ClassA(void)
{
}


ClassA::~ClassA(void)
{
}


void ClassA::Initialise(void)
{
	b = new ClassB;
}