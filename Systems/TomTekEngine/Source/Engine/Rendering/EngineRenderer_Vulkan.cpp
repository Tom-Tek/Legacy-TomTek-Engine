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

#include "Engine/Window/EngineWindow.h"
#include "Engine/Window/EngineWindow_Win32.h"

#include "Utilities/Helpers.hpp"

static VKAPI_ATTR VkBool32 VKAPI_CALL ValidationDebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
	void* userData
) 
{
	//Helpers::Log sucks and i'm not using it here
	std::cout << "Validation error: " << messageSeverity << ", " << messageType << "\n";
	std::cout << "\t" << callbackData->pMessage << "\n";

	return VK_FALSE; //Never abort for now
}

EngineRenderer_Vulkan::EngineRenderer_Vulkan() :
	m_Instance( VK_NULL_HANDLE ),
	m_DebugMessenger( VK_NULL_HANDLE ),
	m_Surface( VK_NULL_HANDLE )
{
}

EngineRenderer_Vulkan::~EngineRenderer_Vulkan()
{
	//Destroy the surface
	PFN_vkDestroySurfaceKHR destroySurface =
		( PFN_vkDestroySurfaceKHR ) vkGetInstanceProcAddr( m_Instance, "vkDestroySurfaceKHR" );
	if ( !destroySurface )
	{
		Helpers::Warn( "Issue when deconstruction. Cannot find address of vkDestroySurfaceKHR ");
	}
	else
	{
		destroySurface( m_Instance, m_Surface, nullptr );
	}

	//Destroy the debug utils messenger
	PFN_vkDestroyDebugUtilsMessengerEXT destroyDebugUtilsMessenger =
		( PFN_vkDestroyDebugUtilsMessengerEXT ) vkGetInstanceProcAddr( m_Instance, "vkDestroyDebugUtilsMessengerEXT" );
	if ( !destroyDebugUtilsMessenger )
	{
		Helpers::Warn( "Issue when deconstructing. Cannot find address of vkDestroyDebugUtilsMessengerEXT" );
	}
	else
	{
		destroyDebugUtilsMessenger( m_Instance, m_DebugMessenger, nullptr );
	}

	//Destroy the vulkan instance
	vkDestroyInstance( m_Instance, nullptr );
}

void EngineRenderer_Vulkan::Initialize( EngineWindow* engineWindow )
{
	CreateMemberInstance();
	CreateDebugCallback();
	CreateSurface( engineWindow );
	
	InitializePhysicalDevices();
	CreateDevice();
}

void EngineRenderer_Vulkan::CreateMemberInstance()
{
	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation",

		
	};

	const std::vector<const char*> extensions = {
		VK_KHR_SURFACE_EXTENSION_NAME,

		//DEBUG EXTENSIONS
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
		
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

	//Describe all needed creation information for the vkCreateInstance command
	//later in this method
	const VkInstanceCreateInfo createInfo = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,				//Does something, but thats for future me to figure out
		.pApplicationInfo = &appInfo,
		.enabledLayerCount = ( uint32_t ) validationLayers.size(),
		.ppEnabledLayerNames = validationLayers.data(),
		.enabledExtensionCount = ( uint32_t ) extensions.size(),
		.ppEnabledExtensionNames = extensions.data()
	};

	//Create the instance, and if anything goes wrong throw an exception.
	if ( vkCreateInstance( &createInfo, nullptr, &m_Instance ) != VK_SUCCESS )
	{
		throw std::runtime_error( "vkCreateInstance failed to create m_Instance!" );
	}

	Helpers::Log( "Vulkan Instance created ok." );
}

void EngineRenderer_Vulkan::CreateDebugCallback()
{
	VkDebugUtilsMessengerCreateInfoEXT createInfo = {
		.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
		.pNext = nullptr,
		//All message severities which we're interested in for debugging
		.messageSeverity =
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT,
		//All message types which we are interested in for debugging
		.messageType =
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
		.pfnUserCallback = &ValidationDebugCallback,
		.pUserData = nullptr,
	};

	PFN_vkCreateDebugUtilsMessengerEXT createDebugUtilsMessegner =
		( PFN_vkCreateDebugUtilsMessengerEXT ) vkGetInstanceProcAddr( m_Instance, "vkCreateDebugUtilsMessengerEXT" );
	if ( !createDebugUtilsMessegner )
	{
		throw std::runtime_error( "Fatal Error! Cannot find address of vkCreateDebugUtilsMessengerEXT" );
	}

	if ( createDebugUtilsMessegner( m_Instance, &createInfo, nullptr, &m_DebugMessenger ) != VK_SUCCESS )
	{
		throw std::runtime_error( "vkCreateDebugUtilsMessengerEXT failed to create m_DebugMessenger!" );
	}

	Helpers::Log( "Vulkan Debug Messenger created ok." );
}

void EngineRenderer_Vulkan::CreateSurface( EngineWindow* engineWindow )
{
	if ( !engineWindow )
	{
		throw std::runtime_error( "EngineRenderer_Vulkan requires address to EngineWindow to create surface." );
	}

#if defined (_WIN32)

	//WINDOWS SURFACE IMPLEMENTATION
	VkWin32SurfaceCreateInfoKHR createInfo = {
		.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
		.hinstance = ( ( EngineWindow_Win32* ) engineWindow )->GetHInstance(),
		.hwnd = ( ( EngineWindow_Win32* ) engineWindow )->GetHWND(),
	};

	if ( vkCreateWin32SurfaceKHR( m_Instance, &createInfo, nullptr, &m_Surface ) != VK_SUCCESS )
	{
		throw std::runtime_error( "vkCreateWin32SurfaceKHR failed to create m_Surface" );
	}

	Helpers::Log( "Vulkan Win32 SurfaceKHR created ok." );

#endif //_WIN32

#if defined (__linux__)

	//LINUX SURFACE IMPLEMENTATION
	//UMM... ACTUALLY WRITE THIS WHEN U HAVE A LINUX OPERATING SYSTEM TO TEST ON

#endif //__linux__

}

void EngineRenderer_Vulkan::InitializePhysicalDevices()
{
	m_PhysicalDevices.Initialize( m_Instance, m_Surface );
	m_QueueFamilyIndex = m_PhysicalDevices.PickDevice( VK_QUEUE_GRAPHICS_BIT, true );
}

void EngineRenderer_Vulkan::CreateDevice()
{
	
}

#endif
