#include "THREADSTARTER.h"

std::vector<int> sharedArray; // Общий массив
std::mutex arrayMutex;       // Мьютекс для синхронизации
// Сортировка пузырьком по возрастанию
void bubbleSortAscending() {
    std::lock_guard<std::mutex> lock(arrayMutex); // Захватываем мьютекс

    int n = sharedArray.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (sharedArray[j] > sharedArray[j + 1]) {
                std::swap(sharedArray[j], sharedArray[j + 1]);
            }
        }
    }

    // Выводим результат
    std::cout << std::setw(60) << "Сортировка пузырьком по возрастанию:";
    for (int num : sharedArray) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    //Мьютекс автоматически освободится по завершению функции
}

// Сортировка выбором по убыванию
void selectionSortDescending() {
    std::lock_guard<std::mutex> lock(arrayMutex); // Захватываем мьютекс

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

    // Выводим результат
    std::cout << std::setw(60) << "Сортировка выбора максимума по убыванию:";
    for (int num : sharedArray) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    //Мьютекс автоматически освободится по завершению функции
}

// Сортировка вставками только четных позиций по возрастанию
void insertionSortEvenPositionsAscending() {
    std::lock_guard<std::mutex> lock(arrayMutex); // Захватываем мьютекс

    int n = sharedArray.size();
    for (int i = 2; i < n; i += 2) { // Рассматриваем только четные позиции
        int key = sharedArray[i];
        int j = i - 2;

        while (j >= 0 && sharedArray[j] > key) {
            sharedArray[j + 2] = sharedArray[j];
            j -= 2;
        }
        sharedArray[j + 2] = key;
    }

    // Выводим результат
    std::cout << std::setw(60) << "Сортировка вставками четных позиций по возрастанию:";
    for (int num : sharedArray) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    //Мьютекс автоматически освободится по завершению функции
}

// Бстрая сортировки только четных позиций по убыванию
void quickSortEvenPositionsDescending() {
    std::lock_guard<std::mutex> lock(arrayMutex); // Захватываем мьютекс

    auto quickSortHelper = [&](auto&& self, int low, int high) -> void {
        if (low < high) {
            int pivot = sharedArray[high];
            int i = low - 2;

            for (int j = low; j <= high - 2; j += 2) { // Рассматриваем только четные позиции
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
    quickSortHelper(quickSortHelper, 0, n - ((n % 2 == 0) ? 2 : 1)); // Рассматриваем только четные позиции

    // Выводим результат
    std::cout << std::setw(60) << "Быстрая сортировка четных позиций по убыванию:";
    for (int num : sharedArray) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    //Мьютекс автоматически освободится по завершению функции
}

// Сортировка слиянием только положительных чисел, по возрастанию
void mergeSortPositiveNumbersAscending() {
    std::lock_guard<std::mutex> lock(arrayMutex); // Захватываем мьютекс

    // Создаем новый массив только с положительными числами
    std::vector<int> positiveNumbers;
    for (int num : sharedArray) {
        if (num > 0) {
            positiveNumbers.push_back(num);
        }
    }

    // Сортируем положительные числа
    std::sort(positiveNumbers.begin(), positiveNumbers.end()); //я так сделал потому что функция sort использует сортировку слиянием

    // Возвращаем их обратно в исходный массив
    int posIndex = 0;
    for (int& num : sharedArray) {
        if (num > 0) {
            num = positiveNumbers[posIndex++];
        }
    }

    // Выводим результат
    std::cout << std::setw(60) << "Сортировка слиянием положительных чисел по возрастанию:";
    for (int num : sharedArray) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    //Мьютекс автоматически освободится по завершению функции
}

void startAllThreads(std::vector<int>& arr) {
    sharedArray = arr;
    arrayMutex.lock();//делаем так чтобы потоки ждали пока все не будут готовы. (Это для наглядности иначе я бы так не сделал)
    // Создаем потоки
    std::thread t1(bubbleSortAscending);
    std::thread t2(selectionSortDescending);
    std::thread t3(insertionSortEvenPositionsAscending);
    std::thread t4(quickSortEvenPositionsDescending);
    std::thread t5(mergeSortPositiveNumbersAscending);
    arrayMutex.unlock();//запускаем все вместе

    // Ждем завершения всех потоков
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}