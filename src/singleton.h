#ifndef HECK_SINGLETON_H
#define HECK_SINGLETON_H

namespace nsd {
template <typename T> class Singleton {
public:
  static T &getInstance() {
    static auto instance{T{}};

    return instance;
  }

  Singleton<T>(const Singleton<T> &) = delete;

  Singleton<T>(Singleton<T> &&) = delete;

  virtual ~Singleton<T>() = default;

  Singleton<T> &operator=(const Singleton<T> &) = delete;

  Singleton<T> &operator=(Singleton<T> &&) = delete;

protected:
  Singleton<T>() = default;
};
} // namespace nsd

#endif
