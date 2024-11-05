#include <cassert>
#include <cstdint>
class LinearCongruentialGenerator {
private:
  int64_t prev_var;
  const int64_t seed, max;
  const int64_t constant1, constant2;

public:
  LinearCongruentialGenerator(int64_t seed, int64_t max, int64_t constant1, int64_t constant2)
      : seed(seed), max(max), constant1(constant1), constant2(constant2) {
        assert(constant1 % constant2 != 0);
        assert(constant1 % constant2 != 0);
      }

  int64_t GenerateInt() {
    int64_t new_val = (constant1 * prev_var + constant2) % max;
    assert(new_val >= 0);
    prev_var = new_val;
    return new_val;
  }

  double GenerateDouble() {
    int64_t new_val = GenerateInt();
    return double(new_val)/double(max-1);
  }
};