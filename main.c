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
    WNDCLASSEX MenuWC, AlarmWC, LearningWC, QuestionWC; //ウィンドウクラスの定義
    TCHAR Lesult[64];                                   //学習モードの結果
    TCHAR import_file[64];
    SYSTEMTIME start_time;         //開始時刻
    SYSTEMTIME close_time;         //終了時刻
    SYSTEMTIME record_time;        //結果
    MSG lpMsg;                     //メッセージ
    int option1, option2, count;   //各モードの選択オプション変数
    int correct_ans = 0, ans = 0;  //正解数カウント
    double percentage_correct_ans; //正答率
    int menu_flag = 0, alarm_flag = 0, timer_flag = 0, learning_flag = 0,
        question_flag = 0, english_1item_flag = 0, english_3item_flag = 0; //ウィンドウクラスの登録を1回だけ行うためのフラグ
    int max_question_num;                                                  //問題数
    int n, buf[32];

    headfont = CreateFont(
        40, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE,
        SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        VARIABLE_PITCH | FF_ROMAN, (LPCTSTR) "メイリオ");

    // mainfont = CreateFont(
    //     20, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE,
    //     SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
    //     CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
    //     VARIABLE_PITCH | FF_ROMAN, (LPCTSTR) "メイリオ");

    //メニュー画面で閉じるボタンを押すと終了
    while (TRUE)
    {
        //変数の初期化
        option1 = 0;
        option2 = 0;
        count = 1;

        //メニューウィンドウの表示
        option1 = MakeWindow(hInstance, nCmdShow, lpMsg, MENU_OPTION, count, menu_flag);
        menu_flag = 1;
        switch (option1)
        {
        //アラームモード選択時
        case ALARM_OPTION:
            //アラームウィンドウの表示
            option2 = MakeWindow(hInstance, nCmdShow, lpMsg, ALARM_OPTION, count, alarm_flag);
            alarm_flag = 1;
            switch (option2)
            {
            //タイマー設定完了時
            case TIMER_OPTION:
                //タイマーウィンドウの表示
                MakeWindow(hInstance, nCmdShow, lpMsg, TIMER_OPTION, count, timer_flag);
                timer_flag = 1;

                srand(time(NULL));
                option2 = 20 + rand() % 1; //optionの項目をランダムで数学の項目に設定

                if (!SetFile(option2, import_file))
                    return -1;

                GetLocalTime(&start_time);
                max_question_num = import_csv(import_file, option2); //csvファイルのインポート
                //問題が解けたら終了
                while (TRUE)
                {
                    //アラーム再生
                    PlaySound(TEXT("Notification.Looping.Alarm2"), NULL, SND_ALIAS | SND_LOOP | SND_ASYNC);
                    //csvファイルから問題数を取得
                    make_question(max_question_num);
                    ans = MakeWindow(hInstance, nCmdShow, lpMsg, QUESTION_OPTION, count, question_flag); //問題ウィンドウの表示
                    question_flag = 1;
                    if (ans == CORRECT || ans == 0)
                        break;
                    count++;
                }
                //アラーム停止
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
                wsprintf(Lesult, TEXT("おはようございます！\n経過時間は %d分 %d秒です"),
                         record_time.wMinute, record_time.wSecond);
                MessageBox(NULL, Lesult, TEXT("結果"), MB_OK);

                break;

            default:
                return -1;
            }
            break;

        //学習モード選択時
        case LEARNING_OPTION:
            //学習ウインドウの表示
            option2 = MakeWindow(hInstance, nCmdShow, lpMsg, LEARNING_OPTION, count, learning_flag);
            learning_flag = 1;

            if (!SetFile(option2, import_file))
                return -1;

            correct_ans = 0;
            GetLocalTime(&start_time);
            max_question_num = import_csv(import_file, option2); //csvファイルのインポート

            if (!SetFile(option2, import_file))
                return -1;

            //数学・英単語の場合
            if (option2 == MATH_BASIC_OPTION || option2 == MATH_FACTORISE_OPTION || option2 == ENGLISH_WORD_OPTION)
            {
                //QUESTION_NUM問だけ問題を表示
                for (n = 0; n < QUESTION_NUM; n++)
                {
                    make_question(max_question_num);                                                     //問題作成
                    ans = MakeWindow(hInstance, nCmdShow, lpMsg, QUESTION_OPTION, count, question_flag); //問題ウィンドウの表示
                    question_flag = 1;
                    if (ans == CORRECT)
                        correct_ans++;
                    else if (ans == 0)
                        break;
                    count++;
                }
            }

            //一問一答形式(part1,part2,part5,英単語)の問題
            else if (option2 == ENGLISH_PART1_OPTION || option2 == ENGLISH_PART2_OPTION ||
                     option2 == ENGLISH_PART5_OPTION)
            {
                for (int n = 0; n < max_question_num; n++)
                    buf[n] = n + 1;

                //QUESTION_NUM問だけ問題を表示
                for (n = 0; n < QUESTION_NUM; n++)
                {
                    answer_num = set_answer_num(buf, max_question_num);                                            //問題作成
                    ans = MakeWindow(hInstance, nCmdShow, lpMsg, ENGLISH_1ITEM_OPTION, count, english_1item_flag); //問題ウィンドウの表示
                    english_1item_flag = 1;
                    if (ans == CORRECT)
                        correct_ans++;
                    else if (ans == 0)
                        break;
                    count++;
                }
            }

            //一問三答形式(part3,part4,part6,part7)の問題
            else if (option2 == ENGLISH_PART3_OPTION || option2 == ENGLISH_PART4_OPTION ||
                     option2 == ENGLISH_PART6_OPTION || option2 == ENGLISH_PART7_OPTION) //一問一答形式の問題
            {
                for (int n = 0; n < max_question_num; n++)
                    buf[n] = n + 1;
                answer_num = set_answer_num(buf, max_question_num);                                                    //問題作成
                correct_ans = MakeWindow(hInstance, nCmdShow, lpMsg, ENGLISH_3ITEM_OPTION, count, english_3item_flag); //問題ウィンドウの表示
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

            //結果をメッセージ出力
            if (option2 == ENGLISH_PART3_OPTION || option2 == ENGLISH_PART4_OPTION ||
                option2 == ENGLISH_PART6_OPTION || option2 == ENGLISH_PART7_OPTION) //一問一答形式の問題
            {
                percentage_correct_ans = 100 * correct_ans / 3;
                sprintf(Lesult, TEXT("正解数: %d/%d\n正答率：%.1f％\n記録： %d分 %d秒"),
                        correct_ans, 3, percentage_correct_ans, record_time.wMinute, record_time.wSecond);
                MessageBox(NULL, Lesult, TEXT("結果"), MB_OK);
            }
            else
            {
                percentage_correct_ans = 100 * correct_ans / QUESTION_NUM;
                sprintf(Lesult, TEXT("正解数: %d/%d\n正答率：%.1f％\n記録： %d分 %d秒"),
                        correct_ans, QUESTION_NUM, percentage_correct_ans, record_time.wMinute, record_time.wSecond);
                MessageBox(NULL, Lesult, TEXT("結果"), MB_OK);
            }
            break;

        default:
            return 0;
        }
    }
    return (int)lpMsg.wParam;
}
