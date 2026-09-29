// clab2.cpp : Визначає точку входу для програми.
//

#include "framework.h"
#include "clab2.h"

#define MAX_LOADSTRING 100

// Глобальні змінні:
HINSTANCE hInst;                                // поточний екземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст рядка заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // ім'я класу головного вікна

// Оголошення функцій, включених у цей модуль коду:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Ініціалізація глобальних рядків
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLAB2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Виконати ініціалізацію програми:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLAB2));

    MSG msg;

    // Цикл основного повідомлення:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

//  ФУНКЦІЯ: MyRegisterClass()
//  ЦІЛЬ: Реєструє клас вікна.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    // Стилі CS_HREDRAW та CS_VREDRAW сигналізують Windows перемальовувати вікно при зміні ширини чи висоти
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLAB2));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CLAB2);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//   ФУНКЦІЯ: InitInstance(HINSTANCE, int)
//   ЦІЛЬ: Зберігає маркер екземпляра і створює головне вікно
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//  ФУНКЦІЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//  ЦІЛЬ: Обробляє повідомлення в головному вікні.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;

    case WM_SIZE:
        // Примусово надсилаємо запит на перемалювання при зміні розміру вікна
        InvalidateRect(hWnd, nullptr, TRUE);
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // 1. Отримуємо актуальні розміри клієнтської частини вікна
        RECT rc;
        GetClientRect(hWnd, &rc);

        int width = rc.right;
        int height = rc.bottom;

        // 2. Визначаємо середину екрана
        int midX = width / 2;
        int midY = height / 2;

        // 3. Створюємо пензлі різного кольору для кожного з 4 секторів
        HBRUSH brush1 = CreateSolidBrush(RGB(173, 216, 230)); // Світло-блакитний (верхній лівий)
        HBRUSH brush2 = CreateSolidBrush(RGB(255, 182, 193)); // Світло-рожевий (верхній правий)
        HBRUSH brush3 = CreateSolidBrush(RGB(144, 238, 144)); // Світло-зелений (нижній лівий)
        HBRUSH brush4 = CreateSolidBrush(RGB(255, 255, 170)); // Світло-жовтий (нижній правий)

        // Створюємо чорне перо товщиною 2 пікселі для чітких меж
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

        // 4. Малюємо 4 прямокутники
        // 1) Верхній лівий: від (0, 0) до (midX, midY)
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, brush1);
        Rectangle(hdc, 0, 0, midX, midY);

        // 2) Верхній правий: від (midX, 0) до (width, midY)
        SelectObject(hdc, brush2);
        Rectangle(hdc, midX, 0, width, midY);

        // 3) Нижній лівий: від (0, midY) до (midX, height)
        SelectObject(hdc, brush3);
        Rectangle(hdc, 0, midY, midX, height);

        // 4) Нижній правий: від (midX, midY) до (width, height)
        SelectObject(hdc, brush4);
        Rectangle(hdc, midX, midY, width, height);

        // 5. Очищення пам'яті GDI: повертаємо системні об'єкти та видаляємо створені нами
        SelectObject(hdc, hOldPen);
        SelectObject(hdc, hOldBrush);

        DeleteObject(brush1);
        DeleteObject(brush2);
        DeleteObject(brush3);
        DeleteObject(brush4);
        DeleteObject(hPen);

        EndPaint(hWnd, &ps);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обробник повідомлень для вікна "Про програму".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}