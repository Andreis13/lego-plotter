

struct Rig
{
  Vec2 position;
  Vec2 prev_position;
  Vec2 power;
  Vec2 error;
  Vec2 prev_error;
  Vec2 integral_error;
};


void rig_update_position(Rig &rig) {
  rig.prev_position = rig.position;
  rig.position.x = MotorRotationCount(M_X);
  rig.position.y = MotorRotationCount(M_Y);
}

void rig_regulate(Rig &rig, Vec2 target_position) {
  rig.prev_error = rig.error;
  rig.error = vec_sub(target_position, rig.position);
  rig.integral_error = vec_add(rig.integral_error, rig.error);

  rig.power.x = Kp * rig.error.x + Ki * rig.integral_error.x + Kd * (rig.error.x - rig.prev_error.x);
  rig.power.y = Kp * rig.error.y + Ki * rig.integral_error.y + Kd * (rig.error.y - rig.prev_error.y);
}

bool rig_is_stationary(Rig &rig) {
  return (vec_is_null(rig.error) && vec_is_null(rig.power));
}

void initialize_rig(Rig &rig) {
  vec_nullify(rig.position);
  rig.prev_position = vec(0, 0);

  rig_update_position(rig);
  rig.prev_position = rig.position;

  vec_nullify(rig.power);
  vec_nullify(rig.error);
  vec_nullify(rig.integral_error);
  vec_nullify(rig.prev_error);
}

void rig_move_to(Rig &rig, Vec2 target_position) {
  Vec2 direction = vec_sub(target_position, rig.position);
  Vec2 offset = rig.position;
  float distance = vec_length(direction);
  float velocity = 0.4; // degrees/ms
  float total_time = distance / velocity; // ms

  float t;
  float start_time = CurrentTick();
  Vec2 p;
  while(true) {
    float current_time = CurrentTick();
    t = (current_time - start_time) / total_time;
    rig_update_position(rig);
    rig_regulate(rig, parametric_line(direction, offset, t));

    ClearScreen();
    NumOut(0, LCD_LINE1, t);
    NumOut(0, LCD_LINE2, rig.power.x);
    NumOut(0, LCD_LINE3, rig.power.y);
    NumOut(0, LCD_LINE4, rig.position.x);
    NumOut(0, LCD_LINE5, rig.position.y);

    OnFwd(M_X, clamp_power(rig.power.x));
    OnFwd(M_Y, clamp_power(rig.power.y));

    if (rig_is_stationary(rig) && t >= 1.0)
    {
      break;
    }

    Wait(REG_TIME);
  }

}
