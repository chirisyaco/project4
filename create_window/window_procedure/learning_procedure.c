#include <windows.h>
#include <tchar.h>
#include <mmsystem.h>
#include "../../mode_function/sound.h"
#include "../window_def.h"
#include "window_procedure.h"

LRESULT CALLBACK LearningProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    MSG lpMsg;      //メッセージの管理
    HDC hdc;        //デバイスコンテキスト
    PAINTSTRUCT ps; //描画に関する情報
    int id;

    switch (msg)
    {
    case WM_CLOSE: //閉じるボタン入力時
        PlaySound(close_window_sound, NULL, SND_FILENAME | SND_ASYNC);
        id = MessageBox(hwnd, TEXT("学習モードを終了しますか?"),
                        TEXT("確認"), MB_YESNO | MB_ICONEXCLAMATION);
        if (id == IDYES)
            DestroyWindow(hwnd);
        break;

    case WM_DESTROY: //ウィンドウを終了
        PostQuitMessage(0);
        break;

    case WM_CREATE: //ウインドウの生成
    {
        CREATESTRUCT *cp;
        cp = (CREATESTRUCT *)lParam;
        SetWindowLongPtr(hwnd, 0, (LONG)cp->lpCreateParams);
        return 0;
    }

    case WM_COMMAND: //ボタン入力時
        switch (LOWORD(wParam))
        {
        }
        PlaySound(button_click_sound, NULL, SND_FILENAME | SND_ASYNC);
        DestroyWindow(hwnd);
        PostQuitMessage(wParam);
        break;

    case WM_PAINT: //ウィンドウ描画
    {
        hdc = BeginPaint(hwnd, &ps);
        SelectObject(hdc, headfont);
        TCHAR *buf = (TCHAR *)GetWindowLongPtr(hwnd, 0);
        TextOut(hdc, 10, 0, buf, (int)_tcslen(buf));
        EndPaint(hwnd, &ps);
        break;
    }

    default:
        return (DefWindowProc(hwnd, msg, wParam, lParam));
    }
    return 0;
}
