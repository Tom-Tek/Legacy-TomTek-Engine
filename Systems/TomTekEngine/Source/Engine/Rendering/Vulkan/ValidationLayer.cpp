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

#include "ValidationLayer.h"
#include "Instance.h"

#include "Utilities/Helpers.hpp"

namespace TomTekRendering::Vulkan
{
	static VKAPI_ATTR VkBool32 VKAPI_CALL ValidationDebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
		void* userData
	) 
	{
		//Helpers::Error sucks and i'm not using it here
		std::cout << "Validation error: " << messageSeverity << ", " << messageType << "\n";
		std::cout << "\t" << callbackData->pMessage << "\n";

		return VK_FALSE; //Never abort for now
	}

	ValidationLayer::ValidationLayer( Instance* instance )
	{
		m_Instance = instance;

#if !defined (NDEBUG)

		const VkDebugUtilsMessengerCreateInfoEXT createInfo = {
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
			(PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr( instance->GetNative(), "vkCreateDebugUtilsMessengerEXT");
		if ( !createDebugUtilsMessegner )
		{
			throw std::runtime_error( "Fatal Error! Cannot find address of vkCreateDebugUtilsMessengerEXT" );
		}

		if ( createDebugUtilsMessegner( instance->GetNative(), &createInfo, nullptr, &m_DebugMessenger ) != VK_SUCCESS )
		{
			throw std::runtime_error( "vkCreateDebugUtilsMessengerEXT failed to create m_DebugMessenger!" );
		}

		Helpers::Log( "VkDebugUtilsMessengerEXT created." );
#endif
	}

	ValidationLayer::~ValidationLayer()
	{
#if !defined (NDEBUG)
		PFN_vkDestroyDebugUtilsMessengerEXT destroyDebugUtilsMessenger =
			( PFN_vkDestroyDebugUtilsMessengerEXT ) vkGetInstanceProcAddr( m_Instance->GetNative(), "vkDestroyDebugUtilsMessengerEXT");
		if ( !destroyDebugUtilsMessenger )
		{
			Helpers::Warn( "Issue when deconstructing. Cannot find address of vkDestroyDebugUtilsMessengerEXT" );
		}
		else
		{
			destroyDebugUtilsMessenger( m_Instance->GetNative(), m_DebugMessenger, nullptr);
		}
#endif
	}
}