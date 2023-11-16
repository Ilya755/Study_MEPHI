#include <iostream>

class Array {
public:
    Array(std::ostream &ostream) 
        : Ostream_(ostream) {
            size_ = 0;
            capacity_ = 2;
            data = new int[capacity_];
            Ostream_.clear();
            ostream << "Constructed. " << (*this) << '\n';
    }
    Array(const Array& array) 
        : Ostream_(array.Ostream_) {
        size_ = array.size_;
        capacity_ = array.capacity_;
        data = new int[capacity_];
        Ostream_.clear();
        for (size_t i = 0; i < size_; ++i) {
            data[i] = array.data[i];
        }
        Ostream_ << "Constructed from another Array. " << (*this) << '\n';
        }
    Array(size_t size, std::ostream& ostream = std::cout, int defaultValue = 0) 
        : Ostream_(ostream) {
        size_ = size;
        capacity_ = 2 * size;
        data = new int[capacity_];
        for(size_t i = 0; i < size_; ++i) {
            data[i] = defaultValue;
        }
        Ostream_.clear();
        Ostream_ << "Constructed with default. " << (*this);
        }
    ~Array() {
        Ostream_.clear();
        Ostream_ << "Destructed " << size_ << '\n';
        delete[] data;
    }

    size_t Size() const {
        return size_;
    }
    size_t Capacity() const {
        return capacity_;
    }
    void Reserve(size_t newCapacity) {
        if (capacity_ < newCapacity) {
            int* newData = new int[newCapacity];
            capacity_ = newCapacity;
            for (size_t i = 0; i < size_; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
    }
    void Resize(size_t newSize) {
        if (size_ >= newSize) {
            int* newData = new int[capacity_];
            size_ = newSize;
            for (size_t i = 0; i < size_; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        else {
            capacity_ = newSize;
            int* newData = new int[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            for (size_t i = size_; i < newSize; ++i) {
                data[i] = 0;
            }
            size_ = newSize;
        }
    }
    void PushBack(int value = 0) {
        if (size_ == capacity_) {
            capacity_ = capacity_ * 2;
            int* newData = new int[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size_] = value;
        ++size_;
    }
    void PopBack() {
        --size_;
    }

    const int& operator[](const size_t i) const {
        return const_cast<Array*>(this)->operator[](i);
    }
    int& operator[](const size_t i) {
        return data[i];
    }
    explicit operator bool() const {
        if (size_ == 0) {
            return false;
        }
        else {
            return true;
        }
    }

    bool operator<(const Array& it) const {
        for (size_t i = 0; i < std::min(size_, it.size_); ++i) {
            if (data[i] >= it.data[i]) {
                return false;
            }
        }
        return size_ < it.size_;
    }
    bool operator>(const Array& it) const {
        for (size_t i = 0; i < std::min(size_, it.size_); ++i) {
            if (data[i] <= it.data[i]) {
                return false;
            }
        }
        return size_ > it.size_;
    }
    bool operator!=(const Array& it) const {
        for (size_t i = 0; i < std::min(size_, it.size_); ++i) {
            if (data[i] == it.data[i]) {
                return false;
            }
        }
        return size_ != it.size_;
    }
    bool operator==(const Array& it) const {
        for (size_t i = 0; i < std::min(size_, it.size_); ++i) {
            if (data[i] != it.data[i]) {
                return false;
            }
        }
        return size_ == it.size_;
    }
    bool operator<=(const Array& it) const {
        for (size_t i = 0; i < std::min(size_, it.size_); ++i) {
            if (data[i] > it.data[i]) {
                return false;
            }
        }
        return size_ <= it.size_;
    }
    bool operator>=(const Array& it) const {
        for (size_t i = 0; i < std::min(size_, it.size_); ++i) {
            if (data[i] < it.data[i]) {
                return false;
            }
        }
        return size_ >= it.size_;
    }

    Array& operator<<(const int value) {
        PushBack(value);
        return (*this);
    }
    Array& operator<<(const Array& it) {
        capacity_ = (size_ + it.size_) * 2;
        int* newData = new int[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            newData[i] = data[i];
        }
        for (size_t i = 0; i < it.size_; ++i) {
            newData[i + size_] = it.data[i];
        }
        size_ = capacity_ / 2;
        delete[] data;
        data = newData;
        return (*this);
    }

    friend std::ostream& operator<<(std::ostream& ostream, const Array& array) {
        ostream.clear();
        ostream << "Result Array's capacity is " << array.capacity_ << " and size is " << array.size_;
        if (array.size_ == 0) {
            return ostream;
        }
        else {
            ostream << ", elements are: ";
            for (size_t i = 0; i < array.size_ - 1; ++i) {
                ostream << array.data[i] << ", ";
            }
            ostream << array.data[array.size_ - 1];
            return ostream;
        }
    }

private:
    std::ostream& Ostream_;
    size_t size_;
    size_t capacity_;
    int* data;
};
