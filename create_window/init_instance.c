#include <windows.h>
#include <stdio.h>
#include "window_def.h"
#include "../mode_function/qa_def.h"

//���j���[�E�C���h�E�̍쐬
BOOL MenuInstance(HINSTANCE hInstance, TCHAR *MenuClassName, int nCmdShow, LPVOID menu)
{
    //�n���h���̒�`
    HWND hwnd;
    TCHAR errorstr[64];

    hwnd = CreateWindow(MenuClassName, TEXT("���j���[���"),
                        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                        100, 100, WINDOW_WIDTH, WINDOW_HEIGHT,
                        NULL, NULL, hInstance, (LPVOID)menu);

    CreateWindow(TEXT("BUTTON"), TEXT("�A���[�����[�h"),
                 WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 200, 175, 400, 300,
                 hwnd, (HMENU)ALARM_OPTION, hInstance, (LPVOID)menu);

    CreateWindow(TEXT("BUTTON"), TEXT("�w�K���[�h"),
                 WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 600, 175, 400, 300,
                 hwnd, (HMENU)LEARNING_OPTION, hInstance, (LPVOID)menu);

    if (!hwnd)
        return FALSE;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    return TRUE;
}

//�A���[���E�B���h�E�̍쐬
BOOL AlarmInstance(HINSTANCE hInstance, TCHAR *AlarmClassName, int nCmdShow, LPVOID alarm)
{
    //�n���h���̒�`
    HWND hwnd;
    TCHAR errorstr[64];

    hwnd = CreateWindow(AlarmClassName, TEXT("�A���[�����[�h"),
                        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                        100, 100, WINDOW_WIDTH, WINDOW_HEIGHT,
                        NULL, NULL, hInstance, (LPVOID)alarm);

    CreateWindow(TEXT("BUTTON"), TEXT("����"),
                 WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 800, 400, 100, 50,
                 hwnd, (HMENU)TIMER_OPTION, hInstance, (LPVOID)alarm);

    if (!hwnd)
    {
        int error = GetLastError();
        wsprintf(errorstr, TEXT("Error code:%d"), error);
        MessageBox(NULL, errorstr, TEXT("�E�B���h�E���쐬�ł��܂���ł���"), MB_OK);
        return FALSE;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    return TRUE;
}

//�^�C�}�[�E�B���h�E�̍쐬
BOOL TimerInstance(HINSTANCE hInstance, TCHAR *TimerClassName, int nCmdShow, LPVOID timer)
{
    //�n���h���̒�`
    HWND hwnd;
    TCHAR errorstr[64];

    hwnd = CreateWindow(TimerClassName, TEXT("�^�C�}�[���"),
                        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                        100, 100, WINDOW_WIDTH, WINDOW_HEIGHT,
                        NULL, NULL, hInstance, (LPVOID)timer);

    if (!hwnd)
    {
        int error = GetLastError();
        wsprintf(errorstr, TEXT("Error code:%d"), error);
        MessageBox(NULL, errorstr, TEXT("�E�B���h�E���쐬�ł��܂���ł���"), MB_OK);
        return FALSE;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    return TRUE;
}

//�w�K�E�B���h�E�̍쐬
BOOL LearningInstance(HINSTANCE hInstance, TCHAR *LearningClassName, int nCmdShow, LPVOID learning)
{
    //�n���h���̒�`
    HWND hwnd;
    TCHAR errorstr[64];

    hwnd = CreateWindow(LearningClassName, TEXT("�w�K���[�h"),
                        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                        100, 100, WINDOW_WIDTH, WINDOW_HEIGHT,
                        NULL, NULL, hInstance, (LPVOID)learning);

    CreateWindow(TEXT("BUTTON"), TEXT("���w"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                 200, 90, 380, 360, hwnd, NULL, hInstance, NULL);

    CreateWindow(TEXT("BUTTON"), TEXT("�l�����Z"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 215, 120, 350, 40, hwnd, (HMENU)MATH_BASIC_OPTION, hInstance, NULL);

    CreateWindow(TEXT("BUTTON"), TEXT("�f��������"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 215, 160, 350, 40, hwnd, (HMENU)MATH_FACTORISE_OPTION, hInstance, NULL);

    CreateWindow(TEXT("BUTTON"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 215, 200, 350, 40, hwnd, (HMENU)MATH_DEFFERENT_OPTION, hInstance, NULL);

    CreateWindow(TEXT("BUTTON"), TEXT("�ϕ�"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 215, 240, 350, 40, hwnd, (HMENU)MATH_INTEGRAL_OPTION, hInstance, NULL);

    CreateWindow(TEXT("BUTTON"), TEXT("�p��(TOEIC���)"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                 620, 90, 380, 360, hwnd, NULL, hInstance, NULL);

    CreateWindow(TEXT("BUTTON"), TEXT("Part1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 635, 120, 350, 40, hwnd, (HMENU)ENGLISH_PART1_OPTION, hInstance, NULL);

    CreateWindow(TEXT("BUTTON"), TEXT("Part2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 635, 160, 350, 40, hwnd, (HMENU)ENGLISH_PART2_OPTION, hInstance, NULL);

    CreateWindow(TEXT("BUTTON"), TEXT("Part3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 635, 200, 350, 40, hwnd, (HMENU)ENGLISH_PART3_OPTION, hInstance, NULL);

    CreateWindow(TEXT("BUTTON"), TEXT("Part4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 635, 240, 350, 40, hwnd, (HMENU)ENGLISH_PART4_OPTION, hInstance, NULL);

    CreateWindow(TEXT("BUTTON"), TEXT("Part5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 635, 280, 350, 40, hwnd, (HMENU)ENGLISH_PART5_OPTION, hInstance, NULL);

    CreateWindow(TEXT("BUTTON"), TEXT("Part6"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 635, 320, 350, 40, hwnd, (HMENU)ENGLISH_PART6_OPTION, hInstance, NULL);

    CreateWindow(TEXT("BUTTON"), TEXT("Part7"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 635, 360, 350, 40, hwnd, (HMENU)ENGLISH_PART7_OPTION, hInstance, NULL);

    CreateWindow(TEXT("BUTTON"), TEXT("�p�P��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 635, 400, 350, 40, hwnd, (HMENU)ENGLISH_WORD_OPTION, hInstance, NULL);

    if (!hwnd)
    {
        int error = GetLastError();
        wsprintf(errorstr, TEXT("Error code:%d"), error);
        MessageBox(NULL, errorstr, TEXT("�E�B���h�E���쐬�ł��܂���ł���"), MB_OK);
        return FALSE;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    return TRUE;
}

//���E�B���h�E�̍쐬
BOOL QuestionInstance(HINSTANCE hInstance, TCHAR *QuestionClassName, int nCmdShow, LPVOID question)
{
    //�n���h���̒�`
    HWND hwnd;
    TCHAR errorstr[64];

    hwnd = CreateWindow(QuestionClassName, TEXT("��������"),
                        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                        100, 100, WINDOW_WIDTH, WINDOW_HEIGHT,
                        NULL, NULL, hInstance, (LPVOID)question);

    CreateWindow(TEXT("BUTTON"), TEXT(Answer[question_num[0]]),
                 WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 200, 400, 200, 100,
                 hwnd, (HMENU)BUTTON_ID0, hInstance, (LPVOID)question);

    CreateWindow(TEXT("BUTTON"), TEXT(Answer[question_num[1]]),
                 WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 400, 400, 200, 100,
                 hwnd, (HMENU)BUTTON_ID1, hInstance, (LPVOID)question);

    CreateWindow(TEXT("BUTTON"), TEXT(Answer[question_num[2]]),
                 WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 600, 400, 200, 100,
                 hwnd, (HMENU)BUTTON_ID2, hInstance, (LPVOID)question);

    CreateWindow(TEXT("BUTTON"), TEXT(Answer[question_num[3]]),
                 WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 800, 400, 200, 100,
                 hwnd, (HMENU)BUTTON_ID3, hInstance, (LPVOID)question);

    if (!hwnd)
    {
        int error = GetLastError();
        wsprintf(errorstr, TEXT("Error code:%d"), error);
        MessageBox(NULL, errorstr, TEXT("�E�B���h�E���쐬�ł��܂���ł���"), MB_OK);
        return FALSE;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    return TRUE;
}

BOOL Eng1ItemInstance(HINSTANCE hInstance, TCHAR *QuestionClassName, int nCmdShow, LPVOID eng_1item_question)
{
    //�n���h���̒�`
    HWND hwnd;
    TCHAR errorstr[64];

    hwnd = CreateWindow(QuestionClassName, TEXT("Question"),
                        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                        100, 100, WINDOW_WIDTH, WINDOW_HEIGHT,
                        NULL, NULL, hInstance, (LPVOID)eng_1item_question);

    CreateWindow(TEXT("BUTTON"), TEXT("A"),
                 WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 200, 500, 200, 50,
                 hwnd, (HMENU)BUTTON_ID0, hInstance, (LPVOID)eng_1item_question);

    CreateWindow(TEXT("BUTTON"), TEXT("B"),
                 WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 400, 500, 200, 50,
                 hwnd, (HMENU)BUTTON_ID1, hInstance, (LPVOID)eng_1item_question);

    CreateWindow(TEXT("BUTTON"), TEXT("C"),
                 WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 600, 500, 200, 50,
                 hwnd, (HMENU)BUTTON_ID2, hInstance, (LPVOID)eng_1item_question);

    if (lstrcmp(sector, "part2") != 0) //part2��A,B,C�̂�
    {
        CreateWindow(TEXT("BUTTON"), TEXT("D"),
                     WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                     800, 500, 200, 50,
                     hwnd, (HMENU)BUTTON_ID3, hInstance, (LPVOID)eng_1item_question);
    }

    if (!hwnd)
    {
        int error = GetLastError();
        wsprintf(errorstr, TEXT("ERROR CODE:%d"), error);
        MessageBox(NULL, errorstr, TEXT("ERROR"), MB_OK);
        return FALSE;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    return TRUE;
}

BOOL Eng3ItemInstance(HINSTANCE hInstance, TCHAR *QuestionClassName, int nCmdShow, LPVOID eng_3item_question)
{
    //�n���h���̒�`
    HWND hwnd;
    TCHAR errorstr[64];

    hwnd = CreateWindow(QuestionClassName, TEXT("Question"),
                        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                        100, 100, WINDOW_WIDTH, WINDOW_HEIGHT,
                        NULL, NULL, hInstance, (LPVOID)eng_3item_question);

    CreateWindow(TEXT("BUTTON"), TEXT("Q1"),
                 WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                 950, 30, 200, 150,
                 hwnd, NULL, hInstance, (LPVOID)eng_3item_question);

    CreateWindow(TEXT("BUTTON"), TEXT("Q2"),
                 WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                 950, 210, 200, 150,
                 hwnd, NULL, hInstance, (LPVOID)eng_3item_question);

    CreateWindow(TEXT("BUTTON"), TEXT("Q3"),
                 WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                 950, 390, 200, 150,
                 hwnd, NULL, hInstance, (LPVOID)eng_3item_question);

    if (!hwnd)
    {
        int error = GetLastError();
        wsprintf(errorstr, TEXT("Error code:%d"), error);
        MessageBox(NULL, errorstr, TEXT("�E�B���h�E���쐬�ł��܂���ł���"), MB_OK);
        return FALSE;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    return TRUE;
}