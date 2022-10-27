#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env) {
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
    vbdSetMode(1); // Set flag to one-shot behaviour

    // Init simulation inputs
    top->clk = 1;
    top->rst = 0;
    top->en = 1; // For this test, let en=1

    int i = 0;
    while (i < 100) {
        if (vbdFlag()) {
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
            if (Verilated::gotFinish()) exit(0);
            i++;
        }
    }

    vbdClose();
    tfp->close();
    exit(0);
}