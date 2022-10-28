#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env) {
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
    top->rst = 0;
    top->en = 1;

    // Run simulation for many clock cycles
    for (int i = 0; i < 100; i ++) {

        // Clock low

        tfp->dump(2*i);
        top->clk = 0;
        top->eval();

        // Clock high
        tfp->dump(2*i + 1);

        top->clk = 1;
        if (top->count == 9 && internalCount < 3) {
            internalCount ++;
        } else if (internalCount == 3) {
            internalCount = 0;
        }
        top->en = internalCount == 0;
        top->rst = i == 5 && internalCount == 0;

        top->eval();
        
        if (Verilated::gotFinish()) exit(0);
    }
    tfp->close();
    exit(0);
}