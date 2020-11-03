#pragma once

#include "Core.h"
#include <windows.h>

namespace SG
{
	struct WindowProps
	{
		uint32_t Width, Height;
		const wchar_t* w_Title;
		std::string s_Title;
		HINSTANCE WinInstance;
		int Show;
		WindowProps(const HINSTANCE& wndInstace, int show, const wchar_t* t = L"Seagull Engine", uint32_t w = 1920, uint32_t h = 1080)
			:w_Title(t), Width(w), Height(h), WinInstance(wndInstace), Show(show), s_Title("NULL") {}

		WindowProps(const std::string& t = "Seagull Engine", uint32_t w = 1920, uint32_t h = 1080)
			:s_Title(t), Width(w), Height(h), Show(0), WinInstance(nullptr), w_Title(L"NULL") {}
	};

	class Window
	{
	public:
		Window() = default;
		virtual ~Window() = default;

		virtual bool OnCreate() = 0;
		virtual void OnUpdate() = 0;

		virtual inline uint32_t GetWidth() const = 0;
		virtual inline uint32_t GetHeight() const = 0;

		virtual inline void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};

}