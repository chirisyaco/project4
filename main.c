#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mmsystem.h>
#include "mode_function/set_file.h"
#include "mode_function/qa_def.h"
#include "mode_function/make_question.h"
#include "create_window/window_def.h"
#include "create_window/make_window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, TCHAR *lpszCmdLine, int nCmdShow)
{
    WNDCLASSEX MenuWC, AlarmWC, LearningWC, QuestionWC; //�E�B���h�E�N���X�̒�`
    TCHAR Lesult[64];                                   //�w�K���[�h�̌���
    TCHAR import_file[64];
    SYSTEMTIME start_time;         //�J�n����
    SYSTEMTIME close_time;         //�I������
    SYSTEMTIME record_time;        //����
    MSG lpMsg;                     //���b�Z�[�W
    int option1, option2, count;   //�e���[�h�̑I���I�v�V�����ϐ�
    int correct_ans = 0, ans = 0;  //���𐔃J�E���g
    double percentage_correct_ans; //������
    int menu_flag = 0, alarm_flag = 0, timer_flag = 0, learning_flag = 0,
        question_flag = 0, english_1item_flag = 0, english_3item_flag = 0; //�E�B���h�E�N���X�̓o�^��1�񂾂��s�����߂̃t���O
    int max_question_num;                                                  //��萔
    int n, buf[32];

    headfont = CreateFont(
        40, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE,
        SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        VARIABLE_PITCH | FF_ROMAN, (LPCTSTR) "���C���I");

    // mainfont = CreateFont(
    //     20, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE,
    //     SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
    //     CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
    //     VARIABLE_PITCH | FF_ROMAN, (LPCTSTR) "���C���I");

    //���j���[��ʂŕ���{�^���������ƏI��
    while (TRUE)
    {
        //�ϐ��̏�����
        option1 = 0;
        option2 = 0;
        count = 1;

        //���j���[�E�B���h�E�̕\��
        option1 = MakeWindow(hInstance, nCmdShow, lpMsg, MENU_OPTION, count, menu_flag);
        menu_flag = 1;
        switch (option1)
        {
        //�A���[�����[�h�I����
        case ALARM_OPTION:
            //�A���[���E�B���h�E�̕\��
            option2 = MakeWindow(hInstance, nCmdShow, lpMsg, ALARM_OPTION, count, alarm_flag);
            alarm_flag = 1;
            switch (option2)
            {
            //�^�C�}�[�ݒ芮����
            case TIMER_OPTION:
                //�^�C�}�[�E�B���h�E�̕\��
                MakeWindow(hInstance, nCmdShow, lpMsg, TIMER_OPTION, count, timer_flag);
                timer_flag = 1;

                srand(time(NULL));
                option2 = 20 + rand() % 1; //option�̍��ڂ������_���Ő��w�̍��ڂɐݒ�

                if (!SetFile(option2, import_file))
                    return -1;

                GetLocalTime(&start_time);
                max_question_num = import_csv(import_file, option2); //csv�t�@�C���̃C���|�[�g
                //��肪��������I��
                while (TRUE)
                {
                    //�A���[���Đ�
                    PlaySound(TEXT("Notification.Looping.Alarm2"), NULL, SND_ALIAS | SND_LOOP | SND_ASYNC);
                    //csv�t�@�C�������萔���擾
                    make_question(max_question_num);
                    ans = MakeWindow(hInstance, nCmdShow, lpMsg, QUESTION_OPTION, count, question_flag); //���E�B���h�E�̕\��
                    question_flag = 1;
                    if (ans == CORRECT || ans == 0)
                        break;
                    count++;
                }
                //�A���[����~
                PlaySound(NULL, NULL, 0);

                GetLocalTime(&close_time);
                if (close_time.wMinute < start_time.wMinute)
                    record_time.wMinute = 60 + close_time.wMinute - start_time.wMinute;
                else
                    record_time.wMinute = close_time.wMinute - start_time.wMinute;
                if (close_time.wSecond < start_time.wSecond)
                {
                    record_time.wSecond = 60 + close_time.wSecond - start_time.wSecond;
                    record_time.wMinute -= 1;
                }
                else
                    record_time.wSecond = close_time.wSecond - start_time.wSecond;
                wsprintf(Lesult, TEXT("���͂悤�������܂��I\n�o�ߎ��Ԃ� %d�� %d�b�ł�"),
                         record_time.wMinute, record_time.wSecond);
                MessageBox(NULL, Lesult, TEXT("����"), MB_OK);

                break;

            default:
                return -1;
            }
            break;

        //�w�K���[�h�I����
        case LEARNING_OPTION:
            //�w�K�E�C���h�E�̕\��
            option2 = MakeWindow(hInstance, nCmdShow, lpMsg, LEARNING_OPTION, count, learning_flag);
            learning_flag = 1;

            if (!SetFile(option2, import_file))
                return -1;

            correct_ans = 0;
            GetLocalTime(&start_time);
            max_question_num = import_csv(import_file, option2); //csv�t�@�C���̃C���|�[�g

            if (!SetFile(option2, import_file))
                return -1;

            //���w�E�p�P��̏ꍇ
            if (option2 == MATH_BASIC_OPTION || option2 == MATH_FACTORISE_OPTION || option2 == ENGLISH_WORD_OPTION)
            {
                //QUESTION_NUM�₾������\��
                for (n = 0; n < QUESTION_NUM; n++)
                {
                    make_question(max_question_num);                                                     //���쐬
                    ans = MakeWindow(hInstance, nCmdShow, lpMsg, QUESTION_OPTION, count, question_flag); //���E�B���h�E�̕\��
                    question_flag = 1;
                    if (ans == CORRECT)
                        correct_ans++;
                    else if (ans == 0)
                        break;
                    count++;
                }
            }

            //���ꓚ�`��(part1,part2,part5,�p�P��)�̖��
            else if (option2 == ENGLISH_PART1_OPTION || option2 == ENGLISH_PART2_OPTION ||
                     option2 == ENGLISH_PART5_OPTION)
            {
                for (int n = 0; n < max_question_num; n++)
                    buf[n] = n + 1;

                //QUESTION_NUM�₾������\��
                for (n = 0; n < QUESTION_NUM; n++)
                {
                    answer_num = set_answer_num(buf, max_question_num);                                            //���쐬
                    ans = MakeWindow(hInstance, nCmdShow, lpMsg, ENGLISH_1ITEM_OPTION, count, english_1item_flag); //���E�B���h�E�̕\��
                    english_1item_flag = 1;
                    if (ans == CORRECT)
                        correct_ans++;
                    else if (ans == 0)
                        break;
                    count++;
                }
            }

            //���O���`��(part3,part4,part6,part7)�̖��
            else if (option2 == ENGLISH_PART3_OPTION || option2 == ENGLISH_PART4_OPTION ||
                     option2 == ENGLISH_PART6_OPTION || option2 == ENGLISH_PART7_OPTION) //���ꓚ�`���̖��
            {
                for (int n = 0; n < max_question_num; n++)
                    buf[n] = n + 1;
                answer_num = set_answer_num(buf, max_question_num);                                                    //���쐬
                correct_ans = MakeWindow(hInstance, nCmdShow, lpMsg, ENGLISH_3ITEM_OPTION, count, english_3item_flag); //���E�B���h�E�̕\��
                english_3item_flag = 1;
            }

            GetLocalTime(&close_time);
            if (close_time.wMinute < start_time.wMinute)
                record_time.wMinute = 60 + close_time.wMinute - start_time.wMinute;
            else
                record_time.wMinute = close_time.wMinute - start_time.wMinute;
            if (close_time.wSecond < start_time.wSecond)
            {
                record_time.wSecond = 60 + close_time.wSecond - start_time.wSecond;
                record_time.wMinute -= 1;
            }
            else
                record_time.wSecond = close_time.wSecond - start_time.wSecond;

            //���ʂ����b�Z�[�W�o��
            if (option2 == ENGLISH_PART3_OPTION || option2 == ENGLISH_PART4_OPTION ||
                option2 == ENGLISH_PART6_OPTION || option2 == ENGLISH_PART7_OPTION) //���ꓚ�`���̖��
            {
                percentage_correct_ans = 100 * correct_ans / 3;
                sprintf(Lesult, TEXT("����: %d/%d\n�������F%.1f��\n�L�^�F %d�� %d�b"),
                        correct_ans, 3, percentage_correct_ans, record_time.wMinute, record_time.wSecond);
                MessageBox(NULL, Lesult, TEXT("����"), MB_OK);
            }
            else
            {
                percentage_correct_ans = 100 * correct_ans / QUESTION_NUM;
                sprintf(Lesult, TEXT("����: %d/%d\n�������F%.1f��\n�L�^�F %d�� %d�b"),
                        correct_ans, QUESTION_NUM, percentage_correct_ans, record_time.wMinute, record_time.wSecond);
                MessageBox(NULL, Lesult, TEXT("����"), MB_OK);
            }
            break;

        default:
            return 0;
        }
    }
    return (int)lpMsg.wParam;
}
