#include "type.h"
#include "main.h"

#define PCM9211_ADDR	0x86    //0x80, 0x82, 0x84, 0x86
#define PCM9211_WRITE	0x01
#define PCM9211_READ	0x00

/* Register definitions */
#define PCM9211_ERR_OUT					0x20	//ERROR Output Condition and Shared Port Settings
#define PCM9211_DIR_INITIAL1			0x21	//DIR Initial Settings 1/3
#define PCM9211_DIR_INITIAL2			0x22	//DIR Initial Settings 2/3
#define PCM9211_DIR_INITIAL3			0x23	//DIR Initial Settings 3/3
#define PCM9211_OSC_CTRL				0x24	//Oscillation Circuit Control
#define PCM9211_ERR_CAUSE				0x25	//ERROR Cause Setting
#define PCM9211_AUTO_SEL_CAUSE			0x26	//AUTO Source Selector Cause Setting
#define PCM9211_DIR_FS_RANGE			0x27	//DIR Acceptable fS Range Setting and Mask
#define PCM9211_NON_PCM_DEF				0x28	//Non-PCM Definition Setting
#define PCM9211_DTS_CD_LD				0x29	//DTS CD/LD Detection Setting
#define PCM9211_INT0_CAUSE				0x2A	//INT0 Output Cause Mask Setting
#define PCM9211_INT1_CAUSE				0x2B	//INT1 Output Cause Mask Setting
#define PCM9211_INT0_OUT				0x2C	//INT0 Output Register
#define PCM9211_INT1_OUT				0x2D	//INT1 Output Register
#define PCM9211_INT_POLARITY			0x2E	//INT0, INT1 Output Polarity Setting
#define PCM9211_DIR_OUT_FMT				0x2F	//DIR Output Data Format
#define PCM9211_DIR_RSCLK_RATIO			0x30	//DIR Recovered System Clock Ratio Setting
#define PCM9211_XTI_SCLK_FREQ			0x31	//XTI Source Clock Frequency Setting
#define PCM9211_DIR_SOURCE_BIT2			0x32	//DIR Source, Sec. Bit/LR Clock Frequency Setting
#define PCM9211_XTI_SOURCE_BIT2			0x33	//XTI Source, Sec. Bit/LR Clock Frequency Setting
#define PCM9211_DIR_INP_BIPHASE			0x34	//DIR Input Biphase Source Select, Coax Amp. Control
#define PCM9211_RECOUT0_BIPHASE			0x35	//RECOUT0 Output Biphase Source Select
#define PCM9211_RECOUT1_BIPHASE			0x36	//RECOUT1 Output Biphase Source Select
#define PCM9211_FS_CALC_TARGET			0x37	//Port fS Calculator Measurement Target Setting
#define PCM9211_FS_CALC_RESULT			0x38	//Port fS Calculator Result Output
#define PCM9211_BIPHASE_INFO			0x39	//Incoming Biphase Information and Calculated fS Output
#define PCM9211_PC_BUF0					0x3A	//PC Buffer Byte0 (Burst Preamble PC Output Register)
#define PCM9211_PC_BUF1					0x3B	//PC Buffer Byte1 (Burst Preamble PC Output Register)
#define PCM9211_PD_BUF0					0x3C	//PD Buffer Byte0 (Burst Preamble PD Output Register)
#define PCM9211_PD_BUF1					0x3D	//PD Buffer Byte1 (Burst Preamble PD Output Register)

#define PCM9211_SYS_RESET				0x40	//System Reset Control

#define PCM9211_ADC_CTRL1				0x42	//ADC Function Control 1/3

#define PCM9211_ADC_L_CH_ATT			0x46	//ADC L-ch, digital ATT control
#define PCM9211_ADC_R_CH_ATT			0x47	//ADC R-ch, digital ATT control
#define PCM9211_ADC_CTRL2				0x48	//ADC Function Control 2/3
#define PCM9211_ADC_CTRL3				0x49	//ADC Function Control 3/3

#define PCM9211_DIR_STATUS1				0x5A	//DIR Channel Status Data Buffer 1/6
#define PCM9211_DIR_STATUS2				0x5B	//DIR Channel Status Data Buffer 2/6
#define PCM9211_DIR_STATUS3				0x5C	//DIR Channel Status Data Buffer 3/6
#define PCM9211_DIR_STATUS4				0x5D	//DIR Channel Status Data Buffer 4/6
#define PCM9211_DIR_STATUS5				0x5E	//DIR Channel Status Data Buffer 5/6
#define PCM9211_DIR_STATUS6				0x5F	//DIR Channel Status Data Buffer 6/6
#define PCM9211_DIT_CTRL1				0x60	//DIT Function Control 1/3
#define PCM9211_DIT_CTRL2				0x61	//DIT Function Control 2/3
#define PCM9211_DIT_CTRL3				0x62	//DIT Function Control 3/3
#define PCM9211_DIT_STATUS1				0x63	//DIT Channel Status Data Buffer 1/6
#define PCM9211_DIT_STATUS2				0x64	//DIT Channel Status Data Buffer 2/6
#define PCM9211_DIT_STATUS3				0x65	//DIT Channel Status Data Buffer 3/6
#define PCM9211_DIT_STATUS4				0x66	//DIT Channel Status Data Buffer 4/6
#define PCM9211_DIT_STATUS5				0x67	//DIT Channel Status Data Buffer 5/6
#define PCM9211_DIT_STATUS6				0x68	//DIT Channel Status Data Buffer 6/6

#define PCM9211_MAIN_AUX_MUTE			0x6A	//Main Output and AUXOUT Port Data Mute Control
#define PCM9211_MAIN_OUT_SOURCE			0x6B	//Main Output Port, Output Source Setting
#define PCM9211_AUX_OUT_SOURCE			0x6C	//AUX Output Port, Output Source Setting
#define PCM9211_MPIO_B_MAIN_HIZ			0x6D	//MPIO_B & Main Output Port Hi-Z Control
#define PCM9211_MPIO_C_MPIO_A_HIZ		0x6E	//MPIO_C and MPIO_A Hi-Z Control
#define PCM9211_MPIO_GROUP				0x6F	//MPIO_A, MPIO_B, MPIO_C Group Function Assign
#define PCM9211_MPIO_A_FLAGS			0x70	//MPIO_A, Flags/GPIO Assign Setting
#define PCM9211_MPIO_B_MPIO_C_FLAGS		0x71	//MPIO_B, MPIO_C, Flags/GPIO Assign Setting
#define PCM9211_MPIO_A1_A0_OUT_FLAG		0x72	//MPIO_A1, MPIO_A0 Output Flag Select
#define PCM9211_MPIO_A3_A2_OUT_FLAG		0x73	//MPIO_A3, MPIO_A2 Output Flag Select
#define PCM9211_MPIO_B1_B0_OUT_FLAG		0x74	//MPIO_B1, MPIO_B0 Output Flag Select
#define PCM9211_MPIO_B3_B2_OUT_FLAG		0x75	//MPIO_B3, MPIO_B2 Output Flag Select
#define PCM9211_MPIO_C1_C0_OUT_FLAG		0x76	//MPIO_C1, MPIO_C0 Output Flag Select
#define PCM9211_MPIO_C3_C2_OUT_FLAG		0x77	//MPIO_C3, MPIO_C2 Output Flag Select
#define PCM9211_MPO_1_0_FUNC			0x78	//MPO1, MPO0 Function Assign Setting
#define PCM9211_MPIO_A_B_DIR			0x79	//GPIO I/O Direction control for MPIO_A, MPIO_B
#define PCM9211_MPIO_C_DIR				0x7A	//GPIO I/O Direction control for MPIO_C
#define PCM9211_MPIO_A_B_DATA_OUT		0x7B	//GPIO Output Data Setting for MPIO_A, MPIO_B
#define PCM9211_MPIO_C_DATA_OUT			0x7C	//GPIO Output Data Setting for MPIO_C
#define PCM9211_MPIO_A_B_DATA_IN		0x7D	//GPIO Input Data Register for MPIO_A, MPIO_B
#define PCM9211_MPIO_C_DATA_IN			0x7E	//GPIO Input Data Register for MPIO_C


/* Register field values (only used ones) */
/* PCM9211_ERR_OUT */
#define PCM9211_ERROR_INT0_MASK		BIT(2)
#define PCM9211_NPCM_INT1_MASK		BIT(0)

/* PCM9211_NON_PCM_DEF */
#define PCM9211_NON_PCM_DTS_CD_DET_MASK	BIT(2)

/* PCM9211_INT0_CAUSE */
#define PCM9211_INT0_MNPCM0_MASK	BIT(6)
#define PCM9211_INT0_MDTSCD0_MASK	BIT(4)
#define PCM9211_INT0_MPCRNW0_MASK	BIT(2)
#define PCM9211_INT0_MFSCHG0_MASK	BIT(1)

/* PCM9211_INT_POLARITY	*/
#define PCM9211_INT0_POLARITY_POS_MASK	BIT(2)

/* PCM9211_DIR_OUT_FMT */
#define PCM9211_DIR_FMT_MASK		0x7
#define PCM9211_DIR_FMT_SHIFT		0

#define PCM9211_DIR_FMT_I2S			4
#define PCM9211_DIR_FMT_LEFT_J		5
#define PCM9211_DIR_FMT_RIGHT_J		0

/* PCM9211_XTI_SCLK_FREQ */
#define PCM9211_XTI_XSCK_SHIFT		4
#define PCM9211_XTI_XSCK_MASK		(0x3 << PCM9211_XTI_XSCK_SHIFT)
#define PCM9211_XTI_BCK_SHIFT		2
#define PCM9211_XTI_BCK_MASK		(0x3 << PCM9211_XTI_BCK_SHIFT)
#define PCM9211_XTI_LRCK_SHIFT		0
#define PCM9211_XTI_LRCK_MASK		(0x3 << PCM9211_XTI_LRCK_SHIFT)


/* PCM9211_BIPHASE_INFO */
#define PCM9211_BIPHASE_SFSST_SHIFT	7
#define PCM9211_BIPHASE_SFSST_MASK	BIT(PCM9211_BIPHASE_SFSST_SHIFT)
#define PCM9211_BIPHASE_SFSOUT_SHIFT	0
#define PCM9211_BIPHASE_SFSOUT_MASK	(0xf << PCM9211_BIPHASE_SFSOUT_SHIFT)


/* PCM9211_SYS_RESET */
#define PCM9211_SYS_RESET_MRST		BIT(7)
#define PCM9211_SYS_RESET_RXDIS_SHIFT	4
#define PCM9211_SYS_RESET_ADDIS_SHIFT	5


/* PCM9211_ADC_CTRL2 */
#define PCM9211_ADFMT_MASK		0x3
#define PCM9211_ADFMT_SHIFT		0

#define PCM9211_ADFMT_I2S		0
#define PCM9211_ADFMT_LEFT_J		1
#define PCM9211_ADFMT_RIGHT_J		2


/* PCM9211_MAIN_OUT_SOURCE */
#define PCM9211_MOSSRC_SHIFT		4
#define PCM9211_MOPSRC_SHIFT		0
#define PCM9211_MOSRC_MASK		0x7
#define PCM9211_MOSSRC_MASK		\
	(PCM9211_MOSRC_MASK << PCM9211_MOSSRC_SHIFT)
#define PCM9211_MOPSRC_MASK		\
	(PCM9211_MOSRC_MASK << PCM9211_MOPSRC_SHIFT)

#define PCM9211_MOSRC_AUTO		0
#define PCM9211_MOSRC_DIR		1
#define PCM9211_MOSRC_ADC		2
#define PCM9211_MOSRC_AUXIN0		3
#define PCM9211_MOSRC_AUXIN1		4
#define PCM9211_MOSRC_AUXIN2		5


/* PCM9211_MPIO_GROUP */
#define PCM9211_MPASEL_SHIFT		6
#define PCM9211_MPASEL_MASK		(0x2 << PCM9211_MPASEL_SHIFT)
#define PCM9211_MPBSEL_SHIFT		3
#define PCM9211_MPBSEL_MASK		(0x7 << PCM9211_MPBSEL_SHIFT)
#define PCM9211_MPCSEL_SHIFT		0
#define PCM9211_MPCSEL_MASK		(0x7 << PCM9211_MPCSEL_SHIFT)


/* PCM9211_MPIO_A_FLAGS */
#define PCM9211_MPAxSEL_SHIFT(x)	(x)
#define PCM9211_MPAxSEL_MASK(x)		BIT(PCM9211_MPAxSEL_SHIFT(x))


/* PCM9211_MPIO_B_MPIO_C_FLAGS */
#define PCM9211_MPBxSEL_SHIFT(x)	((x) + 4)
#define PCM9211_MPBxSEL_MASK(x)		BIT(PCM9211_MPBxSEL_SHIFT(x))
#define PCM9211_MPCxSEL_SHIFT(x)	(x)
#define PCM9211_MPCxSEL_MASK(x)		BIT(PCM9211_MPCxSEL_SHIFT(x))


/* PCM9211_MPIO_A1_A0_OUT_FLAG..PCM9211_MPIO_C3_C2_OUT_FLAG */
#define PCM9211_MPIO_ABCx_FLAG_SHIFT(x)	(((x) % 2) * 4)
#define PCM9211_MPIO_ABCx_FLAG_MASK(x)	(0xf << PCM9211_MPIO_ABCx_FLAG_SHIFT(x))

/* PCM9211_MPO_1_0_FUNC */
#define PCM9211_MPOxOUT_SHIFT(x)	((x) * 4)
#define PCM9211_MPOxOUT_MASK(x)		(0xf << PCM9211_MPOxOUT_SHIFT(x))


/* Data Binding Register */
/* INT0/ERROR select */
#define PCM9211_ERROR_INT0_ERROR						0
#define PCM9211_ERROR_INT0_INT0							1

/* INT1/NPCM select */
#define PCM9211_NPCM_INT1_NPCM							0
#define PCM9211_NPCM_INT1_INT1							1

/* MPIO group functions */
#define PCM9211_MPIO_A_GROUP_BIPHASE_INPUT				0
#define PCM9211_MPIO_A_GROUP_CLKST_VOUT_XMCK_INT0		1
#define PCM9211_MPIO_A_GROUP_SEC_BCK_LRCK_XMCKO_INT0	2
#define PCM9211_MPIO_A_GROUP_DIR_FLAGS_GPIO				3

#define PCM9211_MPIO_B_GROUP_AUXIN2						0
#define PCM9211_MPIO_B_GROUP_AUXOUT						1
#define PCM9211_MPIO_B_GROUP_SAMPLING_FREQ_RES			2
#define PCM9211_MPIO_B_GROUP_DIR_FLAGS_GPIO				3
#define PCM9211_MPIO_B_GROUP_DIR_BCUV_BFRAME_VUC		4
#define PCM9211_MPIO_B_GROUP_EXT_ADC_IN					5
#define PCM9211_MPIO_B_GROUP_TEST_MODE					7

#define PCM9211_MPIO_C_GROUP_AUXIN1						0
#define PCM9211_MPIO_C_GROUP_ADC_CLOCK_DATA				1
#define PCM9211_MPIO_C_GROUP_SAMPLING_FREQ_RES			2
#define PCM9211_MPIO_C_GROUP_DIR_FLAGS_GPIO				3
#define PCM9211_MPIO_C_GROUP_DIR_BCUV_BFRAME_VUC		4
#define PCM9211_MPIO_C_GROUP_DIT_CLOCK_DATA				5

/* MPIO flags/gpio select */
#define PCM9211_MPIO_DIR_FLAGS							0
#define PCM9211_MPIO_GPIO								1

/* MPIO flags */
#define PCM9211_MPIO_FLAG_CLKST							0
#define PCM9211_MPIO_FLAG_EMPH							1
#define PCM9211_MPIO_FLAG_BPSYNC						2
#define PCM9211_MPIO_FLAG_DTSCD							3
#define PCM9211_MPIO_FLAG_PARITY						4
#define PCM9211_MPIO_FLAG_LOCK							5
#define PCM9211_MPIO_FLAG_VOUT							6
#define PCM9211_MPIO_FLAG_UOUT							7
#define PCM9211_MPIO_FLAG_COUT							8
#define PCM9211_MPIO_FLAG_BFRAME						9
#define PCM9211_MPIO_FLAG_FSOUT0						10
#define PCM9211_MPIO_FLAG_FSOUT1						11
#define PCM9211_MPIO_FLAG_FSOUT2						12
#define PCM9211_MPIO_FLAG_FSOUT3						13
#define PCM9211_MPIO_FLAG_INT0							14
#define PCM9211_MPIO_FLAG_INT1							15



void pcm9211_init(void);
void pcm9211_mainOutput(void);
void pcm9211_unMute_outPort(void);

