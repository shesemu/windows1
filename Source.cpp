#include <Windows.h>

/*int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow) {
	MSG msg{};
	HWND hwnd{};
	WNDCLASSEX wc{sizeof(WNDCLASSEX)};
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wparam, LPARAM lparam)->LRESULT {
		switch (uMsg)
		{
			case(WM_DESTROY):
			{
				PostQuitMessage(EXIT_SUCCESS);
			}
			return 0;
		}
		return DefWindowProc(hWnd, uMsg, wparam, lparam);
	};
	wc.lpszClassName = L"MyAppClass";
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	if (!RegisterClassEx(&wc))
		return EXIT_FAILURE;
	if ((hwnd = CreateWindow(wc.lpszClassName, L"Заголовок!", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, nullptr, nullptr, wc.hInstance, nullptr)) == INVALID_HANDLE_VALUE)
		return EXIT_FAILURE;
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return static_cast<int>(msg.wParam);
}*/
#include <Windows.h>

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t* CLASS_NAME = L"Main Class Window";

    WNDCLASS SoftwareMainClass = { 0 };
    SoftwareMainClass.lpszClassName = CLASS_NAME;
    SoftwareMainClass.lpfnWndProc = MainWindowProc;
    SoftwareMainClass.hInstance = hInstance;
    SoftwareMainClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    SoftwareMainClass.style = CS_DBLCLKS;

    RegisterClass(&SoftwareMainClass);

    HWND hwndMain = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Owerlapped Window",
        WS_OVERLAPPEDWINDOW,
        100, 250, 600, 400,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwndMain == NULL)
    {
        return 0;
    }

    CreateWindowEx(
        0,
        CLASS_NAME,
        L"Child Window",
        WS_CHILD | WS_VISIBLE | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU,
        200, 150, 200, 200,
        hwndMain,
        NULL,
        NULL,
        NULL
    );

    CreateWindowEx(
        0,
        CLASS_NAME,
        L"Popup Window",
        WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU,
        300, 250, 600, 400,
        hwndMain,
        NULL,
        NULL,
        NULL
    );

    ShowWindow(hwndMain, nCmdShow);

    MSG SoftwerMainMessage = { 0 };
    while (GetMessage(&SoftwerMainMessage, NULL, NULL, NULL))
    {
        TranslateMessage(&SoftwerMainMessage);
        DispatchMessage(&SoftwerMainMessage);
    }
    return 0;
};

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_CLOSE: {
        DestroyWindow(hwnd);
        break;
    }
    case WM_DESTROY: {
        if (FindWindow(L"Main Class Window", L"Owerlapped Window") == hwnd)
            PostQuitMessage(0);
        break;
    }
    case WM_LBUTTONDOWN:
    {
        HWND child, new_parent, parent;

        parent = GetParent(hwnd);
        new_parent = hwnd;

        if (::GetWindowLong(new_parent, GWL_STYLE) & WS_CHILD)
        {
            return 0;
        }

        child = FindWindowEx(new_parent, NULL, L"Main Class Window", L"Child Window");

        if (child != NULL)
        {
            return 0;
        }
        else if (parent != NULL)
        {
            child = FindWindowEx(parent, NULL, L"Main Class Window", L"Child Window");
        }
        else
        {
            parent = FindWindow(L"Main Class Window", L"Popup Window");
            child = FindWindowEx(parent, NULL, L"Main Class Window", L"Child Window");
        }

        SetParent(child, new_parent);
        return 0;
    }
    case WM_LBUTTONDBLCLK:
    {
        if (hwnd == FindWindow(L"Main Class Window", L"Popup Window"))
        {
            if (::GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_TOPMOST)
                SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, (SWP_NOMOVE | SWP_NOSIZE));
            else
                SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, (SWP_NOMOVE | SWP_NOSIZE));
        }

        return 0;
    }
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

