/*
 * libnbt++ - A library for the Minecraft Named Binary Tag format.
 * Copyright (C) 2013, 2015  ljfa-ag
 *
 * This file is part of libnbt++.
 *
 * libnbt++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libnbt++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libnbt++.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "crtp_tag.h"
#include <type_traits>
#include <vector>

namespace nbt
{
/**
 * @brief Tag that contains an array of byte values
 */
class NBT_EXPORT tag_byte_array final : public detail::crtp_tag<tag_byte_array>
{
public:
    ///The type of the contained values
    typedef int8_t value_type;

    ///The type of the tag
    static constexpr tag_type type = tag_type::Byte_Array;

    //Iterator types
    typedef typename std::vector<value_type>::iterator iterator;
    typedef typename std::vector<value_type>::const_iterator const_iterator;

    ///Constructs an empty array
    tag_byte_array() {}

    ///Constructs an array with the given values
    tag_byte_array(std::initializer_list<value_type> init): data(init) {}
    tag_byte_array(std::vector<value_type>&& vec) noexcept: data(std::move(vec)) {}

    ///Returns a reference to the vector that contains the values
    std::vector<value_type>& get() { return data; }
    const std::vector<value_type>& get() const { return data; }

    /**
     * @brief Accesses a value by index with bounds checking
     * @throw std::out_of_range if the index is out of range
     */
    value_type& at(size_t i) { return data.at(i); }
    value_type at(size_t i) const { return data.at(i); }

    /**
     * @brief Accesses a value by index
     *
     * No bounds checking is performed.
     */
    value_type& operator[](size_t i) { return data[i]; }
    value_type operator[](size_t i) const { return data[i]; }

    ///Appends a value at the end of the array
    void push_back(value_type val) { data.push_back(val); }

    ///Removes the last element from the array
    void pop_back() { data.pop_back(); }

    ///Returns the number of values in the array
    size_t size() const { return data.size(); }

    ///Erases all values from the array.
    void clear() { data.clear(); }

    //Iterators
    iterator begin() { return data.begin(); }
    iterator end()   { return data.end(); }
    const_iterator begin() const  { return data.begin(); }
    const_iterator end() const    { return data.end(); }
    const_iterator cbegin() const { return data.cbegin(); }
    const_iterator cend() const   { return data.cend(); }

    void read_payload(io::stream_reader& reader) override;
    /**
     * @inheritdoc
     * @throw std::length_error if the array is too large for NBT
     */
    void write_payload(io::stream_writer& writer) const override;

private:
    std::vector<value_type> data;
};

inline bool operator==(const tag_byte_array& lhs, const tag_byte_array& rhs)
{ return lhs.get() == rhs.get(); }
inline bool operator!=(const tag_byte_array& lhs, const tag_byte_array& rhs)
{ return !(lhs == rhs); }

}
