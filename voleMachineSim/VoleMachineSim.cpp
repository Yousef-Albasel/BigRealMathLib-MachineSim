#include <bits/stdc++.h>
#include "VoleMachineSim.h"
#include <windef.h>

using namespace std;


Register::Register() {
    value = 0x00;
}
BYTE Register::getValue() {
    return value;
}
void Register::setValue(BYTE val) {
 value = val;
};

Memory::Memory() {
    // Initialize cells with all 0x00 values
    fill(begin(cells), end(cells), 0x00);

};

void Memory::store(BYTE address, BYTE &data) {
    cells[address] = (data);
}

void Memory::clearMemory() {
    fill(begin(cells), end(cells), 0x00);
}

int Memory::getCell(BYTE idx) {
    return cells[idx];
}

MachineSimulator::MachineSimulator() {
    programCounter = 0x00;
};


void MachineSimulator::loadProgram(const string &filename, BYTE address) {
    fstream programFile(filename);

    if (!programFile.is_open()) {
        cout << "Invalid File Name, Please try again." << endl;
        return;
    }

    cout << "Program Loaded at address: 0x" << hex << uppercase << static_cast<int>(address) << endl;

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
}


void MachineSimulator::displayMenu() {
    int opt;
    printf(" 1- Load Program\n"
           " 2- Clear Memory\n"
           " 3- Show Memory Status\n"
           " 4- Exit\n");
    cin >> opt;
    string f_name;
    int address_NAME;
    BYTE address;
    switch (opt) {
        case 1:
            printf("Enter File Program name: \n");
            cin >> f_name;
            printf("Enter starting address in hex: \n");
            cin >> hex >> address_NAME;
            address = static_cast<BYTE>(address_NAME );

            MachineSimulator::loadProgram(f_name, address);
            break;
        case 2:
            MachineSimulator::memory.clearMemory();
            break;
        case 3:
            MachineSimulator::display_Status();
            break;
        case 4:
            exit(-1);
            break;

    }
}

void MachineSimulator::display_Status() {
    // Print Memory Layout
    cout << "Memory Layout:" << endl;
    cout << "----------------" << endl;

    for (int i = 0; i < 256; i++) {
        if (i == 64 || i == 128 || i == 192) {
            cout << endl;
        }
        cout << "[" << uppercase << setw(2) << setfill('0') << i << ":"
             << uppercase << setw(2) << setfill('0') << static_cast<int>(memory.getCell(i)) << "]\n";
    }
    cout << endl << "----------------" << endl;

    // Print Register Values
    cout << "Register Values:" << endl;
    cout << "----------------" << endl;

    for (int i = 0; i < 16; ++i) {
        cout << "[" <<hex<< uppercase << setw(2) << setfill('0') << i << ":"
             << uppercase << setw(2) << setfill('0') << static_cast<int>(registers[i].getValue()) << ']' << endl;
    }
    cout << "----------------" << endl;
}


