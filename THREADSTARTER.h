#ifndef THREADSTARTER_H
#define THREADSTARTER_H

#include <vector>
#include <thread>  // ��� ������ � ��������
#include <functional>  // ��� std::function
#include <iostream>
#include <mutex>
#include <iomanip>
#include <algorithm>


// ������� ��� ������� �������
void startAllThreads(std::vector<int>& arr);

#endif // THREADSTARTER_H