//
// Created by youse on 11/12/2023.
//
#include <windef.h>
#include "VoleMachineSim.h"
#include <bits/stdc++.h>
using namespace std;
int main() {
    string programFile;
    BYTE startingAddress;
    MachineSimulator CPU;
    printf("Enter Program File name: ");
    CPU.loadProgram("ins.txt",00);

    return 0;
}