// Copyright (c) 2017 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#pragma once

#include <chrono>
#include <cstdint>

namespace carla {
namespace detail {

  template <typename CLOCK>
  class StopWatchTmpl {
    static_assert(CLOCK::is_steady, "The StopWatch's clock must be steady");
  public:

    using clock = CLOCK;

    StopWatchTmpl() : _start(clock::now()), _end(), _is_running(true) {}

            // _start 被初始化为当前时间点，表示秒表开始计时
            // _end 初始化为默认值，表示秒表未停止
            // _is_running 设置为 true，表示秒表正在运行
    void Restart() {
      _is_running = true;
      // 将开始时间更新为当前时间点
      _start = clock::now();
    }

    void Stop() {
    	// 将结束时间更新为当前时间点
      _end = clock::now();
      _is_running = false;
    }

    typename clock::duration GetDuration() const {
    	// 如果秒表正在运行，返回当前时间与开始时间的差值
      return _is_running ? clock::now() - _start : _end - _start;
    }

    template <class RESOLUTION=std::chrono::milliseconds>
    size_t GetElapsedTime() const {
      return static_cast<size_t>(std::chrono::duration_cast<RESOLUTION>(GetDuration()).count());
    }

    bool IsRunning() const {
      return _is_running;
    }

  private:

    typename clock::time_point _start;

    typename clock::time_point _end;

    bool _is_running;
  };

} // namespace detail

  using StopWatch = detail::StopWatchTmpl<std::chrono::steady_clock>;

} // namespace carla
