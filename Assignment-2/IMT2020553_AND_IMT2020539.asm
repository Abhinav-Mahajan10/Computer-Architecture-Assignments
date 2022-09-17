#Written by Harshith(IMT2017516)
#email: Harshith.Reddy@iiitb.org

#run in linux terminal by java -jar Mars4_5.jar nc filename.asm(take inputs from console)

#system calls by MARS simulator:
#http://courses.missouristate.edu/kenvollmar/mars/help/syscallhelp.html
.data
	next_line: .asciiz "\n"	
.text
#input: N= how many numbers to sort should be entered from terminal. 
#It is stored in $t1	
jal input_int 
move $t1,$t4			

#input: X=The Starting address of input numbers (each 32bits) should be entered from
# terminal in decimal format. It is stored in $t2
jal input_int
move $t2,$t4

#input:Y= The Starting address of output numbers(each 32bits) should be entered
# from terminal in decimal. It is stored in $t3
jal input_int
move $t3,$t4 

#input: The numbers to be sorted are now entered from terminal.
# They are stored in memory array whose starting address is given by $t2
move $t8,$t2
move $s7,$zero	#i = 0
loop1:  beq $s7,$t1,loop1end
	jal input_int
	sw $t4,0($t2)
	addi $t2,$t2,4
      	addi $s7,$s7,1
        j loop1      
loop1end: move $t2,$t8       
#############################################################
#Do not change any code above this line
#Occupied registers $t1,$t2,$t3. Don't use them in your sort function.
#############################################################
#function: should be written by students(sorting function)
#The below function adds 10 to the numbers. You have to replace this with
#your code
#MY CODE

move $t8,$t2 #using $t8 and $t7 to restore value of $t2 and $t3 after loop2 
move $t7,$t3
move $s7,$zero	#i = 0
#Loop for storing the numbers in the output location because initial/source array
#-should remain unsorted, so copying the initial array to the output memory location
loop2:  beq $s7,$t1,loop2end 
	lw $s6,0($t2) #$s6=mem($t2)
	sw $s6,0($t3) #mem($t3)=$s6
	addi $t2,$t2,4  #$t2=$t2+4
	addi $t3,$t3,4	#$t3=$t3+4
      	addi $s7,$s7,1	#$s7=$s7+1
        j loop2      
loop2end: 
	move $t2,$t8
	move $t3,$t7
	
	
#n is number of elements in the array
add $t5,$t1,-1 #t5 = n - 1
move $s7,$zero	#i = 0
loop_outer:  
	beq $s7,$t5,loop_outer_end #t5=n-1
	sub $t6,$t5,$s7 #t6 = n - 1 - i
	move $s6,$zero #k = 0 , s6 is the counter for inner loop
	move $s0,$t3  #storing the starting address of the array in $s0
	jal loop_inner
	#addi $t0,$t0,4
      	addi $s7,$s7,1 #$s7=$s7+1
        j loop_outer      
loop_outer_end: 
	j after_sort


loop_inner:
	beq $s6,$t6,loop_inner_end #t6 = n-1-i
	addi $s1,$s0,4  #next memory location to $s0
	lw $s2,0($s0)  #suppose s2 holds jth location memory value
	lw $s3,0($s1)  #then s3 hold the (j+1)th location memory value
	slt $s4,$s3,$s2 #if $s3<$s2 then $s4=1(swap condition)
	add $s5,$zero,1 #$s5=1
	beq $s4, $s5, swap #(if $s4==$s5 then go to swap  
	addi $s6,$s6,1 #$s6=$s6+1
	addi $s0,$s0,4 #$s0=$s0+4
	j loop_inner
	 
loop_inner_end:
	jr $ra


swap:
	sw $s3,0($s0)#swapping numbers
	sw $s2,0($s1)
	addi $s6,$s6,1#$s6=$s6+1
	addi $s0,$s0,4#$s0=$s0+4
	j loop_inner
	#saved registers used - s0 , s1 , s2 , s3 , s4 , s5 , s6 , s7
	
	
after_sort:  
	#restoring the original values of saved registers i.e,0
	move $s0,$zero
	move $s1,$zero
	move $s2,$zero
	move $s3,$zero
	move $s4,$zero
	move $s5,$zero
	move $s6,$zero
	move $s7,$zero

	
#endfunction
#############################################################
#You need not change any code below this line

#print sorted numbers
move $s7,$zero	#i = 0
loop: beq $s7,$t1,end
      lw $t4,0($t3)
      jal print_int
      jal print_line
      addi $t3,$t3,4
      addi $s7,$s7,1
      j loop 
#end
end:  li $v0,10
      syscall
#input from command line(takes input and stores it in $t6)
input_int: li $v0,5
	   syscall
	   move $t4,$v0
	   jr $ra
#print integer(prints the value of $t6 )
print_int: li $v0,1		#1 implie
	   move $a0,$t4
	   syscall
	   jr $ra
#print nextline
print_line:li $v0,4
	   la $a0,next_line
	   syscall
	   jr $ra
