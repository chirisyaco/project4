#ifndef _INIT_INSTANCE_H
#define _INIT_INSTANCE_H

BOOL MenuInstance(HINSTANCE hInstance,  //�C���X�^���X�n���h��
                  TCHAR *MenuClassName, //�E�B���h�E�N���X�̖��O
                  int nCmdShow,         //�A�v���P�[�V�����̏����\�����@�̎w��
                  LPVOID menu);         //void *�Ɠ��`

BOOL AlarmInstance(HINSTANCE hInstance, TCHAR *AlarmClassName, int nCmdShow, LPVOID alarm);
BOOL TimerInstance(HINSTANCE hInstance, TCHAR *TimerClassName, int nCmdShow, LPVOID timer);
BOOL LearningInstance(HINSTANCE hInstance, TCHAR *LearningClassName, int nCmdShow, LPVOID learning);
BOOL QuestionInstance(HINSTANCE hInstance, TCHAR *QuestionClassName, int nCmdShow, LPVOID question);
BOOL Eng1ItemInstance(HINSTANCE hInstance, TCHAR *QuestionClassName, int nCmdShow, LPVOID eng_1item_question);
BOOL Eng3ItemInstance(HINSTANCE hInstance, TCHAR *QuestionClassName, int nCmdShow, LPVOID eng_3item_question);

#endif //_INIT_INSTANCE_H