#include <windows.h> // Подключение заголовочного файла Windows API

LPSTR szClassName = "MyClass"; // Объявление строки для имени класса окна
HINSTANCE hInstance; // Объявление глобальной переменной для дескриптора экземпляра
LRESULT __stdcall MyWndProc(HWND, UINT, WPARAM, LPARAM); // Объявление функции обработчика сообщений окна

int __stdcall WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
    WNDCLASS wnd; // Объявление структуры WNDCLASS
    MSG msg; // Объявление структуры MSG для обработки сообщений
    HWND hwnd; // Объявление дескриптора окна

    hInstance = hInst; // Сохранение дескриптора экземпляра в глобальной переменной

    wnd.style = CS_HREDRAW | CS_VREDRAW; // Установка стиля класса окна для перерисовки окна при горизонтальном или вертикальном изменении размера
    wnd.lpfnWndProc = MyWndProc; // Установка функции обработчика сообщений окна
    wnd.cbClsExtra = 0; // Установка дополнительной памяти для класса окна
    wnd.cbWndExtra = 0; // Установка дополнительной памяти для окна
    wnd.hInstance = hInstance; // Установка дескриптора экземпляра
    wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Загрузка иконки по умолчанию
    wnd.hCursor = LoadCursor(NULL, IDC_ARROW); // Загрузка курсора по умолчанию
    wnd.hbrBackground = (HBRUSH)(COLOR_BACKGROUND+30); // Установка цвета фона окна
    wnd.lpszMenuName = NULL; // Окно без меню
    wnd.lpszClassName = szClassName; // Установка имени класса окна

    if(!RegisterClass(&wnd)) // Регистрация структуры WNDCLASS
    {
        MessageBox(NULL, "This Program Requires Windows NT", 
                         "Error", MB_OK);
        return 0;
    }

    hwnd = CreateWindow(szClassName, // Имя класса окна
                        "System Curella", // Заголовок окна
                        WS_OVERLAPPEDWINDOW, // Стиль окна по умолчанию
                        CW_USEDEFAULT,
                        CW_USEDEFAULT, // Координаты окна по умолчанию
                        CW_USEDEFAULT,
                        CW_USEDEFAULT, // Ширина и высота окна по умолчанию
                        NULL, // Без родительского окна
                        NULL, // Без меню
                        hInstance,
                        NULL); // Без параметра
    ShowWindow(hwnd, iCmdShow); // Отображение окна на экране
    UpdateWindow(hwnd); // Обновление окна

    while(GetMessage(&msg, NULL, 0, 0)) // Цикл обработки сообщений
    {
        TranslateMessage(&msg); // Перевод виртуальных ключей в символьные сообщения
        DispatchMessage(&msg); // Отправка сообщения оконной процедуре
    }
    return msg.wParam; // Возвращение кода выхода из приложения
}

LRESULT __stdcall MyWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg) // Обработка сообщений
    {
        case WM_DESTROY: // Сообщение о закрытии окна
            PostQuitMessage(0); // Отправка сообщения WM_QUIT в очередь сообщений
            return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam); // Обработка сообщений, которые не были обработаны в switch
}