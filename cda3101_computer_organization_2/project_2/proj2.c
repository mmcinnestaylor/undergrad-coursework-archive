#include <stdio.h>
#include <string.h>

struct line{
  char command[50];
  int opCode;
  int rs;
  int rt;
  int rd;
  int shamt;
  int funct;
  short immediate;
};
struct ifID{
  char instruction[50];
  int pc4;
  short immediate;
  int rs;
  int rt;
  int rd;
  int opCode;
  int funct;
  int shamt;
};
struct idEX{
  char instruction[50];
  int pc4;
  int branTgt;
  int readData1;
  int readData2;
  short immediate;
  int rs;
  int rt;
  int rd;
  int opCode;
  int funct;
  int shamt;
};
struct exMEM{
  char instruction[50];
  int aluResult;
  int writeDataReg;
  int writeRegister;
  int opCode;
  int funct;
};
struct memWB{
  char instruction[50];
  int writeDataMem;
  int writeDataALU;
  int writeRegister;
  int opCode;
};
struct state{
  int pc;
  struct ifID IF_ID;
  struct idEX ID_EX;
  struct exMEM EX_MEM;
  struct memWB MEM_WB;
};
struct btPB{
  int target;
  int taken;
};

void decodeInstruction(const int instruction, struct line* instStruc,
                       char** const regList);
void copyState(struct state* oldState, struct state* const newState);
void initializeState(struct state* theState);
void printState(struct state* const theState, const int cycle,
                int* const regFile, int* const dataMem, char** const regList);
int lwStallCheck(struct state* const currentState);
void forwardCheck(struct state* nextState, struct state* const currentState);
int main(){
  int cmd, i,j, stalls, branches, mpBranches, haltOccured;
  char lineIn[50];
  char* regList[32] = {"0", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0",
                       "t1", "t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1",
                       "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0",
                       "k1", "gp", "sp", "fp", "ra"};
  int regFile[32];
  int dataMem[32];
  struct line instructArray[100];
  struct btPB branchArray[100];
  struct state currentState, nextState;
  struct line NOOP = {"NOOP", 0, 0, 0, 0, 0, 0, 0};

  //Initialize vars & structs
  initializeState(&currentState);
  initializeState(&nextState);
  cmd = 0;

  for(i = 0; i < 32; i++){
    regFile[i] = 0;
    dataMem[i] = 0;
  }

  i = 0;
  //read in instructions
  while(fgets(lineIn, 50, stdin) != 0){
    sscanf(lineIn, "%d", &cmd);
    if(cmd == 1){
      decodeInstruction(cmd, &instructArray[i], regList);
      strcpy(instructArray[i].command, "halt");
      branchArray[i].target = 0;
      branchArray[i].taken = 2;
      i++;
      break;
    }
    else if(cmd == 0){
      decodeInstruction(cmd, &instructArray[i], regList);
      strcpy(instructArray[i].command, "NOOP");
      branchArray[i].target = 0;
      branchArray[i].taken = 2;
      i++;
    }
    else{
      decodeInstruction(cmd, &instructArray[i], regList);
      if(instructArray[i].opCode == 5){
        branchArray[i].target = i * 4;
        branchArray[i].taken = 2;
      }
      else{
        branchArray[i].target = 0;
        branchArray[i].taken = 2;
      }
      i++;
    }
  }

  //toss blank line
  fgets(lineIn, 50, stdin);
  //set address of start of data section
  const int dataStart = i * 4;

  i = 0;
  //read in data members
  while(fgets(lineIn, 50, stdin) != 0){
    sscanf(lineIn, "%d", &(dataMem[i]));
    i++;
  }
  i = 1;
  stalls = 0;
  branches = 0;
  mpBranches = 0;
  haltOccured = 0;

  printState(&nextState, i++, regFile, dataMem, regList);
  while(strcmp(currentState.MEM_WB.instruction, "halt") != 0){
    if(strcmp(currentState.IF_ID.instruction, "halt") == 0) haltOccured = 1;

    nextState.pc = currentState.pc + 4;

  /*********update IF_ID**********/
    if(haltOccured == 0){
      if(lwStallCheck(&currentState) || currentState.ID_EX.opCode == 5 ||
         currentState.EX_MEM.opCode == 5){
        nextState.pc -= 4;
        strcpy(currentState.IF_ID.instruction, NOOP.command);
        //currentState.IF_ID.pc4 -= 4;
        currentState.IF_ID.immediate = NOOP.immediate;
        currentState.IF_ID.opCode = NOOP.opCode;
        currentState.IF_ID.funct = NOOP.funct;
        currentState.IF_ID.shamt = NOOP.shamt;
        currentState.IF_ID.rs = NOOP.rs;
        currentState.IF_ID.rt = NOOP.rt;
        currentState.IF_ID.rd = NOOP.rd;
        stalls++;
      }
      else{
        strcpy(nextState.IF_ID.instruction,
              instructArray[currentState.pc / 4].command);
        nextState.IF_ID.pc4 = currentState.pc + 4;
        nextState.IF_ID.immediate = instructArray[currentState.pc / 4].immediate;
        nextState.IF_ID.opCode = instructArray[currentState.pc / 4].opCode;
        if(nextState.IF_ID.opCode == 0){
          nextState.IF_ID.funct = instructArray[currentState.pc / 4].funct;
          if(nextState.IF_ID.funct == 0){
            nextState.IF_ID.rs = 0;
            nextState.IF_ID.rt = instructArray[currentState.pc / 4].rt;
            nextState.IF_ID.rd = instructArray[currentState.pc / 4].rd;
            nextState.IF_ID.shamt = instructArray[currentState.pc / 4].shamt;
          }
          else{
            nextState.IF_ID.rs = instructArray[currentState.pc / 4].rs;
            nextState.IF_ID.rt = instructArray[currentState.pc / 4].rt;
            nextState.IF_ID.rd = instructArray[currentState.pc / 4].rd;
            nextState.IF_ID.shamt = 0;
          }
        }
        else{
          nextState.IF_ID.funct = 0;
          nextState.IF_ID.shamt = 0;
          nextState.IF_ID.rs = instructArray[currentState.pc / 4].rs;
          nextState.IF_ID.rt = instructArray[currentState.pc / 4].rt;
          nextState.IF_ID.rd = 0;
        }
      }
    }
    else{
      strcpy(nextState.IF_ID.instruction, NOOP.command);
      nextState.IF_ID.pc4 = currentState.pc + 4;
      nextState.IF_ID.immediate = NOOP.immediate;
      nextState.IF_ID.opCode = NOOP.opCode;
      nextState.IF_ID.funct = NOOP.funct;
      nextState.IF_ID.shamt = NOOP.shamt;
      nextState.IF_ID.rs = NOOP.rs;
      nextState.IF_ID.rt = NOOP.rt;
      nextState.IF_ID.rd = NOOP.rd;
    }

  /**********update ID_EX**********/
    strcpy(nextState.ID_EX.instruction, currentState.IF_ID.instruction);
    nextState.ID_EX.pc4 = currentState.IF_ID.pc4;
    nextState.ID_EX.branTgt =
      (currentState.IF_ID.immediate << 2) + currentState.IF_ID.pc4;
    //set readData based on opCode
    if(currentState.IF_ID.opCode == 0){
      if(currentState.IF_ID.funct == 0){
        nextState.ID_EX.readData1 =
          regFile[currentState.IF_ID.rt];
        nextState.ID_EX.readData2 = 0;
      }
      else{
        nextState.ID_EX.readData1 =
          regFile[currentState.IF_ID.rs];
          nextState.ID_EX.readData2 =
            regFile[currentState.IF_ID.rt];
      }
    }
    else if(currentState.IF_ID.opCode == 5){
      nextState.ID_EX.readData1 =
        regFile[currentState.IF_ID.rs];
      nextState.ID_EX.readData2 =
        regFile[currentState.IF_ID.rt];
    }
    else{
      nextState.ID_EX.readData1 =
        regFile[currentState.IF_ID.rs];
      nextState.ID_EX.readData2 = 0;
    }

    //set immediate value
    nextState.ID_EX.immediate =
      currentState.IF_ID.immediate;

    //update registers
    nextState.ID_EX.rs = currentState.IF_ID.rs;
    nextState.ID_EX.rt = currentState.IF_ID.rt;
    nextState.ID_EX.rd = currentState.IF_ID.rd;

    //update extra information
    nextState.ID_EX.opCode = currentState.IF_ID.opCode;
    nextState.ID_EX.funct = currentState.IF_ID.funct;
    nextState.ID_EX.shamt = currentState.IF_ID.shamt;

  /**********update EX_MEM**********/
    strcpy(nextState.EX_MEM.instruction, currentState.ID_EX.instruction);
    if(strcmp(nextState.EX_MEM.instruction, "NOOP") != 0){
      //R-types
      if(currentState.ID_EX.opCode == 0){
        //perform sll, store in aluResult
        if(currentState.ID_EX.funct == 0)
          nextState.EX_MEM.aluResult =
            currentState.ID_EX.readData1 << currentState.ID_EX.shamt;
        //perform add, store in aluResult
        else if(currentState.ID_EX.funct == 32)
          nextState.EX_MEM.aluResult =
            currentState.ID_EX.readData1 + currentState.ID_EX.readData2;
        //perform sub, store in aluResult
        else
          nextState.EX_MEM.aluResult =
            currentState.ID_EX.readData1 - currentState.ID_EX.readData2;
      }
      //perform bne, store in aluResult
      else if(currentState.ID_EX.opCode == 5){
        nextState.EX_MEM.aluResult =
          currentState.ID_EX.readData1 - currentState.ID_EX.readData2;
        //if(nextState.EX_MEM.aluResult != 0)
          //nextState.pc =currentState.pc + currentState.ID_EX.immediate << 2;
        branches++;
      }
      //perform andi, store in aluResult
      else if(currentState.ID_EX.opCode == 12)
        nextState.EX_MEM.aluResult =
          currentState.ID_EX.readData1 & currentState.ID_EX.immediate;
      //perform ori, store in aluResult
      else if(currentState.ID_EX.opCode == 13)
        nextState.EX_MEM.aluResult =
          currentState.ID_EX.readData1 | currentState.ID_EX.immediate;
      //negate halt immed field
      else if(strcmp(currentState.ID_EX.instruction, "halt") == 0)
        nextState.EX_MEM.aluResult = 0;
      //perform lw or sw, store in aluResult
      else{
        //if(rsFlag){nextState.EX_MEM.aluResult = newRs+currentState.ID_EX.immediate;}
        nextState.EX_MEM.aluResult =
          currentState.ID_EX.readData1 + currentState.ID_EX.immediate;
        }
    }
    //NOOP
    else
      nextState.EX_MEM.aluResult = 0;
    //read data from regFile, store in writeDataReg
    nextState.EX_MEM.writeDataReg = regFile[currentState.ID_EX.rt];
    //set write register
    if(currentState.ID_EX.opCode == 0){
        nextState.EX_MEM.writeRegister = currentState.ID_EX.rd;
    }
    else{
      nextState.EX_MEM.writeRegister = currentState.ID_EX.rt;
    }
    //set extra data
    nextState.EX_MEM.opCode = currentState.ID_EX.opCode;
    nextState.EX_MEM.funct = currentState.ID_EX.funct;

    //update dataMem for sw
    if(currentState.MEM_WB.opCode == 43)
      dataMem[currentState.MEM_WB.writeDataALU] =
        regFile[currentState.MEM_WB.writeRegister];

  /**********update MEM_WB**********/
    strcpy(nextState.MEM_WB.instruction, currentState.EX_MEM.instruction);
    //set writeDataMem
    if(currentState.EX_MEM.opCode == 35 &&
       currentState.EX_MEM.aluResult >= dataStart)
        nextState.MEM_WB.writeDataMem =
          dataMem[(currentState.EX_MEM.aluResult - dataStart) / 4];
    else
      nextState.MEM_WB.writeDataMem = 0;
    //set writeDataALU
    nextState.MEM_WB.writeDataALU = currentState.EX_MEM.aluResult;
    //set writeReg
    nextState.MEM_WB.writeRegister = currentState.EX_MEM.writeRegister;
    //update extra information
    nextState.MEM_WB.opCode = currentState.EX_MEM.opCode;

    //update dataMem and regFile
    if(currentState.MEM_WB.opCode == 35 &&
       currentState.MEM_WB.writeRegister != 0)
      regFile[currentState.MEM_WB.writeRegister] =
        currentState.MEM_WB.writeDataMem;
    else if(currentState.MEM_WB.opCode != 5 &&
            currentState.MEM_WB.opCode != 43 &&
            currentState.MEM_WB.writeRegister != 0)
      regFile[currentState.MEM_WB.writeRegister] =
        currentState.MEM_WB.writeDataALU;

    printState(&nextState, i++, regFile, dataMem, regList);
    forwardCheck(&nextState, &currentState);
    copyState(&currentState, &nextState);
  }

  printf("********************\n");
  printf("Total number of cycles executed: %d\n", i - 1);
  printf("Total number of stalls: %d\n", stalls);
  printf("Total number of branches: %d\n", branches);
  printf("Total number of mispredicted branches: %d\n", mpBranches);
  return 0;
}

void decodeInstruction(const int instruction, struct line* instStruc,
                       char** const regList){
  instStruc->opCode = (instruction >> 26) & 63;
  instStruc->rs = (instruction >> 21) & 31;
  instStruc->rt = (instruction >> 16) & 31;
  instStruc->rd = (instruction >> 11) & 31;
  instStruc->shamt = (instruction >> 6) & 31;
  instStruc->funct = instruction & 63;
  instStruc->immediate = (short)instruction;

  if(instStruc->opCode == 0){
    if(instStruc->funct == 0)
      sprintf(instStruc->command, "sll $%s,$%s,%d",
              regList[instStruc->rd], regList[instStruc->rt],
              instStruc->shamt);

    else if(instStruc->funct == 32)
      sprintf(instStruc->command, "add $%s,$%s,$%s",
              regList[instStruc->rd], regList[instStruc->rs],
              regList[instStruc->rt]);

    else sprintf(instStruc->command, "sub $%s,$%s,$%s",
                 regList[instStruc->rd], regList[instStruc->rs],
                 regList[instStruc->rt]);
  }
  else if(instStruc->opCode == 5)
    sprintf(instStruc->command, "bne $%s,$%s,%d",
            regList[instStruc->rs], regList[instStruc->rt],
            instStruc->immediate);

  else if(instStruc->opCode == 12)
    sprintf(instStruc->command, "andi $%s,$%s,%d",
            regList[instStruc->rt], regList[instStruc->rs],
            instStruc->immediate);

  else if(instStruc->opCode == 13)
    sprintf(instStruc->command, "ori $%s,$%s,%d",
            regList[instStruc->rt], regList[instStruc->rs],
            instStruc->immediate);

  else if(instStruc->opCode == 35)
    sprintf(instStruc->command, "lw $%s,%d($%s)",
            regList[instStruc->rt], instStruc->immediate,
            regList[instStruc->rs]);

  else
    sprintf(instStruc->command, "sw $%s,%d($%s)",
            regList[instStruc->rt], instStruc->immediate,
            regList[instStruc->rs]);
}
void copyState(struct state* oldState, struct state* const newState){
  oldState->pc = newState->pc;
  strcpy(oldState->IF_ID.instruction, newState->IF_ID.instruction);
  oldState->IF_ID.pc4 = newState->IF_ID.pc4;
  oldState->IF_ID.immediate = newState->IF_ID.immediate;
  oldState->IF_ID.rs = newState->IF_ID.rs;
  oldState->IF_ID.rt = newState->IF_ID.rt;
  oldState->IF_ID.rd = newState->IF_ID.rd;
  oldState->IF_ID.opCode = newState->IF_ID.opCode;
  oldState->IF_ID.funct = newState->IF_ID.funct;
  oldState->IF_ID.shamt = newState->IF_ID.shamt;

  strcpy(oldState->ID_EX.instruction, newState->ID_EX.instruction);
  oldState->ID_EX.pc4 = newState->ID_EX.pc4;
  oldState->ID_EX.branTgt = newState->ID_EX.branTgt;
  oldState->ID_EX.readData1 = newState->ID_EX.readData1;
  oldState->ID_EX.readData2 = newState->ID_EX.readData2;
  oldState->ID_EX.immediate = newState->ID_EX.immediate;
  oldState->ID_EX.rs = newState->ID_EX.rs;
  oldState->ID_EX.rt = newState->ID_EX.rt;
  oldState->ID_EX.rd = newState->ID_EX.rd;
  oldState->ID_EX.opCode = newState->ID_EX.opCode;
  oldState->ID_EX.funct = newState->ID_EX.funct;
  oldState->ID_EX.shamt = newState->ID_EX.shamt;

  strcpy(oldState->EX_MEM.instruction, newState->EX_MEM.instruction);
  oldState->EX_MEM.aluResult = newState->EX_MEM.aluResult;
  oldState->EX_MEM.writeDataReg = newState->EX_MEM.writeDataReg;
  oldState->EX_MEM.writeRegister = newState->EX_MEM.writeRegister;
  oldState->EX_MEM.opCode = newState->EX_MEM.opCode;
  oldState->EX_MEM.funct = newState->EX_MEM.funct;

  strcpy(oldState->MEM_WB.instruction, newState->MEM_WB.instruction);
  oldState->MEM_WB.writeDataMem = newState->MEM_WB.writeDataMem;
  oldState->MEM_WB.writeDataALU = newState->MEM_WB.writeDataALU;
  oldState->MEM_WB.writeRegister = newState->MEM_WB.writeRegister;
  oldState->MEM_WB.opCode = newState->MEM_WB.opCode;
}
void initializeState(struct state* theState){
  theState->pc = 0;
  strcpy(theState -> IF_ID.instruction, "NOOP");
  theState -> IF_ID.pc4 = 0;
  theState->IF_ID.immediate = 0;
  theState->IF_ID.rs = 0;
  theState->IF_ID.rt = 0;
  theState->IF_ID.rd = 0;
  theState->IF_ID.opCode = 0;
  theState->IF_ID.funct = 0;
  theState->IF_ID.shamt = 0;

  strcpy(theState -> ID_EX.instruction, "NOOP");
  theState->ID_EX.pc4 = 0;
  theState->ID_EX.branTgt = 0;
  theState->ID_EX.readData1 = 0;
  theState->ID_EX.readData2 = 0;
  theState->ID_EX.immediate = 0;
  theState->ID_EX.rs = 0;
  theState->ID_EX.rt = 0;
  theState->ID_EX.rd = 0;
  theState->ID_EX.opCode = 0;
  theState->ID_EX.funct = 0;
  theState->ID_EX.shamt = 0;

  strcpy(theState->EX_MEM.instruction, "NOOP");
  theState->EX_MEM.aluResult = 0;
  theState->EX_MEM.writeDataReg = 0;
  theState->EX_MEM.writeRegister = 0;
  theState->EX_MEM.opCode = 0;
  theState->EX_MEM.funct = 0;

  strcpy(theState->MEM_WB.instruction, "NOOP");
  theState->MEM_WB.writeDataMem = 0;
  theState->MEM_WB.writeDataALU = 0;
  theState->MEM_WB.writeRegister = 0;
  theState->MEM_WB.opCode = 0;
}
void printState(struct state* const theState, const int cycle,
                int* const regFile, int* const dataMem, char** const regList){
  int i = 0;
  printf("********************\n");
  printf("State at the beginning of cycle %d\n", cycle);
  printf("\tPC = %d\n", theState->pc);

  //print data mem
  printf("\tData Memory:\n");
  for(i = 0; i < 16; i++)
    printf("\t\tdataMem[%d] = %d\t\tdataMem[%d] = %d\n", i, dataMem[i],
           i + 16, dataMem[i + 16]);

  //print register file
  printf("\tRegisters:\n");
  for(i = 0; i < 16; i++)
    printf("\t\tregFile[%d] = %d\t\tregFile[%d] = %d\n", i, regFile[i],
           i + 16, regFile[i + 16]);

  //print IF_ID register
  printf("\tIF/ID:\n");
  printf("\t\tInstruction: %s\n", theState->IF_ID.instruction);
  printf("\t\tPCPlus4: %d\n", theState->IF_ID.pc4);

  //print ID_EX register
  printf("\tID/EX:\n");
  printf("\t\tInstruction: %s\n", theState->ID_EX.instruction);
  printf("\t\tPCPlus4: %d\n", theState->ID_EX.pc4);
  printf("\t\tbranchTarget: %d\n", theState->ID_EX.branTgt);
  printf("\t\treadData1: %d\n", theState->ID_EX.readData1);
  printf("\t\treadData2: %d\n", theState->ID_EX.readData2);
  printf("\t\timmed: %d\n", theState->ID_EX.immediate);
  printf("\t\trs: %s\n", regList[theState->ID_EX.rs]);
  printf("\t\trt: %s\n", regList[theState->ID_EX.rt]);
  printf("\t\trd: %s\n", regList[theState->ID_EX.rd]);

  //print EX_MEM register
  printf("\tEX/MEM:\n");
  printf("\t\tInstruction: %s\n", theState->EX_MEM.instruction);
  printf("\t\taluResult: %d\n", theState->EX_MEM.aluResult);
  printf("\t\twriteDataReg: %d\n", theState->EX_MEM.writeDataReg);
  printf("\t\twriteReg: %s\n", regList[theState->EX_MEM.writeRegister]);

  //print MEM_WB register
  printf("\tMEM/WB:\n");
  printf("\t\tInstruction: %s\n", theState->MEM_WB.instruction);
  printf("\t\twriteDataMem: %d\n", theState->MEM_WB.writeDataMem);
  printf("\t\twriteDataALU: %d\n", theState->MEM_WB.writeDataALU);
  printf("\t\twriteReg: %s\n", regList[theState->MEM_WB.writeRegister]);
}
int lwStallCheck(struct state* const currentState){
  if(currentState->ID_EX.opCode == 35){
    if((currentState->IF_ID.opCode == 0 && currentState->IF_ID.funct == 0 &&
        currentState->IF_ID.rt == currentState->ID_EX.rt)) return 1;

    else if(currentState->IF_ID.opCode == 0 && (currentState->IF_ID.funct == 32
            || currentState->IF_ID.funct == 34) && (currentState->IF_ID.rs ==
            currentState->ID_EX.rt || currentState->IF_ID.rt ==
            currentState->ID_EX.rt)) return 1;

    else if(currentState->IF_ID.opCode == 5 && (currentState->IF_ID.rs ==
            currentState->ID_EX.rt || currentState->IF_ID.rt ==
            currentState->ID_EX.rt)) return 1;

    else if(currentState->IF_ID.opCode > 5 &&
            currentState->IF_ID.rs == currentState->ID_EX.rt) return 1;
    else return 0;
  }
  else return 0;
}
void forwardCheck(struct state* nextState, struct state* const currentState){
  //check and update rs & rt for add, sub, bne
  if((nextState->ID_EX.opCode == 0 && nextState->ID_EX.funct != 0) ||
    (nextState->ID_EX.opCode == 5)){
  /**********rs**********/
  //forward from EX_MEM aluResult
    if(nextState->EX_MEM.writeRegister == nextState->ID_EX.rs &&
      nextState->EX_MEM.writeRegister != 0 /*&&
      currentState->EX_MEM.aluResult != 0 &&
      currentState->EX_MEM.opCode != 35 && currentState->EX_MEM.opCode != 43*/){
      nextState->ID_EX.readData1 = currentState->EX_MEM.aluResult;
    }

  //forward from MEM_WB writeDataALU
    else if(nextState->MEM_WB.writeRegister == nextState->ID_EX.rs &&
      nextState->MEM_WB.writeRegister != 0 /*&&
      currentState->MEM_WB.writeDataALU != 0 &&
      currentState->MEM_WB.opCode != 35 &&
      currentState->MEM_WB.opCode != 43*/)
      nextState->ID_EX.readData1 = nextState->MEM_WB.writeDataALU;

  //forward from MEM_WB writeDataMem
    else if(nextState->MEM_WB.writeRegister == nextState->ID_EX.rs &&
      nextState->MEM_WB.writeRegister != 0 /*&&
      currentState->MEM_WB.writeDataALU != 0 &&
      currentState->MEM_WB.opCode == 35*/)
      nextState->ID_EX.readData1 = nextState->MEM_WB.writeDataMem;

  /**********rt**********/
  /*if(currentState->EX_MEM.writeRegister == currentState->ID_EX.rt &&
  currentState->EX_MEM.writeRegister != 0 &&
  currentState->EX_MEM.aluResult != 0)
  currentState->ID_EX.readData2 = currentState->EX_MEM.aluResult;

  else if(currentState->MEM_WB.writeRegister == currentState->ID_EX.rt &&
  currentState->MEM_WB.writeRegister != 0 &&
  currentState->MEM_WB.writeDataALU != 0)
  currentState->ID_EX.readData2 = currentState->MEM_WB.writeDataALU;*/
  //forward from EX_MEM aluResult
    if(nextState->EX_MEM.writeRegister == nextState->ID_EX.rt &&
      nextState->EX_MEM.writeRegister != 0 /*&&
      currentState->EX_MEM.aluResult != 0 &&
      currentState->EX_MEM.opCode != 35 && currentState->EX_MEM.opCode != 43*/)
      nextState->ID_EX.readData2 = nextState->EX_MEM.aluResult;

  //forward from MEM_WB writeDataALU
    else if(nextState->MEM_WB.writeRegister == nextState->ID_EX.rt &&
      nextState->MEM_WB.writeRegister != 0 /*&&
      currentState->MEM_WB.writeDataALU != 0 &&
      currentState->MEM_WB.opCode != 35 &&
      currentState->MEM_WB.opCode != 43*/)
      nextState->ID_EX.readData2 = nextState->MEM_WB.writeDataALU;

  //forward from MEM_WB writeDataMem
    else if(nextState->MEM_WB.writeRegister == nextState->ID_EX.rt &&
      nextState->MEM_WB.writeRegister != 0 /*&&
      currentState->MEM_WB.writeDataALU != 0 &&
      currentState->MEM_WB.opCode == 35*/)
      nextState->ID_EX.readData2 = nextState->MEM_WB.writeDataMem;
  }
  /**********check and update rt for sll*********/
  else if(nextState->ID_EX.opCode == 0 && nextState->ID_EX.funct == 0){
  /*if(currentState->EX_MEM.writeRegister == currentState->ID_EX.rt &&
  currentState->EX_MEM.writeRegister != 0 &&
  currentState->EX_MEM.aluResult != 0)
  currentState->ID_EX.readData1 = currentState->EX_MEM.aluResult;

  else if(currentState->MEM_WB.writeRegister == currentState->ID_EX.rt &&
  currentState->MEM_WB.writeRegister != 0 &&
  currentState->MEM_WB.writeDataALU != 0)
  currentState->ID_EX.readData1 = currentState->MEM_WB.writeDataALU;*/

  //forward from EX_MEM aluResult
    if(nextState->EX_MEM.writeRegister == nextState->ID_EX.rt &&
      nextState->EX_MEM.writeRegister != 0 /*&&
      currentState->EX_MEM.aluResult != 0 &&
      currentState->EX_MEM.opCode != 35 && currentState->EX_MEM.opCode != 43*/)
      nextState->ID_EX.readData1 = nextState->EX_MEM.aluResult;

  //forward from MEM_WB writeDataALU
    else if(nextState->MEM_WB.writeRegister == nextState->ID_EX.rt &&
      nextState->MEM_WB.writeRegister != 0 /*&&
      currentState->MEM_WB.writeDataALU != 0 &&
      currentState->MEM_WB.opCode != 35 &&
      currentState->MEM_WB.opCode != 43*/)
      nextState->ID_EX.readData1 = nextState->MEM_WB.writeDataALU;

  //forward from MEM_WB writeDataMem
    else if(nextState->MEM_WB.writeRegister == nextState->ID_EX.rt &&
      currentState->MEM_WB.writeRegister != 0 /*&&
      currentState->MEM_WB.writeDataALU != 0 &&
      currentState->MEM_WB.opCode == 35*/)
      nextState->ID_EX.readData1 = nextState->MEM_WB.writeDataMem;
  }
  //check and update rs for i types
  else if(nextState->ID_EX.opCode > 5){
  /*if(currentState->EX_MEM.writeRegister == currentState->ID_EX.rs &&
  currentState->EX_MEM.writeRegister != 0 &&
  currentState->EX_MEM.aluResult != 0)
  currentState->ID_EX.readData1 = currentState->EX_MEM.aluResult;

  else if(currentState->MEM_WB.writeRegister == currentState->ID_EX.rs &&
  currentState->MEM_WB.writeRegister != 0 &&
  currentState->MEM_WB.writeDataALU != 0)
  currentState->ID_EX.readData1 = currentState->MEM_WB.writeDataALU;*/

  //forward from EX_MEM aluResult
    if(nextState->EX_MEM.writeRegister == nextState->ID_EX.rs &&
      nextState->EX_MEM.writeRegister != 0 /*&&
      currentState->EX_MEM.aluResult != 0 &&
      currentState->EX_MEM.opCode != 35 && currentState->EX_MEM.opCode != 43*/)
      nextState->ID_EX.readData1 = nextState->EX_MEM.aluResult;


  //forward from MEM_WB writeDataALU
    else if(nextState->MEM_WB.writeRegister == nextState->ID_EX.rs &&
      nextState->MEM_WB.writeRegister != 0 /*&&
      currentState->MEM_WB.writeDataALU != 0 &&
      currentState->MEM_WB.opCode != 35 &&
      currentState->MEM_WB.opCode != 43*/)
      nextState->ID_EX.readData1 = nextState->MEM_WB.writeDataALU;

  //forward from MEM_WB writeDataMem
    else if(nextState->MEM_WB.writeRegister == nextState->ID_EX.rs &&
      nextState->MEM_WB.writeRegister != 0 /*&&
      currentState->MEM_WB.writeDataALU != 0 &&
      currentState->MEM_WB.opCode == 35*/)
      nextState->ID_EX.readData1 = nextState->MEM_WB.writeDataMem;
    }
  }
