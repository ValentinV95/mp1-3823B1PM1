#pragma once
#include <iostream>

template <class T>
class mathVector
{
private:
    T* items;
    size_t size;
public:
    mathVector();
    mathVector(size_t size, const T& a = 0);
    mathVector(const mathVector& v);
    ~mathVector();

    void setSize(size_t size);
    size_t getSize() const;

    T& operator[](int i);
    T& operator[](int i) const;

    mathVector& operator=(const mathVector& v);

    mathVector& operator+=(const mathVector& v);
    mathVector& operator-=(const mathVector& v);
    mathVector& operator*=(const T& c);
    mathVector& operator/=(const T& c);

    mathVector operator+(const mathVector& v);
    mathVector operator-(const mathVector& v);
    mathVector operator*(const T& c);
    mathVector operator/(const T& c);

    template<class T>
    friend std::ostream& operator<<(std::ostream&, const mathVector<T>&);
    template<class T>
    friend std::istream& operator>>(std::istream&, mathVector<T>&);
};

template<class T>
mathVector<T>::mathVector()
{
    items = nullptr;
    size = 0;
}

template<class T>
mathVector<T>::mathVector(size_t size, const T& a)
{
    items = new T[size];
    for (int i = 0; i < size; i++)
    {
        items[i] = a;
    }
    this->size = size;
}

template<class T>
mathVector<T>::mathVector(const mathVector& v)
{
    size = v.size;
    items = new T[size];
    for (int i = 0; i < size; i++)
    {
        items[i] = v.items[i];
    }
}

template<class T>
mathVector<T>::~mathVector()
{
    size = 0;
    delete[] items;
}

 template<class T>
 void mathVector<T>::setSize(size_t size)
{
    delete[] items;
    this->size = size;
    items = new T[size];
    for (int i = 0; i < size; i++)
    {
        items[i] = 0;
    }
    return;
}

 template<class T>
 size_t mathVector<T>::getSize() const
 {
     return size;
 }

 template<class T>
 T& mathVector<T>::operator[](int i)
 {
     return items[i];
 }

 template<class T>
 T& mathVector<T>::operator[](int i) const
 {
     return items[i];
 }

 template<class T>
 mathVector<T>& mathVector<T>::operator+=(const mathVector<T>& v)
 {
     for (int i = 0; i < size; i++)
     {
         items[i] += v.items[i];
     }
     return *this;
 }

 template<class T>
 mathVector<T> mathVector<T>::operator+(const mathVector<T>& v)
 {
     mathVector<T> t(size);
     t = *this;
     t += v;
     return t;
 }

 template<class T>
 mathVector<T>& mathVector<T>::operator-=(const mathVector& v)
 {
     for (int i = 0; i < size; i++)
     {
         items[i] -= v.items[i];
     }
     return *this;
 }

 template<class T>
 mathVector<T> mathVector<T>::operator-(const mathVector<T>& v)
 {
     mathVector<T> t(size);
     t = *this;
     t -= v;
     return t;
 }

 template<class T>
 mathVector<T>& mathVector<T>::operator=(const mathVector<T>& v)
 {
     for (int i = 0; i < size; i++)
     {
         items[i] = v.items[i];
     }
     return *this;
 }

 template<class T>
 mathVector<T>& mathVector<T>::operator*=(const T& c)
 {
     for (int i = 0; i < size; i++)
     {
         items[i] *= c;
     }
     return *this;
 }

 template<class T>
 mathVector<T>& mathVector<T>::operator/=(const T& c)
 {
     for (int i = 0; i < size; i++)
     {
         items[i] /= c;
     }
     return *this;
 }

 template<class T>
 mathVector<T> mathVector<T>::operator*(const T& c)
 {
     mathVector<T> t(size);
     t = *this;
     t *= c;
     return t;
 }

 template<class T>
 mathVector<T> mathVector<T>::operator/(const T& c)
 {
     mathVector<T> t(size);
     t = *this;
     t /= c;
     return t;
 }

template<class T>
std::ostream& operator<<(std::ostream& os, const mathVector<T>& v)
{
    for (int i = 0; i < v.size; i++)
    {
        os << v.items[i] << " ";
    }
    return os;
}

template<class T>
inline std::istream& operator>>(std::istream& in, mathVector<T>& v)
{
    for (int i = 0; i < v.size; i++)
    {
        in >> v.items[i];
    }
    return in;
}