#include "Vtop.h"

#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);

    // Init top verilog instance
    Vtop* top = new Vtop;

    // Init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("top.vcd");

    // Init Vbuddy
    if (vbdOpen() != 1)
        return(-1);
    vbdHeader("Lab 1: Counter");

    // Init simulation inputs
    top->clk = 1;
    top->rst = 0;
    top->en = 0;

    // Run simulation for all 256 possible values
    for (i = 0; i < 256; i ++) {
        
        // Dump variables into VCD file and toggle clock
        for (clk = 0; clk < 2; clk ++) {
            tfp->dump(2*i + clk);
            top->clk = !top->clk;
            top->eval();
        }

        int val2 = (int(top->bcd) >> 8) & 0xf;
        int val1 = (int(top->bcd) >> 4) & 0xf;
        int val0 = int(top->bcd) & 0xf;
        int bcdVal = val2 * 100 + val1 * 10 + val0;

        if (bcdVal != i) {
            return(-1);
        }

        //Send count value to Vbuddy
        vbdHex(4, 0);
        vbdHex(3, val2);
        vbdHex(2, val1);
        vbdHex(1, val0);
        vbdCycle(i + 1);

        // Change input stimuli
        top->en = 1; // Delay enable so that i = count always

        if (Verilated::gotFinish()) exit(0);
    }

    vbdClose();
    tfp->close();
    exit(0);
}