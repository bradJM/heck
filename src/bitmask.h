// Credit: https://thatgamesguy.co.uk/cpp-game-dev-4/
#ifndef HECK_BITMASK_H
#define HECK_BITMASK_H

#include <cstdint>

namespace nsd {
class Bitmask {
public:
  // Overwrites this bitmask.
  void setMask(Bitmask &other);

  // Returns binary representation of bitmask.
  std::uint32_t getMask() const;

  // Returns true if bit at pos = 1, else false.
  bool getBit(int pos) const;

  // Sets bit at specified pos to 1 or 0 (true or false).
  void setBit(int pos, bool on);

  // Sets bit at pos to 1.
  void setBit(int pos);

  // Sets bit at pos to 0;
  void clearBit(int pos);

  // Sets all bits to 0;
  void clear();

private:
  std::uint32_t bits_ = 0;
};
} // namespace nsd

#endif
