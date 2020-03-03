#ifndef XSTL_NESTED_H_
#define XSTL_NESTED_H_

#include <unordered_map>
#include <map>
#include <memory>
#include <type_traits>
#include <utility>
#include <optional>

namespace xstl {

namespace _nested_helper {

// check if a type is hashable
template <typename T, typename = std::void_t<>>
struct IsHashable : std::false_type {};

template <typename T>
struct IsHashable<T, std::void_t<decltype(std::declval<std::hash<T>>()(
                         std::declval<T>()))>> : std::true_type {};

// type of internal map
// use 'std::unordered_map' if type 'K' is hashable,
// otherwise use 'std::map'
template <typename K, typename V>
using Map = typename std::conditional<IsHashable<K>::value,
                                      std::unordered_map<K, V>,
                                      std::map<K, V>>::type;

}  // namespace _nested_helper

template <typename K, typename V>
class NestedMap;

template <typename K, typename V>
using NestedMapPtr = std::shared_ptr<NestedMap<K, V>>;

template <typename K, typename V>
class NestedMap {
 public:
  NestedMap() : outer_(nullptr) { static_cast<void>(ValChecker{}); }
  NestedMap(const NestedMapPtr<K, V> &outer) : outer_(outer) {
    static_cast<void>(ValChecker{});
  }

  // add item to current map
  void AddItem(const K &key, const V &value) {
    map_.insert({key, value});
  }
  // get item
  V GetItem(const K &key, bool recursive) {
    auto it = map_.find(key);
    if (it != map_.end()) {
      return it->second;
    }
    else if (outer_ && recursive) {
      return outer_->GetItem(key);
    }
    else {
      return nullptr;
    }
  }
  // get item recursively
  V GetItem(const K &key) { return GetItem(key, true); }

  // getters
  // outer map
  const NestedMapPtr<K, V> &outer() const { return outer_; }
  // check if current map is root map
  bool is_root() const { return outer_ == nullptr; }

 private:
  // check if value type is suitable
  struct ValChecker {
    static_assert(std::is_pointer<V>::value ||
                      std::is_constructible<V, std::nullptr_t>::value,
                  "value type must be a pointer or can be constructed "
                  "with nullptr_t");
  };

  NestedMapPtr<K, V> outer_;
  _nested_helper::Map<K, V> map_;
};

template <typename K, typename V>
class NestedMap<K, std::optional<V>> {
 public:
  // actual value type
  using Vl = std::optional<V>;

  NestedMap() : outer_(nullptr) {}
  NestedMap(const NestedMapPtr<K, Vl> &outer) : outer_(outer) {}

  // add item to current map
  void AddItem(const K &key, Vl value) {
    map_.insert({key, value});
  }
  // get item
  Vl GetItem(const K &key, bool recursive) {
    auto it = map_.find(key);
    if (it != map_.end()) {
      return it->second;
    }
    else if (outer_ && recursive) {
      return outer_->GetItem(key);
    }
    else {
      return {};
    }
  }
  // get item recursively
  Vl GetItem(const K &key) { return GetItem(key, true); }

  // getters
  // outer map
  const NestedMapPtr<K, Vl> &outer() const { return outer_; }
  // check if current map is root map
  bool is_root() const { return outer_ == nullptr; }

 private:
  NestedMapPtr<K, Vl> outer_;
  _nested_helper::Map<K, Vl> map_;
};

// create a new nested map
template <typename K, typename V>
inline NestedMapPtr<K, V> MakeNestedMap() {
  return std::make_shared<NestedMap<K, V>>();
}

// create a new nested map (with outer map)
template <typename K, typename V>
inline NestedMapPtr<K, V> MakeNestedMap(const NestedMapPtr<K, V> &outer) {
  return std::make_shared<NestedMap<K, V>>(outer);
}

}  // namespace xstl

#endif  // XSTL_NESTED_H_
