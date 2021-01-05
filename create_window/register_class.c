#include <windows.h>
#include "window_def.h"
#include "window_procedure/window_procedure.h"
#include "register_class.h"

//ウインドウクラスの設定
ATOM MyRegisterClass(WNDCLASSEX wc, HINSTANCE hInstance, TCHAR *szClassName, int proc_id)
{
    switch (proc_id)
    {
    //オプションによって呼び出すウィンドウプロシージャを設定
    case MENU_PROC:
        wc.lpfnWndProc = MenuProc;
        break;
    case ALARM_PROC:
        wc.lpfnWndProc = AlarmProc;
        break;
    case TIMER_PROC:
        wc.lpfnWndProc = TimerProc;
        break;
    case LEARNING_PROC:
        wc.lpfnWndProc = LearningProc;
        break;
    case question_PROC:
        wc.lpfnWndProc = QuestionProc;
        break;
    case ENGLISH_1ITEM_PROC:
        wc.lpfnWndProc = Eng_1ItemProc;
        break;
    case ENGLISH_3ITEM_PROC:
        wc.lpfnWndProc = Eng_3ItemProc;
        break;
    }

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(LONG);
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(hInstance, TEXT("TIPPY"));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szClassName;
    wc.hIconSm = NULL;

    return RegisterClassEx(&wc);
}