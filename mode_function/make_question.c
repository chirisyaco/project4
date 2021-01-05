#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "make_question.h"
#include "qa_def.h"
#include "../create_window/window_def.h"

//問題を作成
void make_question(int max_question_num)
{
    for (int n = 0; n < max_question_num; n++)
        question_num[n] = n + 1;
    shuffle(question_num, max_question_num);
    answer_num = set_answer_num(question_num, 4);
}

//csvファイル読み込み
int import_csv(TCHAR import_file[], int option)
{
    int n;
    int max_question_num = 0;
    FILE *csv;

    csv = fopen(import_file, "r");
    if (csv == NULL)
    {
        MessageBox(NULL, TEXT("ファイルが開けません"), NULL, MB_ICONEXCLAMATION | MB_OK);
        exit(-1);
    }
    fscanf(csv, "%s ", &Answer[0]);

    if (option == ENGLISH_PART3_OPTION || option == ENGLISH_PART4_OPTION ||
        option == ENGLISH_PART6_OPTION || option == ENGLISH_PART7_OPTION) //一問三答問題の場合
    {
        for (n = 1;; n++)
        {

            if (fscanf(csv, "%c,%c,%c ", &Answer[n][0], &Answer[n][1], &Answer[n][2]) == EOF)
                break;
            max_question_num++;
        }
    }
    else //その他の場合
    {
        for (n = 1;; n++)
        {

            if (fscanf(csv, "%s", &Answer[n]) == EOF)
                break;
            max_question_num++;
        }
    }
    return max_question_num;
}

//番号をシャッフルする
void shuffle(int array[], int size)
{
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        int j = rand() % size;
        int t = array[i];
        array[i] = array[j];
        array[j] = t;
    }
}

//答えを決定
int set_answer_num(int question_num[], int size)
{
    int n;
    int buf[size];
    for (n = 0; n < size; n++)
        buf[n] = question_num[n];

    shuffle(buf, size);

    return buf[0];
}
