/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2013 Kyösti Mälkki <kyosti.malkki@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
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

#include <stdint.h>
#include <stdlib.h>
#include <console/console.h>
#include <arch/io.h>
#include <arch/romcc_io.h>
#include <device/pci_def.h>
#include "i915.h"

void i915_early_init(void)
{
	const device_t d0f0 = PCI_DEV(0, 0, 0);
	u32 dev_en;

	/* Setup PCIEXBAR. */
	pci_io_write_config32(d0f0, D0F0_PCIEXBAR_LO, DEFAULT_PCIEXBAR);

	/* Setup MCHBAR. */
	pci_write_config32(d0f0, D0F0_MCHBAR_LO, DEFAULT_MCHBAR);

	/* Setup DMIBAR. */
	pci_write_config32(d0f0, D0F0_DMIBAR_LO, DEFAULT_DMIBAR);

	/* Setup EPBAR. */
	pci_write_config32(d0f0, D0F0_EPBAR_LO, DEFAULT_EPBAR);

	/* Enable all BAR above. */
	dev_en = pci_read_config32(d0f0, DEVEN);
	dev_en |= (1<<31)|(1<<29)|(1<<28)|(1<<27);
	pci_write_config32(d0f0, DEVEN, dev_en);

	/* Set C0000-FFFFF to access RAM on both reads and writes */
	pci_write_config8(d0f0, D0F0_PAM(0), 0x30);
	pci_write_config8(d0f0, D0F0_PAM(1), 0x33);
	pci_write_config8(d0f0, D0F0_PAM(2), 0x33);
	pci_write_config8(d0f0, D0F0_PAM(3), 0x33);
	pci_write_config8(d0f0, D0F0_PAM(4), 0x33);
	pci_write_config8(d0f0, D0F0_PAM(5), 0x33);
	pci_write_config8(d0f0, D0F0_PAM(6), 0x33);
	
	pci_write_config32(PCI_DEV(0, 0x00, 0), SKPAD, SKPAD_NORMAL_BOOT_MAGIC);	
}


