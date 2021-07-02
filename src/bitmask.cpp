// Credit: https://thatgamesguy.co.uk/cpp-game-dev-4/
#include "bitmask.h"

namespace nsd {
void Bitmask::setMask(Bitmask &other) { bits_ = other.getMask(); }

std::uint32_t Bitmask::getMask() const { return bits_; }

bool Bitmask::getBit(int pos) const { return (bits_ & (1 << pos)) != 0; }

void Bitmask::setBit(int pos, bool on) {
  if (on) {
    setBit(pos);
  } else {
    clearBit(pos);
  }
}

void Bitmask::setBit(int pos) { bits_ = bits_ | 1 << pos; }

void Bitmask::clearBit(int pos) { bits_ = bits_ & ~(1 << pos); }

void Bitmask::clear() { bits_ = 0; }
} // namespace nsd
