#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <mmsystem.h>
#include "../../mode_function/sound.h"
#include "../window_def.h"
#include "window_procedure.h"

//�^�C�}�[�v���V�[�W��
LRESULT CALLBACK TimerProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;                  //�f�o�C�X�R���e�L�X�g
    static HDC mhdc;          //�������f�o�C�X�R���e�L�X�g
    PAINTSTRUCT ps;           //�`��Ɋւ�����
    RECT rctSize;             //�����`�̈�̘_�����W
    SYSTEMTIME now_time;      //�ݒ莞���Ƃ̔�r�p
    static TCHAR strTime[64]; //���ݎ����\���p
    static HBITMAP hbitmap;   //�r�b�g�}�b�v�n���h��
    static BITMAP bitmap;     //�r�b�g�}�b�v�\����
    static int width, height; //bmp�摜�̕��E����
    int id;

    switch (msg)
    {
    case WM_CLOSE: //����{�^�����͎�
        PlaySound(close_window_sound, NULL, SND_FILENAME | SND_ASYNC);
        id = MessageBox(hwnd, TEXT("�^�C�}�[���I�����܂���?"),
                        TEXT("�m�F"), MB_YESNO | MB_ICONEXCLAMATION);
        if (id == IDYES)
            DestroyWindow(hwnd);
        break;

    case WM_DESTROY: //�E�B���h�E���I��
        DeleteObject(hbitmap);
        DeleteDC(mhdc);
        PostQuitMessage(0);
        break;

    case WM_CREATE: //�E�C���h�E�̐���
    {
        //�t�@�C���ǂݍ���
        hbitmap = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, TEXT("sleeping_hamster"));
        //�摜�T�C�Y�擾
        GetObject(hbitmap, sizeof(BITMAP), &bitmap);
        width = bitmap.bmWidth;
        height = bitmap.bmHeight;

        //�������f�o�C�X�R���e�L�X�g���쐬
        mhdc = CreateCompatibleDC(NULL);
        //�������f�o�C�X�R���e�L�X�g�Ƀr�b�g�}�b�v��ݒ�
        SelectObject(mhdc, hbitmap);

        CREATESTRUCT *cp;
        cp = (CREATESTRUCT *)lParam;
        SetWindowLongPtr(hwnd, 0, (LONG)cp->lpCreateParams);
        SetTimer(hwnd, 1, 300, NULL);
        return 0;
    }

    case WM_TIMER: //�����ω���
        GetLocalTime(&now_time);
        wsprintf(strTime, "���ݎ���\n%d�N %d�� %d��\n%d�� %d�� %d�b",
                 now_time.wYear, now_time.wMonth, now_time.wDay,
                 now_time.wHour, now_time.wMinute, now_time.wSecond);

        // ���ԂɂȂ�����E�B���h�E�I��
        if (set_time.wHour == now_time.wHour &&
            set_time.wMinute == now_time.wMinute)
            DestroyWindow(hwnd);

        //�E�B���h�E�ĕ`��
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;

    case WM_PAINT: //�E�B���h�E�`��
        hdc = BeginPaint(hwnd, &ps);
        //�t�H���g�̐ݒ�
        SelectObject(hdc, headfont);

        //bitmap�摜�̐ݒ�
        BitBlt(hdc, 400, 150, width, height, mhdc, 0, 0, SRCCOPY);

        //�����̐ݒ�
        GetClientRect(hwnd, &rctSize);
        DrawText(hdc, strTime, -1, &rctSize, DT_RIGHT); //���ݎ����̕\��

        //���o���̐ݒ�
        TCHAR *buf = (TCHAR *)GetWindowLongPtr(hwnd, 0);
        TextOut(hdc, 20, 10, buf, (int)_tcslen(buf));
        EndPaint(hwnd, &ps);
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
