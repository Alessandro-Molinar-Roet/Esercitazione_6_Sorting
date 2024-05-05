#include<iostream>
#include<unistd.h> //per sleep()
#include<chrono> //libreria per misurare tempo
#include<algorithm> //per generate
#include"SortingAlgorithm.hpp"

using namespace std;
using namespace SortLibrary;

int main()
{
    cout << "Inserisci la dimensione del vettore: ";
    int dimension = 0;
    cin >> dimension;

    int max = 1000; // numero casuali in [0,namx]
    int times = 50; // quante volte prendo tempi per media
    double merge_duration = 0;
    double bubble_duration = 0;
    double fake_merge_duration = 0;
    double fake_bubble_duration = 0;

    for(int i = 0; i<times; i++){
        srand(time(0)*i); //prende istante tempo e lo usa come randomseed cosi cambiano numeri

        vector<double> vM(dimension);
        generate( vM.begin(),vM.end(), [&]() {return rand() % max;});
        vector<double> vB = vM; //copio vettore poiche passati a sort per referenza

        //ordino vettore casuale con MergeSort
        chrono::steady_clock::time_point M_begin = chrono::steady_clock::now(); //inizio timer
        MergeSort(vM);
        chrono::steady_clock::time_point M_end = chrono::steady_clock::now(); //fine timer
        merge_duration += chrono::duration_cast<chrono::microseconds>(M_end-M_begin).count(); //intervallo di tempo

        //ordino vettore casuale gia ordinato con MergeSort
        chrono::steady_clock::time_point F_M_begin = chrono::steady_clock::now();
        MergeSort(vM);
        chrono::steady_clock::time_point F_M_end = chrono::steady_clock::now();
        fake_merge_duration += chrono::duration_cast<chrono::microseconds>(F_M_end-F_M_begin).count();

        //ordino vettore casuale con BubbleSort
        chrono::steady_clock::time_point B_begin = chrono::steady_clock::now();
        BubbleSort(vB);
        chrono::steady_clock::time_point B_end = chrono::steady_clock::now();
        bubble_duration += chrono::duration_cast<chrono::microseconds>(B_end-B_begin).count();

        //ordino vettore casuale gia ordinato con BubbubleSort
        chrono::steady_clock::time_point F_B_begin = chrono::steady_clock::now();
        BubbleSort(vB); // gia ordinato
        chrono::steady_clock::time_point F_B_end = chrono::steady_clock::now();
        fake_bubble_duration += chrono::duration_cast<chrono::microseconds>(F_B_end-F_B_begin).count();
    }

    double merge_average = merge_duration/times;
    double bubble_average = bubble_duration/times;

    double fake_merge_average = fake_merge_duration/times;
    double fake_bubble_average = fake_bubble_duration/times;

    cout << "\n";
    cout << "Sorting test of non order random vector with dimension: " << dimension << "\n";
    cout << "Mergesort: " << merge_average << "\n";
    cout << "Bubblesort: " << bubble_average << "\n\n";
    cout << "Sorting test of order vector with dimension: " << dimension << "\n";
    cout << "Mergesort: " << fake_merge_average << "\n";
    cout << "Bubblesort: " << fake_bubble_average << endl;

    return 0;
}

