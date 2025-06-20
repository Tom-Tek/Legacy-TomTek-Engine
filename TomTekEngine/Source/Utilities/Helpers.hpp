/*
	MIT License

	Copyright (c) 2025 Liam Rousselle
	Copyright (c) 2025 TomTek

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

	Script Author: Liam Rousselle
*/
#pragma once

#include <iostream>
#include <format>

#ifdef NDEBUG
	#define ASSERT( condition, ... ) ( ( void ) 0 )
#else
	#define ASSERT( condition, ... ) ( ( void ) 0 ) //todo, write a damn assert macro
#endif

class Helpers
{

public:

	template<typename... T>
	static void Log( std::format_string<T...> fmt, T&&... args )
	{
		std::cout << "[LOG]: " << std::format( fmt, std::forward<T>( args )... ) << "\n";
	}

	template<typename... T>
	static void Warn( std::format_string<T...> fmt, T&&... args )
	{
		std::cerr << "[WARN]: " << std::format( fmt, std::forward<T>( args )... ) << "\n";
	}

	template<typename... T>
	static void Error( std::format_string<T...> fmt, T&&... args )
	{
		std::cerr << "[ERROR]: " << std::format( fmt, std::forward<T>( args )... ) << "\n";
	}

};