
#include <iostream>
#include <string>

#define eps1 1e-14   //для double
#define eps2 1e-6   //для float

template <typename T>
class MyVector {    //реализация вектора
    
    T* mas;
    int mem_s;   //столько занято реально
    int data_size;   //а такой размер - абстракция для юзера
    
public:
    MyVector() { //конструктор по умолчанию
        mem_s = 32;
        data_size = 0;
        mas = new T[mem_s];
    }
    ~MyVector() {   //деструктор
        delete[] mas;
    }

    MyVector(int _size, T el = T(0)) {
        mem_s = _size;
        data_size = _size;
        mas = new T[mem_s];
        for (int i = 0; i < data_size; i++) {
            mas[i] = el;
        }
    }
    MyVector(const MyVector& v) { //конструктор копирования
        mem_s = v.mem_s;
        data_size = v.data_size;
        mas = new T[mem_s];
        for (int i = 0; i < data_size; i++) {
            mas[i] = v.mas[i];
        }
    }
    int size() { //количество обьектов для юзера
        return data_size;
    }
    
    void push_back(const T& el) { //добавление в конец массива нового элемента
        if (data_size < mem_s) {
            mas[data_size] = el;
            data_size++;
        }
        else {
            T* nm = new T[mem_s * 3];
            for (int i = 0; i < data_size; i++) {
                nm[i] = mas[i];
            }
            delete[] mas;
            mas = nm;
            mas[data_size] = el;
            data_size++;
            mem_s *= 2;
        }
    }
    void clear() {
        data_size = 0;
    }
    MyVector<T>& operator=(const MyVector<T>& v) { //перегрузка операции равно
            mem_s = v.mem_s;
            data_size = v.data_size;
            delete[] mas;
            mas = new T[mem_s];
            for (int i = 0; i < data_size; i++) {
                mas[i] = v.mas[i];
            }
            return *this;
    }

    T& operator[] (const int& i) { //перегрузка оператора []
        return mas[i];
    }
};


class error : public std::exception {       //класс ошибки с наследованием от exception
private:
    char* s;

public:
    error() {
        s = nullptr;
    }
    error(const std::string& str) {
        this->s = new char[str.length() + 1];
        std::copy(str.begin(), str.end(), this->s);
        this->s[str.length()] = '\0';
    }
    ~error() {
        delete[] s;
    }
    virtual const char* what() const noexcept override  { //перегрузка функции what
        return s;
    }

};


template <typename T>
class Matrix {  //реализация матрицы
protected:
    int n, m;
public:
    Matrix(int n, int m) {
        data = MyVector<MyVector<T>>(n, MyVector<T>(m, 0));
    }

    MyVector<T>& operator[](int i) {
        return data[i];
    }

    void swap(int i, int j) {
        std::swap(data[i], data[j]);
    }

    void umnogit(int i, T c) { 
        for (int j = 0; j < m; j++) {
            data[i][j] *= c;
        }
    }
    size_t size() {
        return data.size();
    }

    void umnogit_and_plus(int i, int j, T c) {
        for (int k = 0; k < m; k++) {
            data[i][k] += c * data[j][k];
        }
    }
    MyVector<MyVector<T>> data;
};

template<class T>
bool check(Matrix<T>& matrix, int row,double eps) {
    if (abs(matrix[row][matrix[0].size() - 1]) > eps) {
        for (int i = 0; i < matrix[row].size()-1; i++) {
            if (abs(matrix[row][i]) > eps) return true;
        }
        return false;
    }
    return true;
}

template <class T>
void swap(MyVector<T>& a, MyVector<T>& b) {
    MyVector<T> s = a; a = b; b = s;
}
template <class T>
void solve(Matrix<T>& data, int rows, int cols,double eps) {    //решалка
    int n = std::min(rows, cols);

    for (int i = 0; i < n; i++) {
        int maxi = i;

        // Ищем строку с максимальным элементом в текущем столбце
        for (int k = i + 1; k < rows; k++) {
            if (abs(data.data[k][i]) > abs(data.data[maxi][i])) {
                maxi = k;
            }
        }

        // Подгоняем ведущую строку под i
        if (maxi != i) {
            swap(data[maxi], data[i]);
        }
        if (abs(data[i][i]) < eps) continue;
        //Делим ведущую строку на ведущий элемент, чтобы ведущий элемент был единицей
        T lead = data.data[i][i];
        for (int j = cols - 1; j >= i; j--) {
            data.data[i][j] /= lead;
        }

        //вычитаем из элементов строк, элементы ведущей строки на коэффициент
        try {
            for (int k = 0; k < rows; k++) {
                if (k != i) {
                    T koef = data.data[k][i];
                    for (int j = i; j < cols; j++) {
                        data.data[k][j] -= koef * data.data[i][j];
                    }
                    if (!check(data, k,eps)) {
                        throw error("Nesowmestna");
                    }
                }
            }
        }
        catch (std::exception& e){
            std::cout << e.what() << std::endl;
            exit(-1);
        }
        //Вывод промежуточной матрицы
        /*std::cout << "------------------------\n";
        print(data, rows, cols);
        std::cout << "------------------------\n";*/
    }
}



template <class T>
void print_uwu_solve(Matrix<T>& matrix,double eps) {    //Вывод ответа по решенной матрице

    int m = matrix[0].size(), n = matrix.size();
    int cnt_x = 0;
    for (int i = 0; i < matrix.size(); i++) {
        if (abs(matrix[i][i]) < eps) break;
        bool was_printed = 0;
        cnt_x++;
        std::cout << "x" << std::to_string(i + 1) << " = ";
        for (int j = i + 1; j < m-1; j++) {
            
            if (abs(matrix[i][j]) > eps) {
                if (was_printed) {
                    if (-matrix[i][j] < 0) {
                        std::cout << "- " << matrix[i][j] << "x" << std::to_string(j + 1) << " ";
                    }
                    else {
                        std::cout << "+ " << -matrix[i][j] << "x" << std::to_string(j + 1) << " ";
                    }
                }
                else {
                    if (-matrix[i][j] < 0) {
                        std::cout << "- " << matrix[i][j] << "x" << std::to_string(j + 1) << " ";
                    }
                    else {
                        std::cout << -matrix[i][j] << "x" << std::to_string(j + 1) << " ";
                    }
                }
                was_printed = 1;
            }
           
        }
        if (abs(matrix[i][m - 1]) > eps) {
            if (was_printed) {
                if (matrix[i][m - 1] < 0) {
                    std::cout << "- " << -matrix[i][m - 1];
                }
                else {
                    std::cout << "+ " << matrix[i][m - 1];
                }
            }
            else {
                if (matrix[i][m - 1] < 0) {
                    std::cout << "- " << -matrix[i][m - 1];
                }
                else {
                    std::cout << matrix[i][m - 1];
                }
            }
        }
        else if(!was_printed){
            std::cout << "0 ";
        }
        std::cout << std::endl;
    }
    for (int i = cnt_x; i < m - 1; i++) {
        std::cout << "x" << std::to_string(i + 1) << " = " << "t" << std::to_string(i - cnt_x + 1) << std::endl;
    }
}

template <class T>
void print(Matrix<T>& data, int rows, int cols) {
    int n = rows;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    try {
        std::cout << "1 - double\n2 - float\nYou: ";    //выбор типа данных
        int q; std::cin >> q;
        if (q == 1) {   //для double    (используется eps1)
            std::cout << "Type count rows and colums rasshirennoy matrix: ";
            int n, m; std::cin >> n >> m;
            if (m == 1) throw error("no var!");
            Matrix<double> matrix(n, m);
            std::cout << "\nType matrix: \n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    std::cin >> matrix[i][j];
                }
            }

            try {
                solve(matrix, n, m,eps1);

                print_uwu_solve(matrix,eps1);

            }
            catch (std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
        else if (q == 2) {  //для float     (используется eps2)
            std::cout << "Type count rows and colums rasshirennoy matrix: ";
            int n, m; std::cin >> n >> m;
            if (m == 1) throw error("no var!");
            Matrix<float> matrix(n, m);
            std::cout << "\nType matrix: \n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    std::cin >> matrix[i][j];
                }
            }

            try {
                solve(matrix, n, m,eps2);

                print_uwu_solve(matrix,eps2);

            }
            catch (std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
        else {
            throw error("NO, YOU DONT WANT THIS TYPE~!");
        }
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        exit(-1);
    }

    return 0;
}

