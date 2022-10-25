module counter #(parameter WIDTH = 8)
(input logic clk, // Clock
 input logic rst, // Reset
 input logic en, // Counter enable
 output logic[WIDTH-1:0] count); // Counter output
    
    always_ff @(posedge clk)
        if (rst)
            count <= {WIDTH{1'b0}};
        else if (en)
            count <= count + {{WIDTH-1{1'b0}}, 1'b1};
        else
            count <= count - {{WIDTH-1{1'b0}}, 1'b1};

endmodule
