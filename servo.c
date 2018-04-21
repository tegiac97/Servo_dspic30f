// DSPIC30F6010A Configuration Bit Settings
// 'C' source line config statements
// FOSC
#pragma config FOSFPR = HS              // Oscillator (HS)
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)

// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = BORV20          // Brown Out Voltage (Reserved)
#pragma config BOREN = PBOR_ON          // PBOR Enable (Enabled)
#pragma config LPOL = PWMxL_ACT_HI      // Low-side PWM Output Polarity (Active High)
#pragma config HPOL = PWMxH_ACT_HI      // High-side PWM Output Polarity (Active High)
#pragma config PWMPIN = RST_IOPIN       // PWM Output Pin Reset (Control with PORT/TRIS regs)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Enabled)

// FBS
#pragma config BWRP = WR_PROTECT_BOOT_OFF// Boot Segment Program Memory Write Protect (Boot Segment Program Memory may be written)
#pragma config BSS = NO_BOOT_CODE       // Boot Segment Program Flash Memory Code Protection (No Boot Segment)
#pragma config EBS = NO_BOOT_EEPROM     // Boot Segment Data EEPROM Protection (No Boot EEPROM)
#pragma config RBS = NO_BOOT_RAM        // Boot Segment Data RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WR_PROT_SEC_OFF   // Secure Segment Program Write Protect (Disabled)
#pragma config SSS = NO_SEC_CODE        // Secure Segment Program Flash Memory Code Protection (No Secure Segment)
#pragma config ESS = NO_SEC_EEPROM      // Secure Segment Data EEPROM Protection (No Segment Data EEPROM)
#pragma config RSS = NO_SEC_RAM         // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = GSS_OFF            // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define FCY 2000000UL
//#define MAX 40000
//#define percent 100

#include <xc.h>
#include<libpic30.h>
#include<p30F6010A.h>


void resetServo() {
	T3CONbits.TON = 1;
	TMR3 = 0;
	while (TMR3 <= 1100) _RD0 = 1;
	while (TMR3 > 1100 && TMR3 < 40000) _RD0 = 0;
	T3CONbits.TON = 0;
}



void rotateD(int degree) {
	int i;
	for (i = 0; i < 50; i++) {
		int a = 1100 + (int)(3800 * (float)(180 - degree) / 180);
		T3CONbits.TON = 1;
		TMR3 = 0;
		while (TMR3 <= a) _RD0 = 1;
		while (TMR3 > a && TMR3 < 40000) _RD0 = 0;
		T3CONbits.TON = 0;
	}
}

int main() {
    _TRISD0 = 0;
	T3CON = 0;
	TMR3 = 0;
	//resetServo();
	//__delay_ms(500);
	while (1) {
		rotateD(0);
		rotateD(180);
		//__delay_ms(5000);
		//rotate(90);
		//__delay_ms(5000);
		/*rotateServo(180);
		__delay_ms(1000);
		rotateServo(90);
		__delay_ms(1000);*/

	}

}