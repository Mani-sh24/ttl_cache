#include <iostream>
#include<thread>
#include "Cache.h"
using namespace std;

int main()
{
    Cache<string, string> mc{};

    mc.put("Lmao", "Hello", 1);

    cout << "Stored value: " << mc.get("Lmao") << endl;

    cout << "Waiting 3 seconds...\n";
    this_thread::sleep_for(chrono::seconds(3));

    if (mc.exists("Lmao"))
    {
        cout << "Value: " << mc.get("Lmao") << endl;
    }
    else
    {
        cout << "Key expired!" << endl;
    }
    return 0;
}