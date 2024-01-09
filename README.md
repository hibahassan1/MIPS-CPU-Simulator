# Project Understanding
The implementation here is MIPS-32 using Single-Cycle Datapaths

# Instructions implemented
add
addi
lw
sw
sll
and
andi
or
ori
nor
beq
j
slt
sub
mul
srl
slti
xor
xori

# Assumptions made
1. All register files are initially set to 0
2. The Data Memeory and Instruction Memory are initially empty and will only contain data as we enter them
3.  beq and j use PC-relative addressing

# Example code executions
First of all enter the initial PC value, then execute either of the following examples or your own instructions containing only the instructions implemented.
# Example 1:
addi $t0, $zero, 30
sw $t0, 30 ($t0)
lw $t1, 30($t0)

# Example 2:
addi $t1, $zero, 0
addi $t2, $zero, 5
slt $t3, $t1, $t2
beq $t3, $zero, 7
addi $t1, $t1, 1
j 3
addi $s0, $zero, 0

Enter halt to end the line of instructions

# Output Explanation
After executing the example codes, we are able to see the changes in the register files, along with Instruction Memory contents and Data Memory Contents.
We are also able to see the values inside each wires within the Single-Cycle Datapath.



