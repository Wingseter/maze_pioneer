#pragma once
#include "WinDef.h"
#include "Exception.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <optional>
#include <memory>

class Window
{
public:
	class WindowException : public Exception
	{
		using Exception::Exception;
	public:
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
	};
	class HrException: public WindowException
	{
	public:
		HrException(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorDescription() const noexcept;
	private:
		HRESULT hr;
	};
	class NoGfxException: public WindowException
	{
	public:
		using WindowException::WindowException;
		const char* GetType() const noexcept override;
	};
private:
	// ΩÃ±€≈Ê ¿©µµøÏ ≈¨∑πΩ∫
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator = (const WindowClass&) = delete;
		static constexpr const char* wndClassName = "Maze Pioneer";
		static WindowClass wndClass; // ΩÃ±€≈Ê
		HINSTANCE hInst;
	};
public:
	Window(int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator = (const Window&) = delete;
	void SetTitle(const std::string& title);
	static std::optional<int> ProcessMessage() noexcept;
	Graphics& Gfx();
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgThunk(HWND hWNd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	Keyboard kbd;
	Mouse mouse;
private:
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Graphics> pGfx;
};

#define WND_EXCEPT(hr) Window::HrException(__LINE__,__FILE__,hr)
#define WND_LAST_EXCEPT() Window::HrException(__LINE__,__FILE__,GetLastError())
#define WND_NOGFX_EXCEPT() Window::NoGfxException(__LINE__,__FILE__)