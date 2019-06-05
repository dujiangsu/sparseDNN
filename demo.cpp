#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>


//using namespace std;


int main() {
    string raw_data("3, 4, 5, 76"), tmp;
    vector<string> data;
    stringstream input(raw_data);

    while (getline(input, tmp, ',')) data.push_back(tmp);

    for (auto s : data) cout << stoi(s) << endl;

    return 0;
}
