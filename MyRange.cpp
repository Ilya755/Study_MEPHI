#pragma once

#include <iostream>

class Range {
private:
    int64_t start, finish, step;

public: 
    class RangeIterator {
    private:
        int64_t cur, finish, step;

    public:
        RangeIterator(int64_t cur_, int64_t finish_, int64_t step_)
            : cur(cur_)
            , finish(finish_)
            , step(step_)
            {};

        int64_t operator*() const {
            return cur;
        }
        RangeIterator& operator++() {
            if (step > 0 && cur + step > finish) {
                cur = finish;
                return *this;
            }
            else if (step < 0 && cur + step < finish) {
                cur = finish;
                return *this;
            }
            else {
                cur += step;
                return *this;
            }
        }
        RangeIterator operator++(int) {
            RangeIterator it = *this;
            operator++();
            return it;
        }
        bool operator!=(const RangeIterator& it) {
            if (this->cur == it.cur && this->step == it.step) {
                return false;
            }
            else {
                return true;
            }
        }
        bool operator==(const RangeIterator& it) {
            if (*this != it) {
                return false;
            }
            else {
                return true;
            }
        }
    };
    Range(int64_t finish_) 
        : start(0)
        , finish(finish_)
        , step(1)
        {}
    Range(const int64_t& start_, const int64_t& finish_)
        : start(start_)
        , finish(finish_)
        , step(1)
        {}
    Range(const int64_t& start_, const int64_t& finish_, const int64_t& step_) 
        : start(start_)
        , finish(finish_)
        , step(step_)
        {}

    int64_t Size() const {
        if (std::abs(finish - start) % step == 0) {
            return (std::abs(finish - start) / std::abs(step));
        }
        else {
            return (std::abs(finish - start) / std::abs(step) + 1);
        }
    }
    RangeIterator begin() const {
        return RangeIterator(start, finish, step);
    }
    RangeIterator end() const {
        return RangeIterator(finish, finish, step);
    }
};