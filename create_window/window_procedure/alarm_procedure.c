#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <mmsystem.h>
#include "../../mode_function/sound.h"
#include "../window_def.h"
#include "window_procedure.h"

LRESULT CALLBACK AlarmProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HWND edit;               //�������͗p�̃n���h��
    TCHAR buf[16];           //�o�b�t�@
    TCHAR message[64];       //�A���[���ݒ莞���̃��b�Z�[�W
    MSG lpMsg;               //���b�Z�[�W�̊Ǘ�
    HDC hdc;                 //�f�o�C�X�R���e�L�X�g
    PAINTSTRUCT ps;          //�`��Ɋւ�����
    RECT rctSize;            //���͕�����
    SYSTEMTIME stTime;       //���ݎ����擾
    static TCHAR strTime[8]; //���ݎ���(xx��xx��)

    int id;

    switch (msg)
    {
    case WM_CLOSE: //����{�^�����͎�
        PlaySound(close_window_sound, NULL, SND_FILENAME | SND_ASYNC);
        id = MessageBox(hwnd, TEXT("�A���[�����[�h���I�����܂���?"),
                        TEXT("�m�F"), MB_YESNO | MB_ICONEXCLAMATION);
        if (id == IDYES)
            DestroyWindow(hwnd);
        break;

    case WM_DESTROY: //�E�B���h�E���I��
        PostQuitMessage(0);
        break;

    case WM_CREATE: //�E�C���h�E�̐���
    {
        SetTimer(hwnd, 1, 300, NULL);
        CREATESTRUCT *cp;
        cp = (CREATESTRUCT *)lParam;

        //�A���[�����̓E�B���h�E�̍쐬
        edit = CreateWindow(TEXT("EDIT"), TEXT(""),
                            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                            450, 200, 250, 60, hwnd, (HMENU)1,
                            ((LPCREATESTRUCT)(lParam))->hInstance, NULL);
        SetWindowLongPtr(hwnd, 0, (LONG)cp->lpCreateParams);
        break;
    }

    case WM_COMMAND:                        //�{�^�����͎�
        if (LOWORD(wParam) == TIMER_OPTION) //����{�^�����͎�
        {
            //�e�L�X�g�̎擾
            GetWindowText(edit, buf, 10);

            // ��O����(�����F0000~2359�܂ŁExx60�����E4��)
            if (buf[0] == '\0' || buf[1] == '\0' || buf[2] == '\0' || buf[3] == '\0' ||
                buf[4] != '\0' || buf[0] > '2' || buf[2] > '5')
            {
                PlaySound(error_sound, NULL, SND_FILENAME | SND_ASYNC);
                MessageBox(hwnd, TEXT("�������s���ł�"), TEXT("ERROR"), MB_ICONSTOP | MB_OK);
                return 0;
            }
            else if (buf[0] == '2' && buf[1] > '3')
            {
                PlaySound(error_sound, NULL, SND_FILENAME | SND_ASYNC);
                MessageBox(hwnd, TEXT("�������s���ł�"), TEXT("ERROR"), MB_ICONSTOP | MB_OK);
                return 0;
            }
            set_time.wHour = 10 * (buf[0] - '0') + (buf[1] - '0');
            set_time.wMinute = 10 * (buf[2] - '0') + (buf[3] - '0');

            //�ݒ莞���̊m�F���b�Z�[�W�̕\��
            PlaySound(button_click_sound, NULL, SND_FILENAME | SND_ASYNC);
            sprintf(message, TEXT("�A���[���� %d�� %d���ɐݒ肵�܂����I"), set_time.wHour, set_time.wMinute);
            MessageBox(hwnd, message, TEXT("�m�F"), MB_OK);
            DestroyWindow(hwnd);
            PostQuitMessage(wParam);
        }
        break;

    case WM_TIMER:             //�����ω���
        GetLocalTime(&stTime); //�����擾
        wsprintf(strTime, "���ݎ���\n%d�N %d�� %d��\n%d�� %d�� %d�b",
                 stTime.wYear, stTime.wMonth, stTime.wDay,
                 stTime.wHour, stTime.wMinute, stTime.wSecond);
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;

    case WM_PAINT: //�E�B���h�E�`��
    {
        hdc = BeginPaint(hwnd, &ps);
        SelectObject(hdc, headfont);
        GetClientRect(hwnd, &rctSize);
        DrawText(hdc, strTime, -1, &rctSize, DT_RIGHT); //���ݎ����̕\��
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
