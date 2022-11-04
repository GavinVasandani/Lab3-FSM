module sreg4 (
    input logic en,
    input logic clk,
    input logic rst,
    input logic data_in,
    output logic data_out[3:0]
);

        logic [4:1] sreg;

        always_ff @ (posedge clk)
            if (rst)
                sreg <= 4'b0;
            else begin
                sreg[4] <= sreg[3];
                sreg[3] <= sreg[2];
                sreg[2] <= sreg[1];
                sreg[1] <= sreg[3] ^ sreg[4];
            end
        assign data_out = sreg;

        
        // assign data_out[0] = sreg[1];
        // assign data_out[1] = sreg[2];
        // assign data_out[2] = sreg[3];
        // assign data_out[3] = sreg[4];
        

endmodule

