#include "short_array.hpp"
#include <stdexcept>
#include <iostream>

ShortArray::ShortArray() {
    embedded.raw_count = 0;
    embedded.bits.is_inline_bit = 1;
}

ShortArray::ShortArray(size_t initial_size, short fill_value) {
    if (initial_size <= INLINE_CAPACITY) {
        embedded.raw_count = 0;
        embedded.bits.is_inline_bit = 1;
        embedded.bits.inline_count = initial_size;
        for (int i = 0; i < static_cast<int>(initial_size); ++i) {
            embedded.inline_data[i] = fill_value;
        }
    } else {
        dynamic.data = new short[initial_size];
        dynamic.capacity = initial_size;
        dynamic.count = initial_size;
        for (int i = 0; i < static_cast<int>(initial_size); ++i) {
            dynamic.data[i] = fill_value;
        }
        embedded.bits.is_inline_bit = 0;
    }
}

ShortArray::~ShortArray() {
    if (!is_using_dynamic_memory()) {
        return;
    }
    delete[] dynamic.data;
}

short& ShortArray::operator[](size_t index) {
    if (!is_using_dynamic_memory()) {
        if (index >= embedded.bits.inline_count) {
            throw std::out_of_range("Индекс за пределами массива");
        }
        return embedded.inline_data[index];
    } else {
        if (index >= dynamic.count) {
            throw std::out_of_range("Индекс за пределами массива");
        }
        return dynamic.data[index];
    }
}

const short& ShortArray::operator[](size_t index) const {
    if (!is_using_dynamic_memory()) {
        if (index >= embedded.bits.inline_count) {
            throw std::out_of_range("Индекс за пределами массива");
        }
        return embedded.inline_data[index];
    } else {
        if (index >= dynamic.count) {
            throw std::out_of_range("Индекс за пределами массива");
        }
        return dynamic.data[index];
    }
}

void ShortArray::push(short new_val) {
    if (!is_using_dynamic_memory()) {
        if (embedded.bits.inline_count < INLINE_CAPACITY) {
            embedded.inline_data[embedded.bits.inline_count++] = new_val;
            return;
        } else {
            size_t new_capacity = INLINE_CAPACITY * 2;
            short* new_data = new short[new_capacity];
            for (int i = 0; i < static_cast<int>(embedded.bits.inline_count); ++i) {
                new_data[i] = embedded.inline_data[i];
            }
            new_data[embedded.bits.inline_count] = new_val;
            dynamic.data = new_data;
            dynamic.capacity = new_capacity;
            dynamic.count = embedded.bits.inline_count + 1;
            embedded.bits.is_inline_bit = 0;
            return;
        }
    } else {
        if (dynamic.count == dynamic.capacity) {
            size_t new_capacity = dynamic.capacity * 2;
            short* new_data = new short[new_capacity];
            for (int i = 0; i < static_cast<int>(dynamic.count); ++i) {
                new_data[i] = dynamic.data[i];
            }
            delete[] dynamic.data;
            dynamic.data = new_data;
            dynamic.capacity = new_capacity;
        }
        dynamic.data[dynamic.count++] = new_val;
    }
}

short ShortArray::pop() {
    if (!is_using_dynamic_memory()) {
        if (embedded.bits.inline_count == 0) {
            throw std::out_of_range("Массив пуст");
        }
        return embedded.inline_data[--embedded.bits.inline_count];
    } else {
        if (dynamic.count == 0) {
            throw std::out_of_range("Массив пуст");
        }
        return dynamic.data[--dynamic.count];
    }
}

size_t ShortArray::size() const {
    return is_using_dynamic_memory() ? dynamic.count : embedded.bits.inline_count;
}

void ShortArray::resize(size_t new_size, short fill_value) {
    if (new_size <= INLINE_CAPACITY && !is_using_dynamic_memory()) {
        for (size_t i = embedded.bits.inline_count; i < new_size; ++i) {
            embedded.inline_data[i] = fill_value;
        }
        embedded.bits.inline_count = new_size;
    } else if (new_size <= INLINE_CAPACITY && is_using_dynamic_memory()) {
        short temp[INLINE_CAPACITY];
        for (int i = 0; i < static_cast<int>(new_size) && i < static_cast<int>(dynamic.count); ++i) {
            temp[i] = dynamic.data[i];
        }
        for (size_t i = dynamic.count; i < new_size; ++i) {
            temp[i] = fill_value;
        }
        delete[] dynamic.data;
        for (int i = 0; i < static_cast<int>(new_size); ++i) {
            embedded.inline_data[i] = temp[i];
        }
        embedded.bits.inline_count = new_size;
        embedded.bits.is_inline_bit = 1;
    } else {
        if (!is_using_dynamic_memory()) {
            size_t new_capacity = new_size;
            short* new_data = new short[new_capacity];
            for (int i = 0; i < static_cast<int>(embedded.bits.inline_count); ++i) {
                new_data[i] = embedded.inline_data[i];
            }
            for (size_t i = embedded.bits.inline_count; i < new_size; ++i) {
                new_data[i] = fill_value;
            }
            dynamic.data = new_data;
            dynamic.capacity = new_capacity;
            dynamic.count = new_size;
            embedded.bits.is_inline_bit = 0;
        } else {
            if (new_size > dynamic.capacity) {
                size_t new_capacity = new_size;
                short* new_data = new short[new_capacity];
                for (int i = 0; i < static_cast<int>(dynamic.count); ++i) {
                    new_data[i] = dynamic.data[i];
                }
                for (size_t i = dynamic.count; i < new_size; ++i) {
                    new_data[i] = fill_value;
                }
                delete[] dynamic.data;
                dynamic.data = new_data;
                dynamic.capacity = new_capacity;
            } else {
                for (size_t i = dynamic.count; i < new_size; ++i) {
                    dynamic.data[i] = fill_value;
                }
            }
            dynamic.count = new_size;
        }
    }
}

void ShortArray::print() const {
    if (!is_using_dynamic_memory()) {
        for (int i = 0; i < static_cast<int>(embedded.bits.inline_count); ++i) {
            std::cout << embedded.inline_data[i] << " ";
        }
    } else {
        for (int i = 0; i < static_cast<int>(dynamic.count); ++i) {
            std::cout << dynamic.data[i] << " ";
        }
    }
    std::cout << std::endl;
}

bool ShortArray::is_using_dynamic_memory() const {
    return embedded.bits.is_inline_bit == 0;
}