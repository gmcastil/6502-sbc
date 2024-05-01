/*
 * Address and data lines are listed LSB to MSB as they would be hooked up on
 * the board (e.g., pin 24 is assumed to be connected to address pin 1 on the
 * 65C02 IC).
 */
const unsigned int ADDR_PINS[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52};
const unsigned int DATA_PINS[] = {39, 41, 43, 45, 47, 49, 51, 53};

/* This needs to be an interrupt capable pin */
#define CLOCK_PIN         2
#define READ_WRITE_PIN    3

void setup()
{
	/* Initialize the serial port */
	Serial.begin(57600);

	/* Set each address pin as an input */
	for (int i=0; i<16; i++) {
		pinMode(ADDR_PINS[i], INPUT);
	}
	
	/* Set each data pin as an input */
	for (int i=0; i<8; i++) {
		pinMode(DATA_PINS[i], INPUT);
	}

	/* Set up read / write pin as in input */
	pinMode(READ_WRITE_PIN, INPUT);

	/* Set up the clock as an interrupt source */
	pinMode(CLOCK_PIN, INPUT);
	attachInterrupt(digitalPinToInterrupt(CLOCK_PIN), clock_isr, RISING);
}

/*
 * Interrupt service routine for rising edge of clock pin
 */
void clock_isr()
{
	static char msg[40];

	static unsigned int addr = 0;
	static unsigned int data = 0;
	static unsigned int read_bit;

	static char rw;

	addr = 0;
	data = 0;

	/* Sample the address lines MSB to LSB */
	for (int i=15; i>=0; i--) {
		read_bit = digitalRead(ADDR_PINS[i]) ? 1 : 0;
		addr = (addr << 1) + read_bit;
	}
	/* Sample the data lines MSB to LSB */
	for (int i=7; i>=0; i--) {
		read_bit = digitalRead(DATA_PINS[i]) ? 1 : 0;
		data = (data << 1) + read_bit;
	}
	/* Sample the RW line (active low) */
	rw = digitalRead(READ_WRITE_PIN) ? 'R' : 'W';
	sprintf(msg, "0x%04x\t0x%02x\t\t%c", addr, data, rw);
	Serial.println(msg);
}

void loop()
{

}
