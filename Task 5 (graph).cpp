#include <windows.h> // заголовочный файл, содержащий WINAPI
#include <stdlib.h>
#include <math.h>

// Прототип функции обработки сообщений:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR coord_x[] = L"X";
TCHAR coord_y[] = L"Y";

// Управляющая функция:
int WINAPI WinMain(HINSTANCE hInst, // дескриптор экземпляра приложения
    HINSTANCE hPrevInst,
    LPSTR lpCmdLine,
    int nCmdShow) // режим отображения окна
{
    TCHAR szClassName[] = L"My class"; // строка с именем класса
    HWND hMainWnd; // создаём дескриптор будущего окна
    MSG msg; // создём экземпляр структуры MSG для обработки сообщений
    WNDCLASSEX wc; // создаём экземпляр, для обращения к членам класса WNDCLASSEXN
    wc.cbSize = sizeof(wc); // размер структуры (в байтах)
    wc.style = NULL; // стиль класса окошка
    wc.lpfnWndProc = WndProc; // указатель на пользовательскую функцию
    wc.lpszMenuName = NULL; // указатель на имя меню (у нас его нет)
    wc.lpszClassName = szClassName; // указатель на имя класса
    wc.cbWndExtra = NULL; // число освобождаемых байтов в конце структуры
    wc.cbClsExtra = NULL; // число освобождаемых байтов при создании экземпляра приложения
    wc.hIcon = LoadIcon(NULL, IDI_HAND); // декриптор пиктограммы
    wc.hIconSm = LoadIcon(NULL, IDI_HAND); // дескриптор маленькой пиктограммы (в трэе)
    wc.hCursor = LoadCursor(NULL, IDC_CROSS); // дескриптор курсора
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // дескриптор кисти для закраски фона окна
    wc.hInstance = hInst; // указатель на строку, содержащую имя меню, применяемого для класса
    if (!RegisterClassEx(&wc)) {
        // в случае отсутствия регистрации класса:
        MessageBox(NULL, L"Can't register class", L"Error!", MB_OK);

        return NULL;
    }
    // Определение коор-т центра экрана
    HDC screenDC;
    screenDC = GetDC(0);
    int screenX_center, screenY_center;

    screenX_center = GetDeviceCaps(screenDC, HORZRES) / 2;
    screenY_center = GetDeviceCaps(screenDC, VERTRES) / 2;
    // Размеры окна:

    int windowX_size, windowY_size;

    windowX_size = 500;
    windowY_size = 500;
    // Функция, создающая окно:
    hMainWnd = CreateWindow(
        szClassName, // имя класса
        L"Task 5_5 (graph)",
        WS_OVERLAPPEDWINDOW, // режим отображения окна
        screenX_center - windowX_size / 2, // позиция окна по центру OX
        screenY_center - windowY_size / 2, // позиция окна по центру OY
        windowX_size, // ширина окна
        windowY_size, // высота окна
        (HWND)NULL, // дескриптор родительского окна
        NULL, // дескриптор меню
        HINSTANCE(hInst), // дескриптор экземпляра приложения
        NULL); // ничего не передаём из WndProc
    if (!hMainWnd) { // в случае некорректного создания окна:
       
        MessageBox(NULL, L"Can't create the window", L"Error!", MB_OK);
       
        return NULL;
    }
    ShowWindow(hMainWnd, nCmdShow); // отображаем окошко
    UpdateWindow(hMainWnd); // обновляем окошко
    while (GetMessage(&msg, NULL, NULL, NULL)) { // извлекаем сообщения из очереди, посылаемые фу-циями, ОС
        TranslateMessage(&msg); // интерпретируем сообщения
        DispatchMessage(&msg); // передаём сообщения обратно ОС
    }
    return msg.wParam; // возвращаем код выхода из приложения
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    int windowX_size, windowY_size;

    windowX_size = 500;
    windowY_size = 500;

    HDC hdc; // создаём дескриптор ориентации текста на экране
    PAINTSTRUCT ps; // структура, сод-щая информацию о клиентской области (размеры, цвет и тп)
    RECT rect; // стр-ра, определяющая размер клиентской области
    /*rect.left = 200;
    rect.top = 200;
    rect.right = 250;
    rect.bottom = 250;*/
    HPEN pen_coord_sys = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
    HPEN pen_graph = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
    switch (uMsg) {
    case WM_PAINT:

        hdc = BeginPaint(hWnd, &ps); // инициализируем контекст устройства
        GetClientRect(hWnd, &rect); // получаем ширину и высоту области для рисования

        SelectObject(hdc, pen_coord_sys);

        MoveToEx(hdc, 30, windowY_size / 2 - 20, NULL); // ось OX
        LineTo(hdc, windowX_size - 50, windowY_size / 2 - 20);

        MoveToEx(hdc, windowX_size - 50, windowY_size / 2 - 20, NULL); // верхняя часть стрелки OX
        LineTo(hdc, windowX_size - 60, windowY_size / 2 - 25);

        MoveToEx(hdc, windowX_size - 50, windowY_size / 2 - 20, NULL); // нижняя часть стрелки OX
        LineTo(hdc, windowX_size - 60, windowY_size / 2 - 15);

        MoveToEx(hdc, windowX_size / 2 - 10, 80, NULL); // ось OY
        LineTo(hdc, windowX_size / 2 - 10, windowY_size - 140);

        MoveToEx(hdc, windowX_size / 2 - 10, 80, NULL); // левая часть стрелки OY
        LineTo(hdc, windowX_size / 2 - 15, 90);

        MoveToEx(hdc, windowX_size / 2 - 10, 80, NULL); // правая часть стрелки OY
        LineTo(hdc, windowX_size / 2 - 5, 90);

        SetTextColor(hdc, RGB(0, 0, 0)); // устанавливаем цвет контекстного устройства

        DrawText(hdc, coord_x, -1, &rect, DT_SINGLELINE | DT_RIGHT | DT_VCENTER); // ось OX
        DrawText(hdc, coord_y, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_TOP); // ось OY

        SelectObject(hdc, pen_graph);

        for (float x = -14.0f; x <= 14.0f; x += 0.001f) { // груфик синусоиды
            MoveToEx(hdc, 15 * x + 240, -15 * sin(x) + 230, NULL);
            LineTo(hdc, 15 * x + 240, -15 * sin(x) + 230);
        }

        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(NULL);
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return NULL;
}

//HWND hWnd = GetConsoleWindow();
//HDC hDC = GetDC(hWnd);
//HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
//SelectObject(hDC, Pen);
//MoveToEx(hDC, 0, 85, NULL);
//LineTo(hDC, 200, 85);
//MoveToEx(hDC, 100, 0, NULL);
//LineTo(hDC, 100, 170);
//for (float x = -8.0f; x <= 8.0f; x += 0.01f) // O(100,85) - center
//{
//    MoveToEx(hDC, 10 * x + 100, -10 * sin(x) + 85, NULL);//10 - scale
//    LineTo(hDC, 10 * x + 100, -10 * sin(x) + 85);
//}
//system("pause");
//ReleaseDC(hWnd, hDC);



//#ifndef UNICODE
//#define UNICODE
//#endif 
//
//
//
//#include <windows.h>
//
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
//{
//    // Register the window class.
//    const wchar_t CLASS_NAME[] = L"Sample Window Class";
//
//    WNDCLASS wc = { };
//
//    wc.lpfnWndProc = WindowProc;
//    wc.hInstance = hInstance;
//    wc.lpszClassName = CLASS_NAME;
//
//    RegisterClass(&wc);
//
//    // Create the window.
//
//    HWND hwnd = CreateWindowEx(
//        0,                              // Optional window styles.
//        CLASS_NAME,                     // Window class
//        L"Task 5 (graph)",              // Window text
//        WS_OVERLAPPEDWINDOW,            // Window style
//
//        // Size and position
//        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
//
//        NULL,       // Parent window    
//        NULL,       // Menu
//        hInstance,  // Instance handle
//        NULL        // Additional application data
//    );
//
//    if (hwnd == NULL)
//    {
//        return 0;
//    }
//
//    ShowWindow(hwnd, nCmdShow);
//
//    // Run the message loop.
//
//    MSG msg;
//    while (GetMessage(&msg, NULL, 0, 0))
//    {
//        TranslateMessage(&msg);
//        DispatchMessage(&msg);
//    }
//
//    return 0;
//}
//
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    switch (uMsg)
//    {
//    case WM_DESTROY:
//    {
//        PostQuitMessage(0);
//        return 0;
//    }
//    case WM_PAINT:
//    {
//        PAINTSTRUCT ps;
//        HDC hdc = BeginPaint(hwnd, &ps);
//
//        // All painting occurs here, between BeginPaint and EndPaint.
//
//
//
//        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 3));
//
//        EndPaint(hwnd, &ps);
//    }
//    return 0;
//
//    }
//    return DefWindowProc(hwnd, uMsg, wParam, lParam);
//}

//GetClientRect(hWnd, &rect); // получаем ширину и высоту области для рисования
        //SetTextColor(hDC, colorText); // устанавливаем цвет контекстного устройства
        //DrawText(hDC, mainMessage, -1, &rect, DT_SINGLELINE | DT_CENTER); // рисуем текст