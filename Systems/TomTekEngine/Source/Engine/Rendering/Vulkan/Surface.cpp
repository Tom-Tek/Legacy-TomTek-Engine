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
#include <iostream>

#include "Surface.h"
#include "Instance.h"

#include "Engine/Window/EngineWindow.h"
#include "Engine/Window/WinEngineWindow.h"

#include "Utilities/Helpers.hpp"

namespace TomTekRendering::Vulkan 
{

	Surface::Surface( Instance* instance, EngineWindow* localWindow )
	{
		if ( !localWindow )
		{
			throw std::runtime_error( "TomTekRendering::Vulkan::Surface requires address to EngineWindow to create surface." );
		}

#ifdef _WIN32

		//WINDOWS SURFACE IMPLEMENTATION
		VkWin32SurfaceCreateInfoKHR createInfo = {
			.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
			.hinstance = ( ( WinEngineWindow* ) localWindow )->GetHInstance(),
			.hwnd = ( ( WinEngineWindow* ) localWindow )->GetHWND(),
		};

		if ( vkCreateWin32SurfaceKHR( instance->GetNative(), &createInfo, nullptr, &m_VkSurface) != VK_SUCCESS )
		{
			throw std::runtime_error( "vkCreateWin32SurfaceKHR failed to create m_VkSurface" );
		}

		Helpers::Log( "Vulkan Win32 SurfaceKHR created ok." );

#endif
	}

}