#include <bits/stdc++.h>
#include "VoleMachineSim.h"
#include <windef.h>

using namespace std;

MachineSimulator::MachineSimulator() {};

Register::Register() {};

Memory::Memory() {
    // Initialize cells with all 0x00 values
    fill(begin(cells), end(cells), 0x00);

};

void Memory::store(BYTE address, BYTE &data) {
        cells[address] = (data);
}

void Memory::print() {
    for (auto i = 0; i < 256; i++) {
        cout << "[" << i << ":" << static_cast<int>(cells[i]) << "]\n";
    }
}

void MachineSimulator::loadProgram(const string& filename, BYTE address) {
    fstream programFile(filename);

    if (!programFile.is_open()) {
        cout << "Invalid File Name, Please try again." << endl;
        return;
    }

    cout << "Program Loaded at address: " << hex << static_cast<int>(address) << endl;

    string line;
    BYTE memoryAddress = address;
    while (getline(programFile, line)) {
        istringstream ss(line);
        int token1, token2;

        while (ss >> hex >> token1 >> hex >> token2) {
            BYTE data1 = static_cast<BYTE>(token1);
            BYTE data2 = static_cast<BYTE>(token2);

            // Combine the two bytes and store in memory
            BYTE combinedData = (data1 << 4) | data2;
            memory.store(memoryAddress++, combinedData);
        }
    }
    programFile.close();

    memory.print();
}

