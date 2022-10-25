module top #(parameter WIDTH = 8, parameter DIGITS = 3)
(input wire clk, // Clock
 input wire rst, // Reset
 input wire en, // Enable
 input wire[WIDTH-1:0] v, // Value to preload
 output wire [11:0] bcd // Count output
);

    wire[WIDTH-1:0] count; // Interconnect wire

    counter myCounter(clk, rst, en, count);
    bin2bcd myDecoder(count, bcd);

endmodule