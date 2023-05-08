#include<iostream>
#include<string.h>
#include<fstream>
#include<iomanip>
using namespace std;

struct Data {
    int key;
    char * value;
};

int MAXSIZE = 100;
int MaxValue = 2049;

void Sort_count(Data *arr, int n, int k) {
    int count[k+1];
    for (int i = 0; i < k+1; ++i) {
        count[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        count[arr[i].key] += 1;
    }
    for (int i = 1; i < k+1; i++) {
        count[i] = count[i] + count[i-1];
    }
    Data *n_arr = new Data[n];
    for (int i = n - 1; i >= 0; i--) {
        int index = count[arr[i].key] - 1;
        count[arr[i].key]--;
        n_arr[index] = arr[i];
    }
    memcpy(arr, n_arr, n * sizeof(Data));
    delete[] n_arr;
}


int main() {
    ios:: sync_with_stdio(false);
    ifstream fin("input.txt");
    int n = 0;
    int key = 0;
    int max_key = -1;
    char value[2049];
    memset(value, '\0', sizeof(char) * 2049);
    Data *arr = new Data[MAXSIZE];
    while (fin >> key >> value) {
        if (max_key < key) {
            max_key = key;
        }
        int sizevalue = strlen(value);
        arr[n].value = (char*) malloc((sizevalue+1) * sizeof(char));
        arr[n].key = key;
        strncpy(arr[n].value, value, sizevalue+1);
        n++;
        if (n == MAXSIZE) {
            MAXSIZE *= 2;
            arr = (Data *) realloc(arr, MAXSIZE * sizeof(Data));
        }
    }
    fin.close();
    Sort_count(arr, n, max_key);
    for (int i = 0; i < n; i++) {
        printf("%06d\t%s\n", arr[i].key, arr[i].value);
    }
    delete [] arr;
    return 0;
}
