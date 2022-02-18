#include <math.h>
#include <stdio.h>
#include <iostream>
using std::cout;
using std::cin;

int main(){
    // ask for n information
    int n;
    cout << "please input n:\n";
    cin >> n;

    // produce result in sequential way
    char c;
    for (int i = 0; i <= n; i++)
    {
        // for every segment in the same row
        for (int j = 0; j < pow(2, i); j++)
        {
            // choose color
            if (j % 2 == 0){
                c = 'R';
            } else {
                c = 'W';
            }
            // output the color in each segment
            for (int k = 0; k < pow(2, n-i); k++)
            {
                cout << c;
            }
        }
        // go to a new row
        cout << "\n";
    }
}
