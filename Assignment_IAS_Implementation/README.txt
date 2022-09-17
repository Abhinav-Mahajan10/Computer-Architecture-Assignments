Computer Assignment
Title:- Implementation of an IAS Machine
By:- 
Abhinav Mahajan, IMT2020553
 	and
 Shaurya Agrawal, IMT2020539
 
 Main Project File is:- IAS_Implementation.c
 Brief Explanation:-
 in main():-
 Under comments, the first C program is written, sum of the first n numbers
  Then its Assembly level language is written in terms of instructions.
  Then a data structure called mem_1[9] is made, which is the memory stack on which the program works.
  mem_1[9] will contain the machine level language code of the instuctions which an IAS machine can understand.
  Same is done for the next 2 programs. 
  Program 2 is evaluvation of n factorial. Its memory stack structure is called mem_2
  Program 3 is counting number of digits of n. Its memory stack structure is called mem_3
  
 Following these lines of code, for each sample programs memory stack(mem_1, mem2, mem_3), we run the fetch and decode_and_execute cycles until the sample program reach their execution.
 Comments are provided in the code for understanding. All variable names are standard, as used in the IAS machine.(eg. IR, IBR, MAR, MBR)
 
 How to run the program:-
 output file(a.out) provided in the document. ./a.out command in the terminal would result in the execution of the program.
 First line of input is "Enter number n:-"
 Then the user can enter number n, which should be a positive INTEGER > 0.
 The program would evaluate the sum of the first n numbers, n factorial and the number of digits of n.
 NOTE:-
 For n factorial, The answer is correct only upto 14, 15! > 2^40, its value cannot be storred in MQ alone. MQ is the variable used for multiplication in an IAS machine. AC just stores the Overflowed digits of multiplication, but it is not involved in multiplication.
