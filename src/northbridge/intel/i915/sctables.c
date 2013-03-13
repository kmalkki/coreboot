
#include <console/console.h>
#include <cpu/x86/mtrr.h>
#include <cpu/x86/cache.h>
#include <pc80/mc146818rtc.h>
#include <spd.h>
#include <string.h>
#include <arch/romcc_io.h>
#include "raminit.h"
#include "i915.h"
#include <cbmem.h>


static const uint32_t dtpew[12 * 2] = {
	0xa2297a27, 0xdc99b470,	0xd2359e32, 0xeaabb676,
	0xd937a337, 0xe2d9aca3, 0xc0309028, 0xe8bcb88c,
	0xe53aac26, 0xb79a7d61, 0xf53eb82c, 0xb5cb788d,
	0xa4297b1e, 0xeb8fc266, 0xa4297b1e, 0xeb8fc266,
	0xed3cb21f, 0xd7999b5e, 0xd1359d1d, 0xe699b265,
	0xd1359d1d, 0xe699b265, 0xe439ab1b, 0xc5988c5f,
};

static const uint32_t dtaew[12 * 2] = {
	0x27242525, 0x2d2d1e25, 0x1c242424, 0x20202828,
	0x36361920, 0x1e253731, 0x35314040, 0x39392735,
	0x222f2f2c, 0x39323838, 0x4c4c2026, 0x2c3e3e38,
	0x37324343, 0x48482737, 0x2d33483c, 0x51456161,
	0x56563651, 0x3048483e, 0x443d4242, 0x5555142c,
	0x32454541, 0x3d3a4b4b, 0x5a5a2d3d, 0x363f5a4d,
};


static const uint8_t dtc[4][12] = {
	{
	0x72,0x72,0x54,
	0x5f,0x5f,0x42,
	0x66,0x66,0x4b,
	0x55,0x55,0x3b,
	},{
	0x4e,0x4e,0x45,
	0x4f,0x35,0x2c,
	0x6a,0x6a,0x4f,
	0x56,0x56,0x3d,
	},{
	0x5e,0x5e,0x46,
	0x4c,0x4c,0x36,
	0x64,0x64,0x53,
	0x64,0x47,0x3e,
	},{
	0x88,0x88,0x61,
	0x71,0x71,0x4b,
	0x78,0x78,0x56,
	0x64,0x64,0x43,
	}
};

#define DTC_COLUMN 2

/* Register names here were taken from i945, which does not implement any
 * user for these. Same register names appear in gm45, for thermal setup
 * of some sort.
 */
void sdram_thermal_setup(struct sys_info *sysinfo, uint32_t ax)
{
	const uint32_t ebp = (1 << 2) | (1 << 12);
	uint8_t i, j, offset = DTC_COLUMN;
	uint8_t a0, b0, a1, b1;

	/* Check for dual-channel configuration. */
	if ((ebp & 1<<2) && (ebp & 1<<12)) {
		offset += 6;
	}

	a1 = ax & 0xff;
	b1 = (uint8_t)  (ax >> 8);

	a0 = (ax >> 16) & 0xff;
	b0 = (uint8_t)  (ax >> (8+16));

	/* assert( 28 >= a > 40 ) */
	/* assert( 11 >= b > 15 ) */

	i = 2 * (a1-28);
	j = b1 - 11;

	MCHBAR32(C1DTPEW) &= 0x800000;
	MCHBAR32(C1DTPEW + 4) &= 0xffff00e0;
	MCHBAR32(C1DTPEW) |= dtpew[i+1];
	MCHBAR32(C1DTPEW + 4) |= dtpew[i];
	MCHBAR32(C1DTAEW) |= dtaew[i];
	MCHBAR32(C1DTAEW + 4) |= dtaew[i+1];
	MCHBAR8(C1DTC + 1) = dtc[j][i+offset];
	MCHBAR16(C1DRC1) &= 0xfbff;

	i = 2 * (a0-28);
	j = b0 - 11;

	MCHBAR32(C0DTPEW) &= 0x800000;
	MCHBAR32(C0DTPEW + 4) &= 0xffff00e0;
	MCHBAR32(C0DTPEW) |= dtpew[i+1];
	MCHBAR32(C0DTPEW + 4) |= dtpew[i];
	MCHBAR32(C0DTAEW) |= dtaew[i];
	MCHBAR32(C0DTAEW + 4) |= dtaew[i+1];
	MCHBAR8(C0DTC + 1) = dtc[j][i+offset];
	MCHBAR16(C0DRC1) &= 0xfbff;
}


#if 0

static const uint8_t chan0_dram_width[] = {
/* 4a99 */
	0x00, 0x01, 0x05, 0x00,
	0x10, 0x11, 0x15, 0x10,
 	0x50, 0x51, 0x55, 0x50,
 	0x00, 0x01, 0x05, 0x00
};

static const uint8_t chan1_dram_width[] = {
/* 4aa9 */
	0x00, 0x40, 0x50, 0x00,
	0x04, 0x44, 0x54, 0x04,
	0x05, 0x45, 0x55, 0x05,
	0x00, 0x40, 0x50, 0x00
};

#endif

static void sdram_program_dram_width(struct sys_info * sysinfo)
{
#if 0
	MCHBAR8(C0DRAMW) = chan0_dram_width[bl];
	MCHBAR8(C1DRAMW) = chan1_dram_width[bh];
	u8 c0dramw=0, c1dramw=0;

	if (bl & 0x3 == 1)
		c0dramw |= 0x01;
	else if (bl & 0x3 == 2)
		c0dramw |= 0x01 | 0x04;
	if (bl>>2 & 0x3 == 1)
		c0dramw |= 0x10;
	else if (bl>>2 & 0x3 == 2)
		c0dramw |= 0x10 | 0x40;

	if (bh & 0x3 == 1)
		c1dramw |= 0x40;
	else if (bh & 0x3 == 2)
		c1dramw |= 0x10 | 0x40;
	if (bh>>2 & 0x3 == 1)
		c1dramw |= 0x04;
	else if (bh>>2 & 0x3 == 2)
		c1dramw |= 0x01 | 0x04;

	MCHBAR8(C0DRAMW) = c0dramw;
	MCHBAR8(C1DRAMW) = c1dramw;
#else
	MCHBAR8(C0DRAMW) = 0x01;
	MCHBAR8(C1DRAMW) = 0x40;
#endif
}



static const uint8_t strength_multiplier[3][5] = {
/* 74243 */
	{0x33, 0x11, 0x00, 0x33, 0x33},
	{0x33, 0x11, 0x00, 0x33, 0x33},
	{0x22, 0x11, 0x00, 0x33, 0x33}
};

static const uint32_t slew_rate[3][5][16] = {
/* 00074282 */
{
	{
	0x02010000, 0x06050403, 0x0a090807, 0x12100e0c,
	0x1a181614, 0x22201e1c, 0x2a282624, 0x32302e2c,
	0x01010000, 0x03030202, 0x05050404, 0x07070606,
	0x0b0a0908, 0x12100e0c, 0x18161514, 0x201e1c1a,
	},{
	0x07050402, 0x0f0d0b09, 0x17151311, 0x1f1d1b19,
	0x27252321, 0x2f2d2b29, 0x37353331, 0x3f3d3b39,
	0x13110f0d, 0x1b191715, 0x23211f1d, 0x2b292725,
	0x33312f2d, 0x3b393735, 0x3f3f3f3d, 0x3f3f3f3f,
	},{
	0x06040201, 0x0e0c0a08, 0x16141210, 0x1e1c1a18,
	0x26242220, 0x2e2c2a28, 0x36343230, 0x3e3c3a38,
	0x08070504, 0x100e0c0a, 0x14131211, 0x1b191715,
	0x23211f1d, 0x2b292725, 0x33312f2d, 0x3b393735,
	},{
	0x03020202, 0x05040403, 0x09080706, 0x0d0c0b0a,
	0x11100f0e, 0x15141312, 0x19181716, 0x1d1c1b1a,
	0x03030301, 0x04040403, 0x06050505, 0x08070706,
	0x0a0a0908, 0x0e0d0c0b, 0x1211100f, 0x16151413,
	},{
	0x03020202, 0x05040403, 0x09080706, 0x0d0c0b0a,
	0x11100f0e, 0x15141312, 0x19181716, 0x1d1c1b1a,
	0x03030301, 0x04040403, 0x06050505, 0x08070706,
	0x0a0a0908, 0x0e0d0c0b, 0x1211100f, 0x16151413,
	},
},	
/* 000743c2 */
{
	{
	0x02010000, 0x06050403, 0x09080707, 0x110f0d0b,
	0x19171513, 0x211f1d1b, 0x29272523, 0x312f2d2b,
	0x01010000, 0x04030202, 0x05050404, 0x07060605,
	0x0b0a0908, 0x100f0e0c, 0x16141211, 0x1e1c1a18,
	},{
	0x06040200, 0x0e0c0a08, 0x16141210, 0x1e1c1a18,
	0x26242220, 0x2e2c2a28, 0x36343230, 0x3e3c3a38,
	0x110f0d0b, 0x19171513, 0x211f1d1b, 0x29272523,
	0x312f2d2b, 0x39373533, 0x3f3f3d3b, 0x3f3f3f3f,
	},{
	0x05030202, 0x0d0b0907, 0x1513110f, 0x1d1b1917,
	0x2523211f, 0x2d2b2927, 0x3533312f, 0x3d3b3937,
	0x0c0a0806, 0x1412100e, 0x1c1a1816, 0x2422201e,
	0x2c2a2826, 0x3432302e, 0x3c3a3836, 0x3f3f3f3e,
	},{
	0x03030202, 0x05040403, 0x08070605, 0x0c0b0a09,
	0x100f0e0d, 0x14131211, 0x18171615, 0x1c1b1a19,
	0x03030302, 0x04030303, 0x05040404, 0x07060605,
	0x09080807, 0x0d0c0b0a, 0x11100f0e, 0x15141312,
	},{
	0x03030202, 0x05040403, 0x08070605, 0x0c0b0a09,
	0x100f0e0d, 0x14131211, 0x18171615, 0x1c1b1a19,
	0x03030302, 0x04030303, 0x05040404, 0x07060605,
	0x09080807, 0x0d0c0b0a, 0x11100f0e, 0x15141312,
	}
},
/* 00074502 */
{
	{
	0x06050402, 0x0a090807, 0x0f0d0c0b, 0x15131110,
	0x1d1b1917, 0x2523211f, 0x2d2b2927, 0x3533312f,
	0x09070503, 0x0e0d0d0b, 0x1211100f, 0x17141313,
	0x1f1d1b19, 0x27252321, 0x2f2d2b29, 0x37353331,
	},{
	0x04020100, 0x0c0a0806, 0x1412100e, 0x1c1a1816,
	0x2422201e, 0x2c2a2826, 0x3432302e, 0x3c3a3836,
	0x0d0b0907, 0x1513110f, 0x1d1b1917, 0x2523211f,
	0x2d2b2927, 0x3533312f, 0x3d3b3937, 0x3f3f3f3f,
	},{
	0x09070503, 0x110f0d0b, 0x19171513, 0x211f1d1b,
	0x29272523, 0x312f2d2b, 0x39373533, 0x3f3f3d3b,
	0x1513110f, 0x1d1b1917, 0x2523211f, 0x2d2b2927,
	0x3533312f, 0x3d3b3937, 0x3f3f3f3f, 0x3f3f3f3f,
	},{
	0x05040302, 0x09080706, 0x0d0c0b0a, 0x13110f0e,
	0x1b191715, 0x23211f1d, 0x2b292725, 0x33312f2d,
	0x09090705, 0x0d0c0b0a, 0x11100f0e, 0x19171513,
	0x211f1d1b, 0x29272523, 0x312f2d2b, 0x39373533,
	},{
	0x05040302, 0x09080706, 0x0d0c0b0a, 0x13110f0e,
	0x1b191715, 0x23211f1d, 0x2b292725, 0x33312f2d,
	0x09090705, 0x0d0c0b0a, 0x11100f0e, 0x19171513,
	0x211f1d1b, 0x29272523, 0x312f2d2b, 0x39373533,
	},
}};


static const uint8_t strength_multiplier2[3][16] = {
/* 74252 */
	{
	0x00, 0x33, 0x33, 0x00,
	0x33, 0x33, 0x33, 0x33,
	0x33, 0x33, 0x33, 0x33,
	0x00, 0x33, 0x33, 0x33,
	},{
	0x00, 0x33, 0x33, 0x00,
	0x33, 0x33, 0x33, 0x33,
	0x33, 0x33, 0x33, 0x33,
	0x00, 0x33, 0x33, 0x33,
	},{
	0x00, 0x22, 0x33, 0x11,
	0x22, 0x44, 0x77, 0x33,
	0x33, 0x77, 0x77, 0x55,
	0x11, 0x33, 0x55, 0x33, 
	}
};


static const uint8_t slew_rate2_lut[3][16] =
{
/* 00074642 */
	{
	0x00, 0x00, 0x01, 0x02,
	0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00,
	},{
	0x00, 0x03, 0x04, 0x05,
	0x03, 0x03, 0x03, 0x03,
	0x04, 0x03, 0x03, 0x03,
	0x05, 0x03, 0x03, 0x03,
	},{
	0x00, 0x07, 0x0b, 0x06,
	0x07, 0x08, 0x09, 0x0b,
	0x0b, 0x09, 0x09, 0x0a,
	0x06, 0x0b, 0x0a, 0x0b,
	}
};

static const uint32_t slew_rate2[12][16] = {
/* 00074672 */
	{
	0x00000000, 0x05040301, 0x09080706, 0x100e0c0a,
	0x18161412, 0x201e1c1a, 0x28262422, 0x302e2c2a,
	0x02010000, 0x07050403, 0x0b0a0908, 0x0f0e0d0c,
	0x14121110, 0x1c1a1816, 0x2422201e, 0x2c2a2826,
	},{
	0x04030201, 0x0b0a0806, 0x12110f0d, 0x17151413,
	0x1f1d1b19, 0x27252321, 0x2f2d2b29, 0x37353331,
	0x0e0c0a08, 0x16141210, 0x1e1c1a18, 0x24232220,
	0x2a282625, 0x32302e2c, 0x3a383634, 0x3f3f3e3c,
	},{
	0x0a080604, 0x12100e0c, 0x1a181614, 0x22201e1c,
	0x2a282624, 0x32302e2c, 0x3a383634, 0x3f3f3e3c,
	0x0d0b0907, 0x1513110f, 0x1d1b1917, 0x2523211f,
	0x2d2b2927, 0x3533312f, 0x3d3b3937, 0x3f3f3f3f,
	},{
	0x01000000, 0x03020201, 0x07060504, 0x0b0a0908,
	0x0f0e0d0c, 0x13121110, 0x17161514, 0x1b1a1918,
	0x04030201, 0x05050404, 0x0b090706, 0x110f0d0c,
	0x19171513, 0x211f1d1b, 0x29272523, 0x312f2d2b,
	},{
	0x01000000, 0x08060402, 0x100e0c0a, 0x18161412,
	0x201e1c1a, 0x28262422, 0x302e2c2a, 0x38363432,
	0x0c0a0806, 0x1412100e, 0x1c1a1816, 0x2422201e,
	0x2c2a2826, 0x3432302e, 0x3c3a3836, 0x3f3f3f3e,
	},{
	0x05030202, 0x0d0b0907, 0x1513110f, 0x1d1b1917,
	0x2523211f, 0x2d2b2927, 0x3533312f, 0x3d3b3937,
	0x0c0a0806, 0x1412100e, 0x1c1a1816, 0x2422201e,
	0x2c2a2826, 0x3432302e, 0x3c3a3836, 0x3f3f3f3e,
	},{
	0x04020100, 0x0c0a0806, 0x1412100e, 0x1c1a1816,
	0x2422201e, 0x2c2a2826, 0x3432302e, 0x3c3a3836,
	0x0d0b0907, 0x1513110f, 0x1d1b1917, 0x2523211f,
	0x2d2b2927, 0x3533312f, 0x3d3b3937, 0x3f3f3f3f,
	},{
	0x01010000, 0x06050402, 0x0d0b0907, 0x1513110f,
	0x1d1b1917, 0x2321211f, 0x2b292725, 0x33312f2d,
	0x07050301, 0x0f0d0b09, 0x17151311, 0x1f1d1b19,
	0x27252321, 0x2f2d2b29, 0x37353331, 0x3f3d3b39,
	},{
	0x00000000, 0x01000000, 0x05040302, 0x0d0b0907,
	0x13110f0e, 0x1b191715, 0x21211f1d, 0x29272523,
	0x00000000, 0x06040201, 0x0c0a0908, 0x1412100e,
	0x1c1a1816, 0x2422201e, 0x2c2a2826, 0x3432302e,
	},{
	0x00000000, 0x00000000, 0x00000000, 0x02010101,
	0x04030302, 0x07070605, 0x0b0a0908, 0x0f0e0d0c,
	0x00000000, 0x00000000, 0x01010000, 0x03030202,
	0x07050404, 0x0c0b0a09, 0x110f0e0d, 0x19171513,
	},{
	0x00000000, 0x00000000, 0x01010000, 0x04030201,
	0x09070605, 0x0d0c0b0a, 0x11100f0e, 0x15141312,
	0x00000000, 0x01000000, 0x03020201, 0x07060504,
	0x0d0b0908, 0x1513110f, 0x1d1b1917, 0x2523211f,
	},{
	0x00000000, 0x02010000, 0x07050403, 0x0f0d0b09,
	0x17151311, 0x1f1d1b19, 0x27252321, 0x2f2d2b29,
	0x03020100, 0x0a080604, 0x12100e0c, 0x1a181614,
	0x22201e1c, 0x2a282624, 0x32302e2c, 0x3a383634,
	}
};

static void sdram_write_slew_rates(u32 offset, const u32 *slew_rate_table)
{
	int i;

	for (i=0; i<16; i++)
		MCHBAR32(offset+(i*4)) = slew_rate_table[i];
}

static void sdram_rcomp_buffer_strength_and_slew(struct sys_info *sysinfo)
{
	u8 i=2, bl=1, bh=1, k=0;
	
	/* Set Strength Multipliers */

#if 0	
	int idx, dual_channel;

	/* Dual Channel needs different tables. */
	if (sdram_capabilities_dual_channel()) {
		printk(BIOS_DEBUG, "Programming Dual Channel RCOMP\n");
		strength_multiplier = dual_channel_strength_multiplier;
		dual_channel = 1;
		idx = 5 * sysinfo->dimm[0] +  sysinfo->dimm[2];
	} else {
		printk(BIOS_DEBUG, "Programming Single Channel RCOMP\n");
		strength_multiplier = single_channel_strength_multiplier;
		dual_channel = 0;
		idx = 5 * sysinfo->dimm[0] + sysinfo->dimm[1];
	}
#endif

	printk(BIOS_DEBUG, "Table Index: %d\n", i);

	MCHBAR8(G1SC) = strength_multiplier[i][0];
	MCHBAR8(G7SC) = strength_multiplier[i][0];

	MCHBAR8(G3SC) = strength_multiplier[i][1];
	MCHBAR8(G4SC) = strength_multiplier[i][2];
	MCHBAR8(G5SC) = strength_multiplier[i][3];
	MCHBAR8(G6SC) = strength_multiplier[i][4];

	if (bl) /* FIXME */
		MCHBAR8(G2SC) = strength_multiplier2[i][bl];
	if (bh) /* FIXME */
		MCHBAR8(G8SC) = strength_multiplier2[i][bh];

	/* Channel 0 */
	sdram_write_slew_rates(G1SRPUT, slew_rate[i][0]);
	sdram_write_slew_rates(G7SRPUT, slew_rate[i][0]);

	sdram_write_slew_rates(G3SRPUT, slew_rate[i][1]);
	sdram_write_slew_rates(G4SRPUT, slew_rate[i][2]);
	sdram_write_slew_rates(G5SRPUT, slew_rate[i][3]);
	sdram_write_slew_rates(G6SRPUT, slew_rate[i][4]);

	if (bl) { /* FIXME */
		k = slew_rate2_lut[i][bl];
		sdram_write_slew_rates(G2SRPUT, slew_rate2[k]);
	}
	if (bh) { /* FIXME */
		k = slew_rate2_lut[i][bh];
		sdram_write_slew_rates(G8SRPUT, slew_rate2[k]);
	}
}


static const uint32_t dll_dqst_0[2][2] = {
/* 4223 */
	{0x24242424, 0x24242424},
	{0x23232323, 0x23232323}
};

static const uint32_t dll_dqst_1[2][2] = {
/* 4233 */
	{0x23232323, 0x23232323},
	{0x20202020, 0x20202020}
};


static void sdram_program_dll_timings(struct sys_info *sysinfo)
{
	u32 chan0dll = 0, chan1dll = 0;
	int i = 1;

	printk(BIOS_DEBUG, "Programming DLL Timings... \n");

	MCHBAR16(DQSMT) &= ~0x0f;
	if (1) // FIXME
		MCHBAR16(DQSMT) |= (1 << 13) | (0x0c << 0);
	else
		MCHBAR16(DQSMT) |= 0x0c;

	/* We drive both channels with the same speed */
	switch (sysinfo->memory_frequency) {
		case 400: i=0; break;
		case 533: i=1; break;
	}

	if (0) {  /* FIXME */
		chan0dll = dll_dqst_0[i][0];
		chan1dll = dll_dqst_0[i][1];
	} else {
		chan0dll = dll_dqst_1[i][0];
		chan1dll = dll_dqst_1[i][1];
	}

	for (i=0; i < 4; i++) {
		MCHBAR32(C0R0B00DQST + (i * 0x10) + 0) = chan0dll;
		MCHBAR32(C0R0B00DQST + (i * 0x10) + 4) = chan0dll;
		MCHBAR8(C0R0B00DQST + (i * 0x10) + 8) = chan0dll & 0xff;

		MCHBAR32(C1R0B00DQST + (i * 0x10) + 0) = chan1dll;
		MCHBAR32(C1R0B00DQST + (i * 0x10) + 4) = chan1dll;
		MCHBAR8(C1R0B00DQST + (i * 0x10) + 8) = chan1dll & 0xff;
	}
	MCHBAR16(WDLL_RST) |= 0x4000;
}



static void sdram_force_rcomp(void)
{
	u32 reg32;

#if 0
	reg32 = MCHBAR32(ODTC);
	reg32 |= (1 << 28);
	MCHBAR32(ODTC) = reg32;

	reg32 = MCHBAR32(SMSRCTL);
	reg32 |= (1 << 0);
	MCHBAR32(SMSRCTL) = reg32;
#endif
	/* Start initial RCOMP */
	reg32 = MCHBAR32(GBRCOMPCTL);
	reg32 |= (1 << 24);
	MCHBAR32(GBRCOMPCTL) = reg32;
}

void sdram_initialize_system_memory_io(struct sys_info *sysinfo)
{
	u8 reg8;
	u32 reg32;

	printk(BIOS_DEBUG, "Initializing System Memory IO... \n");

	/* Program RCOMP Settings */
	post_code(0x23);
	sdram_program_dram_width(sysinfo);

	sdram_rcomp_buffer_strength_and_slew(sysinfo);

	/* Indicate that RCOMP programming is done */
	reg32 = MCHBAR32(GBRCOMPCTL);
	reg32 &= ~( (1 << 29) | (1 << 26) | (3 << 21) | (3 << 2) );
//	reg32 |= (3 << 27) | (3 << 0);
	MCHBAR32(GBRCOMPCTL) = reg32;
	MCHBAR32(GBRCOMPCTL) |= (1 << 8);

	/* Force RCOMP cycle */
	sdram_force_rcomp();
	
	post_code(0x24);

	reg32 = MCHBAR32(DRTST);
	reg32 |= 0x0c;
	MCHBAR32(DRTST) = reg32;

	sdram_program_receive_enable(sysinfo);


	/* Program DLL Timings */
	sdram_program_dll_timings(sysinfo);

	reg8 = 0xc1; // FIXME
	MCHBAR8(C0HCTC) = reg8;
	MCHBAR8(C1HCTC) = reg8;

	post_code(0x25);

	/* Force RCOMP cycle */
	sdram_force_rcomp();
}



struct clock_crossing  {
	uint32_t dcc_0[6*2];
	uint32_t dcc_1[2*2];
	uint32_t ccc[3*2];
} __attribute__ ((packed));

static const struct clock_crossing crossing_0 = {

/* 4972 .dcc_0 = */
	{
	0x04020110, 0x00000800,
	0x02010010, 0x00000804,
	0x04020110, 0x00000800,
	0x04020108, 0x00000000,
	0x04020108, 0x00000000,
	0x04020108, 0x00000000,
	},
/* 49a2 .dcc_1 = */
	{
	0x04020108, 0x00000000,
	0x00020108, 0x00000000,
	},
/* 49b2 .ccc = */
	{
	0x04020120, 0x00000018,
	0x04020108, 0x00000000,
	0x02010400, 0x00000000,
	}
};

static const struct clock_crossing crossing_1 = {
/* 49ca .dcc_0 = */
	{
	0x04020110, 0x00000000,		/* 1 */
	0x08040110, 0x00000000,		/* 2 */
	0x04020110, 0x00000000,		/* 3 */
	0x10080201, 0x00000000,
	0x10040220, 0x00000000,
	0x10080201, 0x00000000,
	},
/* 49fa .dcc_1 = */
	{
	0x10040220, 0x00000000,		/* 2 */
	0x00100401, 0x00000000,		/* 3 */
	},
/* 4a0a .ccc = */
	{
	0x02000108, 0x00000004,		/* 1 */
	0x02010008, 0x00000400,		/* 2 */
	0x01000400, 0x00000200,		/* 3 */
	}
};

void sdram_program_clock_crossing(void)
{
	const struct clock_crossing * crossing = &crossing_0;
	const u32 *dccft, *cccft;
	/**
	 * We add the indices according to our clocks from CLKCFG.
	 */

	printk(BIOS_DEBUG, "Programming Clock Crossing...");

	MCHBAR8(CLKRST) |= 0x04;

#if 0
	FIXME!
	i = !! (ebp & 0x4)
	j = (MCHBAR32(CLKCFG) >> 4 & 7) - 1;
	k = (ebp >> 8) & 0x03;
#else
	u8 j = 2;
	u8 i = 0;
#endif

	cccft = &crossing->ccc[2*j];
	if ( i ) {
		u8 k = 0;
		dccft = &crossing->dcc_0[2*(j+k)];
	} else {
		dccft = &crossing->dcc_1[2*(j-1)];
	}

	MCHBAR32(CCCFT + 0) = cccft[0];
	MCHBAR32(CCCFT + 4) = cccft[1];
	MCHBAR32(C0DCCFT + 0) = dccft[0];
	MCHBAR32(C0DCCFT + 4) = dccft[1];
	MCHBAR32(C1DCCFT + 0) = dccft[0];
	MCHBAR32(C1DCCFT + 4) = dccft[1];

	MCHBAR8(CLKRST) |= 0x02;
	while (MCHBAR8(CLKRST) & 0x02) { };
	MCHBAR8(CLKRST) &= ~0x04;

	printk(BIOS_DEBUG, "... ok\n");
}


#if 0
static const uint8_t cas_delay[] = {
/* 4ab9 */
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x00,
	0x00, 0x01, 0x01, 0x01,
 	0x00, 0x00, 0x01, 0x00,
};
#endif

/**
 * @brief Enable On-Die Termination for DDR2.
 *
 */

void sdram_on_die_termination(struct sys_info *sysinfo)
{
	u32 reg32;
	int casi = sysinfo->cas - 3;

	MCHBAR32(C0ODT) |= 0x55;
	MCHBAR32(C1ODT) |= 0x55;

	if (0) {   /* FIXME */
#if 0
		MCHBAR32(C0ODT + 4) |= 0x2020 << 16;
		MCHBAR32(C1ODT + 4) |= 0x2020 << 16;

		switch (  ) {
		case 2:
			dth = 0;
			break;
		case 1:
			dth = 1;
			break;
		case 0:
		default:
			dth = 2;
			break;
		}

		reg32 = MCHBAR32(C0ODT + 4);
		reg32 &= ~(3 << 16);
		reg32 |= dth << 16;
		MCHBAR32(C0ODT + 4) = reg32;

		reg32 = MCHBAR32(C1ODT + 4)
		reg32 &= ~(3 << 16);
		reg32 |= dth << 16;
		MCHBAR32(C1ODT + 4) = reg32;

		reg32 = MCHBAR32(ODTC);
		reg32 &= ~(0xf << 16);
		MCHBAR32(ODTC) = reg32;

		if ((ebp >> 13) & 0x7 == 0x1)
			reg32 |= (8 << 16);
		else
			reg32 |= (2 << 16);
		MCHBAR32(ODTC) = reg32;
#endif
	} else {

		uint32_t ebp = 0;
		uint32_t dth, dtl;

		MCHBAR32(C0ODT + 4) |= 0xe020 << 16;
		MCHBAR32(C1ODT + 4) |= 0xe020 << 16;

		switch ( 1 /* (ebp >> 8) & 0x3 */ ) {
		case 2:
			dtl = 0x50;
			dth = 0;
			break;
		case 1:
			dtl = 0xa5;
			dth = 1;
			break;
		case 0:
		default:
			dtl = 0xfa;
			dth = 2;
			break;
		}

		if ( 1 /*((ebp >> 13) & 0x7) == 0x3*/)
			dtl |= 0x200;
		else
			dtl |= 0x100;

		reg32 = MCHBAR32(C0ODT);
		reg32 |= 1<<20;
		reg32 &= ~(0xff << 8);		/* FIXME: use 0x3ff here ? */
		reg32 |= dtl << 8;
		MCHBAR32(C0ODT) = reg32;

		reg32 = MCHBAR32(C1ODT);
		reg32 |= 1<<20;
		reg32 &= ~(0xff << 8);		/* FIXME: use 0x3ff here ? */
		reg32 |= dtl << 8;
		MCHBAR32(C1ODT) = reg32;


		reg32 = MCHBAR32(C0ODT + 4);
		reg32 &= ~(3 << 16);
		reg32 |= dth << 16;
		//reg32 |= (2*cas_delay[bl]) << 16;
		MCHBAR32(C0ODT + 4) = reg32;

		reg32 = MCHBAR32(C1ODT + 4);
		reg32 &= ~(3 << 16);
		reg32 |= dth << 16;
		//reg32 |= (2*cas_delay[bh]) << 16;
		MCHBAR32(C1ODT + 4) = reg32;

		if (((ebp >> 16) & 0x03) != 3) {
			MCHBAR32(ODTC) |= 1<<16;
			MCHBAR32(ODTC) |= 0x40;
			reg32 = MCHBAR32(C0ODT);
			reg32 &= ~(7 << 28);
			MCHBAR32(C0ODT) = reg32;
		}

		if (((ebp >> 18) & 0x03) != 3) {
			MCHBAR32(ODTC) |= 4<<12;
			reg32 = MCHBAR32(C1ODT);
			reg32 &= ~(7 << 28);
			MCHBAR32(C1ODT) = reg32;
		}
	}
}



