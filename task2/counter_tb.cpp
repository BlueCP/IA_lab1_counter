#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    // Init top verilog instance
    Vcounter* top = new Vcounter;
    // Init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("counter.vcd");

    // Init Vbuddy
    if (vbdOpen() != 1)
        return(-1);
    vbdHeader("Lab 1: Counter");

    // Init simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    // Run simulation for many clock cycles
    for (i = 0; i < 100; i ++) {
        
        // Dump variables into VCD file and toggle clock
        for (clk = 0; clk < 2; clk ++) {
            tfp->dump(2*i + clk);
            top->clk = !top->clk;
            top->eval();
        }

        // Send count value to Vbuddy
        vbdHex(4, (int(top->count) >> 16) & 0xf);
        vbdHex(3, (int(top->count) >> 8) & 0xf);
        vbdHex(2, (int(top->count) >> 4) & 0xf);
        vbdHex(1, int(top->count) & 0xf);
        vbdCycle(i + 1);

        // Change input stimuli
        top->rst = (i < 2);
        top->en = vbdFlag();
        if (Verilated::gotFinish()) exit(0);
    }

    vbdClose();
    tfp->close();
    exit(0);
}