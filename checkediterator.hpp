/*
 * Copyright 2016  Ronald Landheer-Cieslak
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at 
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0 
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef vlinder_checkediterator_hpp
#define vlinder_checkediterator_hpp

#include <iterator>
#include <stdexcept>

namespace Vlinder {
    template < typename T, typename It = T* >
    class CheckedOutputIterator : public std::iterator< std::output_iterator_tag, T >
    {
    public :
        CheckedOutputIterator()
            : at_end_(true)
        { /* no-op */ }
        CheckedOutputIterator(It beg, It end)
            : at_end_(false)
            , beg_(beg)
            , end_(end)
        { /* no-op */ }
        ~CheckedOutputIterator()
        { /* no-op */ }

        T& operator*() const
        {
            if (at_end_ || (beg_ == end_)) throw std::range_error("Dereferenced invalid iterator");
            return *beg_;
        }
        
        CheckedOutputIterator& operator++()
        {
            if (at_end_ || (beg_ == end_)) throw std::range_error("Increment past end-of-range");
            ++beg_;
            return *this;
        }
        CheckedOutputIterator operator++(int)
        {
            CheckedOutputIterator temp(*this);
            ++(*this);
            return temp;
        }

    private :
        bool at_end_;
        It beg_;
        It end_;
    };
    
    template < typename T,  size_t N >
    CheckedOutputIterator< T, T* > makeCheckedOutputIterator(T (&a)[N])
    {
        return CheckedOutputIterator< T, T* >(a, a + N);
    }
    
    template < typename It >
    CheckedOutputIterator< typename It::value_type, It > makeCheckedOutputIterator(It beg, It end)
    {
        return CheckedOutputIterator< typename It::value_type, It >(beg, end);
    }
}

#endif

