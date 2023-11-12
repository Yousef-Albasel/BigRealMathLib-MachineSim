#ifndef MACHINESIMULATOR_H
#define MACHINESIMULATOR_H

#include <bits/stdc++.h>
#include <windef.h>

using namespace std;

class Memory; // just forwarding, ignore this

// Register Definition
class Register {
public:
    Register();

    BYTE getValue() const;

    void setValue(BYTE value);

private:
    BYTE value;
};
// Instruction Definition

//class Instruction {
//public:
//    Instruction(Register& programCounter, Register registers[], Memory& memory);
//    virtual void execute() = 0;
//
//protected:
//    BYTE opCode;
//    Register& programCounter;
//    Register registers[16];
//    Memory& memory;
//};

// Memory Definition

class Memory {
public:
    Memory();

    void store(BYTE address, BYTE &data);

    BYTE getCell( int idx);

    void clearMemory();

    BYTE get(BYTE address);

    short getInstruction(BYTE address);

    BYTE* getStartAddress()  ;
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

    void setProgramCounter(BYTE* address);
    //    Instruction fetch();
    void decode();

    void runProgram(); // to call execute in each instruction operation

private:
    Register instructionRegister;
    BYTE* programCounter{};
    Memory memory;
    Register registers[16];
};


#endif  //MACHINESIMULATOR_H
