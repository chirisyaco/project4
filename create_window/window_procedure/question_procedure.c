#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <mmsystem.h>
#include "../../mode_function/sound.h"
#include "../window_def.h"
#include "window_procedure.h"
#include "../../mode_function/qa_def.h"

LRESULT CALLBACK QuestionProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;                                         //デバイスコンテキスト
    static HDC mhdc;                                 //メモリデバイスコンテキスト
    PAINTSTRUCT ps;                                  //描画に関する情報
    static HBITMAP hbitmap;                          //ビットマップハンドル
    static BITMAP bitmap;                            //ビットマップ構造体
    static int width, height;                        //bmp画像の幅・高さ
    int start_pointx, start_pointy;                  //bmp画像の描画開始位置
    TCHAR question[64];                              //bmp画像のパス
    TCHAR correctstr[] = TEXT("正解です！");         //正解時のテキスト
    TCHAR wrongstr[] = TEXT("不正解です\n正解：%s"); //不正解時のテキスト
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
        //ファイル読み込み
        if (lstrcmp(sector, "word") == 0) //英単語だけ
            wsprintf(question, TEXT("english_%s_Q%d"), sector, answer_num);
        else //その他(数学問題)
            wsprintf(question, TEXT("math_%s_Q%d"), sector, answer_num);

        hbitmap = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, question);
        //画像サイズ取得
        GetObject(hbitmap, sizeof(BITMAP), &bitmap);
        width = bitmap.bmWidth;
        height = bitmap.bmHeight;

        //メモリデバイスコンテキストを作成
        mhdc = CreateCompatibleDC(NULL);
        //メモリデバイスコンテキストにビットマップを設定
        SelectObject(mhdc, hbitmap);

        CREATESTRUCT *cp;
        cp = (CREATESTRUCT *)lParam; //ウィンドウの生成を続けるかどうかを問い合わせ
        SetWindowLongPtr(hwnd, 0, (LONG)cp->lpCreateParams);
        break;
    }

    case WM_COMMAND: //ボタン入力時
        switch (LOWORD(wParam))
        {
        case BUTTON_ID0:
            if (question_num[0] == answer_num) //正解時
            {
                PlaySound(correct_sound, NULL, SND_FILENAME | SND_ASYNC);
                MessageBox(hwnd, correctstr, TEXT("結果"), MB_OK);
                DestroyWindow(hwnd);
                PostQuitMessage(CORRECT);
                break;
            }
            else //不正解時
            {
                PlaySound(wrong_sound, NULL, SND_FILENAME | SND_ASYNC);
                sprintf(wrongstr, TEXT("不正解です\n正解：%s"), Answer[answer_num]);
                MessageBox(hwnd, wrongstr, TEXT("結果"), MB_OK);
                DestroyWindow(hwnd);
                PostQuitMessage(WRONG);
                break;
            }
        case BUTTON_ID1:
            if (question_num[1] == answer_num)
            {
                PlaySound(correct_sound, NULL, SND_FILENAME | SND_ASYNC);
                MessageBox(hwnd, correctstr, TEXT("結果"), MB_OK);
                DestroyWindow(hwnd);
                PostQuitMessage(CORRECT);
                break;
            }
            else
            {
                PlaySound(wrong_sound, NULL, SND_FILENAME | SND_ASYNC);
                sprintf(wrongstr, TEXT("不正解です\n正解：%s"), Answer[answer_num]);
                MessageBox(hwnd, wrongstr, TEXT("結果"), MB_OK);
                DestroyWindow(hwnd);
                PostQuitMessage(WRONG);
                break;
            }
        case BUTTON_ID2:
            if (question_num[2] == answer_num)
            {
                PlaySound(correct_sound, NULL, SND_FILENAME | SND_ASYNC);
                MessageBox(hwnd, correctstr, TEXT("結果"), MB_OK);
                DestroyWindow(hwnd);
                PostQuitMessage(CORRECT);
                break;
            }
            else
            {
                PlaySound(wrong_sound, NULL, SND_FILENAME | SND_ASYNC);
                sprintf(wrongstr, TEXT("不正解です\n正解：%s"), Answer[answer_num]);
                MessageBox(hwnd, wrongstr, TEXT("結果"), MB_OK);
                DestroyWindow(hwnd);
                PostQuitMessage(WRONG);
                break;
            }
        case BUTTON_ID3:
            if (question_num[3] == answer_num)
            {
                PlaySound(correct_sound, NULL, SND_FILENAME | SND_ASYNC);
                MessageBox(hwnd, correctstr, TEXT("結果"), MB_OK);
                DestroyWindow(hwnd);
                PostQuitMessage(CORRECT);
                break;
            }
            else
            {
                PlaySound(wrong_sound, NULL, SND_FILENAME | SND_ASYNC);
                sprintf(wrongstr, TEXT("不正解です\n正解：%s"), Answer[answer_num]);
                MessageBox(hwnd, wrongstr, TEXT("結果"), MB_OK);
                DestroyWindow(hwnd);
                PostQuitMessage(WRONG);
                break;
            }
        }
        break;

    case WM_PAINT: //ウィンドウの描画
        hdc = BeginPaint(hwnd, &ps);
        SelectObject(hdc, headfont);

        //bitmap画像の設定
        start_pointx = 600 - (width / 2);
        start_pointy = 225 - (height / 2);
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
