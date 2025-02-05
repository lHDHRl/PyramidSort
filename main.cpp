#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "array.h"
#include "student.h"
#include "sort.h"

// Функция для чтения данных из файла.
// Открывает файл, построчно считывает записи и заполняет массив.
LibArray<StudentRecord> readData(const std::string& filename, size_t n) {
    std::ifstream file(filename);
    if (!file)
        throw std::runtime_error("Невозможно открыть файл: " + filename);

    LibArray<StudentRecord> data(n);
    std::string line;
    size_t count = 0;

    while (count < n && std::getline(file, line)) {
        std::istringstream iss(line);
        std::string surname, name, middlename;
        int group;
        // Если формат строки неверный, выбрасываем исключение.
        if (!(iss >> surname >> name >> middlename >> group))
            throw std::runtime_error("Неверный формат файла");

        // Создаём запись и сохраняем порядковый номер (начиная с 1).
        data[count] = StudentRecord(FullName(surname, name, middlename), GroupNumber(group), count + 1);
        count++;

        if (count % 10000 == 0)
            std::cout << "Обработано " << count << " записей...\n";
    }
    std::cout << "Завершена обработка " << count << " записей.\n";
    return data;
}

// Функция для записи отсортированных данных в файл.
void writeResults(const LibArray<StudentRecord>& data, const std::string& filename, double time_ms) {
    std::ofstream out(filename);
    if (!out)
        throw std::runtime_error("Невозможно создать файл: " + filename);

    for (size_t i = 0; i < data.getSize(); ++i) {
        const auto& record = data[i];
        out << record.name.surname << " "
            << record.name.name << " "
            << record.name.middlename << "\t"
            << record.group.value << "\t"
            << record.original_line << "\n";
    }
    out << "Время сортировки: " << time_ms << " мс\n";
}

// Функция для сравнения времени сортировки двух алгоритмов.
void compareSortTimes(double insertionTime, double heapTime) {
    std::cout << "\nСравнение времени сортировки:\n";
    std::cout << "Сортировка вставками: " << insertionTime << " мс\n";
    std::cout << "Пирамидальная сортировка: " << heapTime << " мс\n";
    
    if (insertionTime < heapTime)
        std::cout << "Сортировка вставками работает быстрее.\n";
    else if (heapTime < insertionTime)
        std::cout << "Пирамидальная сортировка работает быстрее.\n";
    else
        std::cout << "Оба алгоритма работают с одинаковой скоростью.\n";
}

// Функция для проверки устойчивости сортировки.
void testStability() {
    std::cout << "\nПроверка устойчивости сортировки:\n";

    // Создаём тестовый массив из 5 записей.
    LibArray<StudentRecord> testArray(5);
    testArray[0] = StudentRecord(FullName("Ivanov", "Ivan", "Ivanovich"), GroupNumber(101), 1);
    testArray[1] = StudentRecord(FullName("Ivanov", "Ivan", "Ivanovich"), GroupNumber(101), 2);
    testArray[2] = StudentRecord(FullName("Ivanov", "Ivan", "Ivanovich"), GroupNumber(101), 3);
    testArray[3] = StudentRecord(FullName("Petrov", "Petr", "Petrovich"), GroupNumber(102), 4);
    testArray[4] = StudentRecord(FullName("Sidorov", "Sidr", "Sidorovich"), GroupNumber(103), 5);

    // Делаем копии для двух сортировок.
    LibArray testInsertion = testArray;
    LibArray testHeap = testArray;

    // Сортируем с помощью сортировки вставками (устойчивая сортировка).
    insertionSort(testInsertion);
    bool stableInsertion = true;
    // Для одинаковых ключей (группа 101) проверяем, что порядковый номер не изменился.
    for (size_t i = 0; i < testInsertion.getSize() - 1; ++i) {
        if (testInsertion[i].group.value == 101 && testInsertion[i + 1].group.value == 101) {
            if (testInsertion[i].original_line > testInsertion[i + 1].original_line) {
                stableInsertion = false;
                break;
            }
        }
    }

    // Сортируем с помощью пирамидальной сортировки.
    heapSort(testHeap);
    bool stableHeap = true;
    for (size_t i = 0; i < testHeap.getSize() - 1; ++i) {
        if (testHeap[i].group.value == 101 && testHeap[i + 1].group.value == 101) {
            if (testHeap[i].original_line > testHeap[i + 1].original_line) {
                stableHeap = false;
                break;
            }
        }
    }

    std::cout << "Сортировка вставками " << (stableInsertion ? "устойчива" : "не устойчива") << ".\n";
    std::cout << "Пирамидальная сортировка " << (stableHeap ? "устойчива (неожиданный результат)" : "не устойчива") << ".\n";
}

int main(int argc, char* argv[]) {
    try {
        // Проверка аргументов командной строки.
        if (argc != 3) {
            std::cerr << "Использование: " << argv[0] << " <имя_файла> <n>\n";
            return 1;
        }

        int n_int;
        std::istringstream iss(argv[2]);
        if (!(iss >> n_int)) {
            std::cerr << "Неверный формат числа для n.\n";
            return 1;
        }
        if (n_int < 10 || n_int > 1000000) {
            std::cerr << "Значение n должно быть от 10 до 1000000\n";
            return 1;
        }
        

        size_t n = static_cast<size_t>(n_int);
        
        // Чтение данных из файла.
        auto data = readData(argv[1], n);
        
        auto dataInsertion = data;
        auto dataHeap = data;

        // Сортировка вставками.
        // Обожаю тип данных std::chrono::time_point<std::chrono::high_resolution_clock>
        std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
        insertionSort(dataInsertion);
        std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
        double insertionTime = std::chrono::duration<double, std::milli>(end - start).count();

        // Пирамидальная сортировка.
        start = std::chrono::high_resolution_clock::now();
        heapSort(dataHeap);
        end = std::chrono::high_resolution_clock::now();
        double heapTime = std::chrono::duration<double, std::milli>(end - start).count();

        // Записываем результаты сортировки в файлы.
        writeResults(dataInsertion, "insertion_sorted.txt", insertionTime);
        writeResults(dataHeap, "heap_sorted.txt", heapTime);

        // Выводим время сортировки в консоль.
        std::cout << "\nСортировка завершена!\n";
        std::cout << "Время сортировки вставками: " << insertionTime << " мс\n";
        std::cout << "Время пирамидальной сортировки: " << heapTime << " мс\n";

        // Сравниваем время работы алгоритмов.
        compareSortTimes(insertionTime, heapTime);

        // Проверяем устойчивость сортировки.
        testStability();

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
