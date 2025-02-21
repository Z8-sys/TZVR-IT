#ifndef THREADSTARTER_H
#define THREADSTARTER_H

#include <vector>
#include <thread>  // Для работы с потоками
#include <functional>  // Для std::function
#include <iostream>
#include <mutex>
#include <iomanip>
#include <algorithm>


// Функция для запуска потоков
void startAllThreads(std::vector<int>& arr);

#endif // THREADSTARTER_H