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

class EngineWindow;

#ifdef _WIN32
	#define USING_VULKAN
#elif __linux__
	#define USING_VULKAN
#elif __APPLE__
	#define USING_METAL
#endif

namespace TomTekRendering 
{
	class EngineRenderer
	{
	protected:
		EngineRenderer( EngineWindow* localWindow );

	public:
		/**
		 * Responsible for creating a new renderer for the caller.
		 * Type of renderer created depends on the operating system which this application
		 * is running on.
		 * For Windows & Linux the EngineRenderer_Vulkan will be created
		 * For Apple the EngineRenderer_Metal will be created (renderer does not exist yet)
		*/
		static EngineRenderer* ManufactureRendererByOs( EngineWindow* localWindow );

		/**
		 * Used	to see if the renderer is still online and is available to render.
		 * This is meant to be overwritten by the inheritted class
		 */
		virtual bool IsOkay() { return m_RendererOnline; }

	protected:
		bool m_RendererOnline;

	};
}