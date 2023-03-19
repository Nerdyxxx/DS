#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;

const int MAXN = 2e9;
// Не сделал вычисление объема памяти программы потому что у меня не робит компилятор))
int main() {
    cout << "Выполнил Шморгилов Евгений Сергеевич 020303-АИСа-о22" <<endl;
    int a, b;
    cin >> a >> b;

    if (a < 2 || b > MAXN) {
        cout << "Неверное значение диапазон => (2<=A; B <=2 * 10^9)\n";
        return 0;
    }
    auto start = chrono::high_resolution_clock::now();
    int k = 1;
    if (b % a == 0) {
        cout << k;
        return 0;
    }
    k++;
    while (pow(b, k) <= MAXN) {
        if (fmod(pow(b, k), a) == 0) {
            cout << k;
            break;
        } else {
            k++;
        }
    }
    if (pow(b, k) > MAXN) {
        cout << "-1";
    }
    cout << endl;
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Время: " << duration.count() << " ms\n";
    return 0;
}