#include <bits/stdc++.h>
#include "VoleMachineSim.h"
#include <windef.h>

using namespace std;


Register::Register() {
    value = 0x00;
}
BYTE Register::getValue() const {
    return value;
}
void Register::setValue(BYTE val) {
 value = val;
}

Memory::Memory() {
    // Initialize cells with all 0x00 values
    fill(begin(cells), end(cells), 0x00);

}

void Memory::store(BYTE address, BYTE &data) {
    cells[address] = (data);
}

void Memory::clearMemory() {
    fill(begin(cells), end(cells), 0x00);
}

BYTE Memory::getCell(int idx) {
    return cells[idx];
}

BYTE* Memory::getStartAddress()  {
    return &cells[0];
}

MachineSimulator::MachineSimulator() {
    BYTE* initialAddress = memory.getStartAddress();
    programCounter = initialAddress;

}


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
           " 4- Set Program Counter\n"
           " 5- One Cycle\n"
           " 6- Run Until Terminate\n"
           " Other- Exit\n");
    cin >> opt;
    string f_name;
    int address_NAME;
    BYTE address;
    BYTE PC_Address;
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
            MachineSimulator::displayStatus();
            break;
        case 4:
            cout << "Enter Address to start fetching from: \n";
            cin >>hex >> PC_Address;
            setProgramCounter(&PC_Address);
            break;
        default :
            return;
    }
}

void MachineSimulator::displayStatus() {
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

    cout << "Program Counter= " << *programCounter << " \n";
}

void MachineSimulator::setProgramCounter(BYTE* address) {
    programCounter = address;
}

