#include "iostream"
#include "vector"

template<class T>
class FlattenedVector {
private:
    std::vector<std::vector<T>>& vec;
    std::vector<int> pref;

public:
    class Iterator {
    private:
        int pos;
        std::vector<std::vector<T>>& vec;
        std::vector<int>& prefixsum;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = ssize_t;

        Iterator(int pos_, std::vector<std::vector<T>>& vec_, std::vector<int>& pref) 
            : pos(pos_)
            , vec(vec_)
            , prefixsum(pref)
            {}
        T& operator*() const {
            int l = 0;
            int r = prefixsum.size();
            while (r - l > 1) {
                if (prefixsum[(l + r) / 2] > pos) {
                    r = (l + r) / 2;
                } 
                else {
                    l = (l + r) / 2;
                }
            }
            int it = distance(prefixsum.begin(), prefixsum.begin() + r - 1);
            return vec[it][pos - prefixsum[it]];
        }
        Iterator& operator++() { 
            pos++;
            return *this;
        }
        Iterator operator++(int) {
            Iterator it = *this;
            operator++();
            return it;
        }
        Iterator& operator+=(int value) {
            pos += value;
            return *this;
        }
        Iterator& operator--() {
            pos--;
            return *this;
        }
        Iterator operator--(int) {
            Iterator it = *this;
            operator--();
            return it;
        }
        Iterator& operator-=(int value) {
            pos -= value;
            return *this;
        }
        Iterator operator+(int value) const {
            if (pos + value > prefixsum.back()) {
                return Iterator(prefixsum.back(), vec, prefixsum);
            }
            return Iterator(pos + value, vec, prefixsum);
        }
        friend Iterator operator+(const int value, const Iterator& it) {
            return it + value;
        }
        Iterator operator-(int value) const{
            if (pos + value < 0) {
                return Iterator(0, vec, prefixsum);
            }
            return Iterator(pos - value, vec, prefixsum);
        }
        friend Iterator operator-(int value, Iterator& it) {
            return it - value;
        }
        int operator-(const Iterator it) const {
            return pos - it.pos;
        }
        bool operator!=(const Iterator& it) const {
            if (*this == it) {
                return false;
            }
            else {
                return true;
            }
        }
        bool operator<(const Iterator& it) const {
            if (pos >= it.pos) {
                return false;
            }
            else {
                return true;
            }
        }
        bool operator<=(const Iterator& it) const {
            if (pos > it.pos) {
                return false;
            }
            else {
                return true;
            }
        }
        bool operator>(const Iterator& it) const {
            if (pos <= it.pos) {
                return false;
            }
            else {
                return true;
            }
        }
        bool operator>=(const Iterator& it) const {
            if (pos < it.pos) {
                return false;
            }
            else {
                return true;
            }
        }
        bool operator==(const Iterator& it) const {
            if (pos != it.pos) {
                return false;
            }
            else {
                return true;
            }
        }
        bool operator==(int value) {
            if (pos != value) {
                return false;
            }
            else {
                return true;
            }
        }
        Iterator& operator=(Iterator& it) {
            pos = it.pos;
            vec = it.vec;
            prefixsum = it.prefixsum;
            return *this;
        }
        T& operator[](int diff) const {
            return *(*this + diff);
        }
    };
    FlattenedVector(std::vector<std::vector<T>>& vec_)
        :vec(vec_) {
            pref.push_back(0);
            for (int i = 1; i < (int) vec.size() + 1; ++i) {
                pref.push_back(vec[i - 1].size() + pref[i - 1]);
            }
    }
    Iterator begin() {
        return Iterator(0, vec, pref);
    }
    Iterator end() {
        return Iterator(pref.back(), vec, pref);
    }
};