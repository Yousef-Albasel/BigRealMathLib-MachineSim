#ifndef MACHINESIMULATOR_H
#define MACHINESIMULATOR_H
#define BYTE unsigned char

#include <bits/stdc++.h>

using namespace std;

class Memory; // just forwarding, ignore this

// Register Definition
class Register {
public:
    Register();

    BYTE getValue() ;

    void setValue(BYTE value);
private:
    BYTE value;
};

// Memory Definition

class Memory {
public:
    Memory();

    void store(BYTE address, BYTE data);

    BYTE getCell(int idx);

    void clearMemory();

    BYTE *getStartAddress();

private:
    BYTE cells[256]{};  // 16*16
};


// MachineSimulator Definition

class MachineSimulator {
public:
    MachineSimulator();

    void loadProgram(const string &filename, BYTE address);

    void displayMenu();

    void displayStatus();

    void clearRegisters();

    void setProgramCounter(BYTE address);

    void fetchInstruction();

    void decode();

    void findAndExecuteInstruction(BYTE operation_code, BYTE register_index, BYTE addressValue);

private:
    Register instructionRegister[2];
    BYTE programCounter;
    Memory memory;
    Register registers[16];
    BYTE opcode,addValue,registerIndex;
    string screenOutput;
};


#endif  //MACHINESIMULATOR_H
