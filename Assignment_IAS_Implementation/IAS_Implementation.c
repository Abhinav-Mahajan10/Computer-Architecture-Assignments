#include<stdio.h>
#include<stdlib.h>
void fetch(int *PC, long *MBR, int *IR, int *IBR, int *MAR, long *memory_ptr)
{
    if(*IBR == 0)
    {   
        *MAR = *PC;
        *MBR = memory_ptr[*MAR];
        int lo, la, ri;
        /*this is the left opcode,
        left address, and
        right instruction respectively*/
        long temp = *MBR;
        ri = temp & 0b11111111111111111111;
        temp = temp >> 20;
        la = temp & 0b111111111111;
        temp = temp >> 12;
        lo = temp & 0b11111111;
        *IR = lo;
        *MAR = la;
        *IBR = ri;
        *PC = *PC + 1;
    }
    else
    {
        long temp = *IBR;
        int lo, la;
        la = temp & 0b111111111111;
        temp = temp >> 12;
        lo = temp & 0b11111111;
        *IR = lo;
        *MAR = la;
        //clearing IBR for next fetch cycle
        *IBR = 0;
    }
}
int decode_and_execute(int *IR, int *MAR, int *IBR, long *MBR, long *AC, long *MQ, int *PC, long *memory_ptr)
{
    int flag = 1;
    long result;
    switch(*IR)
    {
        case 10://LOAD MQ
        *AC = *MQ;
        break;
        case 9://LOAD MQ,M(X)
        *MBR = memory_ptr[*MAR];
        *MQ = *MBR;
        break;
        case 33://STOR M(X)
        *MBR = *AC;
        memory_ptr[*MAR] = *MBR;
        break;
        case 1://LOAD M(X)
        *MBR = memory_ptr[*MAR];
        *AC = *MBR;
        break;
        case 2://LOAD -M(X)
        *MBR = -1 * memory_ptr[*MAR];
        *AC = *MBR;
        break;
        case 3://LOAD |M(X)|
        *MBR = memory_ptr[*MAR];
        if(*MBR < 0)
        {
            *MBR = -1 * (*MBR);
        }
        *AC = *MBR;
        break;
        case 4://LOAD -|M(X)|
        *MBR = memory_ptr[*MAR];
        if(*MBR >= 0)
        {
            *MBR = -1 * (*MBR);
        }
        *AC = *MBR;
        break;
        case 13://JUMP M(X, 0:19)
        *PC = *MAR;
        //IBR is cleared so that the code can do the next fetch cycle well
        *IBR = 0;
        break;
        case 15://JUMP+ M(X, 0:19)
        if(*AC > 0)
        {
            *PC = *MAR;
            //IBR is cleared so that the code can do the next fetch cycle well
            *IBR = 0;
        }
        break;
        case 5://ADD M(X)
        *MBR = memory_ptr[*MAR];
        *AC = *AC + *MBR;
        break;
        case 7://ADD |M(X)|
        *MBR = memory_ptr[*MAR];
        if(*MBR < 0)
        {
            *MBR = *MBR * -1;
        }
        *AC = *AC + *MBR;
        break;
        case 6://SUB M(X)
        *MBR = memory_ptr[*MAR];
        *AC = *AC - *MBR;
        break;
        case 8://SUB |M(X)|
        *MBR = memory_ptr[*MAR];
        if(*MBR < 0)
        {
            *MBR = *MBR * -1;
        }
        *AC = *AC - *MBR;
        break;
        case 11://MUL M(X)
        *MBR = memory_ptr[*MAR];
        result = *MBR * *MQ;
        *MQ = result & 0b1111111111111111111111111111111111111111;
        result = result >> 40;
        *AC = result;
        break;
        case 12://DIV M(X)
        *MBR = memory_ptr[*MAR];
        result = *AC / *MBR;
        *MQ = result;
        result = *AC % *MBR;
        *AC = result;
        break;
        case 20://LSH
        *AC = *AC << 1;
        break;
        case 21://RSH
        *AC = *AC >> 1;
        break;
        case 76://HLT
        flag = 0;
        return flag;
        break;
    }
    return flag;
}
int main()
{
    long n;
    printf("Enter number n:- ");
    scanf("%ld", &n);

    //1st program : sum of first n numbers
    //sample C code
    /*int c = 0;
    while(n != 0)
    {
        c+=n;
        n = n - 1;
    }*/

    //MACHINE CODE
    /*LOAD M(1), ADD M(0)
    STOR M(1), LOAD M(0)
    SUB M(2), STOR M(0)
    JUMP+ M(5,0:19),  TERMINATION
    */

    //Let's call memory stack of first program in machine language, mem_1;
    long mem_1[9];
    //let first 5 memory locations are dedicated to some variables
    //Each location in memory stores a 40 bit data/instruction
    //The data part has no opcode 
    // WE ARE USING OPCODE 76 TO MARK THE END OF THE EXECUTION PHASE
    //Taking n
    mem_1[0] = n;

    //mem_1[1]: holds the variable which has final ans
    mem_1[1] = 0b0000000000000000000000000000000000000000;
    
    //mem_1[2]:holds a constant 1, which is needed for n = n - 1;
    mem_1[2] = 0b0000000000000000000000000000000000000001;

    //mem_1[3]: has a variable (not used)
    mem_1[3] = 0b0000000000000000000000000000000000000000;

    //mem_1[4]:variable(not used) 
    mem_1[4] = 0b0000000000000000000000000000000000000000;

    //before comma is left instruction , after comma is right instruction
    //loadM(1), addM(0)
    //load c in accumulator , add value of n i.e value at mem_1[0]
    mem_1[5] = 0b0000000100000000000100000101000000000000;

    // STOR M(1), LOAD M(0)
    //store the value in acc to c, load n in acc
    mem_1[6] = 0b0010000100000000000100000001000000000000;
    
    //SUB M(2), STOR M(0)
    //sub value at mem_1[2] from value at acc, store back the value in mem_1[0];
    mem_1[7] = 0b0000011000000000001000100001000000000000;

    //JUMP+ M(5,0:19),  TERMINATION
    //jump to mem_1[5] if acc is positive i.e; current value is n is > 0, else opcode 76 marks for termination of code;
    mem_1[8] = 0b0000111100000000010101001100000000000000;


    //Second program : factorial of a number n
    // Sample C code
    /*int c= 1; 
    while(n>0)
    {
        c=c*n;
        n=n-1;
    }
    */

    //Machine code
    /*LOAD MQ,M(1)
    MUL M(0) , LOAD M(0)
    SUB M(2) , STOR M(0)
    JUMP + M(6,0:19) , LOAD MQ
    STOR M(1) , END OF THE PROGRAM
    */


    long mem_2[10];
    //let first 5 memory locations are dedicated to some variables
    //Each location in memory stores a 40 bit data/instruction
    //The data part has no opcode 
    // WE ARE USING OPCODE 76 TO MARK THE END OF THE EXECUTION PHASE
    mem_2[0] = n;

    //mem_2[1]: holds the variable which has final ans
    mem_2[1] = 0b0000000000000000000000000000000000000001;

    //mem_2[2]:holds a constant 1.
    mem_2[2] = 0b0000000000000000000000000000000000000001;

    //mem_2[3]: has a variable(not used)
    mem_2[3] = 0b0000000000000000000000000000000000000000;

    //mem_2[4]: variable(not used) 
    mem_2[4] = 0b0000000000000000000000000000000000000000;

    //before comma is left instruction , after comma is right instruction
    //load mem_2[1]to MQ
    //LOAD MQ,M(1)   
    mem_2[5] = 0b00001001000000000001;

    // MUL M(0) , LOAD M(0)
    //mulm(0), load mem_2[0] to acc 
    mem_2[6] = 0b0000101100000000000000000001000000000000;

    // SUB M(2) , STOR M(0)
    // sub 1 form it using subm[2] , store the value of acc to mem_2[0]
    mem_2[7] = 0b0000011000000000001000100001000000000000;

    // JUMP + M(6,0:19) , LOAD MQ
    //jump to mem_2[6] if acc is non negative , load mq to acc
    //AS LOAD MQ DOES NOT REQUIRE THE MEMORY ADDRESS I AM GIVING IT AS 1111 1111 1111
    mem_2[8] = 0b0000111100000000011000001010111111111111;

    // STOR M(1) , END OF THE PROGRAM
    //store the acc into mem_2[1], end of the program
    mem_2[9] = 0b0010000100000000000101001100111111111111;


    //Third program :  Count no of digits in a given number n
    //Sample C code
    /*int count =0;
    while(n!=0)
    {
        count=count+1;
        n=n/10;
    }*/

    //Machine code
    /*LOAD M(1), ADD M(3)
    STOR M(1), LOAD M(0)
    DIV M(2) , LOAD MQ
    STOR M(0), JUMP + M(5, 0:19)
    END OF THE PROGRAM
    */
    
    long mem_3[10];
    //let first 5 memory locations are dedicated to some variables
    //Each location in memory stores a 40 bit data/instruction
    //The data part has no opcode
    // WE ARE USING OPCODE 76 TO MARK THE END OF THE EXECUTION PHASE
    mem_3[0] = n;

    //mem_3[1]: holds the variable which has final ans
    mem_3[1] = 0b0000000000000000000000000000000000000000;

    //mem_3[2]:holds a constant 10 .
    mem_3[2] = 0b0000000000000000000000000000000000001010;

    //mem_3[3]: has a constant 1
    mem_3[3] = 0b0000000000000000000000000000000000000001;

    //mem_3[4]:variable(not used)
    mem_3[4] = 0b0000000000000000000000000000000000000000;

    //before comma is left instruction , after comma is right instruction
    //LOAD M(1), ADD M(3)
    //load mem_3[1] in acc,  add mem_3[3] to it
    mem_3[5] = 0b0000000100000000000100000101000000000011;

    //STOR M(1), LOAD M(0)
    //store acc in mem_3[1],load mem_3[0] in acc
    mem_3[6] = 0b0010000100000000000100000001000000000000;

    //DIV M(2) , LOAD MQ
    //divide by mem_3[2], transfer mq to acc
    mem_3[7] = 0b0000110000000000001000001010111111111111;

    // STOR M(0), JUMP + M(5, 0:19)
    //stor the acc to mem_3[0], goto mem_3[5] if acc is non negative
    mem_3[8] = 0b0010000100000000000000001111000000000101;

    // END OF THE PROGRAM
    //end of the program optcode 76;
    mem_3[9] = 0b01001100111111111111;
    

    
    long MBR = 0;
    int MAR = 0;
    int IBR = 0;
    int IR = 0;
    long AC = 0;
    long MQ = 0;

    //PROGRAM 1:-(SUM OF FIRST N NUMBERS)
    int flag = 1;
    long *memory_ptr = mem_1;
    int PC = 5;
    while(flag == 1)
    {
        fetch(&PC, &MBR, &IR, &IBR, &MAR, memory_ptr);
        flag = decode_and_execute(&IR, &MAR, &IBR, &MBR, &AC, &MQ, &PC, memory_ptr);
    }
    printf("Sum of first n numbers is = %ld\n", mem_1[1]);

    //PROGRAM 2:-(PRODUCT OF FIRST N NUMBERS)
    MBR = 0;
    MAR = 0;
    IBR = 0;
    IR = 0;
    AC = 0;
    MQ = 0;
    flag = 1;
    memory_ptr = mem_2;
    PC = 5;
    while(flag == 1)
    {
        fetch(&PC, &MBR, &IR, &IBR, &MAR, memory_ptr);
        flag = decode_and_execute(&IR, &MAR, &IBR, &MBR, &AC, &MQ, &PC, memory_ptr);
    }
    printf("Product of first n numbers is = %ld\n", mem_2[1]);

    //PROGRAM 3:-(SUM OF FIRST N NUMBERS)
    MBR = 0;
    MAR = 0;
    IBR = 0;
    IR = 0;
    AC = 0;
    MQ = 0;
    flag = 1;
    memory_ptr = mem_3;
    PC = 5;
    while(flag == 1)
    {
        fetch(&PC, &MBR, &IR, &IBR, &MAR, memory_ptr);
        flag = decode_and_execute(&IR, &MAR, &IBR, &MBR, &AC, &MQ, &PC, memory_ptr);
    }
    printf("Number of digits of n is = %ld\n", mem_3[1]);
    return 0;
}

