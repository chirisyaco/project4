cmake_minimum_required(VERSION 3.0.0)
project(project4 VERSION 2.3)

add_executable(
    main main.c
    mode_function/make_question.c
    mode_function/set_file.c
    create_window/make_window.c
    create_window/init_instance.c
    create_window/register_class.c
    create_window/window_procedure/alarm_procedure.c
    create_window/window_procedure/learning_procedure.c
    create_window/window_procedure/menu_procedure.c
    create_window/window_procedure/timer_procedure.c
    create_window/window_procedure/eng_1item_procedure.c
    create_window/window_procedure/eng_3item_procedure.c
    create_window/window_procedure/question_procedure.c
    resource/icon.rc
    resource/english.rc
    resource/math.rc
    resource/other.rc
)

target_link_libraries(main winmm.lib)
