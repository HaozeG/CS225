//
//  test.cpp
//  
//
//  Created by KD on 09.05.21.
//  Modified on 18.03.22
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "listbm.cpp"
using std::cout;
using std::cin;

int main()
{
    BMlist<char> *plist = new BMlist<char>();
    (*plist).append('a');
    (*plist).append('b');
    (*plist).append('c');
    (*plist).append('a');
    (*plist).append('b');
    (*plist).append('c');
    (*plist).append('a');
    (*plist).append('c');
    (*plist).append('a');
    (*plist).append('b');
    (*plist).create_d1();
    (*plist).create_d2();
    /* You should create more target lists */
    BMlist<char> *slist = new BMlist<char>();
    (*slist).append('b');
    (*slist).append('a');
    (*slist).append('b');
    (*slist).append('c');
    (*slist).append('b');
    (*slist).append('a');
    (*slist).append('b');
    (*slist).append('c');
    (*slist).append('a');
    (*slist).append('b');
    (*slist).append('c');
    (*slist).append('a');
    (*slist).append('a');
    (*slist).append('b');
    (*slist).append('c');
    (*slist).append('a');
    (*slist).append('b');
    (*slist).append('c');
    (*slist).append('a');
    (*slist).append('b');
    (*slist).append('c');
    (*slist).append('a');
    (*slist).append('c');
    (*slist).append('a');
    (*slist).append('b');
    (*slist).append('c');
    int position = (*plist).bm(slist);
    if (position >= 0)
        cout << "The pattern list appears in the target list\n" << "at position " << position << ".\n";
    else
        cout << "The pattern list does not appear in the target list.\n";
    (*slist).append('a');
    (*slist).append('a');
    (*slist).append('a');
    (*slist).append('b');
    (*slist).append('c');
    (*slist).append('a');
    (*slist).append('a');
    (*slist).append('c');
    (*slist).append('a');
    (*slist).append('c');
    (*slist).append('c');
    (*slist).append('a');
    (*slist).append('c');
    (*slist).append('a');
    (*slist).append('b');
    (*slist).append('a');
    (*plist).bm_all(slist);
    return 0;
}
