#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <mmsystem.h>
#include "../../mode_function/sound.h"
#include "../window_def.h"
#include "window_procedure.h"

//タイマープロシージャ
LRESULT CALLBACK TimerProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;                  //デバイスコンテキスト
    static HDC mhdc;          //メモリデバイスコンテキスト
    PAINTSTRUCT ps;           //描画に関する情報
    RECT rctSize;             //長方形領域の論理座標
    SYSTEMTIME now_time;      //設定時刻との比較用
    static TCHAR strTime[64]; //現在時刻表示用
    static HBITMAP hbitmap;   //ビットマップハンドル
    static BITMAP bitmap;     //ビットマップ構造体
    static int width, height; //bmp画像の幅・高さ
    int id;

    switch (msg)
    {
    case WM_CLOSE: //閉じるボタン入力時
        PlaySound(close_window_sound, NULL, SND_FILENAME | SND_ASYNC);
        id = MessageBox(hwnd, TEXT("タイマーを終了しますか?"),
                        TEXT("確認"), MB_YESNO | MB_ICONEXCLAMATION);
        if (id == IDYES)
            DestroyWindow(hwnd);
        break;

    case WM_DESTROY: //ウィンドウを終了
        DeleteObject(hbitmap);
        DeleteDC(mhdc);
        PostQuitMessage(0);
        break;

    case WM_CREATE: //ウインドウの生成
    {
        //ファイル読み込み
        hbitmap = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, TEXT("sleeping_hamster"));
        //画像サイズ取得
        GetObject(hbitmap, sizeof(BITMAP), &bitmap);
        width = bitmap.bmWidth;
        height = bitmap.bmHeight;

        //メモリデバイスコンテキストを作成
        mhdc = CreateCompatibleDC(NULL);
        //メモリデバイスコンテキストにビットマップを設定
        SelectObject(mhdc, hbitmap);

        CREATESTRUCT *cp;
        cp = (CREATESTRUCT *)lParam;
        SetWindowLongPtr(hwnd, 0, (LONG)cp->lpCreateParams);
        SetTimer(hwnd, 1, 300, NULL);
        return 0;
    }

    case WM_TIMER: //時刻変化時
        GetLocalTime(&now_time);
        wsprintf(strTime, "現在時刻\n%d年 %d月 %d日\n%d時 %d分 %d秒",
                 now_time.wYear, now_time.wMonth, now_time.wDay,
                 now_time.wHour, now_time.wMinute, now_time.wSecond);

        // 時間になったらウィンドウ終了
        if (set_time.wHour == now_time.wHour &&
            set_time.wMinute == now_time.wMinute)
            DestroyWindow(hwnd);

        //ウィンドウ再描画
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;

    case WM_PAINT: //ウィンドウ描画
        hdc = BeginPaint(hwnd, &ps);
        //フォントの設定
        SelectObject(hdc, headfont);

        //bitmap画像の設定
        BitBlt(hdc, 400, 150, width, height, mhdc, 0, 0, SRCCOPY);

        //時刻の設定
        GetClientRect(hwnd, &rctSize);
        DrawText(hdc, strTime, -1, &rctSize, DT_RIGHT); //現在時刻の表示

        //見出しの設定
        TCHAR *buf = (TCHAR *)GetWindowLongPtr(hwnd, 0);
        TextOut(hdc, 20, 10, buf, (int)_tcslen(buf));
        EndPaint(hwnd, &ps);
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
