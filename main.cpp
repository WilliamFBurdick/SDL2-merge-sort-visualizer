#include <iostream>
#include <time.h>
#include <thread>
#include <chrono>
#include <random>
#include <ranges>
#include "SDL2/include/SDL2/SDL.h"

using namespace std;
using namespace std::chrono;

int gap = 4;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
int arrSize;

void draw_state(int* arr, int green1, int green2, int red)
{
    for (int index = 0; index < arrSize; index++)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, index, 99, index, arr[index]);
    }
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, red, 99, red, arr[red]);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(renderer, green1, 99, green1, arr[green1]);
    SDL_RenderDrawLine(renderer, green2, 99, green2, arr[green2]);
}

void merge(int array[], int left, int mid, int right)
{
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    int* leftArr = new int[leftSize];
    int* rightArr = new int[rightSize];

    for (int i = 0; i < leftSize; i++)
    {
        leftArr[i] = array[left + i];
    }
    for (int i = 0; i < rightSize; i++)
    {
        rightArr[i] = array[mid + 1 + i];
    }
    int leftIndex = 0;
    int rightIndex = 0;
    int mergedIndex = left;
    while(leftIndex < leftSize && rightIndex < rightSize)
    {
        if (leftArr[leftIndex] <= rightArr[rightIndex])
        {
            array[mergedIndex] = leftArr[leftIndex];
            leftIndex++;
        }
        else
        {
            array[mergedIndex] = rightArr[rightIndex];
            rightIndex++;
        }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            draw_state(array, left, right, mergedIndex);

            SDL_RenderPresent(renderer);
            SDL_Delay(40);
        mergedIndex++;
    }
    while (leftIndex < leftSize)
    {
        array[mergedIndex] = leftArr[leftIndex];
        leftIndex++;
        mergedIndex++;
    }
    while (rightIndex < rightSize)
    {
        array[mergedIndex] = rightArr[rightIndex];
        rightIndex++;
        mergedIndex++;
    }

}

void MergeSort(int array[], int first, int last)
{
    if (first >= last)
    {
        return;
    }
    int mid = first + (last - first) / 2;
    MergeSort(array, first, mid);
    MergeSort(array, mid + 1, last);
    // thread t1(MergeSort, array, first, mid);
    // thread t2(MergeSort, array, mid + 1, last);
    // t1.join();
    // t2.join();
    merge(array, first, mid, last);
}

int* CreateArray(int size)
{
    int* arr = new int[size];
    std::random_device rd;
    std::uniform_int_distribution d(1,99);
    for (int i = 0; i < size; i++)
    {
        arr[i] = d(rd);
    }
    return arr;
}

void PrintArray(int* const arr, int const size)
{
    for (int i = 0; i < size; i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<'\n';
}

int main(int argc, char* argv[])
{    
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout<<"Failed to initialize the SDL2 library\n";
        return -1;
    }
    //SDL_CreateWindowAndRenderer(100 * 10, 100*10, 0, &window, &renderer);
    window = SDL_CreateWindow("Merge Sort Visual", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 100*10, 100*10, 0);
    if (!window)
    {
        std::cout<<"Failed to create window\n";
        return -1;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderSetScale(renderer, 10, 10);
    cout<<"Renderer: "<<renderer<<"\n";
    SDL_UpdateWindowSurface(window);
    srand(time(NULL));
    arrSize = 100;

    int* arr = CreateArray(arrSize);
    cout<<"Unsorted Array: ";
    PrintArray(arr, arrSize);
    


    MergeSort(arr, 0, arrSize);
    cout<<"Sorted Array: ";
    PrintArray(arr, arrSize);



    return 0;
}