#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "window_def.h"
#include "make_window.h"
#include "window_procedure/window_procedure.h"
#include "init_instance.h"
#include "register_class.h"

//ウインドウの作成・描画
BOOL MakeWindow(HINSTANCE hInstance, int nCmdShow, MSG lpMsg, int option, int count, int flag)
{
    //ウィンドウクラスの定義
    WNDCLASSEX MenuWC, AlarmWC, TimerWC, LearningWC, QuestionWC, Eng1ItemWC, Eng3ItemWC;

    TCHAR QTEXT[] = TEXT("問題%d");
    TCHAR strtime[8]; //アラームの設定時刻

    switch (option)
    {
    //メニュー画面の作成・描画
    case MENU_OPTION:
        //ウインドウクラスの登録
        if (flag == 0)
        {
            if (!MyRegisterClass(MenuWC, hInstance, TEXT("MenuWindow"), MENU_PROC))
                return FALSE;
        }

        //ウインドウの作成
        if (!MenuInstance(hInstance, TEXT("MenuWindow"), nCmdShow, TEXT("モードを選択してください")))
            return FALSE;

        //ウインドウの描画
        while (GetMessage(&lpMsg, NULL, 0, 0))
        {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
        break;

    //アラームモードの作成・描画
    case ALARM_OPTION:
        if (flag == 0)
        {
            if (!MyRegisterClass(AlarmWC, hInstance, TEXT("AlarmWindow"), ALARM_PROC))
                return FALSE;
        }
        if (!AlarmInstance(hInstance, TEXT("AlarmWindow"), nCmdShow, TEXT("アラームを設定してください　例)9時00分 => 0900")))
            return FALSE;
        while (GetMessage(&lpMsg, NULL, 0, 0))
        {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
        break;

    //タイマー画面の作成・描画
    case TIMER_OPTION:
        if (flag == 0)
        {
            if (!MyRegisterClass(TimerWC, hInstance, TEXT("TimerWindow"), TIMER_PROC))
                return FALSE;
        }
        sprintf(strtime, TEXT("設定時刻は %d時 %d分です"), set_time.wHour, set_time.wMinute);
        if (!TimerInstance(hInstance, TEXT("TimerWindow"), nCmdShow, strtime))
            return FALSE;
        while (GetMessage(&lpMsg, NULL, 0, 0))
        {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
        break;

    //学習モードの作成・描画
    case LEARNING_OPTION:
        if (flag == 0)
        {
            if (!MyRegisterClass(LearningWC, hInstance, TEXT("LeaningWindow"), LEARNING_PROC))
                return FALSE;
        }
        if (!LearningInstance(hInstance, TEXT("LeaningWindow"), nCmdShow, TEXT("学習する項目を選択してください")))
            return FALSE;
        while (GetMessage(&lpMsg, NULL, 0, 0))
        {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
        break;

    //問題の作成・描画
    case QUESTION_OPTION:
        if (flag == 0)
        {
            if (!MyRegisterClass(QuestionWC, hInstance, TEXT("QuestionWindow"), question_PROC))
                return FALSE;
        }
        wsprintf(QTEXT, TEXT("問題%d"), count);
        if (!QuestionInstance(hInstance, TEXT("QuestionWindow"), nCmdShow, QTEXT))
            return FALSE;
        while (GetMessage(&lpMsg, NULL, 0, 0))
        {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
        break;

    //英語(part1・part2・part5)問題の作成・描画
    case ENGLISH_1ITEM_OPTION:
        if (flag == 0)
        {
            if (!MyRegisterClass(Eng1ItemWC, hInstance, TEXT("Question"), ENGLISH_1ITEM_PROC))
                return FALSE;
        }
        wsprintf(QTEXT, TEXT("Question%d"), count);
        if (!Eng1ItemInstance(hInstance, TEXT("Question"), nCmdShow, QTEXT))
            return FALSE;
        while (GetMessage(&lpMsg, NULL, 0, 0))
        {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
        break;

    //英語(part3・part4・part6・part7)問題の作成・描画
    case ENGLISH_3ITEM_OPTION:
        if (flag == 0)
        {
            if (!MyRegisterClass(Eng3ItemWC, hInstance, TEXT("Question"), ENGLISH_3ITEM_PROC))
                return FALSE;
        }
        wsprintf(QTEXT, TEXT("Question"));
        if (!Eng3ItemInstance(hInstance, TEXT("Question"), nCmdShow, QTEXT))
            return FALSE;
        while (GetMessage(&lpMsg, NULL, 0, 0))
        {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
        break;
    }

    return (int)lpMsg.wParam;
}