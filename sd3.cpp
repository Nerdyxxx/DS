#include <iostream>
#include <vector>
using namespace std;





int posledniychelovek(int N, int M) {
    vector<int> people(N);
    for (int i = 0; i < N; i++) {
        people[i] = i + 1; // Нумерация людей от 1 до N
    }

    int current = 0;
    while (people.size() > 1) {
        current = (current + M - 1) % people.size();
        people.erase(people.begin() + current);
    }

    return people[0];
}

int startchelovek(int N, int z2last, int M) {
    vector<int> people(N);
    for (int i = 0; i < N; i++) {
        people[i] = i + 1; // Нумерация людей от 1 до N
    }

    int current = 0;
    while (people.size() > 1) {
        current = (current + M - 1) % people.size();
        if (people[current] == z2last) {
            break;
        }
        people.erase(people.begin() + current);
    }

    return people[(current + 1) % people.size()];
}

void menu2() {
    cout << "#########################################################" << endl;
    cout << "  1. Задание А, номер оставшегося человека" << endl;
    cout << "  2. Задание Б, номер человека с которого начился счёт" << endl;
    cout << "#########################################################" << endl;
    cout << endl << "==> ";
    int N;
    int M;
    int menu;
    cin >> menu;
    if (menu == 1)
    {
        cout << "N => ";
        cin >> N;
        cout << endl << "M => ";
        cin >> M;
        int last = posledniychelovek(N, M);
        cout << "Оставшийся человек: " << last << endl;

    } else if (menu == 2) {
        cout << "N => ";
        cin >> N;
        cout << endl << "M => ";
        cin >> M;
        int z2last;
        cout << endl << "Оставшийся чевовек => ";
        cin >> z2last;
        int z2start = startchelovek(N, z2last, M);
        cout << endl << "Начинал счет с человека №" << z2start << endl;



    } else {
        cout << endl << "ERROR";
        menu2();
    }
}


int main() {
    cout << endl;
    cout << "Выполнил Шморгилов Евгений 020303-АИСа-о22" << endl;
    menu2();
    return 0;
}