#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vsinegen.h"

#include "vbuddy.cpp"     // include vbuddy code
//Defining constants in C++
#define MAX_SIM_CYC 1000000
#define ADDRESS_WIDTH 8
#define ROM_SZ 256

int main(int argc, char **argv, char**env) {
        int i;
        int clk;
        int tick;


    //Stays same:
    Verilated::commandArgs(argc, argv);
    sinegen* top = new sinegen; //sinegen needs to be class or struct so I can instance of
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp,99);
    tfp->open ("sinegen.vcd");
    //

    //initialize vbuddy
    if(vbdOpen()!=1) return(-1);
    vbdHeader("Lab 2: Sinegen");

    //intiailize initial simulation inputs
    top->en = 1; //Sinegen input values are incr[7:0], clk, rst, en and initialized to different values
    top->clk = 1;
    top->rst = 1;
    top->en = vbdFlag();

//run simulation for certain number of clock cycles
    for (i=0; i<MAX_SIM_CYC; i++) { //Simulation cycle iterates to 1,000,000
        //i is current clock cycle in overall duration of simulation (given in clock cycles)
        //but as we need clk cycle to iterate between 0,1 then:
        for (clk=0; clk<2; clk++) { //should be tick not clk, but I think that's just a variable name difference, no logic change
            tfp->dump (2*i+clk);
            top->clk = !top->clk;
            top->eval ();
        }
        //Code above switches clk cycle from 0 to 1 so we can create posedges, a 0 to 1 transition would be posedge

        //Send count value to be displayed on 7-seg display every cycle on vbuddy screen:
        /*vbdHex(4, (int(top->count) >> 16) & 0xF);
        vbdHex(3, (int(top->count) >> 8) & 0xF);
        vbdHex(2, (int(top->count) >> 4) & 0xF);
        vbdHex(1, (int(top->count) & 0xF));
        vbdCycle(i+1);*/

        vbdHex(4, (int(top->data_out) >> 16) & 0xF);
        vbdHex(3, (int(top->data_out) >> 8) & 0xF);
        vbdHex(2, (int(top->data_out) >> 4) & 0xF);
        vbdHex(1, (int(top->data_out) & 0xF);
        vbdBar(top->data_out & 0xFF);
        vbdCycle(i+1);

        top->en = vbdFlag();

        /*
        //Plotting ROM output
        //top->incr = vbdValue(); //so increment incr by setting it to vbd value, this varies incr every simulation cycle
        vbdPlot(int(top->dout), 0, 255);
        vbdCycle(i); //Set current vbdCycle to i, go over this method and VbdValue();
        */
        //so reset
        //else let rst = 0; 
 //so doing (i>4) checks whether i>4 and outputs a bool so if >4 then en = 1 so count increment starts
        
        if (i<2) {
            top->rst = 1;
        }
        else {
            top->rst = 0;
        }

        //if condition that's always primed to allow us to exit loop
        if ((Verilated::gotFinish()) || (vbdGetkey()=='q')) {
            exit(0);                // ... exit if finish OR 'q' pressed
        }
    }
    vbdClose();
    tfp->close();
    exit(0);
}