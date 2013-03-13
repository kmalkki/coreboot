/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2012 secunet Security Networks AG
 * Copyright (C) 2013 Kyösti Mälkki <kyosti.malkki@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of
 * the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#include <arch/io.h>
#include <arch/romcc_io.h>
#include "i82801fx.h"

void i82801fx_early_init(void)
{
	const device_t d31f0 = PCI_DEV(0, 0x1f, 0);

	/* Set up RCBA. */
	pci_write_config32(d31f0, D31F0_RCBA, DEFAULT_RCBA | 1);

	/* Set up PMBASE. */
	pci_write_config32(d31f0, D31F0_PMBASE, DEFAULT_PMBASE | 1);
	/* Enable PMBASE. */
	pci_write_config8(d31f0, D31F0_ACPI_CNTL, 0x80);

	/* Set up GPIOBASE. */
	pci_write_config32(d31f0, D31F0_GPIO_BASE, DEFAULT_GPIOBASE);
	/* Enable GPIO. */
	pci_write_config8(d31f0, D31F0_GPIO_CNTL,
			  pci_read_config8(d31f0, D31F0_GPIO_CNTL) | 0x10);


	/* Reset watchdog. */
	outw(0x0008, DEFAULT_TCOBASE + 0x04); /* R/WC, clear TCO caused SMI. */
	outw(0x0002, DEFAULT_TCOBASE + 0x06); /* R/WC, clear second timeout. */

	/* Set NO_REBOOT on TCO timeout. */
	RCBA32(GCS) = RCBA32(GCS) | (1 << 5);
	
#if 1
	/* Change port 0x80 etc.. to PCI */
	RCBA32(GCS) |= 0x04;
#else
	/* Change port80 to LPC */
	RCBA32(GCS) &= ~0x04;
#endif

	/* Enable upper 128bytes of CMOS. */
	RCBA32(RC) = (1 << 2);
}

