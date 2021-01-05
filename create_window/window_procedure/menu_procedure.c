#include <windows.h>
#include <tchar.h>
#include <mmsystem.h>
#include "../window_def.h"
#include "../../mode_function/sound.h"
#include "window_procedure.h"

LRESULT CALLBACK MenuProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    MSG lpMsg;      //メッセージの管理
    TEXTMETRIC tm;  //フォントの詳細情報
    HDC hdc;        //デバイスコンテキスト
    PAINTSTRUCT ps; //描画に関する情報
    int id;

    switch (msg)
    {
    case WM_CLOSE: //閉じるボタン入力時
        PlaySound(close_window_sound, NULL, SND_FILENAME | SND_ASYNC);
        id = MessageBox(hwnd, TEXT("アプリを終了しますか?"),
                        TEXT("確認"), MB_YESNO | MB_ICONEXCLAMATION);
        if (id == IDYES)
            DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY: //ウィンドウを終了
        PostQuitMessage(0);
        break;

    case WM_CREATE: //ウインドウの生成
    {
        CREATESTRUCT *cp;
        cp = (CREATESTRUCT *)lParam; //ウィンドウの生成を続けるかどうかを問い合わせ
        SetWindowLongPtr(hwnd, 0, (LONG)cp->lpCreateParams);
        break;
    }

    case WM_COMMAND: //ボタン入力時
        switch (LOWORD(wParam))
        {
        case ALARM_OPTION: //アラームモード選択時
            PlaySound(button_click_sound, NULL, SND_FILENAME | SND_ASYNC);
            DestroyWindow(hwnd);
            PostQuitMessage(wParam);
            break;
        case LEARNING_OPTION: //学習モード選択時
            PlaySound(button_click_sound, NULL, SND_FILENAME | SND_ASYNC);
            DestroyWindow(hwnd);
            PostQuitMessage(wParam);
            break;
        }
        break;

    case WM_PAINT: //ウィンドウ描画
    {
        hdc = BeginPaint(hwnd, &ps);
        SelectObject(hdc, headfont);
        GetTextMetrics(hdc, &tm);
        TCHAR *buf = (TCHAR *)GetWindowLongPtr(hwnd, 0);
        TextOut(hdc, 20, 10, buf, (int)_tcslen(buf));
        EndPaint(hwnd, &ps);
        break;
    }

    default:
        return (DefWindowProc(hwnd, msg, wParam, lParam));
    }
    return 0;
}