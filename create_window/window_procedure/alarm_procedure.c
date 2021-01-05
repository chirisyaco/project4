#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <mmsystem.h>
#include "../../mode_function/sound.h"
#include "../window_def.h"
#include "window_procedure.h"

LRESULT CALLBACK AlarmProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HWND edit;               //文字入力用のハンドル
    TCHAR buf[16];           //バッファ
    TCHAR message[64];       //アラーム設定時刻のメッセージ
    MSG lpMsg;               //メッセージの管理
    HDC hdc;                 //デバイスコンテキスト
    PAINTSTRUCT ps;          //描画に関する情報
    RECT rctSize;            //入力文字列長
    SYSTEMTIME stTime;       //現在時刻取得
    static TCHAR strTime[8]; //現在時刻(xx時xx分)

    int id;

    switch (msg)
    {
    case WM_CLOSE: //閉じるボタン入力時
        PlaySound(close_window_sound, NULL, SND_FILENAME | SND_ASYNC);
        id = MessageBox(hwnd, TEXT("アラームモードを終了しますか?"),
                        TEXT("確認"), MB_YESNO | MB_ICONEXCLAMATION);
        if (id == IDYES)
            DestroyWindow(hwnd);
        break;

    case WM_DESTROY: //ウィンドウを終了
        PostQuitMessage(0);
        break;

    case WM_CREATE: //ウインドウの生成
    {
        SetTimer(hwnd, 1, 300, NULL);
        CREATESTRUCT *cp;
        cp = (CREATESTRUCT *)lParam;

        //アラーム入力ウィンドウの作成
        edit = CreateWindow(TEXT("EDIT"), TEXT(""),
                            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                            450, 200, 250, 60, hwnd, (HMENU)1,
                            ((LPCREATESTRUCT)(lParam))->hInstance, NULL);
        SetWindowLongPtr(hwnd, 0, (LONG)cp->lpCreateParams);
        break;
    }

    case WM_COMMAND:                        //ボタン入力時
        if (LOWORD(wParam) == TIMER_OPTION) //決定ボタン入力時
        {
            //テキストの取得
            GetWindowText(edit, buf, 10);

            // 例外処理(条件：0000~2359まで・xx60未満・4桁)
            if (buf[0] == '\0' || buf[1] == '\0' || buf[2] == '\0' || buf[3] == '\0' ||
                buf[4] != '\0' || buf[0] > '2' || buf[2] > '5')
            {
                PlaySound(error_sound, NULL, SND_FILENAME | SND_ASYNC);
                MessageBox(hwnd, TEXT("時刻が不正です"), TEXT("ERROR"), MB_ICONSTOP | MB_OK);
                return 0;
            }
            else if (buf[0] == '2' && buf[1] > '3')
            {
                PlaySound(error_sound, NULL, SND_FILENAME | SND_ASYNC);
                MessageBox(hwnd, TEXT("時刻が不正です"), TEXT("ERROR"), MB_ICONSTOP | MB_OK);
                return 0;
            }
            set_time.wHour = 10 * (buf[0] - '0') + (buf[1] - '0');
            set_time.wMinute = 10 * (buf[2] - '0') + (buf[3] - '0');

            //設定時刻の確認メッセージの表示
            PlaySound(button_click_sound, NULL, SND_FILENAME | SND_ASYNC);
            sprintf(message, TEXT("アラームを %d時 %d分に設定しました！"), set_time.wHour, set_time.wMinute);
            MessageBox(hwnd, message, TEXT("確認"), MB_OK);
            DestroyWindow(hwnd);
            PostQuitMessage(wParam);
        }
        break;

    case WM_TIMER:             //時刻変化時
        GetLocalTime(&stTime); //時刻取得
        wsprintf(strTime, "現在時刻\n%d年 %d月 %d日\n%d時 %d分 %d秒",
                 stTime.wYear, stTime.wMonth, stTime.wDay,
                 stTime.wHour, stTime.wMinute, stTime.wSecond);
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;

    case WM_PAINT: //ウィンドウ描画
    {
        hdc = BeginPaint(hwnd, &ps);
        SelectObject(hdc, headfont);
        GetClientRect(hwnd, &rctSize);
        DrawText(hdc, strTime, -1, &rctSize, DT_RIGHT); //現在時刻の表示
        TCHAR *buf = (TCHAR *)GetWindowLongPtr(hwnd, 0);
        TextOut(hdc, 0, 0, buf, (int)_tcslen(buf));
        EndPaint(hwnd, &ps);
        break;
    }

    default:
        return (DefWindowProc(hwnd, msg, wParam, lParam));
    }
    return 0;
}
