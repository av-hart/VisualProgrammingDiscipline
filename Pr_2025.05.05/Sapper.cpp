#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <vector>
using namespace std;
using namespace std::chrono;

void output (int a, int b, vector<vector<int>>& Arr) {
    //виведення ігрового поля у текстовому форматі, з нумерацією строк та стовпців
    cout << "\n     ";
    if (b > 9) {
        for (int k=0; k<9; k++) {cout << " " << k+1 << "  ";} // вирівнювання однозначних чисел №1
        for (int k=9; k<b; k++) {cout << k+1 << "  ";}}
    else {
        for (int k=0; k<b; k++) {cout << " " << k+1 << "  ";}
    }
    cout << endl;
    for(int i=0; i<a; i++){
        if (i < 9){cout << "  ";} // вирівнювання однозначних чисел №2
        else {cout << " ";}
        cout << i+1 << " ";
        for(int j=0; j<b; j++){
            cout << " [";
            if (Arr[i][j] == -9) { // невидимі клітинки
                cout << " ";
            } 
            else if (Arr[i][j] == -1) { // міни
                cout << "*";
            }
            else {
                cout << Arr[i][j];
            }
            cout << "]";
            if (j == b-1) {
                cout << endl;
            }
        }
    }
}

// запит гравця про хід
void move (int& x, int& y) {
    cout << "Enter row: ";
    cin >> x; if(x!=0) {x--;}
    cout << "Enter column: ";
    cin >> y; if(y!=0) {y--;}
}

// поява довільної фігури на ігровому полі, границі якої заповнені числами, більшими за 0, а в середині - нулями
void delete_space(int a, int b, vector<vector<int>>& Arr1, vector<vector<int>>& Arr2) {
    bool changed = true;
    while (changed) {
        changed = false;
        for(int i = 0; i < a; i++) {
            for(int j = 0; j < b; j++) {
                if (Arr2[i][j] == 0) {
                    for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                            int ni = i + dx;
                            int nj = j + dy;
                            if (dx == 0 && dy == 0) continue;
                            if (ni >= 0 && ni < a && nj >= 0 && nj < b) {
                                if (Arr2[ni][nj] == -9) {
                                    Arr2[ni][nj] = Arr1[ni][nj];
                                    if (Arr1[ni][nj] == 0) {
                                        changed = true;
                                    }
                                }                            
                            }
                        }
                    }
                }
            }
        }
    }
}

void end_of_time (steady_clock::time_point& start, int delta) {
    auto end = steady_clock::now();
    auto total_seconds = duration_cast<seconds>(end - start).count();

    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    cout << "You found " << delta << " mines in "
         << setfill('0') << setw(2) << hours << ":"
         << setfill('0') << setw(2) << minutes << ":"
         << setfill('0') << setw(2) << seconds << endl;
}


int main(){

    int level, n, mine = -1, delta=0, a, b, x, y, i, j;
    string choice;
    
        cout << "What level would tou prefer?\n" << endl;
        cout << "  n    level    flied   mines" << endl;
        cout << "  1    easy      9x8     10" << endl;
        cout << "  2   medium    15x13    25" << endl;
        cout << "  3    hard     23x15    75" << endl;
        cout << "\nEnter the number: ";
        cin >> level;
        
        switch (level) {
            case 1: n=10; a=9; b=8; break;
            case 2: n=25; a=15; b=13; break;
            case 3: n=75; a=23; b=15; break;
            default: cout << "\n\nInvalid value"; break;
        }

    vector<vector<int>> field(a, vector<int>(b, 0)); // приховане поле
    vector<vector<int>> pl_field(a, vector<int>(b, 0)); // ігрове поле

    for(i=0; i<a; i++){
        for(j=0; j<b; j++){
            field[i][j] = 0;
            pl_field[i][j]= -9; // -9 - позначка для невидимих клітинок
        }
    }

    auto start = steady_clock::now();

    output(a, b, pl_field); // вивід ігрового поля
    move (x, y); // клітинка, яку обрав гравець, має дорівнювати нулю, щоб гра 100% почалась
    pl_field[x][y] = 0;
  
    // заповнення прихованого поля мінами у ранд. клітинках 
    int mines_placed = 0;
    while (mines_placed < n) {
        int p = rand() % a;
        int q = rand() % b;
    
        // "сліпа зона" на ігровому полі (навколо обраної гравцем клітинки)
        if (abs(p - x) <= 1 && abs(q - y) <= 1) continue; 
    
        if (field[p][q] != mine) {
            field[p][q] = mine;
            mines_placed++;
        }
    }

    // якщо в одному з 8 напрямків навколо клітинки є міна, значення цієї клітинки збільшується на 1
    for(i=0; i<a; i++){
        for(j=0; j<b; j++){
            if (field[i][j] != mine) {
                if (i!=0 && j!=0 && field[i-1][j-1] == mine){ //верхній лівий
                    field[i][j]++;
                } 
                if (i!=0 && field[i-1][j] == mine){ //верхній
                    field[i][j]++;
                }
                if (i!=0 && j!=(b-1) && field[i-1][j+1] == mine){ //верхній правий
                    field[i][j]++;
                }
                if (j!=0 && field[i][j-1] == mine){ //лівий
                    field[i][j]++;
                }
                if (j!=(b-1) && field[i][j+1] == mine){ //правий
                    field[i][j]++;
                }
                if (i!=(a-1) && j!=0 && field[i+1][j-1] == mine){ //нижній лівий
                    field[i][j]++;
                } 
                if (i!=(a-1) && field[i+1][j] == mine){ //нижній
                    field[i][j]++;
                }
                if (i!=(a-1) && j!=(b-1) && field[i+1][j+1] == mine){ //нижній правий
                    field[i][j]++;
                }
            }
        }
    }

    pl_field[x][y] = field[x][y];
    delete_space(a, b, field, pl_field);

    while (2) {
        
        // output(a, b, field); // вивід прихованого поля
        output(a, b, pl_field); // вивід ігрового поля
        
        // хід гравця та його обробка
        move (x, y);
        cout << "Is there a mine here? (y/n): ";
        cin >> choice;

        if (choice == "y") {
            if (field[x][y] == -1) {
                pl_field[x][y] = field[x][y];
                delta++;
            }
            else {
                output(a, b, pl_field);
                cout << "\nGame over\n" << endl; 
                cout << "There was no mine here :)" << endl; 
                end_of_time(start, delta);
                break;
            }
        }
        else if (choice == "n") {
            if (field[x][y] == 0) {
                pl_field[x][y] = field[x][y];
                delete_space(a, b, field, pl_field);
            }        
            if (field[x][y] == -1) {
                output(a, b, pl_field);
                cout << "\nGame over\n" << endl; 
                cout << "Oh, there was a mine here! :O" << endl; 
                end_of_time(start, delta);
                break;
            }
            if (field[x][y] != 0 && field[x][y] != -1) {
                pl_field[x][y] = field[x][y];
            }
        }
        
        bool are_equal = true;
        for (i = 0; i < a; ++i) {
            for (j = 0; j < b; ++j) {
                if (field[i][j] >=0 && field[i][j] != pl_field[i][j]) {
                    are_equal = false;
                    break;
                }
            }
            if (!are_equal) break;
        }
        
        if (are_equal || delta == n) {
            output(a, b, pl_field);
            cout << "\nYou win!\n";
            cout << "Congratulations! :D" << endl; 
            end_of_time(start, delta);
            break;
        }
    }

    // Гарт А.
    system("pause");
    return 0;
}
