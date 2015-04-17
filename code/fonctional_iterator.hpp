#ifndef FONCTIONAL_ITERATOR_HPP
#define FONCTIONAL_ITERATOR_HPP


template<typename T>
class Fonctional_iterator : public std::vector<T>
{
    public:
        const T& operator*() const
        {

        }
        const T* operator->() const;
        Fonctional_iterator& operator++();
        Fonctional_iterator operator++(int);
        bool equal(Fonctional_iterator const& rhs) const;
};

template<typename T>
inline bool operator==(Fonctional_iterator<T> const& lhs,Fonctional_iterator<T> const& rhs)
{
    return lhs.equal(rhs);
}

#endif


