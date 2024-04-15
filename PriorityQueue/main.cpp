#include "VectorPriorityQueue.h"
#include "HeapPriorityQueue.h"
#include <set>
#include <functional>
#include <string>
#include <iterator>
#include <vector>
#include <chrono>
#include <fstream>

struct StringCompare
{
    bool operator () (const std::string& s_left, const std::string& s_right)
    {
        return s_left.length() < s_right.length();
    }
};


void WarAndPeaceTest()
{

    setlocale(LC_ALL, "Rus");
    std::ifstream ifs("WarAndPeace.txt");
    std::string line;
    size_t ind = 0;
    size_t find = 0;
    long long count_words = 0;
    auto start = std::chrono::steady_clock::now();
    std::vector<std::string> allWords;
    while (getline(ifs, line))
    {
        find = 0;
        while (find != std::string::npos)
        {
            find = line.find_first_of({ ',', ' ', '.', '!', '?', ':', ';', '"', '(', ')', '*' }, ind);
            if (ind != find)
            {
                allWords.push_back(line.substr(ind, find - ind));
                ++count_words;
            }
            ind = find + 1;
        }
    }
    
    HeapPriorityQueue<std::string, std::vector<std::string>, StringCompare> q(allWords);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Поиск 20 самых длинных слов: " << elapsed_seconds.count() << " ms" << std::endl;
    std::cout << "20 самых длинных слов: " << std::endl;
    for (int i = 0; i < 20; ++i)
    {
        std::cout << q.top() << "        длины " << q.top().length() << std::endl;
        q.pop();
    }
    std::cout << std::endl;
    ifs.close();
}


int timeCompare() {

    const long n = 100000000;
    {

        std::priority_queue<long> q;
        auto start = std::chrono::steady_clock::now();
        for (long i = 0; i < n; ++i) {
            q.push(i);
        }
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Вставка " << n << " элементов в std::priority_queue: " << elapsed_seconds.count() << "s\n";
    }

    {
        PriorityQueue<long> q;
        auto start = std::chrono::steady_clock::now();
        for (long i = 0; i < n; ++i) {
            q.push(i);
        }
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Вставка " << n << " элементов в ikdr::PriorityQueue: " << elapsed_seconds.count() << "s\n";
    }

    {
        HeapPriorityQueue<long> q;
        auto start = std::chrono::steady_clock::now();
        for (long i = 0; i < n; ++i) {
            q.push(i);
        }
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Вставка " << n << " элементов в ikdr::HeapPriorityQueue: " << elapsed_seconds.count() << "s\n";
    }
}

int timeCompareRandom() {

    srand(time(0));
    const long n = 100000000;
    {

        std::priority_queue<long> q;
        auto start = std::chrono::steady_clock::now();
        for (long i = 0; i < n; ++i) {
            q.push(rand());
        }
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Вставка " << n << " случайных элементов в std::priority_queue: " << elapsed_seconds.count() << "s\n";
    }

    /*{
        PriorityQueue<long> q;
        auto start = std::chrono::steady_clock::now();
        for (long i = 0; i < n; ++i) {
            q.push(rand());
        }
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Вставка " << n << " случайных элементов в ikdr::PriorityQueue: " << elapsed_seconds.count() << "s\n";
    }*/

    {
        HeapPriorityQueue<long> q;
        auto start = std::chrono::steady_clock::now();
        for (long i = 0; i < n; ++i) {
            q.push(rand());
        }
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Вставка " << n << " случайных элементов в ikdr::HeapPriorityQueue: " << elapsed_seconds.count() << "s\n";
    }
}

int main() {

 

    setlocale(LC_ALL, "RUS");
    WarAndPeaceTest();
    timeCompare();
    timeCompareRandom();

    return 0;
}
