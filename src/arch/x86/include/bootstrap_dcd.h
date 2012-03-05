#include <arch/io.h>
#include <device/pnp_def.h>
#include <arch/romcc_io.h>
#include <uart8250.h>

/* grab from devicetree.cb ? */
#define EARLY_SERIAL_DEV PNP_DEV(0x2e, 0x02)
#define EARLY_TTYS0_BASE 0x3f8

#if CONFIG_TTYS0_DCD_HOOK
static int early_dcd_hook(void)
{
	device_t dev = EARLY_SERIAL_DEV;
	u16 port = dev >> 8;
	u16 base;
	u8 dcd, i;
	
	// Set COM1/COM2 decode range
	pci_write_config16(PCI_DEV(0, 0x1f, 0), 0x80, 0x0010);
	// Enable COM1/COM2/KBD/SuperIO1+2
	pci_write_config16(PCI_DEV(0, 0x1f, 0), 0x82, 0x340b);
		
	/* power-up uart, set base if not already set */
	outb(0x87, port);
	outb(0x87, port);
	pnp_set_logical_device(dev);
	pnp_set_enable(dev, 0);
	base = pnp_read_iobase(dev, PNP_IDX_IO0);
	if (!base) {
		base = EARLY_TTYS0_BASE;
		pnp_set_iobase(dev, PNP_IDX_IO0, base);
	}
	pnp_set_enable(dev, 1);
	outb(0xaa, port);

	/* assert DTR, so you can jump-wire DCD high */
	outb(UART_MCR_DTR, base + UART_MCR);
	
	/* just powered up.. better not to trust the first value */
	i = 0;
	do {
		dcd = !!(inb(base + UART_MSR) & UART_MSR_DCD);
	} while (++i<10);
	return dcd;
}

static void early_dtr_drop(void)
{
	device_t dev = EARLY_SERIAL_DEV;
	u16 port = dev >> 8;
	u16 base;
	
	outb(0x87, port);
	outb(0x87, port);
	pnp_set_logical_device(dev);
	base = pnp_read_iobase(dev, PNP_IDX_IO0);
	outb(0xaa, port);
	/* drop DTR */
	outb(0, base + UART_MCR);
}
#endif

