
#include <iostream>
#include <map>
#include <string>

using namespace std;

class Solution {
public:
    std::map<string, int> Roman;
    int romanToInt(string s) {
        return 0;
    }
};

int main() {
    Solution test;
    cout << test.romanToInt("III") << endl;     //3
    cout << test.romanToInt("IV") << endl;      //4
    cout << test.romanToInt("IX") << endl;      //9
    cout << test.romanToInt("LVIII") << endl;   //58
    cout << test.romanToInt("MCMXCIV") << endl; //1994
    cout << test.romanToInt("XLIX") << endl;    //49
    cout << test.romanToInt("CMXCIX") << endl;  //999
}
