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

#if defined (_WIN32) || defined(__linux__)

#if defined (_WIN32)
	#define VK_USE_PLATFORM_WIN32_KHR
#endif //_WIN32
#if defined (__linux__)
	#define VK_USE_PLATFORM_XLIB_KHR
#endif //__linux__

#include <vulkan/vulkan.h>
#if defined (_WIN32)
	#include <vulkan/vulkan_win32.h>
#endif //_WIN32
#if defined (__linux__)
	#include <vulkan/vulkan_xlib.h>
#endif //__linux__

#include "EngineRenderer.h"

class EngineWindow;

class EngineRenderer_Vulkan : public EngineRenderer
{
public:
	EngineRenderer_Vulkan();
	~EngineRenderer_Vulkan();

public:
	virtual void Initialize( EngineWindow* engineWindow ) override;

protected:
	/**
	 * Used	to see if the renderer is still online and is available to render.
	 * This is meant to be overwritten by the inheritted class
	 */
	virtual bool IsOkay() override { return m_RendererOnline; }
	
	/**
	 * Called in constructor and is used to initialize member VkInstance m_Instance.
	 * Extensions and validation layers are defined inside of this method.
	*/
	void CreateMemberInstance();
	/**
	 * Called to create and initialize the Debug Layer Callback.
	 * Exception can be thrown if vulkan cannot find the correct memory address for
	 * the creation of the messenger.
	 */
	void CreateDebugCallback();
	/**
	 * Creates a VkSurfaceKHR from a given
	 */
	void CreateSurface( EngineWindow* engineWindow );

private:
	VkInstance m_Instance;
	VkDebugUtilsMessengerEXT m_DebugMessenger;
	VkSurfaceKHR m_Surface;
};

#endif