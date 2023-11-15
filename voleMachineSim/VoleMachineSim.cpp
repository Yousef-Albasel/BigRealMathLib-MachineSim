#include <bits/stdc++.h>
#include "VoleMachineSim.h"

#define BYTE unsigned char
using namespace std;
enum Opcodes {
    LOAD = 0X1,
    LOAD2 = 0X2,
    STORE = 0X3,
    MOVE = 0X4,
    ADD = 0X5,
    JUMP = 0XB,
    HALT = 0XC
};

/* ============ Register Implementation ============*/

Register::Register() {
    value = 0x00; // initialize with 0x0
}

BYTE Register::getValue() {
    return value; // Getter method
}

void Register::setValue(BYTE val) {
    value = val; // Setter Method
}

/*  ============ Memory Implementation ============*/

Memory::Memory() {
    // Initialize cells with all 0x00 values
    fill(begin(cells), end(cells), 0x00);
}

void Memory::store(BYTE address, BYTE data) {
    cells[address] = (data); // Setter method for using on array of cells
}

void Memory::clearMemory() {
    fill(begin(cells), end(cells), 0x00); // clear memory method sets all with 0x0
}

BYTE Memory::getCell(int idx) {
    return cells[idx]; // getter method
}
//
//BYTE *Memory::getStartAddress() {
//    return &cells[0];
//}

/* ============ Machine Implementation ============*/

MachineSimulator::MachineSimulator() {
    programCounter = 0x0;
    instructionRegister[0].setValue(0x00);
    instructionRegister[1].setValue(0x01);
}


void MachineSimulator::clearRegisters() {
    for (int i = 0; i < 16; ++i) {
        registers[i].setValue(0x0); // Clears all registers and screen
    }
    screenOutput = "";
}

// loading the file function
void MachineSimulator::loadProgram(const string &filename, BYTE address) {
    fstream programFile(filename);

    if (!programFile.is_open()) {
        cout << "Invalid File Name, Please try again." << endl;
        return;
    }

    cout << "Program Loaded at address: 0x" << hex << uppercase << static_cast<int>(address) << endl;

    string line;
    BYTE memoryAddress = address;
    // Consider taking the input line as 0XA 0XB 0XCD
    while (getline(programFile, line)) {
        istringstream ss(line); // string stream to get each token separately
        int token1, token2, token3; // eg: token1 = 0xA , token2 = 0xB, token3 = 0xCD

        while (ss >> hex >> token1 >> hex >> token2 >> hex >> token3) { // take the whole 3 tokens per lien
            BYTE data1 = static_cast<BYTE>(token1);
            BYTE data2 = static_cast<BYTE>(token2);
            BYTE data3 = static_cast<BYTE>(token3);

            // Combine the first two tokens and store in memory
            BYTE combinedData = (data1 << 4) | data2;
            memory.store(memoryAddress++, combinedData);
            memory.store(memoryAddress++, data3); // store the last token in memory, as it doesn't need combine
        }
    }
    programFile.close();
}


void MachineSimulator::displayMenu() {
    int opt;
    printf(" 1- Load Program\n"
           " 2- Show Memory Status\n"
           " 3- Set Program Counter\n"
           " 4- Fetch Program Counter\n"
           " 5- Decode Instruction\n"
           " 6- One Cycle\n"
           " 7- Run Until Halt\n"
           " 8- Clear Memory\n"
           " 9- Clear Registers\n"
           " Other- Exit\n");
    cin >> opt;
    string f_name;
    int address_NAME;
    BYTE address, PC_Address;
    int PC_Address_NAME;
    switch (opt) {
        case 1: // Load file
            printf("Enter File Program name: \n");
            cin >> f_name;
            printf("Enter starting address in hex: \n");
            cin >> hex >> address_NAME;
            address = static_cast<BYTE>(address_NAME );

            MachineSimulator::loadProgram(f_name, address);
            break;
        case 2: // clear memory
            MachineSimulator::memory.clearMemory();
            MachineSimulator::clearRegisters();
            break;
        case 3: // display current memory and registers and counters status
            MachineSimulator::displayStatus();
            break;
        case 4: // start fetching from a specific location
            cout << "Enter Address to start fetching from: \n";
            cin >> hex >> PC_Address_NAME;
            PC_Address = static_cast<BYTE>(PC_Address_NAME);
            setProgramCounter(PC_Address);
            break;
        case 5: // fetch current PC
            fetchInstruction();
            break;
        case 6: // DECODE the current instruction
            decode();
            break;
        case 7: // execute current instruction
            findAndExecuteInstruction(opcode, registerIndex, addValue);
            break;
        case 8: // keep executing until halt
            while (true) {
                fetchInstruction();
                decode();
                findAndExecuteInstruction(opcode, registerIndex, addValue);

                if (opcode == 0x0C && registerIndex == 0x00 && addValue == 0x00) {
                    cout << "Program Executed Successfully!\n";
                    break;
                }
            }
            break;
        default :
            exit(-1);
    }
}

void MachineSimulator::displayStatus() {
    //  Print Memory Layout
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
    if (!screenOutput.empty())
        cout << "Screen:" << screenOutput << endl;
    cout << "Program Counter= 0x" << uppercase << setw(2) << setfill('0') << static_cast<int>( programCounter) << " \n";
    cout << "Instruction Register= " << hex << uppercase
         << setw(2) << setfill('0') << static_cast<int>(instructionRegister[0].getValue())
         << setw(2) << setfill('0') << static_cast<int>(instructionRegister[1].getValue()) << endl;
}

// setting program counter to specific location 
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

    opcode = data1 >> 4; // shift 4 bits to the right, so we can get the opcode separately
    registerIndex = data1 & 0x0F; // add with 0x00001111, so we can get the second nipple separately
    addValue = data2; // the value in address is the data2.
    cout << "\n Opcode:" << uppercase << hex << static_cast<int>(opcode)
         << " Reg:" << uppercase << hex << static_cast<int>(registerIndex)
         << " Add" << uppercase << hex << setw(2) << setfill('0') << static_cast<int>(addValue) << endl;

}

void MachineSimulator::findAndExecuteInstruction(BYTE opcode, BYTE registerIndex, BYTE addressValue) {
    BYTE f_bits, s_bits;
    int add_result;
    f_bits = addressValue >> 4;
    s_bits = addressValue & 0x0F;
    int f_val, s_val;
    switch (opcode) {
        case LOAD:
            registers[registerIndex].setValue(memory.getCell(addressValue));
            cout << "LOAD 0x" <<setw(2)<<setfill('0')<< registerIndex << " with pattern in: 0x" << static_cast<int>(addressValue) << ". [SUCCESS]\n";
            break;

        case LOAD2:
            registers[registerIndex].setValue(addressValue);
            cout << "LOAD 0x" <<setw(2)<<setfill('0')<< registerIndex << " with the pattern: 0x" << static_cast<int>(addressValue) << ". [SUCCESS]\n";
            break;

        case STORE:
            // 3210 put content of reg 2 in add 10
            memory.store(addressValue, registers[registerIndex].getValue());
            cout << "STORE the value in register 0x" <<setw(2)<<setfill('0')<< registerIndex << " in memory cell: 0x" << static_cast<int>(addressValue)
                 << ". [SUCCESS]\n";
            if (addressValue == 0x00) {
                memory.store(addressValue, registers[registerIndex].getValue());
                screenOutput += static_cast<int> (registers[registerIndex].getValue());
            }
            break;

        case MOVE:
            registers[s_bits] = registers[f_bits];
            cout << "MOVE 0x" <<setw(2)<<setfill('0')<< registerIndex << " to: 0x" << static_cast<int>(addressValue) << ". [SUCCESS]\n";
            break;

        case ADD:
            cout << "ADD the values found in 0x" << f_bits << " and 0x" << s_bits << " then store in 0x" <<setw(2)<<setfill('0')<< registerIndex
                 << ". [SUCCESS]\n";

            f_val = static_cast<int>(registers[f_bits].getValue());
            s_val = static_cast<int>(registers[s_bits].getValue());
            add_result = f_val + s_val;
            add_result &= ((1 << 8) - 1);
            registers[registerIndex].setValue(static_cast<BYTE>(add_result));
            break;

        case JUMP:
            cout << "JUMP to " << static_cast<int>(addressValue) << "if 0x0 = " <<setw(2)<<setfill('0')<< registerIndex << ". [SUCCESS]\n";
            if (registers[registerIndex].getValue() == registers[0x00].getValue()) {
                programCounter = addressValue;
            }
            break;

        case HALT:
            if (registerIndex == 0x00 && addressValue == 0x00) {
                cout << "Program Executed Successfully!\n";
                break;
            } else {
                cout << "Invalid Format for the operand\n";
            }

        default:
            cout << "Invalid opcode: " << hex << uppercase << static_cast<int>(opcode) << endl;
            break;
    }
}

