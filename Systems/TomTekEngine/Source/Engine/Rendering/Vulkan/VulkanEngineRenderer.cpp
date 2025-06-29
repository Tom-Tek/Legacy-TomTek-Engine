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
#include "VulkanEngineRenderer.h"
#include "Engine/Window/EngineWindow.h"
#include "Utilities/Helpers.hpp"

namespace TomTekRendering::Vulkan
{
	VulkanEngineRenderer::VulkanEngineRenderer( EngineWindow* localWindow ) :
		EngineRenderer( localWindow )
	{
		if ( !localWindow )
		{
			throw std::runtime_error( "VulkanEngineRenderer constructor missing address for *localWindow" );
		}

		const VkApplicationInfo applicationInfo = {
			.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
			.pNext = nullptr,
			.pApplicationName = "TomTek-Vulkan",
			.applicationVersion = VK_MAKE_VERSION( 1, 0, 0 ),
			.pEngineName = "TomTek-Vulkan-Engine",
			.engineVersion = VK_MAKE_VERSION( 1, 0, 0 ),
			.apiVersion = VK_API_VERSION_1_2,
		};

		m_Instance = std::make_unique<Instance>( applicationInfo );

#if !defined (NDEBUG)
		m_ValidationLayer = std::make_unique<ValidationLayer>( m_Instance.get() );
#endif

		m_Surface = std::make_unique<Surface>( m_Instance.get(), localWindow );

		m_PhysicalDevices = std::make_unique<PhysicalDevices>( m_Instance.get(), m_Surface.get() );
		m_QueueFamilyIndex = m_PhysicalDevices->PickDevice( VK_QUEUE_COMPUTE_BIT, true );
	}

}