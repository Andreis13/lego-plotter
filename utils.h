inline void calibrate(byte motor, bool high_end) {
  long r1 = 0;
  long r2 = 0;

  if (high_end) {
    OnFwd(motor, 40);
  } else {
    OnRev(motor, 40);
  }

  do {
    r1 = r2;
    Wait(50);
    r2 = MotorRotationCount(motor);
    ClearScreen();
    NumOut(50, LCD_LINE1, r2);
  } until(r1 == r2);

  Off(motor);
  Wait(500);
  Coast(motor);
}

float clamp_0_1(float t) {
  if (t < 0.0)
  {
    return 0.0;
  } else if (t > 1.0)
  {
    return 1.0;
  } else {
    return t;
  }
}

long clamp_power(float power) {
  if (power > MAX_POWER) {
    return MAX_POWER;
  } else if (power < -MAX_POWER) {
    return -MAX_POWER;
  }
  return power;
}

void wait_iteration_time(float iteration_start) {
  float iteration_end = iteration_start + ITERATION_TIME;
  Wait(5);
  while(true) {
    if (iteration_end <= CurrentTick()) {
      break;
    }
  }
}
