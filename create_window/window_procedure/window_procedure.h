#ifndef _WINDOW_PROCEDURE_H
#define _WINDOW_PROCEDURE_H

//      �E�B���h�E�v���V�[�W���[

LRESULT CALLBACK MenuProc(HWND Menuhwnd,  //���b�Z�[�W�����������E�B���h�E�̃n���h��
                          UINT msg,       //���b�Z�[�W
                          WPARAM wParam,  //���b�Z�[�W�̕t�����
                          LPARAM lParam); //long�^�Ɠ��`

LRESULT CALLBACK AlarmProc(HWND Alarmhwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK TimerProc(HWND Timerhwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LearningProc(HWND Learninghwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK QuestionProc(HWND Questionhwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Eng_1ItemProc(HWND Eng_1Itemhwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Eng_3ItemProc(HWND Eng_3Itemhwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif //_WINDOW_PROCEDURE_H