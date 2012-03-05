#include <bootblock_common.h>
#include <bootstrap_dcd.h>

static void main(unsigned long bist)
{
	unsigned long entry = 0;
	uint8_t normal = 0;

	if (boot_cpu()) {
		bootblock_mainboard_init();

#if CONFIG_USE_OPTION_TABLE
		sanitize_cmos();
#endif
#if CONFIG_CMOS_POST
		cmos_post_init();
#endif
	}

#if CONFIG_TTYS0_DCD_HOOK
	/* DCD high selects normal */
	normal = early_dcd_hook();
#endif

	if (normal)
		entry = findstage("normal/romstage");
	else
		entry = findstage("fallback/romstage");

	if (entry) call(entry, bist);
	asm volatile ("1:\n\thlt\n\tjmp 1b\n\t");
}

