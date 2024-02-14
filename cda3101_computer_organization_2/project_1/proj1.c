#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct line{
  char operand[5];
  unsigned int rs;
  unsigned int rt;
  unsigned int rd;
  int immediate;
  char targetLabel[33];
};
struct label{
  char name[33];
  int address;
};

unsigned int convertReg(char*);

int main(){
  struct label labelArr[100];
  struct line lineArr[200];
  char lineIn[150];
  char directive[10];
  char rs[4];
  char rt[4];
  char rd[4];
  int lineArrIndex, labArrIndex, addressCount, printCount, immed, machCode;
  lineArrIndex = 0;
  labArrIndex = 0;
  addressCount = 0;
  printCount = 0;
  immed = 0;
  machCode = 0;

  while(fgets(lineIn, 150, stdin) != 0){
    //R-Type add & nor with label
    if(sscanf(lineIn, "%32[^:]: %s $%[^,],$%[^,],$%s",
      labelArr[labArrIndex].name, lineArr[lineArrIndex].operand,
      rd, rs, rt) == 5){
        labelArr[labArrIndex].address = addressCount;
        lineArr[lineArrIndex].rs = convertReg(rs);
        lineArr[lineArrIndex].rt = convertReg(rt);
        lineArr[lineArrIndex].rd = convertReg(rd);
        lineArrIndex += 1;
        labArrIndex += 1;
        addressCount += 4;
      }
    //I-Type addi & ori with label & sll
    else if(sscanf(lineIn, "%32[^:]: %s $%[^,],$%[^,],%d",
      labelArr[labArrIndex].name, lineArr[lineArrIndex].operand,
      rt, rs, &lineArr[lineArrIndex].immediate) == 5){
        if(strcmp(lineArr[lineArrIndex].operand, "sll") == 0){
          lineArr[lineArrIndex].rt = convertReg(rs);
          lineArr[lineArrIndex].rd = convertReg(rt);
        }
        else{
          lineArr[lineArrIndex].rs = convertReg(rs);
          lineArr[lineArrIndex].rt = convertReg(rt);
        }
        labelArr[labArrIndex].address = addressCount;
        lineArrIndex += 1;
        labArrIndex += 1;
        addressCount += 4;
      }
    //I-Type sw & lw with label
    else if(sscanf(lineIn, "%32[^:]: %s $%[^,],%d($%[^)])",
      labelArr[labArrIndex].name, lineArr[lineArrIndex].operand,
      rt, &lineArr[lineArrIndex].immediate, rs) == 5){
        labelArr[labArrIndex].address = addressCount;
        lineArr[lineArrIndex].rs = convertReg(rs);
        lineArr[lineArrIndex].rt = convertReg(rt);
        lineArrIndex += 1;
        labArrIndex += 1;
        addressCount += 4;
      }
    //I-Type bne with label
    else if(sscanf(lineIn, "%32[^:]: %s $%[^,],$%[^,],%s",
      labelArr[labArrIndex].name, lineArr[lineArrIndex].operand,
      rs, rt, lineArr[lineArrIndex].targetLabel) == 5){
        labelArr[labArrIndex].address = addressCount;
        lineArr[lineArrIndex].rs = convertReg(rs);
        lineArr[lineArrIndex].rt = convertReg(rt);
        lineArrIndex += 1;
        labArrIndex += 1;
        addressCount += 4;
      }
    //la with label & lui
    else if(sscanf(lineIn, "%32[^:]: %s $%[^,],%s",
      labelArr[labArrIndex].name, lineArr[lineArrIndex].operand,
      rt, lineArr[lineArrIndex].targetLabel) == 4){
        if(strcmp(lineArr[lineArrIndex].operand, "la") == 0){
          lineArr[lineArrIndex].rt = convertReg(rt);
          labelArr[labArrIndex].address = addressCount;
          addressCount += 8;
        }
        else{
          lineArr[lineArrIndex].immediate = atoi(lineArr[lineArrIndex].targetLabel);
          lineArr[lineArrIndex].rt = convertReg(rt);
          labelArr[labArrIndex].address = addressCount;
          addressCount += 4;
        }
        lineArrIndex += 1;
        labArrIndex += 1;
      }
    //R-Type add & nor without label
    else if(sscanf(lineIn, "%s $%[^,],$%[^,],$%s",
      lineArr[lineArrIndex].operand, rd, rs, rt) == 4){
        labelArr[labArrIndex].address = addressCount;
        lineArr[lineArrIndex].rs = convertReg(rs);
        lineArr[lineArrIndex].rt = convertReg(rt);
        lineArr[lineArrIndex].rd = convertReg(rd);
        lineArrIndex += 1;
        addressCount += 4;
      }
    //I-Type addi & ori without label sll
    else if(sscanf(lineIn, "%s $%[^,],$%[^,],%d",
      lineArr[lineArrIndex].operand, rt, rs,
      &lineArr[lineArrIndex].immediate) == 4){
        if(strcmp(lineArr[lineArrIndex].operand, "sll") == 0){
          lineArr[lineArrIndex].rt = convertReg(rs);
          lineArr[lineArrIndex].rd = convertReg(rt);
        }
        else{
        lineArr[lineArrIndex].rs = convertReg(rs);
        lineArr[lineArrIndex].rt = convertReg(rt);
        }
        lineArrIndex += 1;
        addressCount += 4;
      }
    //I-Type sw & lw without label
    else if(sscanf(lineIn, "%s $%[^,],%d($%[^)])",
      lineArr[lineArrIndex].operand, rt, &lineArr[lineArrIndex].immediate,
      rs) == 4){
        lineArr[lineArrIndex].rs = convertReg(rs);
        lineArr[lineArrIndex].rt = convertReg(rt);
        lineArrIndex += 1;
        addressCount += 4;
      }
    //I-Type bne without label
    else if(sscanf(lineIn, "%s $%[^,],$%[^,],%s",
      lineArr[lineArrIndex].operand, rs, rt,
      lineArr[lineArrIndex].targetLabel) == 4){
        lineArr[lineArrIndex].rs = convertReg(rs);
        lineArr[lineArrIndex].rt = convertReg(rt);
        lineArrIndex += 1;
        addressCount += 4;
      }
    //J-Type j with label
    else if(sscanf(lineIn, "%32[^:]: %s %s",
      labelArr[labArrIndex].name, lineArr[lineArrIndex].operand,
      lineArr[lineArrIndex].targetLabel) == 3){
        labelArr[labArrIndex].address = addressCount;
        lineArrIndex += 1;
        labArrIndex += 1;
        addressCount += 4;
      }
    //la without label & lui
    else if(sscanf(lineIn, "%s $%[^,],%s",
      lineArr[lineArrIndex].operand, rt,
      lineArr[lineArrIndex].targetLabel) == 3){
        if(strcmp(lineArr[lineArrIndex].operand, "la") == 0){
        lineArr[lineArrIndex].rt = convertReg(rt);
        addressCount += 8;
        }
        else{
          lineArr[lineArrIndex].immediate = atoi(lineArr[lineArrIndex].targetLabel);
          lineArr[lineArrIndex].rt = convertReg(rt);
          addressCount += 4;
        }
        lineArrIndex += 1;

      }
    //directives .space & .word with label
    else if (sscanf(lineIn, "%32[^:]: %s %d", labelArr[labArrIndex].name,
      directive, &immed) == 3){
        labelArr[labArrIndex].address = addressCount;
        if(strcmp(directive, ".space") == 0)
          addressCount = addressCount + immed;
        else
          addressCount += 4;
        labArrIndex += 1;
      }
    //directives .space & .word without label
    else if (sscanf(lineIn, "%s %d", directive, &immed) == 2){
        if(strcmp(directive, ".space") == 0)
          addressCount = addressCount + immed;
        else
          addressCount += 4;
      }
    //J-Type j without label
    else if(sscanf(lineIn, "%s %s",
      lineArr[lineArrIndex].operand, lineArr[lineArrIndex].targetLabel) == 2){
        lineArrIndex += 1;
        addressCount += 4;
      }
    //directives .text & .data
    else{
      sscanf(lineIn, "%s", directive);
    }
  }

  addressCount = 0;
  while(printCount < lineArrIndex){
    machCode = 0;
    if(strcmp(lineArr[printCount].operand, "add") == 0){
      machCode = machCode | lineArr[printCount].rs;
      machCode = (machCode << 5) | lineArr[printCount].rt;
      machCode = (machCode << 5) | lineArr[printCount].rd;
      machCode = (machCode << 11) | 32;
      printf("0x%06X: 0x%08X\n", addressCount, machCode);
      printCount += 1;
      addressCount += 4;
    }
    else if(strcmp(lineArr[printCount].operand, "addi") == 0){
      machCode = lineArr[printCount].immediate;
      machCode = machCode & (65535);
      machCode = machCode | (8 << 26);
      machCode = machCode | (lineArr[printCount].rs << 21);
      machCode = machCode | (lineArr[printCount].rt << 16);
      printf("0x%06X: 0x%08X\n", addressCount, machCode);
      printCount += 1;
      addressCount += 4;
    }
    else if(strcmp(lineArr[printCount].operand, "nor") == 0){
      machCode = machCode | lineArr[printCount].rs;
      machCode = (machCode << 5) | lineArr[printCount].rt;
      machCode = (machCode << 5) | lineArr[printCount].rd;
      machCode = (machCode << 11) | 39;
      printf("0x%06X: 0x%08X\n", addressCount, machCode);
      printCount += 1;
      addressCount += 4;
    }
    else if(strcmp(lineArr[printCount].operand, "ori") == 0){
      machCode = lineArr[printCount].immediate;
      machCode = machCode & (65535);
      machCode = machCode | (13 << 26);
      machCode = machCode | (lineArr[printCount].rs << 21);
      machCode = machCode | (lineArr[printCount].rt << 16);
      printCount += 1;
      addressCount += 4;
    }
    else if(strcmp(lineArr[printCount].operand, "sll") == 0){
      machCode = machCode | lineArr[printCount].rt;
      machCode = (machCode << 5) | lineArr[printCount].rd;
      machCode = (machCode << 5) | lineArr[printCount].immediate;
      machCode = machCode << 6;
      printf("0x%06X: 0x%08X\n", addressCount, machCode);
      printCount += 1;
      addressCount += 4;
    }
    else if(strcmp(lineArr[printCount].operand, "lui") == 0){
      machCode = lineArr[printCount].immediate;
      machCode = machCode & (65535);
      machCode = machCode | (15 << 26);
      machCode = machCode | (lineArr[printCount].rt << 16);
      printf("0x%06X: 0x%08X\n", addressCount, machCode);
      printCount += 1;
      addressCount += 4;
    }
    else if(strcmp(lineArr[printCount].operand, "sw") == 0){
      machCode = lineArr[printCount].immediate;
      machCode = machCode & (65535);
      machCode = machCode | (43 << 26);
      machCode = machCode | (lineArr[printCount].rs << 21);
      machCode = machCode | (lineArr[printCount].rt << 16);
      printf("0x%06X: 0x%08X\n", addressCount, machCode);
      printCount += 1;
      addressCount += 4;
    }
    else if(strcmp(lineArr[printCount].operand, "lw") == 0){
      machCode = lineArr[printCount].immediate;
      machCode = machCode & (65535);
      machCode = machCode | (35 << 26);
      machCode = machCode | (lineArr[printCount].rs << 21);
      machCode = machCode | (lineArr[printCount].rt << 16);
      printf("0x%06X: 0x%08X\n", addressCount, machCode);
      printCount += 1;
      addressCount += 4;
    }
    else if(strcmp(lineArr[printCount].operand, "bne") == 0){
      addressCount += 4;
      int i = 0;
      while(strcmp(labelArr[i].name, lineArr[printCount].targetLabel) != 0)
        i += 1;
      immed = labelArr[i].address;
      machCode = ((immed - addressCount) / 4);
      machCode = machCode & (65535);
      machCode = machCode | (5 << 26);
      machCode = machCode | (lineArr[printCount].rs << 21);
      machCode = machCode | (lineArr[printCount].rt << 16);
      printf("0x%06X: 0x%08X\n", (addressCount - 4), machCode);
      printCount += 1;
    }
    else if(strcmp(lineArr[printCount].operand, "j") == 0){
      int i = 0;
      while(strcmp(labelArr[i].name, lineArr[printCount].targetLabel) != 0)
        i += 1;
      machCode = labelArr[i].address;
      machCode = machCode | (2 << 26);
      printf("0x%06X: 0x%08X\n", addressCount, machCode);
      addressCount += 4;
      printCount += 1;
    }
    else if(strcmp(lineArr[printCount].operand, "la") == 0){
      int i = 0;
      while(strcmp(labelArr[i].name, lineArr[printCount].targetLabel) != 0)
        i += 1;
      machCode = (labelArr[i].address >> 16);
      machCode = machCode & (65535);
      machCode = machCode | (15 << 26);
      machCode = machCode | (1 << 16);
      printf("0x%06X: 0x%08X\n", addressCount, machCode);
      addressCount += 4;

      machCode = 0;
      machCode = labelArr[i].address;
      machCode = machCode & (65535);
      machCode = machCode | (13 << 26);
      machCode = machCode | (1 << 21);
      machCode = machCode | (lineArr[printCount].rt << 16);
      printf("0x%06X: 0x%08X\n", addressCount, machCode);
      addressCount += 4;
      printCount += 1;
    }
    else printCount += 1;
  }
  return 0;
}

unsigned int convertReg(char* reg){
  if(strcmp(reg, "t0") == 0) return 8;
  else if(strcmp(reg, "t1") == 0) return 9;
  else if(strcmp(reg, "t2") == 0) return 10;
  else if(strcmp(reg, "t3") == 0) return 11;
  else if(strcmp(reg, "t4") == 0) return 12;
  else if(strcmp(reg, "t5") == 0) return 13;
  else if(strcmp(reg, "t6") == 0) return 14;
  else if(strcmp(reg, "t7") == 0) return 15;
  else if(strcmp(reg, "s0") == 0) return 16;
  else if(strcmp(reg, "s1") == 0) return 17;
  else if(strcmp(reg, "s2") == 0) return 18;
  else if(strcmp(reg, "s3") == 0) return 19;
  else if(strcmp(reg, "s4") == 0) return 20;
  else if(strcmp(reg, "s5") == 0) return 21;
  else if(strcmp(reg, "s6") == 0) return 22;
  else if(strcmp(reg, "s7") == 0) return 23;
  else return 0;
}
