#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "window_def.h"
#include "make_window.h"
#include "window_procedure/window_procedure.h"
#include "init_instance.h"
#include "register_class.h"

//�E�C���h�E�̍쐬�E�`��
BOOL MakeWindow(HINSTANCE hInstance, int nCmdShow, MSG lpMsg, int option, int count, int flag)
{
    //�E�B���h�E�N���X�̒�`
    WNDCLASSEX MenuWC, AlarmWC, TimerWC, LearningWC, QuestionWC, Eng1ItemWC, Eng3ItemWC;

    TCHAR QTEXT[] = TEXT("���%d");
    TCHAR strtime[8]; //�A���[���̐ݒ莞��

    switch (option)
    {
    //���j���[��ʂ̍쐬�E�`��
    case MENU_OPTION:
        //�E�C���h�E�N���X�̓o�^
        if (flag == 0)
        {
            if (!MyRegisterClass(MenuWC, hInstance, TEXT("MenuWindow"), MENU_PROC))
                return FALSE;
        }

        //�E�C���h�E�̍쐬
        if (!MenuInstance(hInstance, TEXT("MenuWindow"), nCmdShow, TEXT("���[�h��I�����Ă�������")))
            return FALSE;

        //�E�C���h�E�̕`��
        while (GetMessage(&lpMsg, NULL, 0, 0))
        {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
        break;

    //�A���[�����[�h�̍쐬�E�`��
    case ALARM_OPTION:
        if (flag == 0)
        {
            if (!MyRegisterClass(AlarmWC, hInstance, TEXT("AlarmWindow"), ALARM_PROC))
                return FALSE;
        }
        if (!AlarmInstance(hInstance, TEXT("AlarmWindow"), nCmdShow, TEXT("�A���[����ݒ肵�Ă��������@��)9��00�� => 0900")))
            return FALSE;
        while (GetMessage(&lpMsg, NULL, 0, 0))
        {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
        break;

    //�^�C�}�[��ʂ̍쐬�E�`��
    case TIMER_OPTION:
        if (flag == 0)
        {
            if (!MyRegisterClass(TimerWC, hInstance, TEXT("TimerWindow"), TIMER_PROC))
                return FALSE;
        }
        sprintf(strtime, TEXT("�ݒ莞���� %d�� %d���ł�"), set_time.wHour, set_time.wMinute);
        if (!TimerInstance(hInstance, TEXT("TimerWindow"), nCmdShow, strtime))
            return FALSE;
        while (GetMessage(&lpMsg, NULL, 0, 0))
        {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
        break;

    //�w�K���[�h�̍쐬�E�`��
    case LEARNING_OPTION:
        if (flag == 0)
        {
            if (!MyRegisterClass(LearningWC, hInstance, TEXT("LeaningWindow"), LEARNING_PROC))
                return FALSE;
        }
        if (!LearningInstance(hInstance, TEXT("LeaningWindow"), nCmdShow, TEXT("�w�K���鍀�ڂ�I�����Ă�������")))
            return FALSE;
        while (GetMessage(&lpMsg, NULL, 0, 0))
        {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
        break;

    //���̍쐬�E�`��
    case QUESTION_OPTION:
        if (flag == 0)
        {
            if (!MyRegisterClass(QuestionWC, hInstance, TEXT("QuestionWindow"), question_PROC))
                return FALSE;
        }
        wsprintf(QTEXT, TEXT("���%d"), count);
        if (!QuestionInstance(hInstance, TEXT("QuestionWindow"), nCmdShow, QTEXT))
            return FALSE;
        while (GetMessage(&lpMsg, NULL, 0, 0))
        {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
        break;

    //�p��(part1�Epart2�Epart5)���̍쐬�E�`��
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

    //�p��(part3�Epart4�Epart6�Epart7)���̍쐬�E�`��
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