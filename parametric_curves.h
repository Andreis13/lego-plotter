

inline Vec2 parametric_line(Vec2 direction, Vec2 offset, float t) {
  Vec2 v = vec_add(vec_mul(direction, clamp_0_1(t)), offset);
  return v;
}
