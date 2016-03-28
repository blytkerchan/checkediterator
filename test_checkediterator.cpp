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
#include <iostream>
#include "checkediterator.hpp"
#include <algorithm>
#include <vector>

using namespace Vlinder;
using namespace std;

int testNormalUsage01()
{
    int a[10];
    auto it_a(makeCheckedOutputIterator(a));
    int i(0);
    generate_n(it_a, 10, [&i](){ return i++; });    
    std::copy(a, a + 10, ostream_iterator< int >(cout));
    cout << endl;
    
    return 0;
}

int testNormalUsage02()
{
    vector< int > a(10);
    auto it_a(makeCheckedOutputIterator(a.begin(), a.end()));
    int i(0);
    generate_n(it_a, 10, [&i](){ return i++; });    
    std::copy(a.begin(), a.end(), ostream_iterator< int >(cout));
    cout << endl;
    
    return 0;
}

int testOverflow01()
{
    int a[10];
    auto it_a(makeCheckedOutputIterator(a));
    int i(0);
    bool caught(false);
    try
    {
        generate_n(it_a, 11, [&i](){ return i++; });
    }
    catch (out_of_range const &e)
    {
        caught = true;
        cout << "Expected exception caught" << endl;
    }
    std::copy(a, a + 10, ostream_iterator< int >(cout));
    cout << endl;
    
    return caught ? 0 : 1;
}

int testOverflow02()
{
    vector< int > a(10);
    auto it_a(makeCheckedOutputIterator(a.begin(), a.end()));
    int i(0);
    bool caught(false);
    try
    {
        generate_n(it_a, 11, [&i](){ return i++; });
    }
    catch (out_of_range const &e)
    {
        caught = true;
        cout << "Expected exception caught" << endl;
    }
    std::copy(a.begin(), a.end(), ostream_iterator< int >(cout));
    cout << endl;
    
    return caught ? 0 : 1;
}

int main()
{
    return 0
        || testNormalUsage01()
        || testNormalUsage02()
        || testOverflow01()
        || testOverflow02()
        ;
}