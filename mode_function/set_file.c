#include <stdio.h>
#include <windows.h>
#include "../create_window/window_def.h"
#include "set_file.h"
#include "csv_file.h"

//csvファイル名と分野の指定
int SetFile(int option, TCHAR import_file[64])
{
    switch (LOWORD(option))
    {
    case MATH_BASIC_OPTION:
        strcpy(import_file, math_basic_csv);
        strcpy(sector, "basic");
        break;
    case MATH_FACTORISE_OPTION:
        strcpy(import_file, math_factorize_csv);
        strcpy(sector, "factorize");
        break;
    case MATH_DEFFERENT_OPTION:
        strcpy(import_file, math_defferent_csv);
        strcpy(sector, "defferent");
        break;
    case MATH_INTEGRAL_OPTION:
        strcpy(import_file, math_integral_csv);
        strcpy(sector, "integral");
        break;
    case ENGLISH_PART1_OPTION:
        strcpy(import_file, english_part1_csv);
        strcpy(sector, "part1");
        break;
    case ENGLISH_PART2_OPTION:
        strcpy(import_file, english_part2_csv);
        strcpy(sector, "part2");
        break;
    case ENGLISH_PART3_OPTION:
        strcpy(import_file, english_part3_csv);
        strcpy(sector, "part3");
        break;
    case ENGLISH_PART4_OPTION:
        strcpy(import_file, english_part4_csv);
        strcpy(sector, "part4");
        break;
    case ENGLISH_PART5_OPTION:
        strcpy(import_file, english_part5_csv);
        strcpy(sector, "part5");
        break;
    case ENGLISH_PART6_OPTION:
        strcpy(import_file, english_part6_csv);
        strcpy(sector, "part6");
        break;
    case ENGLISH_PART7_OPTION:
        strcpy(import_file, english_part7_csv);
        strcpy(sector, "part7");
        break;
    case ENGLISH_WORD_OPTION:
        strcpy(import_file, english_word_csv);
        strcpy(sector, "word");
        break;
    default:
        return 0;
    }
    return 1;
}