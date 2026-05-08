#include <iostream>
#include<thread>
#include "Cache.h"
using namespace std;

int main()
{
    Cache<string, string> mc{};

    mc.put("Lmao", "Hello", 3);
    mc.put("Lmao1", "Hello");

    cout << "Waiting 5 seconds...\n";
    this_thread::sleep_for(chrono::seconds(5));
    
    cout << "Stored value: " << mc.get("Lmao") << endl;

    if (mc.exists("Lmao"))
    {
        cout << "Value: " << mc.get("Lmao") << endl;
    }
    else
    {
        cout << "Key expired!" << endl;
    }
    if (mc.exists("Lmao1"))
    {
        cout << "Value: " << mc.get("Lmao1") << endl;
    }
    else
    {
        cout << "Key expired!" << endl;
    }
    return 0;
}