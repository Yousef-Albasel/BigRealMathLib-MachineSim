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
}

Memory::Memory() {
    // Initialize cells with all 0x00 values
    fill(begin(cells), end(cells), 0x00);

}

void Memory::store(BYTE address, BYTE data) {
    cells[address] = (data);
}

void Memory::clearMemory() {
    fill(begin(cells), end(cells), 0x00);
}

BYTE Memory::getCell(int idx) {
    return cells[idx];
}

BYTE *Memory::getStartAddress() {
    return &cells[0];
}

MachineSimulator::MachineSimulator() {
    BYTE *initialAddress = memory.getStartAddress();
    programCounter = *initialAddress;
    instructionRegister[0].setValue(0x00);
    instructionRegister[1].setValue(0x01);
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
        int token1, token2, token3;

        while (ss >> hex >> token1 >> hex >> token2 >> hex >> token3) {
            BYTE data1 = static_cast<BYTE>(token1);
            BYTE data2 = static_cast<BYTE>(token2);
            BYTE data3 = static_cast<BYTE>(token3);

            // Combine the two bytes and store in memory
            BYTE combinedData = (data1 << 4) | data2;
            memory.store(memoryAddress++, combinedData);
            combinedData = (data3 << 4);
            memory.store(memoryAddress++, '0'+combinedData);
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
           " 5- Fetch Program Counter\n"
           " 6- Decode Instruction\n"
           " 7- One Cycle\n"
           " 8- Run Until Terminate\n"
           " Other- Exit\n");
    cin >> opt;
    string f_name;
    int address_NAME;
    BYTE address, PC_Address;
    int PC_Address_NAME;
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
            cin >> hex >> PC_Address_NAME;
            PC_Address = static_cast<BYTE>(PC_Address_NAME);
            setProgramCounter(PC_Address);
            break;
        case 5:
            fetchInstruction();
            break;
        case 6:
            decode();
            break;
        case 7:
            findAndExecuteInstruction(opcode, registerIndex, addValue);
            break;
        default :
            exit(-1);
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
        cout << "[" << hex << uppercase << setw(2) << setfill('0') << i << ":"
             << uppercase << setw(2) << setfill('0') << static_cast<int>(registers[i].getValue()) << ']' << endl;
    }
    cout << "----------------\n\n";

    cout << "Program Counter= 0x" << uppercase << setw(2) << setfill('0') << static_cast<int>( programCounter) << " \n";
    cout << "Instruction Register= " << hex << uppercase
         << setw(2) << setfill('0') << static_cast<int>(instructionRegister[0].getValue())
         << setw(2) << setfill('0') << static_cast<int>(instructionRegister[1].getValue()) << endl;
}

void MachineSimulator::setProgramCounter(BYTE address) {
    programCounter = address;
}

void MachineSimulator::fetchInstruction() {
    // Get the two bytes from memory starting from the PC Address
    BYTE byte1 = memory.getCell(programCounter);
    BYTE byte2 = memory.getCell(programCounter + 1);

    programCounter += 2;

    instructionRegister[0].setValue(byte1);
    instructionRegister[1].setValue(byte2);
    cout << "Instruction: " << uppercase << hex << setw(2) << setfill('0') << static_cast<int>(byte1);
    cout << uppercase << hex << setw(2) << setfill('0') << static_cast<int>(byte2) << endl;

}

void MachineSimulator::decode() {
    // Combine the two bytes
    BYTE data1 = instructionRegister[0].getValue(); //0001 0011 -> 0011 0000
    BYTE data2 = instructionRegister[1].getValue(); //0010 0011
    cout << "Instruction: " << uppercase << hex << setw(2) << setfill('0') << static_cast<int>(data1);
    cout << uppercase << hex << setw(2) << setfill('0') << static_cast<int>(data2) << endl;

    opcode = data1 >> 4;
    registerIndex = data1 & 0x0F;
    addValue = data2;
    cout << "\n Opcode:" << uppercase << hex << static_cast<int>(opcode)
         << " Reg:" << uppercase << hex << static_cast<int>(registerIndex)
         << " Add" << uppercase << hex << setw(2) << setfill('0') << static_cast<int>(addValue) << endl;

}

void MachineSimulator::findAndExecuteInstruction(BYTE opcode, BYTE registerIndex, BYTE addressValue) {
    BYTE f_bits, s_bits;
    int add_result;
    f_bits = addressValue >> 4;
    s_bits = addressValue & 0x0F;
    switch (opcode) {
        case 0x01:
            registers[registerIndex].setValue(memory.getCell(addressValue));
            break;
        case 0x02:
            registers[registerIndex].setValue(addressValue);
            break;
        case 0x03:
            // 3210 put content of reg 2 in add 10
            memory.store(addressValue, registers[registerIndex].getValue());
            break;
        case 0x04:
            registers[s_bits] = registers[f_bits];
            break;
        case 0x05:

            break;
        case 0x0B:
            if(registers[registerIndex].getValue() == registers[0x00].getValue())
            {
                programCounter = addressValue;
            }
            break;
        case 0x0C:
            if (registerIndex == 0x00 && addressValue == 0x00){
                cout << "Program Executed Successfully!\n";
                break;
            }else{
                cout << "Invalid Format for the operand\n";
            }
        default:
            cout << "Invalid opcode: " << hex << uppercase << static_cast<int>(opcode) << endl;
            break;
    }
}

