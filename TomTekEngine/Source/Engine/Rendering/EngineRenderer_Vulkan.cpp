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
#if defined (_WIN32) || defined (__linux__)

#include <vector>
#include "EngineRenderer_Vulkan.h"

EngineRenderer_Vulkan::EngineRenderer_Vulkan() :
	m_Instance( VK_NULL_HANDLE )
{
	CreateMemberInstance();
}

EngineRenderer_Vulkan::~EngineRenderer_Vulkan()
{

}

void EngineRenderer_Vulkan::CreateMemberInstance()
{
	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation",

		
	};

	const std::vector<const char*> extensionLayers = {
		VK_KHR_SURFACE_EXTENSION_NAME,

		//DEBUG EXTENSIONS
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
		VK_EXT_DEBUG_REPORT_EXTENSION_NAME,

		//OPERATING SYSTEM SPECIFIC EXTENSION LAYERS
#if defined (_WIN32)
		"VK_KHR_win32_surface",
#elif defined (__linux__)
		"VK_KHR_xcb_surface",
#endif
	};

	//Application info for creating the instance
	const VkApplicationInfo appInfo = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext = nullptr,
		.pApplicationName = "TomTek-App",
		.applicationVersion = VK_MAKE_VERSION( 1, 0, 0 ),
		.pEngineName = "TomTek-Engine",
		.engineVersion = VK_MAKE_VERSION( 1, 0, 0 ),
		.apiVersion = VK_API_VERSION_1_2, //MOST IMPORTANT FIELD!
	};


}

#endif
