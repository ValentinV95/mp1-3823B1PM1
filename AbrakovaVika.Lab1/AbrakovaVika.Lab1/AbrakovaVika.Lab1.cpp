#include <stdio.h>
#include <stdlib.h>
#include <locale.h> 
#include <time.h>
#include <math.h>

#define N 100000 //ввод константы - максимального количества элементов в массиве

// сортировки
void _bubble_sort(float a[], int n); // сортировка пузырьком 
void _hoara_sort(float a[], int n); // сортировка Хоара
void _merge_sort(float a[], int n); // сортировка слиянием
void _radix_sort(float a[], int n); // поразрядная сортировка

void print_Array(float a[], int fa) // функция печати массива (фрагмент начала и фрагмент конца)
{ // а - массив, fa - длина массива
    for (int i = 0; i < 6; i++)
        printf("%f ", a[i]);
    printf(". . . ");
    for (int i = fa - 3; i < fa; i++)
        printf("%f ", a[i]);
    printf("\n");
}

int fmenu(char* a[], int n) // функция печати меню и считывания выбранной позиции в меню. Возвращает выбранный пункт меню
{ // а - массив, содержащий текстовое описание меню, n - длина массива а
    int k; // k - индекс выбранного пункта меню
    printf("\nМеню:\n");
    for (int i = 0; i < n; i++)
        printf("%s\n", a[i]);
    printf("введите номер желаемого действия: \n");
    scanf_s("%d", &k); // считывание выбранного пункта меню
    return k;
}

int input_Array(float a[])// функция заполнения массива а псевдослучайными числами
{ //В функции запрашивается ввод количества элементов, массив заполняется na псевдослучайными числами.
    //Возвращается количество элементов
    int na; // na - количество элементов
    int seed; //ключ генерации
    int left; //левая граница диапазона значений
    int right; //правая граница диапазона значений
    printf("Введите количество элементов в массиве (не более 100000):\n ");
    scanf_s("%d", &na);
    printf("Введите ключ генерации псевдослучайных чисел:\n ");
    scanf_s("%d", &seed);
    printf("Введите левую границу диапазона значений:\n ");
    scanf_s("%d", &left);
    printf("Введите правую границу диапазона значений:\n ");
    scanf_s("%d", &right);
    srand(seed);
    for (int i = 0; i < na; i++)
        a[i] = left + ((float)rand() / RAND_MAX) * (right - left);
    printf("\nСоздан массив из %d элементов с помощью датчика псевдослучайных чисел\nМассив:\n ", na);
    print_Array(a, na);
    return na;
}

// основная функция
int main()
{
    setlocale(LC_ALL, "RUS"); // подключаем русификацию
    int count = 6; // count - количество позиций в меню
    char* pmenu[6] = { "0) Ввод данных", "1) Выполнить сортировку пузырьком", "2) Выполнить сортировку Хоара", "3) Выполнить сортировку слиянием", "4) Выполнить поразрядную сортировку", "5) Выйти" };
    // pmenu - массив строк, в котором содержатся пункты меню
    int k; // k - индекс позиции меню
    int na = 0; // na - количество элементов в массиве (задается с клавиатуры)
    char* smenu[4] = { "Пузырёк", "Хоара", "Слиянием", "Поразрядная" };
    // smenu - массив строк, в котором содержатся названия сортировок
    float a[N], c[N]; // a[] - рабочий массив; c[] - копия массива, обновляемая перед каждой сортировкой
    do
    {
        k = fmenu(pmenu, count);
        for (int i = 0; i < na; i++) c[i] = a[i]; // копируем массив а в массив с
        double t1, t2; // t1, t2 - время начала и окончания работы функции сортировки соответственно
        if (k == 0) na = input_Array(a);
        if ((na == 0)) printf("\nМассив пуст\n");
        if ((k > 0) && (na != 0) && (k < 8))
        {
            t1 = clock();
            switch (k)
            {
            case 1: {
                _bubble_sort(c, na);
                break;
            }
            case 2: {
                _hoara_sort(c, na);
                break;
            }
            case 3: {
                _merge_sort(c, na);
                break;
            }
            case 4: {
                _radix_sort(c, na);
                break;
            }
            }
            t2 = clock();
            printf("\nСортировка %s выполнена за %4.3f секунд\n", smenu[k - 1], ((t2 - t1) / 1000));
            printf("\nОтсортированный массив из %d элементов:\n", na);
            print_Array(c, na);
        }
    } while (k < 8);
}

// сортировки
// функция сортировки массива методом пузырька
void _bubble_sort(float a[], int n) {// a - массив из na элементов
    int i, j;
    float tmp;
    int flag = 0;// Флаг, указывающий на то, были ли произведены обмены
    for (i = 0; i < n; i++) {
        flag = 0;// Обнуляем флаг на каждой итерации
        for (j = n - 1; j > i; j--) {
            if (a[j] < a[j - 1]) {
                // Обмен значениями a[j] и a[j-1]
                tmp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = tmp;
                flag = 1;// Устанавливаем флаг, если была произведена замена
            }
        }
        // Если на данной итерации не было произведено ни одной замены, то массив уже отсортирован, можно завершить сортировку
        if (flag == 0)
            break;
    }
}

// функция сортировки массива Хоара
int _partition(float* a, int s, int f) {// Функция, определяющая правильную позицию опорного элемента
    float b = a[s];// Опорный элемент
    float tmp;
    f--;
    while (s <= f) {
        while (a[s] < b)
            s++;
        while (a[f] > b)
            f--;
        if (s <= f) {// Если текущий элемент меньше или равен опорному
            tmp = a[s];
            a[s] = a[f];
            a[f] = tmp;
            s++; // Увеличиваем индекс более маленького элемента
            f--;
        }
    }
    return s;
}

void _qsort(float* a, int s, int f) {// Основная функция быстрой сортировки
    if (f - s < 2) // Индекс разделения, a[p] - теперь на правильном месте
        return;
    int p = _partition(a, s, f);
    // Рекурсивно сортируем элементы перед разделением и после него
    _qsort(a, s, p);
    _qsort(a, p, f);
}

void _hoara_sort(float a[], int n) {
    _qsort(a, 0, n);
}

// функция сортировки массива методом слияния

void _merge(float* a, float* b, float* res, int an, int bn) {// Функция для слияния двух подмассивов
    int ia = 0, ib = 0, ir = 0;
    while (an > ia && ib < bn) {// Слияние временных подмассивов
        if (a[ia] < b[ib])
            res[ir++] = a[ia++];
        else {
            res[ir++] = b[ib++];
        }
    }// Копирование оставшихся элементов
    for (; ia < an; ia++) {
        res[ir++] = a[ia];
    }
    for (; ib < bn; ib++) {
        res[ir++] = b[ib];
    }
}

int _max(int a, int b) { //вернуть максимальное значение
    if (a > b) {
        return a;
    }
    return b;
}

int _min(int a, int b) { //вернуть минимальное значение
    if (a < b) {
        return a;
    }
    return b;
}

void _copy(float* src, float* dst, int first, int last) {
    int i;
    for (i = first; i < last; i++) dst[i] = src[i];
}

void _mergesort(float* a, int n) {// Основная функция сортировки слиянием
    int step = 1, i;
    int counter = 0;
    float* temp;
    float* tmpdata = (float*)malloc(n * sizeof(float));
    for (step = 1; step < n; step *= 2) {
        for (i = 0; i < n; i += 2 * step) {
            _merge(a + i, a + i + step, &tmpdata[i], _max(0, _min(step, n - i)), _max(0, _min(step, n - step - i)));//аргументы объединяются
        }
        temp = a;
        a = tmpdata;
        tmpdata = temp;//меняем местами массив res и исходный массив
        counter++;
    }
    if ((counter % 2) != 0) {
        temp = a;
        a = tmpdata;
        tmpdata = temp;
        _copy(tmpdata, a, 0, n);
    }
    free(tmpdata);
}

void _merge_sort(float a[], int n) {
    _mergesort(a, n);
}


// функция поразрядной сортировки

void foffset(unsigned char* a, int n, int offset, int count[257]) {
    int i = 0;
    int tmp;
    int temp;
    for (i = 0; i < 257; count[i++] = 0) {};
    for (i = 0; i < n; i++) {
        count[  //подсчитывает значения в байтах
            a[offset + i * sizeof(float)]  //i-байт каждой цифры
        ]++;
    }
    tmp = count[0];//байт == 0
    count[0] = 0;
    for (i = 0; i < 256; i++) {
        {
            temp = tmp;
            tmp = count[i + 1];
            count[i + 1] = temp;
        }
        count[i + 1] += count[i];
    }
}

void _radixsort(float* a, int n) {
    int i = 0, j = 0;
    unsigned int negativeDigits = 0;
    int count[257];
    float* tempp;
    float* a2 = (float*)malloc(n * sizeof(float));
    unsigned char* pm = (unsigned char*)a;  //Представление числа в байтах
    for (; i < sizeof(float); i++) {
        foffset(pm, n, i, count);
        for (j = 0; j < n; j++) {
            a2[
                count[
                    pm[j * sizeof(float) + i]
                ]++
            ] = a[j];
        }
        tempp = a;
        a = a2;
        a2 = tempp;
        pm = (unsigned char*)a;//Представление числа в байтах
    }
    for (i = n - 1; i > -1; i--) {//начать подсчет отрицательных элементов
        if (a[i] >= 0) {
            break;
        }
        negativeDigits++;
    }
    for (i = 0; i < negativeDigits; i++) {//начать проталкивать элементы в a2
        a2[i] = a[n - i - 1];
    }
    for (i = negativeDigits; i < n; i++) {
        a2[i] = a[i - negativeDigits];
    }
    for (i = 0; i < n; i++) {// Копируем отсортированный массив обратно в исходный массив
        a[i] = a2[i];
    }
    free(a2);
}

void _radix_sort(float a[], int n) {
    _radixsort(a, n);
}
