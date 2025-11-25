#pragma once
#include <coroutine>
#include <deque>
#include <iostream>

class Routine {
public:
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    struct promise_type {
        Routine get_return_object() {return Routine{handle_type::from_promise(*this)};}
        std::suspend_never initial_suspend() {return {};}
        std::suspend_always final_suspend() noexcept {return {};}
        void return_void() {}
        void unhandled_exception() {std::terminate();}
    };

    Routine(handle_type h) : coro(h) {}
    ~Routine() {if (coro) coro.destroy();}
    
    Routine(const Routine&) = delete;
    Routine& operator=(const Routine&) = delete;
    Routine(Routine&& other) noexcept : coro(other.coro) {other.coro = nullptr;}

    void resume() {if (coro && !coro.done()) coro.resume();}
    bool done() const {return !coro || coro.done();}

private:
    handle_type coro;
};

struct Awaiter {
    const std::deque<int>& buffer;

    bool await_ready() const {
        if (buffer.size() < 3) return true;

        int last = buffer.back();
        int prev1 = buffer[buffer.size() - 2];
        int prev2 = buffer[buffer.size() - 3];

        bool should_suspend = (last == prev1) && (last == prev2);
        return !should_suspend;
    }

    void await_suspend(std::coroutine_handle<>) const {
        std::cout << "\nSuspended! Found 3 equal values: " 
                  << buffer.back() << std::endl;
    }

    void await_resume() const {
        std::cout << "Resuming processing..." << std::endl;
    }
};

Routine average_calculator();