#include <windows.h>
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

int test_func(int var, float break_time);

int main() {
    // Указание количества тестов
    const int TEST_SIZE = 15000;

    // Создание генератора случайных чисел
    random_device generator;
    mt19937 mt(generator());
    uniform_int_distribution<int> dist(0, 50);

    // Создание масивов для записи тестов и ответов к этим тестам
    int test_array[TEST_SIZE];
    int ans_array[TEST_SIZE];

    // Заполнение тестовых массивов
    for (int i = 0; i < TEST_SIZE; ++i) {
        test_array[i] = dist(mt);
        ans_array[i] = test_array[i] % 7 == 0 ? NULL : test_array[i] % 10;
    }

    // Создание временной переменной для симуляции поломки системы
    clock_t it_will_break_each_2_seconds = clock();

    // Создание сообщений о симуляции и переменной для их вывода
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    bool failed_on_100 = false;
    string report[2] = {
            "TEST PASSED",
            "TEST FAILED"
    };

    // Тестирование функции на автогенерированных тестах
    for (int i = 0; i < TEST_SIZE; ++i) {
        if (i % 1000 == 0 && i != 0) {
            // Функция установки консоли в иной цвет
            SetConsoleTextAttribute(hConsole, failed_on_100 + 11);
            cout << " " << report[failed_on_100] << endl;
            failed_on_100 = false;
        }
        if (test_func(test_array[i],
                      clock() - it_will_break_each_2_seconds) != ans_array[i]) {
            failed_on_100 = true;
        }
    }
}

// Функция эмуляции работы  ПО
int test_func(int var, float break_time) {
    if ((int) break_time % 2 != 0) {
        // Симуляция ошибочного поведения системы
        return NULL;
    } else {
        // Ожидаемый ответ системы на входной агрумент 'var'
        return var % 7 == 0 ? NULL : var % 10;
    }
}