#include <iostream>
#include <stdexcept>
#include <random>
#include <string>
#include <utility>

template <typename T>
class Set {
private:
    T* elements;
    size_t size;
    size_t capacity;

    void resize();
    void addUniq(const T& value);

public:
    Set();
    Set(const T* values, size_t size);
    Set(size_t count, T min, T max);
    Set(const Set& other); // Конструктор копирования
    Set& operator=(const Set& other); // Оператор присваивания
    ~Set();

    T operator[] (size_t i) const;

    bool operator==(const Set& other) const;

    Set operator+(const Set& other) const;
    Set operator-(const Set& other) const;
    Set operator+(const T& value) const;
    Set& operator+=(const T& value);
    Set operator-(const T& value) const;
    Set& operator-=(const T& value);
    Set intersection(const Set& other) const;
    bool contains(const T& value) const;

    friend std::ostream& operator<<(std::ostream& os, const Set& set) {
        for (size_t i = 0; i < set.size; i++) {
            os << set.elements[i] << "   ";
        }
        return os;
    }

    size_t give_me_size() const{
        return size;
    }
};

//iostream
// Перегрузка оператора << для std::pair<int, double>
std::ostream& operator<<(std::ostream& os, const std::pair<int, double>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}


// Увеличение размера массива в 2 раза
template<typename T>
void Set<T>::resize() {
    capacity = (capacity == 0) ? 1 : capacity * 2;
    T* newElements = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
        newElements[i] = elements[i];
    }
    delete[] elements;
    elements = newElements;
}

// Добавление элемента
template<typename T>
void Set<T>::addUniq(const T& value) {
    bool Uniqflag = true;
    for (size_t i = 0; i < size; i++) {
        if (contains(value)) { 
            Uniqflag = false; 
            break;
        }
    }

    if (Uniqflag) {
        if (size >= capacity) { resize(); };
        elements[size] = value;
        size++;
    }
}

template<typename T>
Set<T>::Set() : size(0), capacity(1) {
    elements = new T[1];
}

template<typename T>
Set<T>::Set(const T* values, size_t _size) : size(0), capacity(_size) {
    elements = new T[capacity];
    for (size_t i = 0; i < _size; i++)
        addUniq(values[i]);
}

template<typename T>
Set<T>::Set(size_t count, T min, T max) : size(0), capacity(count) {
    if (count > abs(max - min) + 1) {
        throw std::invalid_argument("Size > [min, max)");
    }
    elements = new T[capacity];
    std::random_device rd;
    std::mt19937 gen(rd());
    if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, std::pair<int, double>>) {
        throw std::invalid_argument("Random generation for this type is not supported");
    }
    else {
        std::uniform_real_distribution<> dis(min, max);
        for (size_t i = 0; i < count; i++) {
            addUniq(static_cast<T>(dis(gen)));
            if (i = size) { i--; };
        }
    }
}

template<typename T>
Set<T>::Set(const Set& other) : size(other.size), capacity(other.capacity) {
    elements = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
        elements[i] = other.elements[i];
    }
}

template<typename T>
Set<T>& Set<T>::operator=(const Set& other) {
    if (this == &other) {
        return *this;
    }
    delete[] elements;
    size = other.size;
    capacity = other.capacity;
    elements = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
        elements[i] = other.elements[i];
    }

    return *this;
}

template<typename T>
Set<T>::~Set() {
    delete[] elements;
}

template<typename T>
T Set<T>::operator[](size_t i) const {
    if (i < size) {
        return elements[i];
    }
    else {
        throw std::out_of_range("Index out of range");
    }
}

template<typename T>
Set<T> Set<T>::operator+(const Set& other) const {
    Set result;
    for (size_t i = 0; i < size; ++i) {
        result += elements[i];
    }
    for (size_t i = 0; i < other.size; ++i) {
        result += other.elements[i];
    }
    return result;
}

template<typename T>
Set<T> Set<T>::operator+(const T& value) const {
    Set result = *this;
    result += value;
    return result;
}

template<typename T>
Set<T>& Set<T>::operator+=(const T& value) {
    if (!contains(value)) {
        addUniq(value);
    }
    return *this;
}

template<typename T>
Set<T>& Set<T>::operator-=(const T& value) {
    bool found = false;
    for (size_t i = 0; i < size; ++i) {
        if (elements[i] == value) {
            found = true;
            for (size_t j = i; j < size - 1; ++j) {
                elements[j] = elements[j + 1];
            }
            --size;
            break;
        }
    }
    if (!found) {
        throw std::invalid_argument("Element not found in the set");
    }
    return *this;
}

template<typename T>
Set<T> Set<T>::operator-(const Set& other) const {
   /* Set result;
    for (size_t i = 0; i < size; ++i) {
        if (!other.contains(elements[i])) {
            result += elements[i];
        }
    }
    if (result.size == 0) {
        throw std::invalid_argument("No elements to subtract, result is an empty set");
    } 
    return result;*/
    Set result(elements, size);
    for (size_t i = 0; i < other.size; i++) {
        result -= elements[i];
    }
    if (result.size == 0) {
        throw std::invalid_argument("No elements to subtract, result is an empty set");
    }
    return result;
}

template<typename T>
Set<T> Set<T>::operator-(const T& value) const {
    Set result = *this;
    try {
        result -= value;
    }
    catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Element not found in the set for subtraction");
    }
    return result;
}


template<typename T>
Set<T> Set<T>::intersection(const Set& other) const {
    Set result;
    for (size_t i = 0; i < size; ++i) {
        if (other.contains(elements[i])) {
            result += elements[i];
        }
    }
    return result;
}

//Нашел - true
template<typename T>
bool Set<T>::contains(const T& value) const {
    if (size == 0) return false; // Проверка на пустой набор
    size_t left = 0;
    size_t right = size - 1;
    
    for (size_t i = 0; i < size; i++) {
        if (elements[i] == value) {
            return true;
        }
    }
    return false;
}

template<typename T>//Р’С‹РІРѕРґ РјРЅРѕР¶РµСЃС‚Р° СѓРЅРёРєР°Р»СЊРЅС‹С… СЌР»Р»РµРјРµРЅС‚РѕРІ РёР· 2-СѓС… РјРЅРѕР¶РµСЃС‚РІ
Set<T> UniqueElements(const Set<T>& set1, const Set<T>& set2) {
    Set<T> result;
    for (size_t i = 0; i < set1.give_me_size(); i++) {
        if (!set2.contains(set1[i])) {
            result += set1[i];
        }
    }
    for (size_t i = 0; i < set2.give_me_size(); i++) {
        if (!set1.contains(set2[i])) {
            result += set2[i];
        }
    }
    return result;
}

template<typename T>
bool Set<T>::operator==(const Set& other) const {
    bool flag = true;
    if (size != other.size) { return false; }
    for (size_t i = 0; i < size; i++) {
        if (!contains(other.elements[i])) { return false; }
    }
    return true;
}