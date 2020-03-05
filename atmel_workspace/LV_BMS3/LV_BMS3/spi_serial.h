/*
 * spi_serial.h
 *
 * Created: 2020-03-03 13:33:12
 *  Author: mat15mal
 */ 


#ifndef SPI_SERIAL_H_
#define SPI_SERIAL_H_

#define MD_422HZ_1KHZ 0
#define MD_27KHZ_14KHZ 1
#define MD_7KHZ_3KHZ 2
#define MD_26HZ_2KHZ 3

#define ADC_OPT_ENABLED 1
#define ADC_OPT_DISABLED 0

#define CELL_CH_ALL 0
#define CELL_CH_1and7 1
#define CELL_CH_2and8 2
#define CELL_CH_3and9 3
#define CELL_CH_4and10 4
#define CELL_CH_5and11 5
#define CELL_CH_6and12 6

#define SELFTEST_1 1
#define SELFTEST_2 2

#define AUX_CH_ALL 0
#define AUX_CH_GPIO1 1
#define AUX_CH_GPIO2 2
#define AUX_CH_GPIO3 3
#define AUX_CH_GPIO4 4
#define AUX_CH_GPIO5 5
#define AUX_CH_VREF2 6

#define STAT_CH_ALL 0
#define STAT_CH_SOC 1
#define STAT_CH_ITEMP 2
#define STAT_CH_VREGA 3
#define STAT_CH_VREGD 4

#define REG_ALL 0
#define REG_1 1
#define REG_2 2
#define REG_3 3
#define REG_4 4
#define REG_5 5
#define REG_6 6

#define DCP_DISABLED 0
#define DCP_ENABLED 1

#define PULL_UP_CURRENT 1
#define PULL_DOWN_CURRENT 0

#define NUM_RX_BYT 8
#define CELL 1
#define AUX 2
#define STAT 3
#define CFGR 0
#define CFGRB 4
#define CS_PIN 10

struct io_descriptor *spi_io;

/*! Cell Voltage data structure. */
typedef struct
{
	uint16_t c_codes[18]; //!< Cell Voltage Codes
	uint8_t pec_match[6]; //!< If a PEC error was detected during most recent read cmd
} cv;

/*! AUX Reg Voltage Data structure */
typedef struct
{
	uint16_t a_codes[9]; //!< Aux Voltage Codes
	uint8_t pec_match[4]; //!< If a PEC error was detected during most recent read cmd
} ax;

/*! Status Reg data structure. */
typedef struct
{
	uint16_t stat_codes[4]; //!< Status codes.
	uint8_t flags[3]; //!< Byte array that contains the uv/ov flag data
	uint8_t mux_fail[1]; //!< Mux self test status flag
	uint8_t thsd[1]; //!< Thermal shutdown status
	uint8_t pec_match[2]; //!< If a PEC error was detected during most recent read cmd
} st;

/*! IC register structure. */
typedef struct
{
	uint8_t tx_data[6];  //!< Stores data to be transmitted
	uint8_t rx_data[8];  //!< Stores received data
	uint8_t rx_pec_match; //!< If a PEC error was detected during most recent read cmd
} ic_register;

/*! PEC error counter structure. */
typedef struct
{
	uint16_t pec_count; //!< Overall PEC error count
	uint16_t cfgr_pec;  //!< Configuration register data PEC error count
	uint16_t cell_pec[6]; //!< Cell voltage register data PEC error count
	uint16_t aux_pec[4];  //!< Aux register data PEC error count
	uint16_t stat_pec[2]; //!< Status register data PEC error count
} pec_counter;

/*! Register configuration structure */
typedef struct
{
	uint8_t cell_channels; //!< Number of Cell channels
	uint8_t stat_channels; //!< Number of Stat channels
	uint8_t aux_channels;  //!< Number of Aux channels
	uint8_t num_cv_reg;    //!< Number of Cell voltage register
	uint8_t num_gpio_reg;  //!< Number of Aux register
	uint8_t num_stat_reg;  //!< Number of  Status register
} register_cfg;

/*! Cell variable structure */
typedef struct
{
	ic_register config;
	ic_register configb;
	cv  cells;
	ax  aux;
	st  stat;
	ic_register com;
	ic_register pwm;
	ic_register pwmb;
	ic_register sctrl;
	ic_register sctrlb;
	uint8_t sid[6];
	bool isospi_reverse;
	pec_counter crc_count;
	register_cfg ic_reg;
	long system_open_wire;
} cell_asic;





void SPI_test(void);
void write_68(uint8_t total_ic, //Number of ICs to be written to
uint8_t tx_cmd[2], //The command to be transmitted
uint8_t data[] // Payload Data
);

void LTC681x_adcv( uint8_t MD, //ADC Mode
uint8_t DCP, //Discharge Permit
uint8_t CH //Cell Channels to be measured
);


void spi_init(void);
//The command to be transmitted
 
void cmd_68(uint8_t tx_cmd[2]);

uint16_t pec15_calc(uint8_t len, //Number of bytes that will be used to calculate a PEC
uint8_t *data //Array of data that will be used to calculate  a PEC
);

/* Start ADC Conversion for GPIO and Vref2  */
void LTC681x_adax(uint8_t MD, //ADC Mode
uint8_t CHG //GPIO Channels to be measured
);

/* Start ADC Conversion for Status  */
void LTC681x_adstat(uint8_t MD, //ADC Mode
uint8_t CHST //Stat Channels to be measured
);


/*
The function reads a single GPIO voltage register and stores the read data
in the *data point as a byte array. This function is rarely used outside of
the LTC681x_rdaux() command.
*/
void LTC681x_rdaux_reg(uint8_t reg, //Determines which GPIO voltage register is read back
uint8_t total_ic //The number of ICs in the system
);


//void LTC6810_init_reg_limits(uint8_t total_ic, // Number of ICs in the system
//cell_asic *ic // A two dimensional array that stores the data
//);

#endif /* SPI_SERIAL_H_ */


