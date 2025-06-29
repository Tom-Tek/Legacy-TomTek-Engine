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

#include "Instance.h"
#include "ValidationLayer.h"

#include "Utilities/Helpers.hpp"

namespace TomTekRendering::Vulkan
{
	Instance::Instance( const VkApplicationInfo applicationInfo )
	{
		const VkInstanceCreateInfo createInfo = {
			.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.pApplicationInfo = &applicationInfo,
			.enabledLayerCount = (uint32_t) ValidationLayer::k_ValidationLayers.size(),
			.ppEnabledLayerNames = ValidationLayer::k_ValidationLayers.data(),
			.enabledExtensionCount = (uint32_t) k_Extensions.size(),
			.ppEnabledExtensionNames = k_Extensions.data()
		};

		if ( vkCreateInstance( &createInfo, nullptr, &m_VkInstance ) != VK_SUCCESS )
		{
			throw std::runtime_error( "vkCreateInstance failed to create m_Instance!" );
		}

		Helpers::Log( "VkInstance created." );
	}

	Instance::~Instance()
	{
		vkDestroyInstance( m_VkInstance, nullptr );
	}
}