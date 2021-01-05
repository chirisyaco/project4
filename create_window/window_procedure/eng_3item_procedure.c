#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <mmsystem.h>
#include "window_procedure.h"
#include "../window_def.h"
#include "../../mode_function/sound.h"
#include "../../mode_function/qa_def.h"

LRESULT CALLBACK Eng_3ItemProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;                                         //デバイスコンテキスト
    static HDC mhdc;                                 //メモリデバイスコンテキスト
    PAINTSTRUCT ps;                                  //描画に関する情報
    static HBITMAP hbitmap;                          //ビットマップハンドル
    static BITMAP bitmap;                            //ビットマップ構造体
    static int width, height;                        //bmp画像の幅・高さ
    int start_pointx, start_pointy;                  //bmp画像の描画開始位置
    int correct_ans = 0;                             //正解数
    TCHAR bmpstr[64];                                //bmp画像のパス
    TCHAR wavstr[64];                                //音源のパス
    TCHAR correctstr[] = TEXT("正解です！");         //正解時のテキスト
    TCHAR wrongstr[] = TEXT("不正解です\n正解：%c"); //不正解時のテキスト
    int id;

    switch (msg)
    {
    case WM_CLOSE: //閉じるボタン入力時
        PlaySound(close_window_sound, NULL, SND_FILENAME | SND_ASYNC);
        id = MessageBox(hwnd, TEXT("問題を終了しますか?"),
                        TEXT("確認"), MB_YESNO | MB_ICONEXCLAMATION);
        if (id == IDYES)
            DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_CREATE:
    {
        if (lstrcmp(sector, "part3") == 0 || lstrcmp(sector, "part4") == 0)
        {
            wsprintf(wavstr, "../question/english/%s/Q%d.wav", sector, answer_num);
            PlaySound(wavstr, NULL, SND_FILENAME | SND_ASYNC);
        }

        //ファイル読み込み
        wsprintf(bmpstr, TEXT("english_%s_Q%d"), sector, answer_num);
        hbitmap = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, bmpstr);
        //画像サイズ取得
        GetObject(hbitmap, sizeof(BITMAP), &bitmap);
        width = bitmap.bmWidth;
        height = bitmap.bmHeight;

        //メモリデバイスコンテキストを作成
        mhdc = CreateCompatibleDC(NULL);
        //メモリデバイスコンテキストにビットマップを設定
        SelectObject(mhdc, hbitmap);

        //チェックボックスの作成
        CreateWindow(TEXT("BUTTON"), TEXT("A"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                     970, 45, 160, 30, hwnd, (HMENU)BUTTON_ID1A, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("B"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                     970, 75, 160, 30, hwnd, (HMENU)BUTTON_ID1B, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("C"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                     970, 105, 160, 30, hwnd, (HMENU)BUTTON_ID1C, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("D"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                     970, 135, 160, 30, hwnd, (HMENU)BUTTON_ID1D, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("A"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                     970, 225, 160, 30, hwnd, (HMENU)BUTTON_ID2A, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("B"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                     970, 255, 160, 30, hwnd, (HMENU)BUTTON_ID2B, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("C"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                     970, 285, 160, 30, hwnd, (HMENU)BUTTON_ID2C, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("D"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                     970, 315, 160, 30, hwnd, (HMENU)BUTTON_ID2D, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("A"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                     970, 405, 160, 30, hwnd, (HMENU)BUTTON_ID3A, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("B"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                     970, 435, 160, 30, hwnd, (HMENU)BUTTON_ID3B, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("C"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                     970, 465, 160, 30, hwnd, (HMENU)BUTTON_ID3C, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("D"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                     970, 495, 160, 30, hwnd, (HMENU)BUTTON_ID3D, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("決定"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                     1050, 560, 100, 40, hwnd, (HMENU)DECIDE_BUTTON, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        CREATESTRUCT *cp;
        cp = (CREATESTRUCT *)lParam;
        SetWindowLongPtr(hwnd, 0, (LONG)cp->lpCreateParams);
        break;
    }

    case WM_COMMAND: //ボタン入力時
        switch (LOWORD(wParam))
        {
        case BUTTON_ID1A:
            select_ans[0] = 'A';
            break;
        case BUTTON_ID1B:
            select_ans[0] = 'B';
            break;
        case BUTTON_ID1C:
            select_ans[0] = 'C';
            break;
        case BUTTON_ID1D:
            select_ans[0] = 'D';
            break;
        case BUTTON_ID2A:
            select_ans[1] = 'A';
            break;
        case BUTTON_ID2B:
            select_ans[1] = 'B';
            break;
        case BUTTON_ID2C:
            select_ans[1] = 'C';
            break;
        case BUTTON_ID2D:
            select_ans[1] = 'D';
            break;
        case BUTTON_ID3A:
            select_ans[2] = 'A';
            break;
        case BUTTON_ID3B:
            select_ans[2] = 'B';
            break;
        case BUTTON_ID3C:
            select_ans[2] = 'C';
            break;
        case BUTTON_ID3D:
            select_ans[2] = 'D';
            break;
        case DECIDE_BUTTON:
            if (Answer[answer_num][0] == select_ans[0]) //正解時
            {
                PlaySound(correct_sound, NULL, SND_FILENAME | SND_ASYNC);
                MessageBox(hwnd, correctstr, TEXT("Q1：結果"), MB_OK);
                correct_ans++;
            }
            else //不正解時
            {
                PlaySound(wrong_sound, NULL, SND_FILENAME | SND_ASYNC);
                sprintf(wrongstr, TEXT("不正解です\n正解：%c"), Answer[answer_num][0]);
                MessageBox(hwnd, wrongstr, TEXT("Q1：結果"), MB_OK);
            }

            if (Answer[answer_num][1] == select_ans[1])
            {
                PlaySound(correct_sound, NULL, SND_FILENAME | SND_ASYNC);
                MessageBox(hwnd, correctstr, TEXT("Q2：結果"), MB_OK);
                correct_ans++;
            }
            else
            {
                PlaySound(wrong_sound, NULL, SND_FILENAME | SND_ASYNC);
                sprintf(wrongstr, TEXT("不正解です\n正解：%c"), Answer[answer_num][1]);
                MessageBox(hwnd, wrongstr, TEXT("Q2：結果"), MB_OK);
            }

            if (Answer[answer_num][2] == select_ans[2])
            {
                PlaySound(correct_sound, NULL, SND_FILENAME | SND_ASYNC);
                MessageBox(hwnd, correctstr, TEXT("Q3：結果"), MB_OK);
                correct_ans++;
                DestroyWindow(hwnd);
                PostQuitMessage(correct_ans);
            }
            else
            {
                PlaySound(wrong_sound, NULL, SND_FILENAME | SND_ASYNC);
                sprintf(wrongstr, TEXT("不正解です\n正解：%c"), Answer[answer_num][2]);
                MessageBox(hwnd, wrongstr, TEXT("Q3：結果"), MB_OK);
                DestroyWindow(hwnd);
                PostQuitMessage(correct_ans);
            }
            break;
        }
        break;

    case WM_PAINT: //ウィンドウの描画
        hdc = BeginPaint(hwnd, &ps);
        SelectObject(hdc, headfont);

        //bitmap画像の設定
        start_pointx = 500 - (width / 2);
        start_pointy = 300 - (height / 2);
        BitBlt(hdc, start_pointx, start_pointy, width, height, mhdc, 0, 0, SRCCOPY);

        TCHAR *buf = (TCHAR *)GetWindowLongPtr(hwnd, 0);
        TextOut(hdc, 20, 10, buf, (int)_tcslen(buf));
        EndPaint(hwnd, &ps);
        break;

    default:
        return (DefWindowProc(hwnd, msg, wParam, lParam));
    }
    return 0;
}
