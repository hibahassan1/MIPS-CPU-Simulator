# Project Understanding
The implementation here is MIPS-32 using Single-Cycle Datapaths

# Instructions implemented
1. add
2. addi
3. lw
4. sw
5. sll
6. and
7. andi
8. or
9. ori
10. nor
11. beq
12. j
13. slt
14. sub
15. mul
16. srl
17. slti
18. xor
19. xori


# Assumptions made
1. All register files are initially set to 0
2. The Data Memeory and Instruction Memory are initially empty and will only contain data as we enter them
3.  beq and j use PC-relative addressing

# Example code executions
First, enter the initial PC value, then execute either of the following examples or your own instructions containing only the instructions implemented.

Example 1:

addi $t0, $zero, 30

sw $t0, 30 ($t0)

lw $t1, 30($t0)


Example 2:

addi $t1, $zero, 0

addi $t2, $zero, 5

slt $t3, $t1, $t2

beq $t3, $zero, 7

addi $t1, $t1, 1

j 3

addi $s0, $zero, 0


Enter halt to end the line of instructions

# Output Explanation
After executing the example codes, we can see the changes in the register files, Instruction Memory contents and Data Memory Contents.
We can also see the values inside each wire within the Single-Cycle Datapath.



