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

#if defined (_WIN32) || defined (__linux__)

#include <vector>
#include <vulkan/vulkan.h>

struct PhysicalDeviceStruct
{
	VkPhysicalDevice m_PhysDevice;
	VkPhysicalDeviceProperties m_PhysDeviceProps;

	std::vector<VkQueueFamilyProperties> m_QueueFamilyProps;
	std::vector<VkBool32> m_QueueSupportsPresent;
	std::vector<VkSurfaceFormatKHR> m_SurfaceFormats;
	std::vector<VkPresentModeKHR> m_PresentModes;

	VkSurfaceCapabilitiesKHR m_SurfaceCapabilities;
	VkPhysicalDeviceMemoryProperties m_MemoryProps;
};

class VkTtPhysicalDevice
{
public:
	VkTtPhysicalDevice() = default;
	~VkTtPhysicalDevice() = default;

public:
	void Initialize( const VkInstance& instance, const VkSurfaceKHR& surface );

	uint32_t PickDevice( VkQueueFlags queueType, bool supportsPresent );

	const PhysicalDeviceStruct& Get() const;

private:
	std::vector<PhysicalDeviceStruct> m_Devices;
	int m_DeviceIndex = -1;

};

#endif