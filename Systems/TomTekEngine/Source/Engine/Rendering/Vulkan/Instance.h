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

#include <vector>
#include <vulkan/vulkan.h>

namespace TomTekRendering::Vulkan
{
	class ValidationLayer;

	class Instance final
	{
	public:
		Instance( const VkApplicationInfo applicationInfo );
		~Instance();

	public:
		VkInstance GetNative() const { return m_VkInstance; }
		operator VkInstance() const { return m_VkInstance; }

	private:
		VkInstance m_VkInstance = VK_NULL_HANDLE;
			
		ValidationLayer* m_ValidationLayer = nullptr;

		const std::vector<const char*> k_Extensions = {
			VK_KHR_SURFACE_EXTENSION_NAME,

			//DEBUG EXTENSIONS
			VK_EXT_DEBUG_UTILS_EXTENSION_NAME,

			//OS SPECIFIC EXTENSION LAYERS
			#ifdef _WIN32
				"VK_KHR_win32_surface",
			#elif __linux__
				"VK_KHR_xcb_surface",
			#endif
		};

	};
}