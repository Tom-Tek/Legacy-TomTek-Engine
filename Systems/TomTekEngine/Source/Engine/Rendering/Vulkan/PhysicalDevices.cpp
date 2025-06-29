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

#include "PhysicalDevices.h"
#include "Instance.h"
#include "Surface.h"

#include "Utilities/Helpers.hpp"

namespace TomTekRendering::Vulkan 
{

	PhysicalDevices::PhysicalDevices( const Instance* instance, const Surface* surface )
	{
		uint32_t deviceCount = 0;
		if ( vkEnumeratePhysicalDevices( instance->GetNative(), &deviceCount, nullptr ) != VK_SUCCESS )
		{
			throw std::runtime_error( "Fatal error! vkEnumeratePhysicalDevices failed. [0]" );
		}

		Helpers::Log( "Vulkan PhysicalDevice's found: {}", deviceCount );

		m_Devices.resize( deviceCount );

		std::vector<VkPhysicalDevice> allDevices( deviceCount );
		if ( vkEnumeratePhysicalDevices( instance->GetNative(), &deviceCount, allDevices.data() ) != VK_SUCCESS )
		{
			throw std::runtime_error( "Fatal error! vkEnumeratePhysicalDevices failed. [1]" );
		}

		for ( uint32_t i = 0; i < deviceCount; i++ )
		{
			VkPhysicalDevice physDevice = allDevices[i];
			m_Devices[i].m_PhysDevice = physDevice;

			vkGetPhysicalDeviceProperties( physDevice, &m_Devices[ i ].m_PhysDeviceProps );

			uint32_t apiVersion = m_Devices[i].m_PhysDeviceProps.apiVersion;

			Helpers::Log( "Device name: {}", m_Devices[i].m_PhysDeviceProps.deviceName );
			Helpers::Log( "\tAPI version: {}.{}.{}.{}",
				VK_API_VERSION_VARIANT( apiVersion ),
				VK_API_VERSION_MAJOR( apiVersion ),
				VK_API_VERSION_MINOR( apiVersion ),
				VK_API_VERSION_PATCH( apiVersion )
			);

			uint32_t queueFamilyCount = 0;
			vkGetPhysicalDeviceQueueFamilyProperties( physDevice, &queueFamilyCount, nullptr );

			Helpers::Log( "\t# of family queues: {}", queueFamilyCount );

			m_Devices[ i ].m_QueueFamilyProps.resize( queueFamilyCount );
			m_Devices[ i ].m_QueueSupportsPresent.resize( queueFamilyCount );

			vkGetPhysicalDeviceQueueFamilyProperties( physDevice, &queueFamilyCount, m_Devices[ i ].m_QueueFamilyProps.data() );

			for ( uint32_t x = 0; x < queueFamilyCount; x++ )
			{
				const VkQueueFamilyProperties& queueFamilyProps = m_Devices[ i ].m_QueueFamilyProps[ x ];

				Helpers::Log( "\t\tFamily [{}]; Queue count: {}", x, queueFamilyProps.queueCount );

				VkQueueFlags flags = queueFamilyProps.queueFlags;
				Helpers::Log( 
					"\t\tGFX [{}]. Compute [{}], Transfer [{}], Sparce Binding [{}]",
					( flags & VK_QUEUE_GRAPHICS_BIT ) ? "ON" : "OFF",
					( flags & VK_QUEUE_COMPUTE_BIT ) ? "ON" : "OFF",
					( flags & VK_QUEUE_TRANSFER_BIT ) ? "ON" : "OFF",
					( flags & VK_QUEUE_SPARSE_BINDING_BIT ) ? "ON" : "OFF"
				);

				if ( vkGetPhysicalDeviceSurfaceSupportKHR( physDevice, x, surface->GetNative(), &( m_Devices[i].m_QueueSupportsPresent[x] )) != VK_SUCCESS )
				{
					throw std::runtime_error( "VkTtPhysicalDevice::Initialize() vkGetPhysicalDeviceSurfaceSupportKHR fatal error." );
				}
			}

			uint32_t formatsCount = 0;
			if ( vkGetPhysicalDeviceSurfaceFormatsKHR( physDevice, surface->GetNative(), &formatsCount, nullptr) != VK_SUCCESS )
			{
				throw std::runtime_error( "vkGetPhysicalDeviceSurfaceFormatsKHR fatal error [0]" );
			}

			ASSERT( formatsCount > 0, "No formatsCount counted for" );

			m_Devices[ i ].m_SurfaceFormats.resize( formatsCount );

			if ( vkGetPhysicalDeviceSurfaceFormatsKHR( physDevice, surface->GetNative(), &formatsCount, m_Devices[i].m_SurfaceFormats.data()) != VK_SUCCESS )
			{
				throw std::runtime_error( "vkGetPhysicalDeviceSurfaceFormatsKHR fatal error [1]" );
			}

			if ( vkGetPhysicalDeviceSurfaceCapabilitiesKHR( physDevice, surface->GetNative(), &( m_Devices[i].m_SurfaceCapabilities )) != VK_SUCCESS )
			{
				throw std::runtime_error( "vkGetPhysicalDeviceSurfaceCapabilitiesKHR fatal error" );
			}

			uint32_t presentModesCount = 0;
			if ( vkGetPhysicalDeviceSurfacePresentModesKHR( physDevice, surface->GetNative(), &presentModesCount, nullptr) != VK_SUCCESS )
			{
				throw std::runtime_error( "vkGetPhysicalDeviceSurfacePresentModesKHR fatal error! [0]" );
			}

			ASSERT( presentModesCount > 0, "No presentModesCount counted for");

			m_Devices[ i ].m_PresentModes.resize( presentModesCount );
			Helpers::Log( "# of Presentation Modes: {}", presentModesCount );

			if ( vkGetPhysicalDeviceSurfacePresentModesKHR( physDevice, surface->GetNative(), &presentModesCount, m_Devices[i].m_PresentModes.data()) != VK_SUCCESS )
			{
				throw std::runtime_error( "vkGetPhysicalDeviceSurfacePresentModesKHR fatal error! [1]" );
			}

			vkGetPhysicalDeviceMemoryProperties( physDevice, &( m_Devices[ i ].m_MemoryProps ));
			Helpers::Log( "# of Memory Types: {}", m_Devices[i].m_MemoryProps.memoryTypeCount );
		}
	}

	uint32_t PhysicalDevices::PickDevice( const VkQueueFlags& queueType, const bool supportsPresent )
	{
		for ( uint32_t x = 0; x < m_Devices.size(); x++ )
		{
			for ( uint32_t y = 0; y < m_Devices[ x ].m_QueueFamilyProps.size(); y++ )
			{
				const VkQueueFamilyProperties& queueFamilyProps = m_Devices[ x ].m_QueueFamilyProps[ y ];
				if ( ( queueFamilyProps.queueFlags & queueType ) && ( (bool) m_Devices[ x ].m_QueueSupportsPresent[ y ] == supportsPresent ) )
				{
					m_DeviceIndex = x;
					return y;
				}
			}
		}

		Helpers::Error( "QueueType and supports present not found!\n" );

		return 0;
	}

	int PhysicalDevices::GetDeviceIndex() const
	{
		if ( m_DeviceIndex == -1 )
		{
			throw std::runtime_error( "No physical device has been selected yet." );
		}
		return m_DeviceIndex;
	}

}