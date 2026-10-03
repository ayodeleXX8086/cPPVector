#include <iostream>

#include "core_implementation/Vectors.h"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    core_implementation::Vectors<int> v(2);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    for (const int t:v) {
        std::cout<< "The number is " << t<<std::endl;
    }
    std::cout<< "Vector index at " << 2 << " is " << v[2]  << "\n";
    v[2]=4;
    std::cout<< "After setting index at "<< 2 << " is "<< v[2] << "\n";
    int testVariable = 324234324;
    v.push_back(testVariable);
    std::cout<< "After inserted \n";
    std::cout<< "Vector length " << v.size() << " is " << v[v.size()-1]  << "\n";
    std::cout<< "Test variable "<< testVariable << "\n";
    return 0;
}