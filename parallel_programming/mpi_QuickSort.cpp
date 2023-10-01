
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include"mpi.h"
using namespace std;
#define TRUE 1
#define SIZE 10

int Partition(int* wht_data, int wht_start, int wht_end)
{
    int wht_pivot = 0;
    int wht_i = 0, wht_j = 0;
    int wht_tmp = 0;
    wht_pivot = wht_data[wht_end];
    wht_i = wht_start - 1; //  wht_i (активный указатель) 
    for (wht_j = wht_start; wht_j < wht_end; wht_j++)
        if (wht_data[wht_j] <= wht_pivot)
        {
            wht_i++; //  wht_i представляет количество элементов меньше, чем wht_pivot 
            wht_tmp = wht_data[wht_i];
            wht_data[wht_i] = wht_data[wht_j];
            wht_data[wht_j] = wht_tmp;
        }
    wht_tmp = wht_data[wht_i + 1];
    wht_data[wht_i + 1] = wht_data[wht_end];
    wht_data[wht_end] = wht_tmp; //   wht_pivot в качестве границы, wht_data [wht_i + 1] = wht_pivot 
    return wht_i + 1;
}

void QuickSort(int* wht_data, int wht_start, int wht_end)
{
    int wht_r = 0;
    if (wht_start < wht_end)
    {
        wht_r = Partition(wht_data, wht_start, wht_end);
        QuickSort(wht_data, wht_start, wht_r - 1);
        QuickSort(wht_data, wht_r + 1, wht_end);
    }
}

int exp2(int wht_num)
{
    int wht_i;
    wht_i = 1;
    while (wht_num > 0)
    {
        wht_num--;
        wht_i = wht_i * 2;
    }
    return wht_i;
}

int log2(int wht_num)
{
    int wht_i, wht_j;
    wht_i = 1;
    wht_j = 2;
    while (wht_j < wht_num)
    {
        wht_j = wht_j * 2;
        wht_i++;
    }
    if (wht_j > wht_num)
        wht_i--;
    return wht_i;
}

void para_QuickSort(int* wht_data, int wht_start, int wht_end, int wht_m, int id, int MyID)
{
    int wht_i = 0, wht_j = 0;
    int wht_r = 0;
    int MyLength;
    int* wht_tmp;
    MPI_Status status;
    MyLength = -1; // буфер отправки
    if (wht_m == 0)
    {
        if (MyID == id)
            QuickSort(wht_data, wht_start, wht_end);
        return;
    }
    if (MyID == id)
    {
        wht_r = Partition(wht_data, wht_start, wht_end);
        MyLength = wht_end - wht_r;
        MPI_Send(&MyLength, 1, MPI_INT, id + exp2(wht_m - 1), MyID, MPI_COMM_WORLD);
        //(адрес буфера отправки, число перес эл-в, тип пос-х эл-в, номер проц-са пол-ля, индент-р сообщения, коммуникатор обл связи)
        if (MyLength != 0)
            MPI_Send(wht_data + wht_r + 1, MyLength, MPI_INT, id + exp2(wht_m - 1), MyID, MPI_COMM_WORLD);
    }
    if (MyID == id + exp2(wht_m - 1))
    {
        MPI_Recv(&MyLength, 1, MPI_INT, id, id, MPI_COMM_WORLD, &status);
        wht_tmp = nullptr;
        if (MyLength != 0)
        {
            wht_tmp = (int*)malloc(MyLength * sizeof(int));
            if (wht_tmp == 0) printf("Malloc memory error!");
            MPI_Recv(wht_tmp, MyLength, MPI_INT, id, id, MPI_COMM_WORLD, &status);
        }
        wht_j = wht_r - 1 - wht_start;
        MPI_Bcast(&wht_j, 1, MPI_INT, id, MPI_COMM_WORLD);
        if (wht_j > 0)
            para_QuickSort(wht_data, wht_start, wht_r - 1, wht_m - 1, id, MyID);
        // Использование процессоров 2 ^ wht_m-1 для рекурсивной сортировки данных (wht_r + 1) - wht_end 
        wht_j = MyLength;
        MPI_Bcast(&wht_j, 1, MPI_INT, id, MPI_COMM_WORLD);
        if (wht_j > 0)
            para_QuickSort(wht_tmp, 0, MyLength - 1, wht_m - 1, id + exp2(wht_m - 1), MyID);
        // Отправляем отсортированные данные обратно в процессор id по идентификатору процессора + exp2 (wht_m-1), соответствующему алгоритму 
        if ((MyID == id + exp2(wht_m - 1)) && (MyLength != 0))
            MPI_Send(wht_tmp, MyLength, MPI_INT, id, id + exp2(wht_m - 1), MPI_COMM_WORLD);
        if ((MyID == id) && (MyLength != 0))
            MPI_Recv(wht_data + wht_r + 1, MyLength, MPI_INT, id + exp2(wht_m - 1), id + exp2(wht_m - 1), MPI_COMM_WORLD, &status);
    }
}

    int main(int *argc, char** argv){
        double wht_dataSize;
        int* wht_data;
        int* wht_data1 = nullptr;
        int MyID, SumID; // MyID - идентификатор процесса; SumID  -  количество процессов в группе 
        int wht_i=0, wht_j=0;
        int wht_m=0, wht_r=0;
        MPI_Status status;
        MPI_Init(argc, &argv);
        // MPI_COMM_WORLD - коммуникатор 
        // Определяем ваш собственный идентификатор процесса MyID 
        MPI_Comm_rank(MPI_COMM_WORLD, &MyID);
        // Количество процессов в группе SumID 
        MPI_Comm_size(MPI_COMM_WORLD, &SumID);
        // Корневой процессор (MyID = 0) получает необходимую информацию и назначает каждый процессор для работы 
        wht_data = nullptr;
        if (MyID == 0)
        {
            // Получить длину массива для сортировки 
            wht_dataSize = SIZE;
            wht_data = (int*)malloc(wht_dataSize * sizeof(int));
            wht_data1 = (int*)malloc(wht_dataSize * sizeof(int));
            // Генерация последовательности для динамической сортировки 
            srand(396);
            printf("Случайный массив перед сортировкой: \ n");
            for (wht_i = 0; wht_i < wht_dataSize; wht_i++)
            {
                wht_data[wht_i] = (int)rand();
                wht_data1[wht_i] = wht_data[wht_i];
                if (wht_i < 100)
                    printf("%d ", wht_data[wht_i]);
            }
            printf("... ...\n");
        }
        wht_m = log2(SumID);
        // Передача последовательности данных от корневого процессора другим процессорам 
        // {"1" означает количество элементов в переданном буфере ввода, 
        // "MPI_INT" указывает тип элемента ввода, 
        // «0» означает идентификатор корневого процессора} 
        MPI_Bcast(&wht_dataSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
        // Процессор с идентификационным номером 0 планирует и выполняет сортировку 
        para_QuickSort(wht_data, 0, wht_dataSize - 1, wht_m, 0, MyID);
        // Процессор с идентификационным номером 0 печатает отсортированную упорядоченную последовательность 	
        if (MyID == 0)
        {
            printf("Отсортированный массив: \ n");
            for (wht_i = 0; wht_i < wht_dataSize; wht_i++)
                if (wht_i < 100)
                    printf("%d ", wht_data[wht_i]);
            printf("... ...\n");
        }
        MPI_Finalize();
    }