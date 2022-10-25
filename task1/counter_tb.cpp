#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env) {
    int clk;
    int internalCount = 0;

    Verilated::commandArgs(argc, argv);
    // Init top verilog instance
    Vcounter* top = new Vcounter;
    // Init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("counter.vcd");

    // Init simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    // Run simulation for many clock cycles
    for (int i = 0; i < 100; i ++) {
        
        // Dump variables into VCD file and toggle clock
        for (clk = 0; clk < 2; clk ++) {
            tfp->dump(2*i + clk);
            top->clk = !top->clk;
            top->eval();
        }
        if (top->count == 9 && internalCount < 3) {
            internalCount ++;
        } else if (internalCount == 3) {
            internalCount = 0;
        }
        top->en = internalCount == 0;
        top->rst = i == 15 && internalCount == 0;
        if (Verilated::gotFinish()) exit(0);
    }
    tfp->close();
    exit(0);
}