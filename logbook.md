# Task 1:

Setup was completed as required by the specification.

## Challenge 1

I added a conditional statement to the testbench to start a counter if count=9. This de-asserts enable for three additional cycles, for a total of four cycles spent in the count=9 state. When the internal counter reaches 3, it is reset and enable is asserted again. The reset signal was modified to prevent it from overriding the pause from the internal counter.

## Challenge 2

Asynchronous reset was implemented by adding 'posedge rst' to the sensitivity list of the always_ff statement. In the case that the positive edges of the clock and reset coincided, the counter was seen to increment. This was expected since just before the positive edge of the reset, it would have been deasserted. Therefore, the always_ff block was executed with rst=0. As an additional note, implementing asynchronous signals with Verilator is probably ill-advised, since Verilator only simulates on the clock edge.

# Task 2:

There were found to be some problems with using the Vbuddy to see simulation results. This was due to a fault with the provided software, which was fixed in a modified version of vbuddy.cpp.

For the challenge, I expanded the conditional statement within the always_ff block to test en. A binary value of 1 is either added or subtracted from count depending on the value of en.

# Task 3:

## Challenge 1

I expanded the counter component with a data signal and a control signal which determines whether this new data signal is assigned to count. When the Vbuddy flag is read, the control signal is set to 1 (for 1 clock cycle), which overwrites the counter. The order of precedence of control signals is now preset, followed by reset, followed by enable.

## Challenge 2

The task was to provide one clock pulse every time the flag was triggered. The testbench was altered to only execute a clock cycle if the flag was set, and the for loop was changed to a while loop in antipication of the fact that not every iteration of the code corresponds to a clock cycle.

# Task 4:

For this task, the testbench was modified to continuously increment the counter to test all 8 bit unsigned numbers. For testing, it was set up so that the counter value was equal to the clock cycle for 0 - 255 (to do this, en was deasserted for the first clock cycle, then asserted for every one after that). The three decimal digits were extracted from the bcd output via shifts and combined into an integer in C++, then compared to the cycle number in the testbench. The extracted integer was also printed to the display, rather than the hexadecimal value. Testing proceeded without invoking the exception, proving that the binary to BCD converted works for all 8-bit numbers.