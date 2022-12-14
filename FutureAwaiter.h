#pragma once

#include "coroutine_common.h"
#include "Executor.h"
#include "CommonAwaiter.h"
#include <future>
#include <thread>

template<typename R>
struct FutureAwaiter : public Awaiter<R> {
  explicit FutureAwaiter(std::future<R> &&future) noexcept
      : _future(std::move(future)) {}

  FutureAwaiter(FutureAwaiter &&awaiter) noexcept
      : Awaiter<R>(awaiter), _future(std::move(awaiter._future)) {}

  FutureAwaiter(FutureAwaiter &) = delete;

  FutureAwaiter &operator=(FutureAwaiter &) = delete;

 protected:
  void after_suspend() override {
    std::thread([this](){
      this->resume(this->_future.get());
    }).detach();
  }

 private:
  std::future<R> _future;
};
