#include <bits/stdc++.h>
using namespace std;

//Opcodes
unordered_map<string, string> opcodes = {
        {"add", "000000"},
        {"addi", "001000"},
        {"lw", "100011"},
        {"sw", "101011"},
        {"sll", "000000"},
        {"and", "000000"},
        {"andi", "001100"},
        {"or", "000000"},
        {"ori", "001101"},
        {"nor", "000000"},
        {"beq", "000100"},
        {"j", "000010"},
        {"jal", "000011"},
        {"jr", "000000"},
        {"slt", "000000"},
        {"sub","000000"},
        {"mul","000000"},
        {"srl","000000"},
        {"slti","001010"},
        {"xor","000000"},
        {"xori","001110"}
};

//Function codes
unordered_map<string, string> functs = {
        {"add", "100000"},
        {"sll", "000000"},
        {"srl","000010"},
        {"and", "100100"},
        {"or", "100101"},
        {"nor", "100111"},
        {"slt", "101010"},
        {"jr", "001000"},
        {"sub","100010"},
        {"mul","011000"},
        {"xor","100110"}
};

//Register File with MIPS type registers 
unordered_map<string, string> registerFile = {
        {"$zero", "$0"},
        {"$at", "$1"},
        {"$v0", "$2"},
        {"$v1", "$3"},
        {"$a0", "$4"},
        {"$a1", "$5"},
        {"$a2", "$6"},
        {"$a3", "$7"},
        {"$t0", "$8"},
        {"$t1", "$9"},
        {"$t2", "$10"},
        {"$t3", "$11"},
        {"$t4", "$12"},
        {"$t5", "$13"},
        {"$t6", "$14"},
        {"$t7", "$15"},
        {"$s0", "$16"},
        {"$s1", "$17"},
        {"$s2", "$18"},
        {"$s3", "$19"},
        {"$s4", "$20"},
        {"$s5", "$21"},
        {"$s6", "$22"},
        {"$s7", "$23"},
        {"$t8", "$24"},
        {"$t9", "$25"},
        {"$k0", "$26"},
        {"$k1", "$27"},
        {"$gp", "$28"},
        {"$sp", "$29"},
        {"$fp", "$30"},
        {"$ra", "$31"}
};


//Converting to binary
string toBinary(int num, int width) {
    string binary = "";
    for (int i = width - 1; i >= 0; --i) {
        binary += ((num >> i) & 1) ? "1" : "0";
    }
    return binary;
}

//Parsing the registers
string parseRegister(const string& data) {
    string reg = registerFile.at(data);
    string regNum = reg.substr(1);
    int regVal = stoi(regNum);
    return toBinary(regVal, 5);
}


//Parsing the offset/ immediate
string parseOffset(const string& offset) {
    int offsetVal = stoi(offset);
    return toBinary(offsetVal, 16);
}

//Parsing the shamt val
string parseShamt(const string& shamt) {
    int shamtVal = stoi(shamt);
    return toBinary(shamtVal, 5);
}

//Parsing the target val
string parseTarget(const string& target){
    int targetVal = stoi(target);
    return toBinary(targetVal, 26);
}

//Instruction memory- converting the entered instructions to machine code
string convertToMachineCode(const string& instruction) {
    istringstream iss(instruction);
    string opcode, rs, rt, rd, target, offset, shamt;
    iss >> opcode;
    if (opcode == "halt") {
        return "";
    } else if (opcode == "add") {
        iss >> rd >> rs >> rt;
        return opcodes[opcode] + parseRegister(rs) + parseRegister(rt) + parseRegister(rd) + "00000" + functs[opcode];
    }else if (opcode == "and") {
        iss >> rd >> rs >> rt;
        return opcodes[opcode] + parseRegister(rs) + parseRegister(rt) + parseRegister(rd) + "00000" + functs[opcode];
    }else if (opcode == "or") {
        iss >> rd >> rs >> rt;
        return opcodes[opcode] + parseRegister(rs) + parseRegister(rt) + parseRegister(rd) + "00000" + functs[opcode];
    }else if (opcode == "nor") {
        iss >> rd >> rs >> rt;
        return opcodes[opcode] + parseRegister(rs) + parseRegister(rt) + parseRegister(rd) + "00000" + functs[opcode];
    }else if (opcode == "slt") {
        iss >> rd >> rs >> rt;
        return opcodes[opcode] + parseRegister(rs) + parseRegister(rt) + parseRegister(rd) + "00000" + functs[opcode];
    }else if (opcode == "sub") {
        iss >> rd >> rs >> rt;
        return opcodes[opcode] + parseRegister(rs) + parseRegister(rt) + parseRegister(rd) + "00000" + functs[opcode];
    } else if (opcode == "mul") {
        iss >> rd >> rs >> rt;
        return opcodes[opcode] + parseRegister(rs) + parseRegister(rt) + parseRegister(rd) + "00000" + functs[opcode];
    }else if (opcode == "xor") {
        iss >> rd >> rs >> rt;
        return opcodes[opcode] + parseRegister(rs) + parseRegister(rt) + parseRegister(rd) + "00000" + functs[opcode];
    }else if (opcode == "addi" || opcode == "andi" || opcode == "ori"|| opcode=="slti" || opcode=="xori") {
        iss >> rt >> rs >> offset;
        return opcodes[opcode] + parseRegister(rs) + parseRegister(rt) + parseOffset(offset);
    } else if (opcode == "lw" || opcode == "sw") {
        iss >> rt >> offset >> rs;
        return opcodes[opcode] + parseRegister(rs) + parseRegister(rt) + parseOffset(offset);
    } else if (opcode == "sll") {
        iss >> rd >> rt >> shamt;
        return opcodes[opcode] + "00000" + parseRegister(rt) + parseRegister(rd) + parseShamt(shamt) + functs[opcode];
    }else if (opcode == "srl") {
        iss >> rd >> rt >> shamt;
        return opcodes[opcode] + "00000" + parseRegister(rt) + parseRegister(rd) + parseShamt(shamt) + functs[opcode];
    } else if (opcode == "beq") {
        iss >> rs >> rt >> offset;
        return opcodes[opcode] + parseRegister(rs) + parseRegister(rt) + parseOffset(offset);
    } else if (opcode == "j" || opcode == "jal") {
        iss >> target;
        return opcodes[opcode] + parseTarget(target);
    } else if (opcode == "jr") {
        iss >> rs;
        return opcodes[opcode] + parseRegister(rs) + toBinary(0, 10) + "00000" + functs[opcode];
    } 
}

unordered_map<string, string> controlSignals = {
//saved the opcodes and control signals
//Each bit represent a specific control signal
//in the order RegDst, ALUSrc, MemtoReg, Reg-Write, Mem-Read, Mem-Write, Branch, Jump
        {"000000", "10010000"}, //R-type
        {"001000", "01010000"}, //addi
        {"001100", "01010000"}, //andi
        {"001101", "01010000"}, //ori
        {"001010", "01010000"}, //slti
        {"001110", "01010000"}, //xori
        {"100011", "01111000"}, //lw
        {"101011", "01000100"}, //sw
        {"000100", "00000010"}, //beq
        {"000010", "00000001"}, //j
        {"000011", "00000001"} //jal
};


//MUX- string implementation - for RegDst and ALUSrc
string mux(const string& val1, const string& val2, char control ){
    if(control=='0'){
        return val1;
    }
    else if(control=='1'){
        return val2;
    }
    else
        return "";

}

//MUX - integer implementation - for MemtoReg
int mux(int val1, int val2, int val3, char control ){
    if(control=='0'){
        return val1;
    }
    else if(control=='1'){
        return val2;
    }
    else if(control=='2'){
        return val3;
    }
    else
        return 0;

}

//Method to read the register data
int ReadRegisterData(const string& data, unordered_map<string, int>& registers){
    int value = registers["$" + to_string(stoi(data, 0, 2))];
    return value;
}


//Method to read the numerical or offset data
int ReadNumericalData(const string& data) {
    int value = stoi(data, 0, 2);  // Convert binary string to integer
    // Check if the most significant bit (MSB) is set
    if (data[0] == '1') {
        // Perform two's complement conversion
        int numBits = data.length();
        int mask = (1 << numBits) - 1;
        value = -((~value & mask) + 1);
    }
    return value;
}

//The ALU for all operations - except sll and srl
int ALU(const string& opcode, int rsVal, int mux2Val, const string& funct, int mux1Val){
    if (opcode == opcodes["add"]) {
        if(funct == functs["add"]){
            return rsVal + mux2Val;}
        else if(funct == functs["and"]){
            return rsVal & mux2Val;
        }
        else if(funct == functs["or"]){
            return rsVal | mux2Val;
        }
        else if(funct==functs["nor"]){
            return ~(rsVal | mux2Val);
        }
        else if(funct==functs["slt"]){
            return (rsVal < mux2Val) ? 1 : 0;
        }
        else if(funct==functs["sub"]){
            return rsVal-mux2Val;
        }
        else if(funct==functs["mul"]){
            return rsVal*mux2Val;
        }
        else if(funct==functs["xor"]){
            return rsVal^ mux2Val;
        }
        else if(funct==functs["jr"]||funct==functs["sll"]||funct==functs["srl"]){
            return 0;
        }
    }
    else if(opcode == opcodes["addi"]){
        return rsVal + mux2Val;
    }
    else if(opcode == opcodes["andi"]){
        return rsVal & mux2Val;
    }
    else if(opcode == opcodes["ori"]){
        return rsVal | mux2Val;
    }
    else if(opcode == opcodes["ori"]){
        return rsVal | mux2Val;
    }
    else if(opcode == opcodes["xori"]){
        return rsVal ^ mux2Val;
    }
    else if(opcode == opcodes["lw"] || opcode == opcodes["sw"]){
        return rsVal + mux2Val;
    }
    else if(opcode == opcodes["beq"]){
        int result = rsVal - mux1Val;
        return abs(result);
    }
    else if(opcode==opcodes["slti"]){
            return (rsVal < mux2Val) ? 1 : 0;
        }
    else if(opcode == opcodes["j"] || opcode==opcodes["jal"]){
        return 0;
    }
    
}

//For sll and srl
int Shifter(const string& opcode,const string& funct, int shamtVal, int mux2Val){
    if(opcode==opcodes["sll"]){
        if(funct==functs["sll"]){
            return mux2Val << shamtVal;
        }
        else if(funct==functs["srl"]){
            return mux2Val >> shamtVal;
        }
    }
}

//Only for SW
void MemWritefun(int address, const string&muxOutput1, unordered_map<int, string>& dataMemory, unordered_map<string, int>& registers, char control){
    if(control=='1'){
    int mux1Val = registers["$" + to_string(stoi(muxOutput1, 0, 2))];
    bitset<32> registerValueBits(mux1Val);
    dataMemory[address] = registerValueBits.to_string();
    }
}

//Only for LW
int MemReadfun(int address, unordered_map<int, string>& dataMemory, const string&muxOutput1, char control){
        if(control=='1'){
        int mux1Val = stoi(dataMemory[address], 0, 2);
        return mux1Val;
        }
}

//Reg Write for writing back in registers
void RegWritefun(int ALUOutput, const string&muxOutput1, unordered_map<string, int>& registers, char control){
    if(control=='1'){
    registers["$" + to_string(stoi(muxOutput1, 0, 2))] = ALUOutput;
    }
}

//AND operator for beq implementation
int AND(int& zeroFlag, char control){
    int signal  = atoi(&control);
    int andResult = zeroFlag & control;
    return andResult;
}

//Shift-left-2
int shiftleft2(int data){
    int result = data*4;
    return result;
}

//Adder
void Adder(int& pc) {
    pc += 4;
}

//Second Adder
void Adder2(int& pc, int&branching){
    pc= pc +shiftleft2(branching)+4;
}

//Sign Extender
string signExtend(const string& data, int value){
    int val = ReadNumericalData(data);
    int newVal = val*value;
    bitset<32> binary(newVal);
    string signextend =binary.to_string();
    return signextend;
}


int main() {
    string initialPC;
    cout << "Enter the initial PC value: ";
    getline(cin, initialPC);

    string instruction;
    cout << "Enter the instructions (enter 'halt' to stop):\n";

    //Map for saving the instruction memory along with PC
    unordered_map<int, string> memory;

    //Map for saving the data memory for lw retrieval and sw saving
    unordered_map<int, string> dataMemory;
    int pc = stoi(initialPC);

    // Register file - with values inside registers - eg: $1 , 8, if 8 is the value inside it
    // For ease, we activated all the values to be zero initially
    unordered_map<string, int> registers;

    for (int i = 0; i < 32; ++i) {
        registers["$" + to_string(i)] = 0;
    }

    const int& zero = registers.at("$0");

    //Keeping track of instructions executed
    int clockCycles = 0;

    //Loop to enter instructions
    while (true) {
        cout << pc << ". ";
        getline(cin, instruction);
        // Remove commas, '(' and ')' from the instruction
        instruction.erase(remove(instruction.begin(), instruction.end(), ','), instruction.end());
        instruction.erase(remove(instruction.begin(), instruction.end(), '('), instruction.end());
        instruction.erase(remove(instruction.begin(), instruction.end(), ')'), instruction.end());
        
        if (instruction == "halt") {
            break;
        }

        //Saving the instruction to instruction memory
        memory[pc] = convertToMachineCode(instruction);

        if (memory[pc] == "") {
            break;
        }
        //Adder for pc+4;
        Adder(pc);
    }


    pc = stoi(initialPC);

    //Loop for executing the instructions
    while (true) {
        string machineCode = memory[pc];
        if (machineCode == "") {
            break;
        }

        //Breaking down of machine code for execution
        string opcode = machineCode.substr(0, 6);
        string rs = machineCode.substr(6, 5);
        string rt = machineCode.substr(11, 5);
        string rd = machineCode.substr(16, 5);
        string shamt = machineCode.substr(21, 5);
        string funct = machineCode.substr(26, 6);
        string immediate = machineCode.substr(16, 16);
        string target = machineCode.substr(6, 26);


        //Creating a string for control signals
        string signal = controlSignals[opcode];

        //Control Signals as characters of the string
        char RegDst = signal[0];
        char ALUSrc= signal[1];
        char MemtoReg = signal[2];
        char RegWrite = signal[3];
        char MemRead = signal[4];
        char MemWrite = signal[5];
        char Branch = signal[6];
        char Jump = signal[7];

        //RegDst- MUX
        string muxOutput1 = mux(rt, rd, RegDst);


        //ALUSrc- MUX
        string muxOutput2 = mux(rt, immediate, ALUSrc);

        //Read Data before passing to ALU
        int rsVal= ReadRegisterData(rs, registers);
        int mux1Val = ReadRegisterData(muxOutput1, registers);
        int shamtVal = ReadNumericalData(shamt);
        int mux2Val = 0;

        //For reading the values accurately
        //Here R-Type mux2val is a register while others are numerical values
        //So data should be accurately read
        if(opcode==opcodes["add"]){
            mux2Val = ReadRegisterData(muxOutput2, registers);
        }
        else{
            mux2Val = ReadNumericalData(muxOutput2);
        }

        //Calling ALU after the data is read
        int ALUOutput = ALU(opcode, rsVal, mux2Val, funct, mux1Val);

        //Since MemtoReg is different for sll and srl
        if(opcode=="000000"){
            if(funct=="000000" || funct=="000010"){
                MemtoReg ='2';
            }
        }

        //Calling Shifter
        int shiftedVal = Shifter(opcode, funct, shamtVal, mux2Val);

        //Zero flag
        int zeroFlag;
        if(ALUOutput==0){
            zeroFlag=1;
        }
        else{
            zeroFlag=0;
        }

        //AND operator
        int andOutput= AND(zeroFlag, Branch);

        //For sw
        MemWritefun(ALUOutput, muxOutput1, dataMemory, registers, MemWrite);

        //For lw
        int LWOutput = MemReadfun(ALUOutput, dataMemory, muxOutput1, MemRead);

        //MemtoReg MUX
        int finalOutput = mux(ALUOutput, LWOutput, shiftedVal, MemtoReg);

        //Writing Back in Registers
        RegWritefun(finalOutput, muxOutput1, registers, RegWrite);


        //For Branching and Jumps- This serves as the MUX of the adders
        if(andOutput==1 && Jump=='0'){
            int branching = ReadNumericalData(immediate);
            Adder2(pc,branching);
        }else if(andOutput==0 && Jump=='1'){
            int targetVal=ReadNumericalData(target);
            pc= shiftleft2(targetVal);
        }
        else{
            Adder(pc);
        }

        //Printing the values of all the wires
        cout<<"\nValues inside wires: "<<'\n';
        cout<<"Opcode: "<<opcode<<'\n';
        cout<<"Rs field: "<<rs<<'\n';
        cout<<"Rt field: "<<rt<<'\n';
        cout<<"Rd field: "<<rd<<'\n';
        cout<<"RegDest Mux Output: "<<muxOutput1<<'\n';
        cout<<"Offset field: "<<immediate<<'\n';
        cout<<"Sign Extend: "<<signExtend(immediate,1)<<'\n';
        cout<<"Shift left 2: "<<signExtend(immediate, 4)<<'\n';
        cout<<"Function code: "<<funct<<'\n';
        cout<<"Read Data 1: "<<rsVal<<'\n';
        cout<<"Read Data 2: "<<mux2Val<<'\n';
        cout<<"ALU second input: "<<mux2Val<<'\n';
        cout<<"ALU output: "<<ALUOutput<<'\n';
        cout<<"Zero Flag: "<<zeroFlag<<'\n';
        cout<<"MemtoReg Mux output: "<<finalOutput<<'\n';
        cout<<"AND Gate: "<<andOutput<<'\n';
        cout<<"Control Signals:"<<'\n';
        cout<<"RegDest: "<<RegDst<<'\n';
        cout<<"Branch: "<<Branch<<'\n';
        cout<<"MemRead: "<<MemRead<<'\n';
        cout<<"MemtoReg: "<<MemtoReg<<'\n';
        cout<<"MemWrite: "<<MemWrite<<'\n';
        cout<<"ALUSrc: "<<ALUSrc<<'\n';
        cout<<"RegWrite: "<<RegWrite<<'\n';
        
        clockCycles++;
    }

    //Printing register values
    cout << "\nRegister Values:\n";
    for (const auto& pair : registerFile) {
        const string& registerName = pair.first;
        const string& registerAlias = pair.second;
        const int& registerValue = registers[registerAlias];
        cout << registerName << " : " << registerValue << endl;
    }

    //Print instruction memory contents
    cout << "\nInstruction Memory Contents:\n";
    for (const auto& entry : memory) {
        cout << entry.first << ": " << entry.second << endl;
    }

    //Printing Data memory contents
    cout << "\nData Memory Contents:\n";
    for (const auto& entry : dataMemory) {
        cout << entry.first << ": " << entry.second << endl;
    }

    //Printing the clock cycles - here the number of programs executed
    cout << "\nClock Cycles: " << clockCycles << endl;
    
    return 0;
}
