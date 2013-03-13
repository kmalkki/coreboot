#include <stdint.h>
#include <stdlib.h>
#include <console/console.h>
#include <arch/io.h>
#include <arch/romcc_io.h>
#include <device/pci_def.h>
#include "i915.h"

int i915_silicon_revision(void)
{
	return pci_read_config8(PCI_DEV(0, 0x00, 0), PCI_CLASS_REVISION);
}

void i915_detect_chipset(void)
{
	u8 reg8;
	u8 i;

	printk(BIOS_INFO, "MCH CAPID0: ");
	for (i = 0xe3; i < 0xe9; i++) {
		reg8 = pci_read_config8(PCI_DEV(0, 0x00, 0), i);
		printk(BIOS_INFO, "%02x ", reg8);
	}
	printk(BIOS_INFO, "\n");

	/* If this GMCH does not have internal graphics capability (CAPID0[38] = 1)  */
	
}

