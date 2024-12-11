#ifndef ISR_H_
#define ISR_H_

// CPU exceptions ISRs
extern void *DivisionError;
extern void *Debug;
extern void *NonMaskableInterrupt;
extern void *Breakpoint;
extern void *Overflow;
extern void *BoundRangeExceeded;
extern void *InvalidOpcode;
extern void *DeviceNotAvailable;
extern void *DoubleFault;

extern void *InvalidTSS;
extern void *SegmentNotPresent;
extern void *StackSegmentFault;
extern void *GeneralProtectionFault;
extern void *PageFault;

extern void *FloatingPoint;
extern void *AlignmentCheck;
extern void *MachineCheck;

// IRQ
extern void *PIT;
extern void *Keyboard;

extern void *COM2;
extern void *COM1;
extern void *LPT2;
extern void *Floppy;
extern void *LPT1;
extern void *CMOS;

extern void *Mouse;
extern void *FPU;
extern void *PrimaryATA;
extern void *SecondaryATA;

// Software interrupts
extern void *test_interrupt;

#endif

