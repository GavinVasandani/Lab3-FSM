module div3FSM (
    input logic clk,
    input logic rst,
    output logic out
);

    //Define all possible states:
    typedef enum {S0, S1, S2, S3, S4, S5, S6, S7, S8} my_state;
    my_state current_state, next_state;

    //State registers
    always_ff @(posedge clk) begin
        
        if(rst)begin
            current_state<=S0;
        end
        
        if(en)begin
            current_state<=next_state;
        end
        else begin
            current_state<=current_state;
        end
    end

    //next state logic
    always_comb
        case (current_state)
            S0: if (en==1'b1) next_state = S1;
            S1: if (en==1'b1) next_state = S2;
            S2: if (en==1'b1) next_state = S3;
            S3: if (en==1'b1) next_state = S4;
            S4: if (en==1'b1) next_state = S4;
            S5: if (en==1'b1) next_state = S6;
            S6: next_state = S7;
            S7: next_state = S8;
            S8: next_state = S0;
            default: next_state = S0;
        endcase
    
    //Output logic
    always_comb begin
        case (current_state)
            S0: out = 8'b0;
            S1: out = 8'b1;
            S2: out = 8'b11;
            S3: out = 8'b111;
            S4: out = 8'b1111;
            S5: out = 8'b11111;
            S6: out = 8'b111111;
            S7: out = 8'b1111111;
            S8: out = 8'b11111111;
            default: out = 8'b0;
    end

endmodule

