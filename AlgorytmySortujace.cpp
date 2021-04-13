#include <iostream>
#include <cstdlib>
#include <vector>
#include <chrono>
#define SIZE 10000   //Liczba elementów w tablicy
#define NUMBER 100   //Liczba tablic w pojedyńczym teście


template<class T>
bool test(std::vector<T> arr , int length)  //Funkcja testująca czy posortowano poprawnie
{
    for(int i = 0; i < length-1; i++)
    {
        if( arr[i] > arr[i+1] ) { return false; }
    }
    return true;
}

template<class T>
void swap(T &a, T &b)  //funkcja zamieniająca elementy miejscami
{
    T tmp = a;
    a = b;
    b = tmp;
}

template<class T>
void printArray(std::vector<T> arr , int length)        //Funkcja wypisująca elementy tablicy
{
    for(int i = 0; i < length; i++)
    {
        std::cout << arr[i] << "\n";
    }
}

template<class T>
void quickSort(std::vector<T> &arr , int left , int right)    //Funkcja wykonująca sortowanie rekursywnym algorytmem quick sort
{
    int pivot = arr[(right+left)/2];   //wybór pivotu jako środkowego elementu

    int j = left;
    for(int i = left; i < right; i++)
    {
        if( arr[i] < pivot ) //Przyrównanie elementu do pivota
        {                    //Zamiana elementów miejscami
            T tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            j++;
        }
        
    }
    arr[right] = arr[j];
    arr[j] = pivot;
    if(left < j - 1) quickSort<T>(arr,left,j-1);     //Wywołanie quickSort dla lewej części
    if(j + 1 < right) quickSort<T>(arr,j+1,right);   //Wywołanie quickSort dla prawej części

}

template<class T>
void mergeSort(std::vector<T> &arr , int left , int right) //Algorytm sortowania przez scalanie
{
    if(left < right)  //Sprawdzanie czy przedział w którym sortujemy zawiera więcej elementów niż 1
    {
        int mid = (right+left)/2;     //wyznaczenie środka przedziału w którym sortujemy
        mergeSort(arr,left,mid);      //wywołanie mergSort() dla dwóch nowo powstałych przedziałów
        mergeSort(arr,mid+1,right);

        //Początek procedury scalania
        int lenL = mid - left + 1;      //długość lewej tablicy
        int lenR = right - mid; //długość prawej tablicy

        std::vector<T> L(lenL); //deklaracja tablic
        std::vector<T> R(lenR);

        for(int i = 0; i < lenL; i++) //przepisanie elementów do lewej tablicy
        {
            L[i] = arr[left+i];
        }

        for(int i = 0; i < lenR; i++) //przepisanie elementów do prawej tablicy
        {
            R[i] = arr[mid+i+1];
        }
        //inicjalizacja indeksów dla tablic
        int i = 0;
        int j = 0;
        int k = left;

        while(i < lenL && j < lenR) //porównywanie składników tablic i przepisywanie mniejszego
        {
            if( L[i] <= R[j] )
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        
        while(i < lenL) //przepisanie pozostałych składników lewej tablicy
        {
            arr[k] = L[i];
            i++;
            k++;
        }
        while(j < lenR) //przepisanie pozostałych składników prawej tablicy
        {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
}

template<class T>
void heapify(std::vector<T> &arr, int length, int i) //Tworzenie kopca(gałęzi) maksymalnego
{
    int max = i;    //inicjalizacja max jako index rodzica (korzenia)
    int L = 2*i+1;  //inicjalizacja L jako index pierwszego dziecka rodzica
    int R = 2*i+2;  //inicjalizacja R jako index drugiego dziecka rodzica
 
    if (L < length && arr[L] > arr[max]) //przyrównanie pierwszego dziecka do rodzica
    {
        max = L;
    }

    if (R < length && arr[R] > arr[max]) //przyrównanie drugiego dziecka do rodzica
    {
        max = R;
    }

    if (max != i) //Jeśli rodzic nie był większy od dzieci to zamień i wywołaj funkcje dla kolejnego
    {
        swap(arr[i], arr[max]);
        heapify(arr, length, max);
    }
}
 

template<class T>
void heapSort(std::vector<T> &arr, int length)
{
    
    for (int i = length/2-1; i >= 0; i--) // maksymalizuj kopiec od ostatniego rodzica do pierwszego
    {
        heapify(arr, length, i);
    }

    for (length--; length > 0; length--) //odrzucaj ostatni element i maksymalizuj kopiec aż do wyczerpania elementów
    { 
        swap(arr[0], arr[length]);
        heapify(arr, length, 0);
    }
}

int main()
{
    float lvl[] = { 0.0 , 0.25 , 0.5 , 0.75 , 0.95 , 0.99 , 0.997};   //Poziomy posortowania

    for(int k = 0; k < 7; k++)
    {
        int default_value = 1;

        std::vector<std::vector<int>> matrixQ;    //Deklaracja tablicy
        matrixQ.resize(NUMBER, std::vector<int>(SIZE, default_value));    //Ustawienie rozmiaru tablic

        //WYPEŁNIENIE TABLICY
        
        for(int i = 0; i < NUMBER; i++)
            for(int j = int(lvl[k]*SIZE) - 2; j < SIZE; j++)
                matrixQ[i][j] = (1000000 + rand() % 10000000);
        
        for(int i = 0; i < NUMBER; i++)
            for(int j = 0; j < int(lvl[k]*SIZE); j++)
                matrixQ[i][j] = j;
                
    /* ************ ODWROTNA *************
        for(int i = 0; i < NUMBER; i++)
            for(int j = 0; j < SIZE; j++)
                matrixQ[i][j] = SIZE-j;
    */// *********************************

        //Kopiowanie tablicy
        std::vector<std::vector<int>> matrixM(matrixQ);
        std::vector<std::vector<int>> matrixH(matrixQ);

        //QuickSort Test
        auto startQ = std::chrono::steady_clock::now();
        for(int i = 0; i < NUMBER; i++)
        {
            quickSort<int>(matrixQ[i],0,SIZE-1);
        }
        auto endQ = std::chrono::steady_clock::now();
        auto Q_ms = std::chrono::duration_cast<std::chrono::milliseconds>(endQ - startQ); //std::chrono::duration<unsigned long long, std::milli>
        
    
        //MergeSort Test
        auto startM = std::chrono::steady_clock::now();
        for(int i = 0; i < NUMBER; i++)
        {
            mergeSort(matrixM[i],0,SIZE-1);
        }
        auto endM = std::chrono::steady_clock::now();
        auto M_ms = std::chrono::duration_cast<std::chrono::milliseconds>(endM - startM); //std::chrono::duration<unsigned long long, std::milli>
    
        //HeapSort Test
        auto startH = std::chrono::steady_clock::now();
        for(int i = 0; i < NUMBER; i++)
        {
            //introSort(matrixH[i],0,SIZE-1,9);
            heapSort(matrixH[i],SIZE);
        }
        auto endH = std::chrono::steady_clock::now();
        auto H_ms = std::chrono::duration_cast<std::chrono::milliseconds>(endH - startH); //std::chrono::duration<unsigned long long, std::milli>
    

        std::cout << "\n   SIZE: " << SIZE << "  |  Level: " << lvl[k]*100 << "%";
        std::cout << "\n---------------------------";
        std::cout << "\n QuickSort: " << Q_ms.count() << "ms";
        std::cout << "\n MergeSort: " << M_ms.count() << "ms";
        std::cout << "\n HeapSort:  " << H_ms.count() << "ms";
        std::cout << "\n---------------------------";

    }
    return 0;
}