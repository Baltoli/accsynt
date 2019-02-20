#pragma once
 
#include <limits>
#include <memory>

namespace support {

class argument_generator {
public:
  template <typename T>
  argument_generator(T&& strat) :
    strategy_(std::make_unique<model<T>>(strat))
  {
  }

  // Interface
  int gen_int(int min = std::numeric_limits<int>::min(),
              int max = std::numeric_limits<int>::max())
  {
    return strategy_->gen_int(min, max);
  }

  float gen_float(float min = std::numeric_limits<float>::min(),
                  float max = std::numeric_limits<float>::max())
  {
    return strategy_->gen_float(min, max);
  }

  // Type erasure
  struct concept {
    virtual ~concept() {}
    virtual int gen_int(int min, int max) = 0;
    virtual float gen_float(float min, float max) = 0;
  };

  template <typename T>
  struct model : concept {
    model(T& obj) :
      object_(obj)
    {
    }

    int gen_int(int min, int max) override
    {
      return object_.gen_int(min, max);
    }

    float gen_float(float min, float max) override
    {
      return object_.gen_float(min, max);
    }

  private:
    T& object_;
  };

private:
  std::unique_ptr<concept> strategy_;
};

}
