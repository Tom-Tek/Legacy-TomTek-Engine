#pragma once

#include <iostream>

class Engine
{

public:
	Engine() = default;

	void SayHello()
	{
		std::cout << "Hello World!\n";
	}

};