#include <windows.h>
#include <tchar.h>
#include <mmsystem.h>
#include "../window_def.h"
#include "../../mode_function/sound.h"
#include "window_procedure.h"

LRESULT CALLBACK MenuProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    MSG lpMsg;      //���b�Z�[�W�̊Ǘ�
    TEXTMETRIC tm;  //�t�H���g�̏ڍ׏��
    HDC hdc;        //�f�o�C�X�R���e�L�X�g
    PAINTSTRUCT ps; //�`��Ɋւ�����
    int id;

    switch (msg)
    {
    case WM_CLOSE: //����{�^�����͎�
        PlaySound(close_window_sound, NULL, SND_FILENAME | SND_ASYNC);
        id = MessageBox(hwnd, TEXT("�A�v�����I�����܂���?"),
                        TEXT("�m�F"), MB_YESNO | MB_ICONEXCLAMATION);
        if (id == IDYES)
            DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY: //�E�B���h�E���I��
        PostQuitMessage(0);
        break;

    case WM_CREATE: //�E�C���h�E�̐���
    {
        CREATESTRUCT *cp;
        cp = (CREATESTRUCT *)lParam; //�E�B���h�E�̐����𑱂��邩�ǂ�����₢���킹
        SetWindowLongPtr(hwnd, 0, (LONG)cp->lpCreateParams);
        break;
    }

    case WM_COMMAND: //�{�^�����͎�
        switch (LOWORD(wParam))
        {
        case ALARM_OPTION: //�A���[�����[�h�I����
            PlaySound(button_click_sound, NULL, SND_FILENAME | SND_ASYNC);
            DestroyWindow(hwnd);
            PostQuitMessage(wParam);
            break;
        case LEARNING_OPTION: //�w�K���[�h�I����
            PlaySound(button_click_sound, NULL, SND_FILENAME | SND_ASYNC);
            DestroyWindow(hwnd);
            PostQuitMessage(wParam);
            break;
        }
        break;

    case WM_PAINT: //�E�B���h�E�`��
    {
        hdc = BeginPaint(hwnd, &ps);
        SelectObject(hdc, headfont);
        GetTextMetrics(hdc, &tm);
        TCHAR *buf = (TCHAR *)GetWindowLongPtr(hwnd, 0);
        TextOut(hdc, 20, 10, buf, (int)_tcslen(buf));
        EndPaint(hwnd, &ps);
        break;
    }

    default:
        return (DefWindowProc(hwnd, msg, wParam, lParam));
    }
    return 0;
}