/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2016 Intel Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef MAINBOARD_GPIO_H
#define MAINBOARD_GPIO_H

#include <soc/gpio.h>

static const struct pad_config gpio_table[] = {
	/** South West Community **/
	/* PCIe WAKE */
	PAD_CFG_NF(GPIO_205, NATIVE, DEEP, NF1), /* PCIE_WLAN_WAKE3_N */
	PAD_NC(GPIO_206, UP_20K), /* PCIE_WAKE1_B */
	PAD_NC(GPIO_207, UP_20K), /* PCIE_WAKE2_B */
	PAD_CFG_NF(GPIO_208, UP_20K, DEEP, NF1), /* PCIE_SSD_WAKE0_N */
	/* eMMC */
	PAD_CFG_NF(GPIO_156, DN_20K, DEEP, NF1), /* EMMC0_CLK */
	PAD_CFG_NF(GPIO_157, UP_20K, DEEP, NF1), /* EMMC0_D0 */
	PAD_CFG_NF(GPIO_158, UP_20K, DEEP, NF1), /* EMMC0_D1 */
	PAD_CFG_NF(GPIO_159, UP_20K, DEEP, NF1), /* EMMC0_D2 */
	PAD_CFG_NF(GPIO_160, UP_20K, DEEP, NF1), /* EMMC0_D3 */
	PAD_CFG_NF(GPIO_161, UP_20K, DEEP, NF1), /* EMMC0_D4 */
	PAD_CFG_NF(GPIO_162, UP_20K, DEEP, NF1), /* EMMC0_D5 */
	PAD_CFG_NF(GPIO_163, UP_20K, DEEP, NF1), /* EMMC0_D6 */
	PAD_CFG_NF(GPIO_164, UP_20K, DEEP, NF1), /* EMMC0_D7 */
	PAD_CFG_NF(GPIO_165, UP_20K, DEEP, NF1), /* EMMC0_CMD */
	PAD_CFG_NF(GPIO_182, DN_20K, DEEP, NF1), /* EMMC_RCLK */
	/* SDIO */
	PAD_NC(GPIO_166, DN_20K), /* SDIO_CLK */
	PAD_CFG_GPI(GPIO_167, NONE, DEEP), /* DB_ID */
	/* Configure SDIO to enable power gating */
	PAD_CFG_NF(GPIO_168, UP_20K, DEEP, NF1), /* SDIO_D1 */
	PAD_NC(GPIO_169, DN_20K), /* SDIO_D2 */
	PAD_NC(GPIO_170, DN_20K), /* SDIO_D3 */
	PAD_NC(GPIO_171, DN_20K), /* SDIO_CMD */
	/* SD CARD */
	PAD_CFG_NF(GPIO_172, UP_20K, DEEP, NF1), /* SDCARD_CLK */
	PAD_CFG_NF(GPIO_173, UP_20K, DEEP, NF1), /* SDCARD_D0 */
	PAD_CFG_NF(GPIO_174, UP_20K, DEEP, NF1), /* SDCARD_D1 */
	PAD_CFG_NF(GPIO_175, UP_20K, DEEP, NF1), /* SDCARD_D2 */
	PAD_CFG_NF(GPIO_176, UP_20K, DEEP, NF1), /* SDCARD_D3 */
	PAD_CFG_NF(GPIO_177, NATIVE, DEEP, NF1), /* SDCARD_CD_B */
	PAD_CFG_NF(GPIO_178, UP_20K, DEEP, NF1), /* SDCARD_CMD */
	PAD_CFG_NF(GPIO_179, NATIVE, DEEP, NF1), /* SDCARD_CLK_FB */
	PAD_CFG_GPO(GPIO_183, 1, DEEP), /* SDCARD_PWR_EN_N */
	PAD_NC(GPIO_186, DN_20K), /* SDCARD_LVL_WP */
	/* SmBus */
	PAD_NC(SMB_ALERTB, UP_20K), /* SMB_ALERTB */
	PAD_NC(SMB_CLK, UP_20K), /* SMB_CLK */
	PAD_NC(SMB_DATA, UP_20K), /* SMB_DATA */
	/* LPC */
	PAD_CFG_NF(LPC_ILB_SERIRQ, NATIVE, DEEP, NF1), /* LPC_SERIRQ */
	PAD_CFG_NF(LPC_CLKOUT0, NONE, DEEP, NF1), /* LPC_CLKOUT0 */
	PAD_NC(LPC_CLKOUT1, NONE), /* LPC_CLKOUT1 */
	PAD_CFG_NF(LPC_AD0, NATIVE, DEEP, NF1), /* LPC_AD0 */
	PAD_CFG_NF(LPC_AD1, NATIVE, DEEP, NF1), /* LPC_AD1 */
	PAD_CFG_NF(LPC_AD2, NATIVE, DEEP, NF1), /* LPC_AD2 */
	PAD_CFG_NF(LPC_AD3, NATIVE, DEEP, NF1), /* LPC_AD3 */
	PAD_CFG_NF(LPC_CLKRUNB, NATIVE, DEEP, NF1), /* LPC_CLKRUN_N */
	PAD_CFG_NF(LPC_FRAMEB, NATIVE, DEEP, NF1), /* LPC_FRAMEB */
	/** end of South West Community **/

	/** West Community **/
	/* I2C lines */
	PAD_CFG_NF(GPIO_124, UP_2K, DEEP, NF1), /* I2C0_SDA for Audio Codec */
	PAD_CFG_NF(GPIO_125, UP_2K, DEEP, NF1), /* I2C0_SCL for Audio Codec */
	PAD_CFG_NF(GPIO_126, NONE, DEEP, NF1), /* LPSS_I2C1_SDA for NFC*/
	PAD_CFG_NF(GPIO_127, NONE, DEEP, NF1), /* LPSS_I2C1_SCL for NFC*/
	PAD_NC(GPIO_128, UP_20K), /* LPSS_I2C2_SDA */
	PAD_NC(GPIO_129, UP_20K), /* LPSS_I2C2_SCL */
	PAD_CFG_NF(GPIO_130, UP_2K, DEEP, NF1), /* I2C3_SDA for Touch Screen */
	PAD_CFG_NF(GPIO_131, UP_2K, DEEP, NF1), /* I2C3_SCL for Touchscreen */
	PAD_CFG_NF(GPIO_132, UP_2K, DEEP, NF1), /* I2C4_SDA for Trackpad */
	PAD_CFG_NF(GPIO_133, UP_2K, DEEP, NF1), /* I2C4_SCL for Trackpad */
	PAD_NC(GPIO_134, UP_20K), /* LPSS_I2C5_SDA */
	PAD_NC(GPIO_135, UP_20K), /* LPSS_I2C5_SCL */
	PAD_NC(GPIO_136, UP_20K), /* LPSS_I2C6_SDA */
	PAD_NC(GPIO_137, UP_20K), /* LPSS_I2C6_SCL */
	PAD_NC(GPIO_138, UP_20K), /* LPSS_I2C7_SDA */
	PAD_NC(GPIO_139, UP_20K), /* LPSS_I2C7_SCL */
	/* I2S lines */
	PAD_CFG_NF(GPIO_146, NATIVE, DEEP, NF2), /* I2S6_BCLK_Codec */
	PAD_CFG_NF(GPIO_147, NATIVE, DEEP, NF2), /* I2S6_SYNC_Codec */
	PAD_CFG_NF(GPIO_148, NATIVE, DEEP, NF2), /* I2S6_SDI_Codec */
	PAD_CFG_NF(GPIO_149, NATIVE, DEEP, NF2), /* I2S6_SDO_Codec */
	/* Misc */
	PAD_CFG_GPO(GPIO_150, 1, DEEP), /* NFC_RESET_N */
	PAD_CFG_GPI(GPIO_151, UP_20K, DEEP), /* RSVD (ISH_BASE_ACCEL_INT_N) */
	PAD_CFG_GPI(GPIO_152, UP_20K, DEEP), /* RSVD (ALS_IRQ_N) */
	PAD_NC(GPIO_153, DN_20K), /* ISH_GPIO_7 */
	PAD_CFG_GPO(GPIO_154, 1, DEEP), /* BT_DISABLE_1P8_N */
	PAD_CFG_GPO(GPIO_155, 1, DEEP), /* RSVD (WIFI_PERST_1P8_N) */
	/* PCIE_CLKREQ */
	PAD_CFG_NF(GPIO_209, UP_20K, DEEP, NF1), /* SSD CLKREQ */
	PAD_NC(GPIO_210, UP_20K), /* PCIE_CLKREQ1_B */
	PAD_NC(GPIO_211, UP_20K), /* PCIE_CLKREQ2_B */
	PAD_CFG_NF(GPIO_212, NATIVE, DEEP, NF1), /* Wifi CLKREQ */
	/* OSC signals */
	PAD_NC(OSC_CLK_OUT_0, DN_20K),
	PAD_NC(OSC_CLK_OUT_1, DN_20K),
	PAD_NC(OSC_CLK_OUT_2, DN_20K),
	PAD_NC(OSC_CLK_OUT_3, DN_20K),
	PAD_NC(OSC_CLK_OUT_4, DN_20K),
	/* PMU */
	PAD_NC(PMU_AC_PRESENT, DN_20K), /* PMU_AC_PRESENT */
	PAD_NC(PMU_BATLOW_B, UP_20K), /* PMU_BATLOW_B */
	PAD_CFG_NF(PMU_PLTRST_B, NONE, DEEP, NF1), /* PMU_PLTRST_N */
	PAD_CFG_NF(PMU_PWRBTN_B, UP_20K, DEEP, NF1), /* PMU_PWRBTN_N */
	PAD_CFG_NF(PMU_RESETBUTTON_B, NONE, DEEP, NF1),	/* PMU_RSTBTN_N */
	PAD_CFG_NF(PMU_SLP_S0_B, NONE, DEEP, NF1), /* PMU_SLP_S0_N */
	PAD_CFG_NF(PMU_SLP_S3_B, NONE, DEEP, NF1), /* PMU_SLP_S3_N */
	PAD_CFG_NF(PMU_SLP_S4_B, NONE, DEEP, NF1), /* PMU_SLP_S4_N */
	PAD_CFG_NF(PMU_SUSCLK, NONE, DEEP, NF1), /* PMU_SUSCLK */
	PAD_NC(PMU_WAKE_B, UP_20K), /* PMU_WAKE_B */
	PAD_CFG_NF(SUS_STAT_B, NONE, DEEP, NF1), /* SUS_STAT_N */
	PAD_CFG_NF(SUSPWRDNACK, NONE, DEEP, NF1), /* SUSPWRDNACK */
	/** end of West Community **/

	/** North West Community */
	/* DDI */
	PAD_NC(GPIO_187, UP_20K), /* HV_DDI0_DDC_SDA */
	PAD_NC(GPIO_188, UP_20K), /* HV_DDI0_DDC_SCL */
	PAD_NC(GPIO_189, UP_20K), /* HV_DDI1_DDC_SDA */
	PAD_NC(GPIO_190, UP_20K), /* HV_DDI1_DDC_SCL */
	/* DBI */
	PAD_NC(GPIO_191, UP_20K), /* DBI_SDA */
	PAD_NC(GPIO_192, UP_20K), /* DBI_SCL */
	/* Panel 0 */
	PAD_CFG_NF(GPIO_193, NATIVE, DEEP, NF1), /* PANEL0_VDDEN */
	PAD_CFG_NF(GPIO_194, NATIVE, DEEP, NF1), /* PANEL0_BKLTEN */
	PAD_CFG_NF(GPIO_195, NATIVE, DEEP, NF1), /* PANEL0_BKLTCTL */
	/* Panel 1 */
	PAD_NC(GPIO_196, DN_20K), /* PANEL1_VDDEN */
	PAD_NC(GPIO_197, DN_20K), /* PANEL1_BKLTEN */
	PAD_NC(GPIO_198, DN_20K), /* PANEL1_BKLTCTL */
	/* Hot Plug Detect */
	PAD_CFG_NF(GPIO_199, UP_20K, DEEP, NF2), /* DDI0_HPD */
	PAD_CFG_NF(GPIO_200, UP_20K, DEEP, NF2), /* DDI1_HPD */
	/* GP_INTD_DSI */
	PAD_NC(GPIO_201, DN_20K), /* GP_INTD_DSI_TE1 */
	PAD_NC(GPIO_202, DN_20K), /* GP_INTD_DSI_TE2 */
	/* USB OC */
	PAD_CFG_NF(GPIO_203, NATIVE, DEEP, NF1), /* USB2_OC0_3p3_N */
	PAD_CFG_NF(GPIO_204, NATIVE, DEEP, NF1), /* USB2_OC2_N */
	/* SPI */
	PAD_NC(PMC_SPI_FS0, UP_20K), /* PMC_SPI_FS0 */
	PAD_CFG_NF(PMC_SPI_FS1, NATIVE, DEEP, NF2), /* HV_DDI2_HPD */
	PAD_NC(PMC_SPI_FS2, UP_20K), /* PMC_SPI_FS2 */
	PAD_NC(PMC_SPI_RXD, DN_20K), /* PMC_SPI_RXD */
	PAD_NC(PMC_SPI_TXD, DN_20K), /* PMC_SPI_TXD */
	PAD_NC(PMC_SPI_CLK, DN_20K), /* PMC_SPI_CLK */
	/* PMIC */
	PAD_NC(PMIC_PWRGOOD, NONE), /* PMIC_PWRGOOD */
	PAD_NC(PMIC_RESET_B, NONE), /* PMIC_RESET_B */
	PAD_NC(GPIO_213, NONE), /* PMIC_SDWN_B */
	PAD_NC(GPIO_214, DN_20K), /* PMIC_BCUDISW2 */
	PAD_NC(GPIO_215, DN_20K), /* PMIC_BCUDISCRIT */
	PAD_CFG_NF(PMIC_THERMTRIP_B, UP_20K, DEEP, NF1), /* PMIC_THERMTRIP_B */
	PAD_NC(PMIC_STDBY, DN_20K), /* PMIC_STDBY */
	PAD_CFG_NF(PROCHOT_B, UP_20K, DEEP, NF1), /* PROCHOT_N */
	PAD_CFG_NF(PMIC_I2C_SCL, UP_1K, DEEP, NF1), /* PMIC_I2C_SCL */
	PAD_CFG_NF(PMIC_I2C_SDA, UP_1K, DEEP, NF1), /* PMIC_I2C_SDA */
	/* I2S1 */
	PAD_NC(GPIO_74, DN_20K), /* I2S1_MCLK */
	PAD_CFG_GPI(GPIO_75, UP_20K, DEEP), /* SPI_WP_STAT */
	PAD_NC(GPIO_76, DN_20K), /* I2S1_WS_SYNC */
	PAD_NC(GPIO_77, DN_20K), /* I2S1_SDI */
	PAD_NC(GPIO_78, DN_20K), /* I2S1_SDO */
	/* I2S4 or DMIC */
	PAD_CFG_NF(GPIO_79, NATIVE, DEEP, NF1), /* DMIC_CLK_A1 */
	PAD_CFG_NF(GPIO_80, NATIVE, DEEP, NF1), /* DMIC_CLK_B1 */
	PAD_CFG_NF(GPIO_81, NATIVE, DEEP, NF1), /* DMIC_DATA_1 */
	PAD_CFG_NF(GPIO_82, NATIVE, DEEP, NF1), /* DMIC_CLK_AB2 */
	PAD_CFG_NF(GPIO_83, NATIVE, DEEP, NF1), /* DMIC_DATA_2 */
	PAD_CFG_NF(GPIO_84, NATIVE, DEEP, NF1), /* MCLK */
	/* I2S2 or Headset amp */
	PAD_CFG_NF(GPIO_85, NATIVE, DEEP, NF1), /* I2S2_BCLK_AMP */
	PAD_CFG_NF(GPIO_86, NATIVE, DEEP, NF1), /* I2S2_SYNC_AMP */
	PAD_CFG_NF(GPIO_87, NATIVE, DEEP, NF1), /* I2S2_SDI_AMP */
	PAD_CFG_NF(GPIO_88, NATIVE, DEEP, NF1), /* I2S2_SDO_AMP */
	/* I2S3 */
	PAD_NC(GPIO_89, DN_20K), /* I2S3_BCLK */
	PAD_NC(GPIO_90, DN_20K), /* I2S3_WS_SYNC */
	PAD_NC(GPIO_91, DN_20K), /* I2S3_SDI */
	PAD_NC(GPIO_92, DN_20K), /* I2S3_SDO */
	/* Fast SPI */
	PAD_CFG_NF(GPIO_97, NATIVE, DEEP, NF1), /* FST_SPI_CS0_B */
	PAD_NC(GPIO_98, UP_20K), /* FST_SPI_CS1_B */
	PAD_CFG_NF(GPIO_99, NATIVE, DEEP, NF1), /* FST_SPI_MOSI_IO0 */
	PAD_CFG_NF(GPIO_100, NATIVE, DEEP, NF1), /* FST_SPI_MISO_IO1 */
	PAD_NC(GPIO_101, UP_20K), /* FST_IO2 */
	PAD_NC(GPIO_102, UP_20K), /* FST_IO3 */
	PAD_CFG_NF(GPIO_103, NATIVE, DEEP, NF1), /* FST_SPI_CLK */
	PAD_CFG_NF(FST_SPI_CLK_FB, NATIVE, DEEP, NF1), /* FST_SPI_CLK_FB */
	/* GP_SSP_0 / SPI - FP */
	PAD_CFG_NF(GPIO_104, NATIVE, DEEP, NF1), /* SPI for FP */
	PAD_CFG_NF(GPIO_105, NATIVE, DEEP, NF1), /* SPI for FP */
	PAD_CFG_NF(GPIO_106, NATIVE, DEEP, NF3), /* FST_SPI_CS2_B for TPM */
	PAD_CFG_NF(GPIO_109, NATIVE, DEEP, NF1), /* SPI for FP */
	PAD_CFG_NF(GPIO_110, NATIVE, DEEP, NF1), /* SPI for FP */
	/* GP_SSP_1 */
	PAD_NC(GPIO_111, DN_20K), /* GP_SSP_1_CLK */
	PAD_CFG_GPO(GPIO_112, 1, DEEP), /* FP Reset */
	PAD_NC(GPIO_113, DN_20K), /* GP_SSP_1_FS1 */
	PAD_CFG_GPI_APIC(GPIO_116, UP_20K, DEEP, LEVEL, INVERT),
	/* AUDIO_CODEC_IRQ_N */
	PAD_NC(GPIO_117, DN_20K), /* GP_SSP_1_TXD */
	/* GP_SSP_2 */
	PAD_NC(GPIO_118, DN_20K), /* GP_SSP_2_CLK */
	PAD_NC(GPIO_119, DN_20K), /* GP_SSP_2_FS0 */
	PAD_NC(GPIO_120, DN_20K), /* GP_SSP_2_FS1 */
	PAD_NC(GPIO_121, DN_20K), /* GP_SSP_2_FS2 */
	PAD_NC(GPIO_122, DN_20K), /* GP_SSP_2_RXD */
	PAD_NC(GPIO_123, DN_20K), /* GP_SSP_2_TXD */
	/** end of North West Community */
	/** North Community */
	/* MIPI60 debug */
	PAD_CFG_NF(GPIO_0, NATIVE, DEEP, NF1),
	PAD_CFG_NF(GPIO_1, NATIVE, DEEP, NF1),
	PAD_CFG_NF(GPIO_2, NATIVE, DEEP, NF1),
	PAD_CFG_NF(GPIO_3, NATIVE, DEEP, NF1),
	PAD_CFG_NF(GPIO_4, NATIVE, DEEP, NF1),
	PAD_CFG_NF(GPIO_5, NATIVE, DEEP, NF1),
	PAD_CFG_NF(GPIO_6, NATIVE, DEEP, NF1),
	PAD_CFG_NF(GPIO_7, NATIVE, DEEP, NF1),
	PAD_CFG_NF(GPIO_8, NATIVE, DEEP, NF1),
	PAD_CFG_GPI(GPIO_9, UP_20K, DEEP), /* SPI_TPM_IRQ_N  */
	PAD_NC(GPIO_10, DN_20K), /* RSVD for MIPI (unused) */
	PAD_CFG_GPI_SCI(GPIO_11, UP_20K, DEEP, LEVEL, NONE),
	/* SOC_WAKE_SCI_N */
	PAD_NC(GPIO_12, DN_20K),
	PAD_NC(GPIO_13, DN_20K),
	PAD_CFG_GPI_APIC(GPIO_14, UP_20K, DEEP, LEVEL, NONE), /* FP INT */
	PAD_NC(GPIO_15, DN_20K),
	PAD_NC(GPIO_16, UP_20K),
	PAD_NC(GPIO_17, UP_20K),
	PAD_CFG_GPI_APIC(GPIO_18, UP_20K, DEEP, LEVEL, NONE),
	/* Trackpad_INT_N */
	PAD_CFG_GPI_APIC(GPIO_19, UP_20K, DEEP, LEVEL, NONE),
	/* Audio_Jack_Present_N */
	PAD_CFG_GPI_APIC(GPIO_20, UP_20K, DEEP, LEVEL, NONE),
	/* NFC INT */
	PAD_CFG_GPI_APIC(GPIO_21, UP_20K, DEEP, LEVEL, NONE),
	/* TCH_INT_N */
	PAD_CFG_GPI_APIC(GPIO_22, UP_20K, DEEP, LEVEL, NONE),
	/* EC_SOC_WAKE_1P8_N */
	PAD_CFG_GPO(GPIO_23, 1, DEEP), /* GPS_NSTANDBY */
	PAD_CFG_GPO(GPIO_24, 1, DEEP), /* SSD_SATA_DEVSLP */
	PAD_NC(GPIO_25, DN_20K),
	PAD_NC(GPIO_26, DN_20K),
	PAD_CFG_GPO(GPIO_27, 0, DEEP), /* NFC DL REQ */
	PAD_NC(GPIO_28, DN_20K),
	PAD_NC(GPIO_29, DN_20K),
	PAD_CFG_GPI_APIC(GPIO_30, UP_20K, DEEP, LEVEL, NONE),
	/* EC_KBD_IRQ_SOC_N */
	PAD_NC(GPIO_31, DN_20K),
	PAD_CFG_NF(GPIO_32, NATIVE, DEEP, NF5), /* GPS_SUSCLK_32K */
	PAD_CFG_GPI(GPIO_33, UP_20K, DEEP), /* EC_KBD_IRQ_SOC_N */
	PAD_NC(GPIO_34, DN_20K),
	PAD_NC(GPIO_35, DN_20K),
	PAD_CFG_GPO(GPIO_36, 0, DEEP), /* TOUCH_PNL_RST */
	PAD_CFG_NF(GPIO_37, NATIVE, DEEP, NF1), /* SOC_BUZZER */
	PAD_NC(GPIO_38, UP_20K),
	PAD_NC(GPIO_39, UP_20K),
	PAD_NC(GPIO_40, UP_20K),
	PAD_CFG_GPI(GPIO_41, UP_20K, DEEP), /* LPSS_UART0_CTS_B */
	PAD_CFG_NF(GPIO_42, NATIVE, DEEP, NF1), /* GPS_UART_RXD */
	PAD_CFG_NF(GPIO_43, NATIVE, DEEP, NF1), /* GPS_UART_TXD */
	PAD_CFG_NF(GPIO_44, NATIVE, DEEP, NF1), /* GPS_UART_RTS_B */
	PAD_CFG_NF(GPIO_45, NATIVE, DEEP, NF1), /* GPS_UART_CTS_N */
	PAD_CFG_NF(GPIO_46, NATIVE, DEEP, NF1), /* UART2 RX*/
	PAD_CFG_NF(GPIO_47, NATIVE, DEEP, NF1), /* UART2 TX*/
	PAD_NC(GPIO_48, UP_20K),
	PAD_CFG_GPI_SMI(GPIO_49, UP_20K, DEEP, LEVEL, NONE), /* EC_SMI_N */
	/* Camera interface*/
	PAD_NC(GPIO_62, DN_20K), /* GP_CAMERASB00 */
	PAD_NC(GPIO_63, DN_20K), /* GP_CAMERASB01 */
	PAD_NC(GPIO_64, DN_20K), /* GP_CAMERASB02 */
	PAD_NC(GPIO_65, DN_20K), /* GP_CAMERASB03 */
	PAD_NC(GPIO_66, DN_20K), /* GP_CAMERASB04 */
	PAD_NC(GPIO_67, DN_20K), /* GP_CAMERASB05 */
	PAD_NC(GPIO_68, DN_20K), /* GP_CAMERASB06 */
	PAD_NC(GPIO_69, DN_20K), /* GP_CAMERASB07 */
	PAD_NC(GPIO_70, DN_20K), /* GP_CAMERASB08 */
	PAD_NC(GPIO_71, DN_20K), /* GP_CAMERASB09 */
	PAD_NC(GPIO_72, DN_20K), /* GP_CAMERASB10 */
	PAD_NC(GPIO_73, DN_20K), /* GP_CAMERASB11 */
	/** End of North Community */
};

#endif
