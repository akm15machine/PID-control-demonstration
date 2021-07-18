//IO Pins
#define IN A0
#define OP 11

uint16_t setPoint = 128; //0 to 255
double measuredVoltage;

//timing variables
unsigned long lastMeasureTime;
unsigned long lastPoll;

//PID variables
double e;
double derivative;
double integral;

//PID constants
const double Kp = 0.006;
const double Ki = 0.05;
const double Kd = 0.00001;

double e_prev;

//function to compute PID
bool operation_PID (int interval)
{
  e = (double)setPoint - (double)measuredVoltage;
  unsigned long dt = micros() - lastMeasureTime;
  bool logic = (dt >= interval);
  if(logic)
  {
    derivative = (((double)e-(double)e_prev)*1000000/(double)dt);
    integral += e*(double)dt/1000000;
    e_prev = e;
    lastMeasureTime = micros();
  }
  return logic;
}

//modified map function for double datatype
double map_d(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
  //Serial Monitor at 115200 BAUD
  Serial.begin(115200);
  //setup IO
  pinMode(IN, INPUT);
  pinMode(OP, OUTPUT);
}

void loop() {
  //ADC is 10 bit, PWM is 8-bit, so mapping from 10-bit to 8-bit
  measuredVoltage = map_d(analogRead(IN), 0, 1023, 0, 255.0);

  
  if(operation_PID (700))//measure the error every 700us
  {
    int pid = Kp*e + Ki*integral + Kd*derivative;
    digitalWrite(OP, (pid >= 0) );
    //(pid >= 0) gives a boolean value, used to enable charging
  }

  //debug scheduler (every 100ms)
  if(millis() - lastPoll >= 100)
  {
    double calculateVoltage = map_d(measuredVoltage, 0, 255, 0.0, 5.0);
    Serial.println(measuredVoltage);
    lastPoll = millis();
  }
}
