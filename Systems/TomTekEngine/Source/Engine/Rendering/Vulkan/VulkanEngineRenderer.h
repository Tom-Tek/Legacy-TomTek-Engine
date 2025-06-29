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

#include <iostream>
#include <vulkan/vulkan.h>

#include "Engine/Rendering/EngineRenderer.h"

#include "Instance.h"
#include "ValidationLayer.h"
#include "Surface.h"
#include "PhysicalDevices.h"

class EngineWindow;

namespace TomTekRendering::Vulkan
{
	/**
	 * README!
	 * VulkanEngineRenderer class assumes that the caller has already done neccessary OS checks
	 * Be aware of the possibility this header is accidentally included on builds of TomTekEngine which
	 * do not support vulkan!
	 */
	class VulkanEngineRenderer final : public EngineRenderer
	{
	public:
		VulkanEngineRenderer( EngineWindow* localWindow );
		~VulkanEngineRenderer() = default;
		
	private:
		std::unique_ptr<Instance> m_Instance = nullptr;
		std::unique_ptr<Surface> m_Surface = nullptr;
		std::unique_ptr<PhysicalDevices> m_PhysicalDevices = nullptr;

		std::unique_ptr<ValidationLayer> m_ValidationLayer = nullptr;

		uint32_t m_QueueFamilyIndex = -1;

	};
};