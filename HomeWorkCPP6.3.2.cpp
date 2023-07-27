#include <iostream>
#include <iterator>
#include <future>
#include <random>
#include <vector>

template<typename T>
void exponentiation(T& elem) {

    elem *= elem;
}

template<typename It, typename T>  
void my_for_each(It begin, It end, void(*function)(T&), int flow = 8) {

    if (flow > 1) {

        auto size = std::distance(begin, end);
        auto middle = begin;
        std::advance(middle, size / 2);

        auto fl1 = std::async(my_for_each<It, T>, begin, middle, function, flow / 2);
        auto fl2 = std::async(my_for_each<It, T>, middle, end, function, flow / 2);
    }
    else {

        for (auto iter = begin; iter != end; iter++) {

            function(*iter);
        }
    }

    //std::cout << std::this_thread::get_id() << std::endl;
}

void vector_random(std::vector<int>& num, int size_vector) {

    std::random_device rv;
    std::mt19937 gen(rv());
    std::uniform_int_distribution<> dist(0, 1000);

    for (int i = 0; i < size_vector; i++) {

        num.push_back(dist(gen));
    }
}

void print(std::vector<int>& num) {

    for (const auto n : num) {

        std::cout << n << " ";
    }

    std::cout << "\n" << std::endl;
}

int main() {

    int size = 16000;
    std::vector<int>vec;

    vector_random(vec, size);
    //print(vec);

    my_for_each(vec.begin(), vec.end(), exponentiation<int>);
    //print(vec);
}