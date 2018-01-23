#include <synth/generator.h>

int Sequential::next()
{
  return state_++;
}

void Sequential::reset()
{
  state_ = 0;
}

int Zero::next()
{
  return 0;
}
