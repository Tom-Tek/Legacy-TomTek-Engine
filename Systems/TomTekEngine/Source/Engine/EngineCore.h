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

#include "Window/EngineWindow.h"
#include "Rendering/EngineRenderer.h"

using namespace TomTekRendering;

class EngineCore final
{
public:
	EngineCore( EngineWindow* window, EngineRenderer* renderer );

public:
	/** Checks to see if the engine is running */
	bool IsEngineRunning();

	/** Called every game update and updates the engine. */
	void UpdateEngine();

	/** Getter for m_Window */
	EngineWindow* GetWindow() const { return m_Window.get(); }
	/** Getter for m_Renderer */
	EngineRenderer* GetRenderer() const { return m_Renderer.get(); }

private:
	bool m_EngineOnline = false;

	std::unique_ptr<EngineWindow> m_Window;
	std::unique_ptr<EngineRenderer> m_Renderer;

};