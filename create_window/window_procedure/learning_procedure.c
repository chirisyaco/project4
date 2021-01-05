#include <windows.h>
#include <tchar.h>
#include <mmsystem.h>
#include "../../mode_function/sound.h"
#include "../window_def.h"
#include "window_procedure.h"

LRESULT CALLBACK LearningProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    MSG lpMsg;      //���b�Z�[�W�̊Ǘ�
    HDC hdc;        //�f�o�C�X�R���e�L�X�g
    PAINTSTRUCT ps; //�`��Ɋւ�����
    int id;

    switch (msg)
    {
    case WM_CLOSE: //����{�^�����͎�
        PlaySound(close_window_sound, NULL, SND_FILENAME | SND_ASYNC);
        id = MessageBox(hwnd, TEXT("�w�K���[�h���I�����܂���?"),
                        TEXT("�m�F"), MB_YESNO | MB_ICONEXCLAMATION);
        if (id == IDYES)
            DestroyWindow(hwnd);
        break;

    case WM_DESTROY: //�E�B���h�E���I��
        PostQuitMessage(0);
        break;

    case WM_CREATE: //�E�C���h�E�̐���
    {
        CREATESTRUCT *cp;
        cp = (CREATESTRUCT *)lParam;
        SetWindowLongPtr(hwnd, 0, (LONG)cp->lpCreateParams);
        return 0;
    }

    case WM_COMMAND: //�{�^�����͎�
        switch (LOWORD(wParam))
        {
        }
        PlaySound(button_click_sound, NULL, SND_FILENAME | SND_ASYNC);
        DestroyWindow(hwnd);
        PostQuitMessage(wParam);
        break;

    case WM_PAINT: //�E�B���h�E�`��
    {
        hdc = BeginPaint(hwnd, &ps);
        SelectObject(hdc, headfont);
        TCHAR *buf = (TCHAR *)GetWindowLongPtr(hwnd, 0);
        TextOut(hdc, 10, 0, buf, (int)_tcslen(buf));
        EndPaint(hwnd, &ps);
        break;
    }

    default:
        return (DefWindowProc(hwnd, msg, wParam, lParam));
    }
    return 0;
}
