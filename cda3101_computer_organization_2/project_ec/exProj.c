#include <stdio.h>
#include <string.h>

typedef struct rtype{
  int rs;
  int rt;
  int rd;
  int funct;
}rtype;
typedef struct itype{
  int rs;
  int rt;
  char target[33];
}itype;
union r_i{
  rtype r;
  itype i;
};
typedef struct line{
  char command[150];
  char label[33];
  char operand[5];
  int opCode;
  union r_i type;
}line;

void decodeInstruction(char* lineIn, line* instruction);
unsigned int convertReg(char* reg);
int checkHaz(line* previous, line* current);

int main(){
  int i, j;
  char lineIn[151];
  char tempLabel[33];
  char tempLabel2[33];
  line lineArr[200];
  line tempLine;

  i = 0;
  while(fgets(lineIn, 150, stdin) != 0){
    strcpy(lineArr[i].command, lineIn);
    decodeInstruction(lineIn, &(lineArr[i]));
    i++;

  }
  const int SIZE = i;
  i = 1;
  while(lineArr[i].opCode != -2){
    if(lineArr[i].opCode == 5){
      i++;
      continue;
    }
    else if(checkHaz(&(lineArr[i-1]), &(lineArr[i]))){
      if(checkHaz(&(lineArr[i]), &(lineArr[i+1])) != 1 &&
        checkHaz(&(lineArr[i-1]), &(lineArr[i+1])) != 1 &&
        lineArr[i+1].opCode != 5 && lineArr[i+1].opCode != -2){
          strcpy(tempLabel, lineArr[i].label);
          strcpy(tempLabel2, lineArr[i+1].label);
          tempLine = lineArr[i+1];
          lineArr[i+1] = lineArr[i];
          lineArr[i] = tempLine;
          strcpy(lineArr[i].label, tempLabel);
          strcpy(lineArr[i+1].label, tempLabel2);

      }
      i++;
      continue;
    }
    i++;
  }


  for(i = 0; i < SIZE; i++){
    printf("%s", lineArr[i].command);
  }
  printf("\n");
  return 0;
}

void decodeInstruction(char* lineIn, line* instruction){
  char rs[4], rt[4], rd[4];
  int immediate;
  //R-Type add & sub with label
  if(sscanf(lineIn, "%32[^:]: %s $%[^,],$%[^,],$%s",
    instruction->label, instruction->operand, rd, rs, rt) == 5){
      //labelArr[labArrIndex].address = addressCount;
      instruction->opCode = 0;
      instruction->type.r.rs = convertReg(rs);
      instruction->type.r.rt = convertReg(rt);
      instruction->type.r.rd = convertReg(rd);
      instruction->type.r.funct = -1;
  }
  //I-Type andi & ori with label & sll
  else if(sscanf(lineIn, "%32[^:]: %s $%[^,],$%[^,],%d",
    instruction->label, instruction->operand, rt, rs, &immediate) == 5){
      if(strcmp(instruction->operand, "sll") == 0){
        instruction->opCode = 0;
        instruction->type.r.rt = convertReg(rs);
        instruction->type.r.rd = convertReg(rt);
        instruction->type.r.funct = 0;
      }
      else{
        instruction->type.i.rs = convertReg(rs);
        instruction->type.i.rt = convertReg(rt);
        if(strcmp(instruction->operand, "andi") == 0)
          instruction->opCode = 12;
        else instruction->opCode = 13;
      }
  }
  //I-Type sw & lw with label
  else if(sscanf(lineIn, "%32[^:]: %s $%[^,],%d($%[^)])",
    instruction->label, instruction->operand, rt, &immediate, rs) == 5){
      instruction->type.i.rs = convertReg(rs);
      instruction->type.i.rt = convertReg(rt);
      if(strcmp(instruction->operand, "lw") == 0) instruction->opCode = 35;
      else instruction->opCode = 43;
  }
  //I-Type bne with label
  else if(sscanf(lineIn, "%32[^:]: %s $%[^,],$%[^,],%s",
    instruction->label, instruction->operand,
    rs, rt, instruction->type.i.target) == 5){
      instruction->opCode = 5;
      instruction->type.i.rs = convertReg(rs);
      instruction->type.i.rt = convertReg(rt);
  }
  //R-Type add & sub without label
  else if(sscanf(lineIn, "%s $%[^,],$%[^,],$%s",
    instruction->operand, rd, rs, rt) == 4){
      strcpy(instruction->label, "");
      instruction->type.r.rs = convertReg(rs);
      instruction->type.r.rt = convertReg(rt);
      instruction->type.r.rd = convertReg(rd);
      instruction->opCode = 0;
      instruction->type.r.funct = -1;
  }
  //I-Type addi & ori without label & sll without label
  else if(sscanf(lineIn, "%s $%[^,],$%[^,],%d",
    instruction->operand, rt, rs, &immediate) == 4){
      strcpy(instruction->label, "");
      if(strcmp(instruction->operand, "sll") == 0){
        instruction->opCode = 0;
        instruction->type.r.rt = convertReg(rs);
        instruction->type.r.rd = convertReg(rt);
        instruction->type.r.funct = 0;
      }
      else{
        instruction->type.i.rs = convertReg(rs);
        instruction->type.i.rt = convertReg(rt);
        if(strcmp(instruction->operand, "andi") == 0)
          instruction->opCode = 12;
        else instruction->opCode = 13;
      }
  }
  //I-Type sw & lw without label
  else if(sscanf(lineIn, "%s $%[^,],%d($%[^)])",
    instruction->operand, rt, &immediate, rs) == 4){
      strcpy(instruction->label, "");
      instruction->type.i.rs = convertReg(rs);
      instruction->type.i.rt = convertReg(rt);
      if(strcmp(instruction->operand, "lw") == 0) instruction->opCode = 35;
      else instruction->opCode = 43;
    }
  //I-Type bne without label
  else if(sscanf(lineIn, "%s $%[^,],$%[^,],%s",
    instruction->operand, rs, rt, instruction->type.i.target) == 4){
      strcpy(instruction->label, "");
      instruction->opCode = 5;
      instruction->type.i.rs = convertReg(rs);
      instruction->type.i.rt = convertReg(rt);
  }
  //directives .word with label
  else if(sscanf(lineIn, "%32[^:]: %s %d",
    instruction->label, instruction->operand, &immediate) == 3){
  }
  //NOOP & halt with label
  else if(sscanf(lineIn, "%s %s",
    instruction->label, instruction->operand) == 2){
      if(strcmp(instruction->operand, "noop") == 0) instruction->opCode = -1;
      else instruction->opCode = -2;
  }
  //directive .word without label
  else if (sscanf(lineIn, "%s %d", instruction->operand, &immediate) == 2){
    strcpy(instruction->label, "");
  }
  //directives .text .data, NOOP & halt without label
  else{
    sscanf(lineIn, "%s", instruction->operand);
    strcpy(instruction->label, "");
    if(strcmp(instruction->operand, "noop") == 0) instruction->opCode = -1;
    else if(strcmp(instruction->operand, "halt") == 0) instruction->opCode = -2;
    else instruction->opCode = -3;
  }
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
int checkHaz(line* previous, line* current){
  if(previous->opCode == 0){
    if(current->opCode == 0){
      if(current->type.r.funct != 0)
        if(current->type.r.rs == previous->type.r.rd ||
          current->type.r.rt == previous->type.r.rd){
            //printf("hit1\n");
            return 1;}
      else
        if(current->type.r.rt == previous->type.r.rd){
          //printf("hit2\n");
          return 1;}
    }
    else if(current->opCode == 5){
      if(current->type.i.rs == previous->type.r.rd ||
        current->type.i.rt == previous->type.r.rd){
          //printf("hit3\n");
          return 1;}
    }
    else if(current->opCode > 5 && current->opCode < 43){
      if(current->type.i.rs == previous->type.r.rd){
        //printf("hit4\n");
        return 1;}
    }
    else if(current->opCode == 43){
      if(current->type.i.rt == previous->type.r.rd)
        return 1;
    }
  }
  else if(previous->opCode > 5 /*&& previous->opCode < 43*/){
    if(current->opCode == 0){
      if(current->type.r.funct != 0)
        if(current->type.r.rs == previous->type.i.rt ||
          current->type.r.rt == previous->type.i.rt){
            //printf("hit5\n");
            return 1;}
      else
        if(current->type.r.rt == previous->type.i.rt){
          //printf("hit6\n");
          return 1;}
    }
    else if(current->opCode == 5){
      if(current->type.i.rs == previous->type.i.rt ||
        current->type.i.rt == previous->type.i.rt){
          //printf("hit7\n");
          return 1;}
    }
    else if(current->opCode > 5){
      if(current->type.i.rs == previous->type.i.rt){
        //printf("hit8\n");
        return 1;}
    }
  }
  return 0;
}
