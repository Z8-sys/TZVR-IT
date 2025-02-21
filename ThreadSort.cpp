#include "THREADSTARTER.h"

std::vector<int> sharedArray; // ����� ������
std::mutex arrayMutex;       // ������� ��� �������������
// ���������� ��������� �� �����������
void bubbleSortAscending() {
    std::lock_guard<std::mutex> lock(arrayMutex); // ����������� �������

    int n = sharedArray.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (sharedArray[j] > sharedArray[j + 1]) {
                std::swap(sharedArray[j], sharedArray[j + 1]);
            }
        }
    }

    // ������� ���������
    std::cout << std::setw(60) << "���������� ��������� �� �����������:";
    for (int num : sharedArray) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    //������� ������������� ����������� �� ���������� �������
}

// ���������� ������� �� ��������
void selectionSortDescending() {
    std::lock_guard<std::mutex> lock(arrayMutex); // ����������� �������

    int n = sharedArray.size();
    for (int i = 0; i < n - 1; ++i) {
        int maxIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (sharedArray[j] > sharedArray[maxIndex]) {
                maxIndex = j;
            }
        }
        if (maxIndex != i) {
            std::swap(sharedArray[i], sharedArray[maxIndex]);
        }
    }

    // ������� ���������
    std::cout << std::setw(60) << "���������� ������ ��������� �� ��������:";
    for (int num : sharedArray) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    //������� ������������� ����������� �� ���������� �������
}

// ���������� ��������� ������ ������ ������� �� �����������
void insertionSortEvenPositionsAscending() {
    std::lock_guard<std::mutex> lock(arrayMutex); // ����������� �������

    int n = sharedArray.size();
    for (int i = 2; i < n; i += 2) { // ������������� ������ ������ �������
        int key = sharedArray[i];
        int j = i - 2;

        while (j >= 0 && sharedArray[j] > key) {
            sharedArray[j + 2] = sharedArray[j];
            j -= 2;
        }
        sharedArray[j + 2] = key;
    }

    // ������� ���������
    std::cout << std::setw(60) << "���������� ��������� ������ ������� �� �����������:";
    for (int num : sharedArray) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    //������� ������������� ����������� �� ���������� �������
}

// ������ ���������� ������ ������ ������� �� ��������
void quickSortEvenPositionsDescending() {
    std::lock_guard<std::mutex> lock(arrayMutex); // ����������� �������

    auto quickSortHelper = [&](auto&& self, int low, int high) -> void {
        if (low < high) {
            int pivot = sharedArray[high];
            int i = low - 2;

            for (int j = low; j <= high - 2; j += 2) { // ������������� ������ ������ �������
                if (sharedArray[j] > pivot) {
                    i += 2;
                    std::swap(sharedArray[i], sharedArray[j]);
                }
            }
            std::swap(sharedArray[i + 2], sharedArray[high]);

            int pi = i + 2;

            self(self, low, pi - 2);
            self(self, pi + 2, high);
        }
        };

    int n = sharedArray.size();
    quickSortHelper(quickSortHelper, 0, n - ((n % 2 == 0) ? 2 : 1)); // ������������� ������ ������ �������

    // ������� ���������
    std::cout << std::setw(60) << "������� ���������� ������ ������� �� ��������:";
    for (int num : sharedArray) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    //������� ������������� ����������� �� ���������� �������
}

// ���������� �������� ������ ������������� �����, �� �����������
void mergeSortPositiveNumbersAscending() {
    std::lock_guard<std::mutex> lock(arrayMutex); // ����������� �������

    // ������� ����� ������ ������ � �������������� �������
    std::vector<int> positiveNumbers;
    for (int num : sharedArray) {
        if (num > 0) {
            positiveNumbers.push_back(num);
        }
    }

    // ��������� ������������� �����
    std::sort(positiveNumbers.begin(), positiveNumbers.end()); //� ��� ������ ������ ��� ������� sort ���������� ���������� ��������

    // ���������� �� ������� � �������� ������
    int posIndex = 0;
    for (int& num : sharedArray) {
        if (num > 0) {
            num = positiveNumbers[posIndex++];
        }
    }

    // ������� ���������
    std::cout << std::setw(60) << "���������� �������� ������������� ����� �� �����������:";
    for (int num : sharedArray) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    //������� ������������� ����������� �� ���������� �������
}

void startAllThreads(std::vector<int>& arr) {
    sharedArray = arr;
    arrayMutex.lock();//������ ��� ����� ������ ����� ���� ��� �� ����� ������. (��� ��� ����������� ����� � �� ��� �� ������)
    // ������� ������
    std::thread t1(bubbleSortAscending);
    std::thread t2(selectionSortDescending);
    std::thread t3(insertionSortEvenPositionsAscending);
    std::thread t4(quickSortEvenPositionsDescending);
    std::thread t5(mergeSortPositiveNumbersAscending);
    arrayMutex.unlock();//��������� ��� ������

    // ���� ���������� ���� �������
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}