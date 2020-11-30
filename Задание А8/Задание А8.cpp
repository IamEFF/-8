#include<Windows.h>
#include<windowsx.h>
#include<tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HPEN hRedPen, hBluePen;
HBRUSH hRedBrush, hBlueBrush;
POINT pt[6] = { {550,40},{575,140},{500,75}, {600,75}, {525,140}, {550,40} };
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hMainWnd;
	TCHAR szClassName[] = _T("MyClass");
	MSG msg;
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassExW(&wc)) {
		MessageBoxW(NULL, _T("Cannot registr class"), _T("Error"), MB_OK);
		return 0;
	}
	hMainWnd = CreateWindow(szClassName, _T("Задание A8"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);

	if (!hMainWnd) {
		MessageBox(NULL, _T("Cannot create main window"), _T("Error"), MB_OK);
		return 0;
	}
	ShowWindow(hMainWnd, nCmdShow);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	switch (uMsg) {
	case WM_CREATE:
		hRedPen = CreatePen(PS_SOLID, 4, RGB(150, 0, 0));
		hBluePen = CreatePen(PS_SOLID, 4, RGB(0, 0, 150));
		hRedBrush = CreateSolidBrush(RGB(255, 120, 120));
		hBlueBrush = CreateSolidBrush(RGB(120, 120, 255));
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkColor(hdc, RGB(200, 200, 100));
		SelectPen(hdc, hBluePen);
		SelectBrush(hdc, hBlueBrush);
		Chord(hdc, 0, 0, 200, 200, 200, 100, 0, 100);
		SelectPen(hdc, hRedPen);
		SelectBrush(hdc, hRedBrush);
		Chord(hdc, 0, 0, 200, 200, 0, 100, 200, 100);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hRedPen);
		DeleteObject(hBluePen);
		DeleteObject(hRedBrush);
		DeleteObject(hBlueBrush);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}