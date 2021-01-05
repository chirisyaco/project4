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
    HDC hdc;                                         //�f�o�C�X�R���e�L�X�g
    static HDC mhdc;                                 //�������f�o�C�X�R���e�L�X�g
    PAINTSTRUCT ps;                                  //�`��Ɋւ�����
    static HBITMAP hbitmap;                          //�r�b�g�}�b�v�n���h��
    static BITMAP bitmap;                            //�r�b�g�}�b�v�\����
    static int width, height;                        //bmp�摜�̕��E����
    int start_pointx, start_pointy;                  //bmp�摜�̕`��J�n�ʒu
    TCHAR question[64];                              //bmp�摜�̃p�X
    TCHAR correctstr[] = TEXT("�����ł��I");         //�������̃e�L�X�g
    TCHAR wrongstr[] = TEXT("�s�����ł�\n�����F%s"); //�s�������̃e�L�X�g
    int id;

    switch (msg)
    {
    case WM_CLOSE: //����{�^�����͎�
        PlaySound(close_window_sound, NULL, SND_FILENAME | SND_ASYNC);
        id = MessageBox(hwnd, TEXT("�����I�����܂���?"),
                        TEXT("�m�F"), MB_YESNO | MB_ICONEXCLAMATION);
        if (id == IDYES)
            DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_CREATE:
    {
        //�t�@�C���ǂݍ���
        if (lstrcmp(sector, "word") == 0) //�p�P�ꂾ��
            wsprintf(question, TEXT("english_%s_Q%d"), sector, answer_num);
        else //���̑�(���w���)
            wsprintf(question, TEXT("math_%s_Q%d"), sector, answer_num);

        hbitmap = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, question);
        //�摜�T�C�Y�擾
        GetObject(hbitmap, sizeof(BITMAP), &bitmap);
        width = bitmap.bmWidth;
        height = bitmap.bmHeight;

        //�������f�o�C�X�R���e�L�X�g���쐬
        mhdc = CreateCompatibleDC(NULL);
        //�������f�o�C�X�R���e�L�X�g�Ƀr�b�g�}�b�v��ݒ�
        SelectObject(mhdc, hbitmap);

        CREATESTRUCT *cp;
        cp = (CREATESTRUCT *)lParam; //�E�B���h�E�̐����𑱂��邩�ǂ�����₢���킹
        SetWindowLongPtr(hwnd, 0, (LONG)cp->lpCreateParams);
        break;
    }

    case WM_COMMAND: //�{�^�����͎�
        switch (LOWORD(wParam))
        {
        case BUTTON_ID0:
            if (question_num[0] == answer_num) //������
            {
                PlaySound(correct_sound, NULL, SND_FILENAME | SND_ASYNC);
                MessageBox(hwnd, correctstr, TEXT("����"), MB_OK);
                DestroyWindow(hwnd);
                PostQuitMessage(CORRECT);
                break;
            }
            else //�s������
            {
                PlaySound(wrong_sound, NULL, SND_FILENAME | SND_ASYNC);
                sprintf(wrongstr, TEXT("�s�����ł�\n�����F%s"), Answer[answer_num]);
                MessageBox(hwnd, wrongstr, TEXT("����"), MB_OK);
                DestroyWindow(hwnd);
                PostQuitMessage(WRONG);
                break;
            }
        case BUTTON_ID1:
            if (question_num[1] == answer_num)
            {
                PlaySound(correct_sound, NULL, SND_FILENAME | SND_ASYNC);
                MessageBox(hwnd, correctstr, TEXT("����"), MB_OK);
                DestroyWindow(hwnd);
                PostQuitMessage(CORRECT);
                break;
            }
            else
            {
                PlaySound(wrong_sound, NULL, SND_FILENAME | SND_ASYNC);
                sprintf(wrongstr, TEXT("�s�����ł�\n�����F%s"), Answer[answer_num]);
                MessageBox(hwnd, wrongstr, TEXT("����"), MB_OK);
                DestroyWindow(hwnd);
                PostQuitMessage(WRONG);
                break;
            }
        case BUTTON_ID2:
            if (question_num[2] == answer_num)
            {
                PlaySound(correct_sound, NULL, SND_FILENAME | SND_ASYNC);
                MessageBox(hwnd, correctstr, TEXT("����"), MB_OK);
                DestroyWindow(hwnd);
                PostQuitMessage(CORRECT);
                break;
            }
            else
            {
                PlaySound(wrong_sound, NULL, SND_FILENAME | SND_ASYNC);
                sprintf(wrongstr, TEXT("�s�����ł�\n�����F%s"), Answer[answer_num]);
                MessageBox(hwnd, wrongstr, TEXT("����"), MB_OK);
                DestroyWindow(hwnd);
                PostQuitMessage(WRONG);
                break;
            }
        case BUTTON_ID3:
            if (question_num[3] == answer_num)
            {
                PlaySound(correct_sound, NULL, SND_FILENAME | SND_ASYNC);
                MessageBox(hwnd, correctstr, TEXT("����"), MB_OK);
                DestroyWindow(hwnd);
                PostQuitMessage(CORRECT);
                break;
            }
            else
            {
                PlaySound(wrong_sound, NULL, SND_FILENAME | SND_ASYNC);
                sprintf(wrongstr, TEXT("�s�����ł�\n�����F%s"), Answer[answer_num]);
                MessageBox(hwnd, wrongstr, TEXT("����"), MB_OK);
                DestroyWindow(hwnd);
                PostQuitMessage(WRONG);
                break;
            }
        }
        break;

    case WM_PAINT: //�E�B���h�E�̕`��
        hdc = BeginPaint(hwnd, &ps);
        SelectObject(hdc, headfont);

        //bitmap�摜�̐ݒ�
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
