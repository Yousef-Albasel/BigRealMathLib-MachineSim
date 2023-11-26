//                                                                      بسم الله الرحمن الرحيم
#include <windef.h>
#include "VoleMachineSim.cpp"
#include <bits/stdc++.h>

#define BYTE unsigned char
using namespace std;

int main() {
    MachineSimulator CPU;
    printf("Welcome to Vole Machine Simulator\n");
    while (true) {
        CPU.displayMenu();
    }
}
