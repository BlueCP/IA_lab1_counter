module counter #(parameter WIDTH = 8)
(input logic clk, // Clock
 input logic rst, // Reset
 input logic en, // Counter enable
 output logic[WIDTH-1:0] count); // Counter output

    logic[1:0] internalCount;
    
    always @(posedge clk, rst) // Not sure how to make this block trigger on both positive clock edge and reset signal.
        if (count == {{WIDTH-4{1'b0}}, {4'b1001}} && internalCount != 2'b11) begin
            internalCount <= internalCount + 2'b01;
        end else if (internalCount == 2'b11) begin
            internalCount <= 2'b00;
            count <= count + {{WIDTH-1{1'b0}}, en};
        end else begin
            count <= count + {{WIDTH-1{1'b0}}, en};
        end

endmodule
