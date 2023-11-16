#include <iostream>

template<typename T>
class Array {
public:
    T* begin() {
        return data;
    }
    T* end() {
        return data + size_;
    }   
    const T* begin() const {
        return data;
    }
    const T* end() const {
        return data + size_;
    }

    Array(std::ostream &ostream) 
        : Ostream_(ostream) {
            size_ = 0;
            capacity_ = 2;
            data = new T[capacity_];
            Ostream_.clear();
            ostream << "Constructed. " << (*this) << '\n';
    }

    Array(const Array& array) 
        : Ostream_(array.Ostream_) {
        size_ = array.size_;
        capacity_ = array.capacity_;
        data = new T[capacity_];
        Ostream_.clear();
        for (size_t i = 0; i < size_; ++i) {
            data[i] = array.data[i];
        }
        Ostream_ << "Constructed from another Array. " << (*this) << '\n';
        }
    Array(int& size, std::ostream& ostream = std::cout) 
        : Ostream_(ostream) {
        size_ = size;
        capacity_ = 2 * size;
        data = new T[capacity_];
        Ostream_.clear();
        Ostream_ << "Constructed with default. " << (*this);
        }
    Array(size_t size, std::ostream& ostream = std::cout, T defaultValue = 0) 
        : Ostream_(ostream) {
        size_ = size;
        capacity_ = 2 * size;
        data = new T[capacity_];
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
            T* newData = new T[newCapacity];
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
            T* newData = new T[capacity_];
            size_ = newSize;
            for (size_t i = 0; i < size_; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        else {
            capacity_ = newSize;
            T* newData = new T[capacity_];
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
    void PushBack(T value) {
        if (size_ == capacity_) {
            capacity_ = capacity_ * 2;
            T* newData = new T[capacity_];
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

    const T& operator[](const size_t i) const {
        return const_cast<Array<T>*>(this)->operator[](i);
    }
    T& operator[](const size_t i) {
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

    bool operator==(const Array<T>& it) const {
        for (size_t i = 0; i < std::min(size_, it.size_); ++i) {
            if (data[i] != it.data[i]) {
                return false;
            }
        }
        return size_ == it.size_;
    }
    bool operator>(const Array<T>& it) const {
        for (size_t i = 0; i < std::min(size_, it.size_); ++i) {
            if (data[i] <= it.data[i]) {
                return false;
            }
        }
        return size_ > it.size_;
    }
    bool operator<(const Array<T>& it) const {
        for (size_t i = 0; i < std::min(size_, it.size_); ++i) {
            if (data[i] >= it.data[i]) {
                return false;
            }
        }
        return size_ < it.size_;
    }

    void Clear() {
        for (size_t i = 0; i < size_; ++i) {
            delete data[i];
        }
    }
    bool Insert(size_t pos, const T& value) {
        if (pos > size_) {
            return false;
        }
        if (size_ + 1 >= capacity_) {
            capacity_ *= 2;
        }
        T* newData = new T[capacity_];
        size_t i = 0;
        for (; i < pos; ++i) {
            newData[i] = data[i];
        }
        newData[i] = value;
        ++i;
        size_++;
        for (; i < size_; ++i) {
            newData[i] = data[i - 1];
        } 
        delete [] data;
        data = newData;
        return true;
    }

    bool Erase(size_t pos) {
        if (pos >= size_) {
            return false;
        }
        T* newData = new T[capacity_];
        size_t i;
        if (pos == 0) {
            i = 1;
            for (; i < size_; ++i) {
                newData[i - 1] = data[i];
            }
        }
        else {
            i = 0;
            for (; i < pos - 1; ++i) {
                newData[i] = data[i];
            }
            i += 2;
            for (; i < size_; ++i) {
                newData[i - 1] = data[i];
            }
        }
        size_--;
        delete [] data;
        data = newData;
        return true;
    }

    template<typename P>
    friend std::ostream& operator << (std::ostream& ostream, const Array<P>& array);

private:
    std::ostream& Ostream_;
    size_t size_;
    size_t capacity_;
    T* data;
};

template<typename P>
std::ostream& operator << (std::ostream& ostream, const Array<P>& array) {
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
