//CPP program to illustrate auto-initializing of pair STL
#include <iostream>
#include <utility>

using namespace std;

/// Initializing a pair
/// If not initialized, the first value of the pair gets automatically initialized.

int main()
{
    pair <int, double> PAIR1 ;
    pair <string, char> PAIR2 ;

    cout << PAIR1.first ;  //it is initialised to 0
    cout << PAIR1.second ; //it is initialised to 0

    cout << " ";

    cout << PAIR2.first ;  //it prints nothing i.e NULL
    cout << PAIR2.second ; //it prints nothing i.e NULL

    return 0;
}
