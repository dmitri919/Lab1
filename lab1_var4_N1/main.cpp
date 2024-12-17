#include "set.h"
float my_tools(Set<int> set1, Set<int> set2);
int main() {
    int values[] = { 5, 4, 6 };
    Set<int> set1(values, 3);
    Set<int> set_test(values, 3);

    if (set1 == set_test) { std::cout << "True" << std::endl; }// Проверка оператора==
    
    Set<int> set2;
    set2 += 4;
    set2 += 2;
    set2 += 6;

    if (set1 == set2) { std::cout << "True" << std::endl; }// Проверка оператора==
    else { std::cout << "False" << std::endl; }

    float test = my_tools(set1, set2);//Доп задание
    std::cout << test << std::endl;

    Set<int> set = set1 + set2;
    
    Set<int> set_r(10, 1, 11);

    std::cout << "Set1: " << set1 << std::endl;
    std::cout << "Set2: " << set2 << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Set: " << set << std::endl;
    std::cout << "Set random: " << set_r << std::endl;
    std::cout<< "\n" << std::endl;
    std::cout << "Unique elements: " << UniqueElements(set, set_r) << std::endl;
    std::cout << "Set - Set2: " << set - set2 << std::endl;//вычитание
    std::cout << "Intersection Set & Set1: " << set.intersection(set1) << std::endl;//пересечение
    // Попытка удаления несуществующего элемента
    std::cout << "Set2 - 4: ";
    try {
        set2 -= 4;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    // Пример с типом float
    float arr3[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
    float arr4[] = { 4.4, 5.5, 6.6, 7.7, 8.8 };
    Set<float> set3(arr3, 5);
    Set<float> set4(arr4, 5);
    Set<float> uniqueFloatElements = UniqueElements(set3, set4);
    std::cout << "Unique float elements: " << uniqueFloatElements << std::endl;

    // Пример с типом std::string
    std::string arr5[] = { "apple", "banana", "cherry", "date", "fig" };
    std::string arr6[] = { "date", "fig", "grape", "honeydew", "kiwi" };
    Set<std::string> set5(arr5, 5);
    Set<std::string> set6(arr6, 5);
    Set<std::string> uniqueStringElements = UniqueElements(set5, set6);
    std::cout << "Unique string elements: " << uniqueStringElements << std::endl;

    // Пример с типом std::pair<int, double>
    std::pair<int, double> arr7[] = { {1, 1.1}, {2, 2.2}, {3, 3.3}, {4, 4.4}, {5, 5.5} };
    std::pair<int, double> arr8[] = { {4, 4.4}, {5, 5.5}, {6, 6.6}, {7, 7.7}, {8, 8.8} };
    Set<std::pair<int, double>> set7(arr7, 5);
    Set<std::pair<int, double>> set8(arr8, 5);
    Set<std::pair<int, double>> uniquePairElements = UniqueElements(set7, set8);
    std::cout << "Unique pair elements: " << uniquePairElements << std::endl;

    Set<float> set10(10, 0, 11);
    std::cout << "Random float" << set10 << std::endl;

    return 0;
}

//Доп задание
float my_tools(Set<int> set1, Set<int> set2) {
    Set<int> tmp = set1 + set2;
    int sum = 0;
    for (size_t i = 0; i < tmp.give_me_size(); i++) {
        sum += tmp[i];
    }

    return sum / float(tmp.give_me_size());
};

//int main() {
//    // Пример с типом float
//    float arr3[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
//    float arr4[] = { 4.4, 5.5, 6.6, 7.7, 8.8 };
//    Set<float> set3(arr3, 5);
//    Set<float> set4(arr4, 5);
//    Set<float> uniqueFloatElements = set3.uniqueElements(set4);
//    std::cout << "Unique float elements: " << uniqueFloatElements << std::endl;
//
//    // Операции с float
//    set3 += 6.6f;
//    set3 -= 1.1f;
//    Set<float> unionFloat = set3 + set4;
//    Set<float> intersectionFloat = set3.intersection(set4);
//    std::cout << "Union float elements: " << unionFloat << std::endl;
//    std::cout << "Intersection float elements: " << intersectionFloat << std::endl;
//
//    // Пример с типом std::string
//    std::string arr5[] = { "apple", "banana", "cherry", "date", "fig" };
//    std::string arr6[] = { "date", "fig", "grape", "honeydew", "kiwi" };
//    Set<std::string> set5(arr5, 5);
//    Set<std::string> set6(arr6, 5);
//    Set<std::string> uniqueStringElements = set5.uniqueElements(set6);
//    std::cout << "Unique string elements: " << uniqueStringElements << std::endl;
//
//    // Операции с std::string
//    set5 += "grape";
//    set5 -= "apple";
//    Set<std::string> unionString = set5 + set6;
//    Set<std::string> intersectionString = set5.intersection(set6);
//    std::cout << "Union string elements: " << unionString << std::endl;
//    std::cout << "Intersection string elements: " << intersectionString << std::endl;
//
//    // Пример с типом std::pair<int, double>
//    std::pair<int, double> arr7[] = { {1, 1.1}, {2, 2.2}, {3, 3.3}, {4, 4.4}, {5, 5.5} };
//    std::pair<int, double> arr8[] = { {4, 4.4}, {5, 5.5}, {6, 6.6}, {7, 7.7}, {8, 8.8} };
//    Set<std::pair<int, double>> set7(arr7, 5);
//    Set<std::pair<int, double>> set8(arr8, 5);
//    Set<std::pair<int, double>> uniquePairElements = set7.uniqueElements(set8);
//    std::cout << "Unique pair elements: " << uniquePairElements << std::endl;
//
//    // Операции с std::pair<int, double>
//    set7 += std::make_pair(9, 9.9);
//    set7 -= std::make_pair(1, 1.1);
//    Set<std::pair<int, double>> unionPair = set7 + set8;
//    Set<std::pair<int, double>> intersectionPair = set7.intersection(set8);
//    std::cout << "Union pair elements: " << unionPair << std::endl;
//    std::cout << "Intersection pair elements: " << intersectionPair << std::endl;
//
//    return 0;
//}
