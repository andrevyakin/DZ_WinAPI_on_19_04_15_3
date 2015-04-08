/*3.	На форме разместить список строк, однострочный редактор и кнопка «Найти».
При нажатии на кнопку найти строку из редактора в списке строк.
Если найти не удалось, то сообщить об этом.*/

#include<Windows.h>
#include<tchar.h>
#include<string>

#define ID_ListBox 1001
#define ID_EditBox 1002
#define ID_Button 1003

static TCHAR WindowsClass[] = L"win32app";
static TCHAR Title[] = L"MyApp";
HINSTANCE hinst;
RECT desktop, cr;
HWND ListBox, EditBox, Button;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinstance;
	wcex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);*/
	wcex.hbrBackground = CreateSolidBrush(RGB(10, 128, 256));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WindowsClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"Call faild!", L"MyApp", NULL);
		return 1;
	}

	hinst = hinstance;
	GetWindowRect(GetDesktopWindow(), &desktop);
	HWND hWnd = CreateWindow(
		WindowsClass,
		Title,
		WS_OVERLAPPEDWINDOW,
		desktop.right / 4,
		desktop.bottom / 6,
		desktop.right / 2,
		desktop.bottom / 2,
		NULL,
		NULL,
		hinst,
		NULL);

	if (!hWnd)
	{
		MessageBox(NULL, L"Create window faild!", L"MyApp", NULL);
		return 1;
	}
	SetTimer(hWnd, 1, 100, NULL);
	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return(int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{

	case WM_COMMAND:

	case BN_CLICKED:
		if (LOWORD(wParam) == ID_Button)
		{
			wchar_t str [100];
			SendMessage(EditBox, WM_GETTEXT, sizeof(str), (LPARAM)str);
			auto count = SendMessage(ListBox, LB_FINDSTRING, -1, (LPARAM) str);
			wchar_t num [10];
			_itow_s(count, num, 10);
			MessageBox(hWnd, num, L"", TRUE);
		}

		break;

	case WM_CREATE:
	{
					  GetClientRect(hWnd, &cr);

					  ListBox = CreateWindowEx(
						  WS_EX_CLIENTEDGE,
						  L"listbox",
						  L"",
						  WS_CHILD | WS_VISIBLE | WS_VSCROLL,
						  cr.right / 4,
						  cr.bottom / 5,
						  cr.right / 2,
						  cr.bottom / 3,
						  hWnd,
						  (HMENU)ID_ListBox,
						  hinst,
						  NULL);

					  EditBox = CreateWindowEx(
						  WS_EX_CLIENTEDGE,
						  L"edit",
						  L"",
						  WS_CHILD | WS_VISIBLE,
						  cr.right / 4,
						  cr.bottom / 5 * 3.5,
						  cr.right / 2,
						  20,
						  hWnd,
						  (HMENU)ID_EditBox,
						  hinst,
						  NULL);

					  std::wstring Agatha_Christie[10] =
					  {
						  L"Я на тебе, как на войне,",
						  L"а на войне, как на тебе,",
						  L"Но я устал, окончен бой,",
						  L"беру портвейн, иду домой.",
						  L"                         ",
						  L"Окончен бой, зачах огонь,",
						  L"и не осталось ничего.",
						  L"А мы живём, а нам с тобою повезло",
						  L"назло.",
						  L"(c) \"Агата Кристи\""
					  };

					  for (int i = 0; i < 10; i++)
						  SendMessage(ListBox, LB_ADDSTRING, 0, (LPARAM)Agatha_Christie[i].c_str());

					  Button = CreateWindowEx(
						  WS_EX_CLIENTEDGE,
						  L"button",
						  L"Найти",
						  WS_CHILD | WS_VISIBLE,
						  cr.right / 2 - 8 * 6,
						  cr.bottom - 50,
						  80,
						  30,
						  hWnd,
						  (HMENU)ID_Button,
						  hinst, NULL);

					  break;
	}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}