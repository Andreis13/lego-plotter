void set_pen(bool set_up) {
  static bool is_up = true;
  if (set_up == is_up) {
    return;
  }

  if (set_up) {
    RotateMotor(M_PEN, 30, 90);
  } else {
    RotateMotor(M_PEN, -30, 90);
  }

  Wait(500);
  Coast(M_PEN);

  is_up = set_up;
}

inline void pen_up() {
  set_pen(true);
}

inline void pen_down() {
  set_pen(false);
}
