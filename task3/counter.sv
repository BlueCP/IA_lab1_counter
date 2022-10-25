module counter #(parameter WIDTH = 8)
(input logic clk, // Clock
 input logic rst, // Reset
 input logic en, // Counter enable

 input logic pst, // Preset (to Vbuddy internal value)
 input logic[WIDTH-1:0] vbdval, // Vbuddy internal value

 output logic[WIDTH-1:0] count); // Counter output
    
    always_ff @(posedge clk)
        if (pst)
            count = vbdval;
        else if (rst)
            count <= {WIDTH{1'b0}};
        else
            count <= count - {{WIDTH-1{1'b0}}, en};

endmodule
