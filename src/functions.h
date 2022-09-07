// variables for looping frequency
long last_loop_time = 0;
long duration;
long freq;


void Calc_Loop_Speed() {
  duration = currenttime - last_loop_time;
  freq = (double)1000000.0/(double)duration;

  // Serial.print("Loop Duration:  ");
  // Serial.print(duration); 
  // Serial.print("\tLoop Frequency:  ");
  // Serial.println(freq);
  last_loop_time = currenttime;
}