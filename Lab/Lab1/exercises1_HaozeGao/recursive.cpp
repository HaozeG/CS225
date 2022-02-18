#include <stdio.h>
#include <iostream>
#include "recursive.h"
using std::cin;
using std::cout;
int m, init_n;

int main(){
    // ask for n information
    cout << "please input n:\n";
    cin >> m;
    init_n = m;

    // produce result in recursive way
    recur_row(m);
}

void recur_row(int n){
    // n: row number
    if (n >= 0)
    {
        // recurse down the whole structure
        recur(init_n, 'R');
        // update row number
        m--;
        // to next row
        cout << "\n";
        recur_row(n - 1);
    }
}

void recur(int n, char c){
    if (n > 0)
    {
        recur(n - 1, 'R');
        recur(n - 1, 'W');
    }
    // output contents at the desired row
    if (n == m)
        loop(1 << n, c);
}

// perform the same as a loop
void loop(int n, char c){
    if (n > 0){
        loop(n - 1, c);
        cout << c;
    }
}
