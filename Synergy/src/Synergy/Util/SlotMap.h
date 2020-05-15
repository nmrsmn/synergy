#pragma once
#include <cassert>
#include <limits>  // find max value of key_size_type
#include <tuple>
#include <type_traits>  // declval, remove_reference
#include <vector>
#include <stdexcept>

namespace stdext
{
    template <typename T, typename Token = std::pair<unsigned, unsigned>, template <typename...> class Container = std::vector>
    class slot_map
    {
    public:
        using key_size_type = std::remove_reference_t<decltype(std::get<0>(std::declval<Token>()))>;
        using key_generation_type = std::remove_reference_t<decltype(std::get<1>(std::declval<Token>()))>;
        using mapped_type = typename Container<T>::value_type;
        using value_type = mapped_type;
        using key_type = Token;
        using size_type = std::remove_reference_t<decltype(std::get<0>(std::declval<Token>()))>;
        using reference = typename Container<value_type>::reference;
        using const_reference = typename Container<value_type>::const_reference;
        using pointer = typename Container<value_type>::pointer;
        using const_pointer = typename Container<value_type>::const_pointer;
        using container_type = Container<value_type>;

        using iterator = typename Container<value_type>::iterator;
        using const_iterator = typename Container<value_type>::const_iterator;
        using reverse_iterator = typename Container<value_type>::reverse_iterator;
        using const_reverse_iterator = typename Container<value_type>::const_reverse_iterator;

        static_assert(sizeof(key_size_type) <= sizeof(typename Container<T>::size_type),
                      "The size of the type of get<0>() for the Token type must be at most Container::size_type.");
        
        static_assert(std::tuple_size<Token>::value == 2,
                      "The token type for a slot_map must be decomposable into 2 integer-like types.");
        
        static_assert(std::is_same<typename std::iterator_traits<iterator>::iterator_category, std::random_access_iterator_tag>::value,
                      "slot_map requires the adapted container to provide random access iterators.");

        constexpr slot_map();
        constexpr slot_map(const slot_map &) = default;
        constexpr slot_map(slot_map &&)      = default;

        ~slot_map() = default;
    
        constexpr slot_map &operator=(const slot_map &) = default;
        constexpr slot_map &operator=(slot_map &&) = default;

        constexpr const container_type &data() const;

        constexpr reference at(const key_type &key);
        constexpr const_reference at(const key_type &key) const;
        
        constexpr reference operator[](const key_type &key);
        constexpr const_reference operator[](const key_type &key) const;
        
        constexpr iterator find(const key_type &key);
        constexpr const_iterator find(const key_type &key) const;

        constexpr iterator               begin();
        constexpr iterator               end();
        constexpr const_iterator         begin() const;
        constexpr const_iterator         end() const;
        constexpr const_iterator         cbegin() const;
        constexpr const_iterator         cend() const;
        constexpr reverse_iterator       rbegin();
        constexpr reverse_iterator       rend();
        constexpr const_reverse_iterator rbegin() const;
        constexpr const_reverse_iterator rend() const;
        constexpr const_reverse_iterator crbegin() const;
        constexpr const_reverse_iterator crend() const;

        constexpr bool      empty() const;
        constexpr size_type size() const;
        constexpr size_type max_size() const;
        constexpr size_type capacity() const;
        constexpr void reserve(size_type n);

        constexpr void reserve_slots(size_type n);
        constexpr size_type capacity_slots() const;
        
        constexpr void     clear();
        
        constexpr key_type insert(const_reference value);
        constexpr key_type insert(value_type &&value);
        
        template <typename... Args>
        constexpr key_type emplace(Args &&... args);
        
        constexpr iterator erase(iterator pos);
        constexpr iterator erase(iterator first, iterator last);
        constexpr iterator erase(const_iterator pos);
        constexpr iterator erase(const_iterator first, const_iterator last);
        constexpr size_type erase(const key_type &key);

    private:
        Container<key_type> m_slots;
        Container<T>        m_data;

        Container<key_size_type> m_erase_helper;
        key_size_type            m_free_head;
        key_size_type            m_free_tail;

        constexpr size_type pop_head();
        constexpr void      push_tail(size_type);
        constexpr key_type  finish_inserting_last_element();
        constexpr bool key_valid(const key_type &key);
        constexpr void           grow();
        constexpr void           grow_slots();
        constexpr void           pre_insert();
        constexpr key_size_type &key_index(key_type &key);
        constexpr const key_size_type &key_index(const key_type &key) const;
        constexpr key_generation_type &key_generation(key_type &key);
        constexpr const key_generation_type &key_generation(const key_type &key) const;
        constexpr key_size_type &element_index(key_type &key);
        constexpr const key_size_type &element_index(const key_type &key) const;
        
        constexpr reference find_unchecked(const key_type &key);
        constexpr const_reference find_unchecked(const key_type &key) const;

        static constexpr size_type growth_rate { 2 };
        static constexpr size_type initial_alloc_size { static_cast<size_type>(20) };
    };

    template <typename T, typename Token, template <typename...> class Container>
    constexpr slot_map<T, Token, Container>::slot_map()
        : m_free_head(0), m_free_tail(0)
    {}

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::iterator slot_map<T, Token, Container>::begin()
    {
        return std::begin(m_data);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::iterator slot_map<T, Token, Container>::end()
    {
        return std::end(m_data);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::const_iterator slot_map<T, Token, Container>::begin() const
    {
        return std::begin(m_data);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::const_iterator slot_map<T, Token, Container>::end() const
    {
        return std::end(m_data);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::const_iterator slot_map<T, Token, Container>::cbegin() const
    {
        return std::cbegin(m_data);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::const_iterator slot_map<T, Token, Container>::cend() const
    {
        return std::cend(m_data);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::reverse_iterator slot_map<T, Token, Container>::rbegin()
    {
        return std::rbegin(m_data);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::reverse_iterator slot_map<T, Token, Container>::rend()
    {
        return std::rend(m_data);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::const_reverse_iterator slot_map<T, Token, Container>::rbegin() const
    {
        return std::rbegin(m_data);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::const_reverse_iterator slot_map<T, Token, Container>::rend() const
    {
        return std::rend(m_data);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::const_reverse_iterator slot_map<T, Token, Container>::crbegin() const
    {
        return std::rbegin(m_data);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::const_reverse_iterator slot_map<T, Token, Container>::crend() const
    {
        return std::rend(m_data);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr const typename slot_map<T, Token, Container>::container_type &slot_map<T, Token, Container>::data() const
    {
        return m_data;
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::reference slot_map<T, Token, Container>::at(const key_type &key)
    {
        const auto &index {this->key_index(key) };
        const auto &generation { this->key_generation(key) };
        
        if(index >= m_slots.size() || generation != key_generation(*(m_slots.begin() + index)))
            throw std::range_error("Invalid key used with slot_map::at.");
        else
            return find_unchecked(key);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::const_reference slot_map<T, Token, Container>::at(const key_type &key) const
    {
        const auto &index { key_index(key) };
        const auto &generation { key_generation(key) };
        
        if(index >= m_slots.size() || generation != this->key_generation(*(std::begin(m_slots) + index)))
            throw std::range_error("Invalid key used with slot_map::at.");
        else
            return this->find_unchecked(key);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::const_reference slot_map<T, Token, Container>::operator[](const key_type &key) const
    {
        const auto &index { key_index(key) };
        const auto &generation { key_generation(key) };
    
        if(index >= m_slots.size() || generation != this->key_generation(*(std::begin(m_slots) + index)))
            throw std::range_error("Invalid key used with slot_map::operator[].");
        
        return *(std::cbegin(m_data) + this->element_index(key));
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::reference slot_map<T, Token, Container>::operator[](const key_type &key)
    {
        const auto &index { key_index(key) };
        const auto &generation { key_generation(key) };
    
        if(generation != key_generation(*(m_slots.begin() + index)))
            throw std::range_error("Invalid key used with slot_map::operator[].");
        else
            return this->find_unchecked(key);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::iterator slot_map<T, Token, Container>::find(const key_type &key)
    {
        const auto &index { key_index(key) };
        const auto &generation { key_generation(key) };
        
        if(generation != this->key_generation(*(m_slots.begin() + index)))
            return this->end();
        
        return std::begin(m_data) + element_index(key);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::const_iterator slot_map<T, Token, Container>::find(const key_type &key) const
    {
        const auto &index { key_index(key) };
        const auto &generation { key_generation(key) };
        
        if(generation != this->key_generation(*(m_slots.begin() + index)))
            return this->end();
        
        return this->cbegin() + this->element_index(key);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr bool slot_map<T, Token, Container>::empty() const
    {
        return m_data.empty();
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::size_type slot_map<T, Token, Container>::size() const
    {
        return static_cast<size_type>(m_data.size());
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::size_type slot_map<T, Token, Container>::max_size() const
    {
        return static_cast<size_type>(m_data.max_size());
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::size_type slot_map<T, Token, Container>::capacity() const
    {
        return static_cast<size_type>(m_data.capacity());
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr void slot_map<T, Token, Container>::reserve(size_type n)
    {
        if(n > this->capacity())
        {
            m_data.reserve(n);
            m_slots.reserve(n);
            this->grow_slots();
            m_erase_helper.reserve(n);
        }
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr void slot_map<T, Token, Container>::reserve_slots(size_type n)
    {
        if(n > this->capacity_slots())
        {
            m_slots.reserve(n);
            this->grow_slots();
        }
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::size_type slot_map<T, Token, Container>::capacity_slots() const
    {
        return m_slots.capacity();
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr void slot_map<T, Token, Container>::clear()
    {
        m_data.clear();
        m_slots.clear();
        m_erase_helper.clear();
        
        this->grow_slots();
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::key_type slot_map<T, Token, Container>::finish_inserting_last_element()
    {
        size_type                  slot_index { pop_head() };
        key_type &                 key { *(std::begin(m_slots) + slot_index) };
        key_size_type &            index      = this->key_index(key);
        const key_generation_type &generation = this->key_generation(key);
        
        index = static_cast<size_type>(m_data.size() - 1);
        m_erase_helper.push_back(slot_index);
        
        return { static_cast<key_size_type>(slot_index), generation };
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::key_type slot_map<T, Token, Container>::insert(const_reference value)
    {
        this->pre_insert();
        m_data.push_back(value);
        return this->finish_inserting_last_element();
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::key_type slot_map<T, Token, Container>::insert(value_type &&value)
    {
        this->pre_insert();
        m_data.push_back(std::move(value));
        return this->finish_inserting_last_element();
    }

    template <typename T, typename Token, template <typename...> class Container>
    template <typename... Args>
    constexpr typename slot_map<T, Token, Container>::key_type slot_map<T, Token, Container>::emplace(Args &&... args)
    {
        this->pre_insert();
        m_data.emplace_back(std::forward<Args>(args)...);
        return this->finish_inserting_last_element();
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::iterator slot_map<T, Token, Container>::erase(iterator pos)
    {
        if(pos == this->end())
            return pos;
        
        else if(pos == (std::end(m_data) - 1))
        {
            m_data.pop_back();
            this->push_tail(m_erase_helper.back());
            m_erase_helper.pop_back();
            
            return this->end();
        }
        else
        {
            const auto          dist { std::distance(this->begin(), pos) };
            const key_size_type slot_index { *(m_erase_helper.begin() + dist) };
            
            this->push_tail(slot_index);
            *pos = std::move(m_data.back());
            m_data.pop_back();
            
            const key_size_type update_slot { m_erase_helper.back() };
            
            *(m_erase_helper.begin() + dist) = m_erase_helper.back();
            m_erase_helper.pop_back();
            
            this->key_index(*(std::begin(m_slots) + update_slot)) = static_cast<key_size_type>(dist);
            
            return pos;
        }
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::iterator slot_map<T, Token, Container>::erase(iterator first, iterator last)
    {
        const auto range_size { std::distance(first, last) };
        const auto dist_from_end { std::distance(last, this->end()) };
        
        if(last == this->end())
        {
            for(auto it { last - 1 }; it >= first; --it)
            {
                this->erase(it);
            }
            return first;
        }
        else if(range_size < dist_from_end)
        {
            iterator separator { first + dist_from_end };
            for(auto it { first }; it != separator; ++it)
            {
                this->erase(it);
            }
            
            assert(last == end());
        
            for(auto it {last - 1 }; it >= first; --it)
            {
                this->erase(it);
            }
        
            return first;
        }
        else
        {  // length of range does not reach the end
            for(auto it { first }; it != last; ++it)
            {
                this->erase(it);
            }
            return first;
        }
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::iterator slot_map<T, Token, Container>::erase(const_iterator pos)
    {
        const auto dist { std::distance(this->cbegin(), pos) };
        return this->erase(this->begin() + dist);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::iterator slot_map<T, Token, Container>::erase(const_iterator first, const_iterator last)
    {
        const auto fdist { std::distance(this->cbegin(), first) };
        const auto ldist { std::distance(this->cbegin(), last) };
        
        return this->erase(this->begin() + fdist, this->begin() + ldist);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::size_type slot_map<T, Token, Container>::erase(const key_type &key)
    {
        if(this->key_valid(key))
        {
            this->erase(this->begin() + this->element_index(key));
            return 1;
        }
        return 0;
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::size_type slot_map<T, Token, Container>::pop_head()
    {
        if(this->size() == this->capacity())
            this->grow();
        
        key_size_type next_free_head { this->key_index(*(std::begin(m_slots) + m_free_head)) };
        
        if(next_free_head == m_free_head)
        {
            return static_cast<size_type>(m_free_head);
        }
        else
        {
            key_size_type result { m_free_head };
            m_free_head = next_free_head;
            return static_cast<size_type>(result);
        }
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr void slot_map<T, Token, Container>::push_tail(size_type tail_index)
    {
        this->key_index(*(std::begin(m_slots) + m_free_tail)) = tail_index;
        this->key_index(*(std::begin(m_slots) + tail_index))  = tail_index;
        m_free_tail                                           = tail_index;
        
        ++this->key_generation(*(std::begin(m_slots) + tail_index));
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr bool slot_map<T, Token, Container>::key_valid(const key_type &key)
    {
        return this->key_generation(key) == this->key_generation(*(std::begin(m_slots) + key_index(key)));
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr void slot_map<T, Token, Container>::grow()
    {
        auto new_capacity { capacity() * growth_rate };
        
        if(capacity() == 0)
            new_capacity = initial_alloc_size;
        
        if(new_capacity < capacity())
            new_capacity = std::numeric_limits<size_type>::max();
        
        grow_slots();
        
        m_data.reserve(new_capacity);
        m_erase_helper.reserve(new_capacity);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr void slot_map<T, Token, Container>::grow_slots()
    {
        size_type initial_size { static_cast<size_type>(m_slots.capacity()) };
        if(initial_size)
        {
            m_slots.reserve(initial_size * growth_rate);
        }
        else
        {
            m_slots.reserve(initial_alloc_size);
        }
        
        size_type capacity { static_cast<size_type>(m_slots.capacity()) };
        
        for(size_type i { initial_size }; i < capacity; ++i)
        {
            m_slots.emplace(std::end(m_slots), i + 1, 0);
        }
        
        this->key_index(m_slots.back()) = static_cast<key_size_type>(m_slots.size() - 1);
        
        m_free_head = initial_size;
        m_free_tail = this->key_index(m_slots.back());
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr void slot_map<T, Token, Container>::pre_insert()
    {
        if(this->size() == this->capacity()) this->grow();
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::key_size_type &slot_map<T, Token, Container>::key_index(key_type &key)
    {
        return std::get<0>(key);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr const typename slot_map<T, Token, Container>::key_size_type &slot_map<T, Token, Container>::key_index(const key_type &key) const
    {
        return std::get<0>(key);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::key_generation_type &slot_map<T, Token, Container>::key_generation(key_type &key)
    {
        return std::get<1>(key);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr const typename slot_map<T, Token, Container>::key_generation_type &slot_map<T, Token, Container>::key_generation(const key_type &key) const
    {
        return std::get<1>(key);
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::key_size_type &slot_map<T, Token, Container>::element_index(key_type &key)
    {
        return this->key_index(std::begin(m_slots) + this->key_index(key));
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr const typename slot_map<T, Token, Container>::key_size_type &slot_map<T, Token, Container>::element_index(const key_type &key) const
    {
        return this->key_index(*(std::begin(m_slots) + this->key_index(key)));
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::reference slot_map<T, Token, Container>::find_unchecked(const key_type &key)
    {
        return *(std::begin(m_data) + this->element_index(key));
    }

    template <typename T, typename Token, template <typename...> class Container>
    constexpr typename slot_map<T, Token, Container>::const_reference slot_map<T, Token, Container>::find_unchecked(const key_type &key) const
    {
        return *(std::cbegin(m_data) + this->element_index(key));
    }
}
