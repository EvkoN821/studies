#include <iostream>
template <class T>
void quickSort(T* a, const long n) {
    long i = 0, j = n - 1;
    T pivot = a[n / 2];

    do {
        while (a[i] < pivot) {
            i++;
        }
        while (a[j] > pivot) {
            j--;
        }
        if (i <= j) {
            std::swap(a[i], a[j]);
            i++; j--;
        }
    } while (i <= j);

#pragma omp task shared(a)
    {
        if (j > 0) {
            quickSort(a, j + 1);
        }
    }
#pragma omp task shared(a)
    {
        if (n > i) {
            quickSort(a + i, n - i);
        }
    }
#pragma omp taskwait
}
int main() {
    const long n=100;
    int mas[n];
    for (int i = 0; i < n; i++)
        mas[i] = 1 + rand() % 100;
    quickSort(mas, n);
    for (int i = 0; i < 10; i++) {
        std::cout << mas[i] << ", ";

    }
}