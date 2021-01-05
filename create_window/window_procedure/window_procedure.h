#ifndef _WINDOW_PROCEDURE_H
#define _WINDOW_PROCEDURE_H

//      ウィンドウプロシージャー

LRESULT CALLBACK MenuProc(HWND Menuhwnd,  //メッセージが発生したウィンドウのハンドル
                          UINT msg,       //メッセージ
                          WPARAM wParam,  //メッセージの付加情報
                          LPARAM lParam); //long型と同義

LRESULT CALLBACK AlarmProc(HWND Alarmhwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK TimerProc(HWND Timerhwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LearningProc(HWND Learninghwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK QuestionProc(HWND Questionhwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Eng_1ItemProc(HWND Eng_1Itemhwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Eng_3ItemProc(HWND Eng_3Itemhwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif //_WINDOW_PROCEDURE_H