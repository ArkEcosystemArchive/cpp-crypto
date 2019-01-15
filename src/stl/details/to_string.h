#ifndef ARDUINO_STL_DETAILS_TO_STRING_H
#define ARDUINO_STL_DETAILS_TO_STRING_H

#include <cstdio>
#include <cstdlib>
#include <cwchar>
#include <string>

namespace std {

inline std::string to_string(int value) {
  char buf[24] = {};
  snprintf(buf, sizeof(buf), "%d", value);
  return buf;
}
inline std::string to_string(long value) {
  char buf[24] = {};
  snprintf(buf, sizeof(buf), "%ld", value);
  return buf;
}
inline std::string to_string(long long value) {
  char buf[24] = {};
  snprintf(buf, sizeof(buf), "%lld", value);
  return buf;
}
inline std::string to_string(unsigned value) {
  char buf[24] = {};
  snprintf(buf, sizeof(buf), "%u", value);
  return buf;
}
inline std::string to_string(unsigned long value) {
  char buf[24] = {};
  snprintf(buf, sizeof(buf), "%lu", value);
  return buf;
}
inline std::string to_string(unsigned long long value) {
  char buf[24] = {};
  snprintf(buf, sizeof(buf), "%llu", value);
  return buf;
}
inline std::string to_string(float value) {
  char buf[24] = {};
  snprintf(buf, sizeof(buf), "%f", value);
  return buf;
}
inline std::string to_string(double value) {
  char buf[24] = {};
  snprintf(buf, sizeof(buf), "%lf", value);
  return buf;
}
inline std::string to_string(long double value) {
  char buf[24] = {};
  snprintf(buf, sizeof(buf), "%Lf", value);
  return buf;
}

inline float stof(const std::string& str, std::size_t* pos = 0) {
  char* end = nullptr;
  auto ret = strtof(str.c_str(), &end);
  if (pos != nullptr) {
    *pos = end - str.c_str();
  }
  return ret;
}
inline double stod(const std::string& str, std::size_t* pos = 0) {
  char* end = nullptr;
  auto ret = strtod(str.c_str(), &end);
  if (pos != nullptr) {
    *pos = end - str.c_str();
  }
  return ret;
}
inline long double stold(const std::string& str, std::size_t* pos = 0) {
  char* end = nullptr;
  auto ret = strtold(str.c_str(), &end);
  if (pos != nullptr) {
    *pos = end - str.c_str();
  }
  return ret;
}

inline int stoi(const std::string& str, std::size_t* pos = 0, int base = 10) {
  char* end = nullptr;
  auto ret = strtol(str.c_str(), &end, base);
  if (pos != nullptr) {
    *pos = end - str.c_str();
  }
  return static_cast<int>(ret);
}
inline long stol(const std::string& str, std::size_t* pos = 0, int base = 10) {
  char* end = nullptr;
  auto ret = strtol(str.c_str(), &end, base);
  if (pos != nullptr) {
    *pos = end - str.c_str();
  }
  return ret;
}
inline long long stoll(const std::string& str, std::size_t* pos = 0, int base = 10) {
  char* end = nullptr;
  auto ret = strtoll(str.c_str(), &end, base);
  if (pos != nullptr) {
    *pos = end - str.c_str();
  }
  return ret;
}

inline unsigned long stoul(const std::string& str, std::size_t* pos = 0, int base = 10) {
  char* end = nullptr;
  auto ret = strtoul(str.c_str(), &end, base);
  if (pos != nullptr) {
    *pos = end - str.c_str();
  }
  return ret;
}
inline unsigned long long stoull(const std::string& str, std::size_t* pos = 0, int base = 10) {
  char* end = nullptr;
  auto ret = strtoull(str.c_str(), &end, base);
  if (pos != nullptr) {
    *pos = end - str.c_str();
  }
  return ret;
}

inline std::wstring to_wstring(int value) {
  wchar_t buf[24] = {};
  swprintf(buf, sizeof(buf), L"%d", value);
  return buf;
}
inline std::wstring to_wstring(long value) {
  wchar_t buf[24] = {};
  swprintf(buf, sizeof(buf), L"%ld", value);
  return buf;
}
inline std::wstring to_wstring(long long value) {
  wchar_t buf[24] = {};
  swprintf(buf, sizeof(buf), L"%lld", value);
  return buf;
}
inline std::wstring to_wstring(unsigned value) {
  wchar_t buf[24] = {};
  swprintf(buf, sizeof(buf), L"%u", value);
  return buf;
}
inline std::wstring to_wstring(unsigned long value) {
  wchar_t buf[24] = {};
  swprintf(buf, sizeof(buf), L"%lu", value);
  return buf;
}
inline std::wstring to_wstring(unsigned long long value) {
  wchar_t buf[24] = {};
  swprintf(buf, sizeof(buf), L"%llu", value);
  return buf;
}
inline std::wstring to_wstring(float value) {
  wchar_t buf[24] = {};
  swprintf(buf, sizeof(buf), L"%f", value);
  return buf;
}
inline std::wstring to_wstring(double value) {
  wchar_t buf[24] = {};
  swprintf(buf, sizeof(buf), L"%lf", value);
  return buf;
}
inline std::wstring to_wstring(long double value) {
  wchar_t buf[24] = {};
  swprintf(buf, sizeof(buf), L"%Lf", value);
  return buf;
}
}  // namespace std

#endif
