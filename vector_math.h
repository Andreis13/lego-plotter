struct Vec2 {
  float x;
  float y;
};

Vec2 vec_sub(Vec2 v1, Vec2 v2) {
  Vec2 v;
  v.x = v1.x - v2.x;
  v.y = v1.y - v2.y;
  return v;
}

Vec2 vec_add(Vec2 v1, Vec2 v2) {
  Vec2 v;
  v.x = v1.x + v2.x;
  v.y = v1.y + v2.y;
  return v;
}

Vec2 vec_mul(Vec2 v, float t) {
  Vec2 mv;
  mv.x = v.x * t;
  mv.y = v.y * t;
  return mv;
}

inline void vec_nullify(Vec2 &v) {
  v.x = 0;
  v.y = 0;
}

inline float vec_length(Vec2 v) {
  return sqrt(v.x*v.x + v.y*v.y);
}

bool vec_is_null(Vec2 v) {
  return (v.x == 0.0 && v.y == 0.0);
}

inline Vec2 vec(float x, float y) {
  Vec2 v;
  v.x = x;
  v.y = y;
  return v;
}
