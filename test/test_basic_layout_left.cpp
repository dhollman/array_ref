////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2015 Bryce Adelstein Lelbach aka wash
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <boost/detail/lightweight_test.hpp>

#include <vector>
#include <tuple>

#include <array_ref>

using std::vector;
using std::tuple;

using std::experimental::dyn;
using std::experimental::dimensions;
using std::experimental::basic_layout_left;

template <std::size_t X>
void test_1d_static()
{ // {{{
    dimensions<X> d;
    basic_layout_left<dimensions<1>, dimensions<0> > l;

    int dptr[X];

    for (auto i = 0; i < d[0]; ++i)
    {
        BOOST_TEST_EQ((l.index(d, i)), i);

        BOOST_TEST_EQ(&(dptr[l.index(d, i)]), &(dptr[i])); 

        dptr[l.index(d, i)] = i;

        BOOST_TEST_EQ((dptr[l.index(d, i)]), i); 
    }
} // }}}

template <std::size_t X>
void test_1d_dynamic()
{ // {{{
    dimensions<dyn> d(X);
    basic_layout_left<dimensions<1>, dimensions<0> > l;

    vector<int> data(d[0], 42);
    int* dptr = data.data();

    for (auto i = 0; i < d[0]; ++i)
    {
        BOOST_TEST_EQ((l.index(d, i)), i);

        BOOST_TEST_EQ(&(dptr[l.index(d, i)]), &(dptr[i])); 

        BOOST_TEST_EQ((dptr[l.index(d, i)]), 42); 

        dptr[l.index(d, i)] = i;

        BOOST_TEST_EQ((dptr[l.index(d, i)]), i); 

        // Bound-checking.
        BOOST_TEST_EQ((data.at(l.index(d, i))), i); 
    }
} // }}}

template <std::size_t X, std::size_t Y>
void test_2d_static()
{ // {{{
    dimensions<X, Y> d;
    basic_layout_left<dimensions<1, 1>, dimensions<0, 0> > l;

    tuple<int, int> dptr[X*Y];

    for (auto j = 0; j < d[1]; ++j)
    for (auto i = 0; i < d[0]; ++i)
    {
        auto const true_idx = i + j*d[0];

        BOOST_TEST_EQ((l.index(d, i, j)), true_idx);

        BOOST_TEST_EQ(&(dptr[l.index(d, i, j)]), &(dptr[true_idx])); 

        std::get<0>(dptr[l.index(d, i, j)]) = i;
        std::get<1>(dptr[l.index(d, i, j)]) = j;

        BOOST_TEST_EQ((std::get<0>(dptr[l.index(d, i, j)])), i); 
        BOOST_TEST_EQ((std::get<1>(dptr[l.index(d, i, j)])), j); 
    }
} // }}}

template <std::size_t X, std::size_t Y>
void test_2d_dynamic()
{ // {{{
    dimensions<dyn, dyn> d(X, Y);
    basic_layout_left<dimensions<1, 1>, dimensions<0, 0> > l;

    vector<tuple<int, int> > data(d[0]*d[1], tuple<int, int>(17, 42));

    tuple<int, int>* dptr = data.data();

    for (auto j = 0; j < d[1]; ++j)
    for (auto i = 0; i < d[0]; ++i)
    {
        auto const true_idx = i + j*d[0];

        BOOST_TEST_EQ((l.index(d, i, j)), true_idx);

        BOOST_TEST_EQ(&(dptr[l.index(d, i, j)]), &(dptr[true_idx])); 

        BOOST_TEST_EQ((std::get<0>(dptr[l.index(d, i, j)])), 17); 
        BOOST_TEST_EQ((std::get<1>(dptr[l.index(d, i, j)])), 42); 

        std::get<0>(dptr[l.index(d, i, j)]) = i;
        std::get<1>(dptr[l.index(d, i, j)]) = j;

        BOOST_TEST_EQ((std::get<0>(dptr[l.index(d, i, j)])), i); 
        BOOST_TEST_EQ((std::get<1>(dptr[l.index(d, i, j)])), j); 

        // Bound-checking.
        BOOST_TEST_EQ((std::get<0>(data.at(l.index(d, i, j)))), i); 
        BOOST_TEST_EQ((std::get<1>(data.at(l.index(d, i, j)))), j); 
    }
} // }}}

template <std::size_t X, std::size_t Y>
void test_2d_mixed()
{ // {{{
    dimensions<dyn, Y> d(X);
    basic_layout_left<dimensions<1, 1>, dimensions<0, 0> > l;

    vector<tuple<int, int> > data(d[0]*d[1], tuple<int, int>(17, 42));

    tuple<int, int>* dptr = data.data();

    for (auto j = 0; j < d[1]; ++j)
    for (auto i = 0; i < d[0]; ++i)
    {
        auto const true_idx = i + j*d[0];

        BOOST_TEST_EQ((l.index(d, i, j)), true_idx);

        BOOST_TEST_EQ(&(dptr[l.index(d, i, j)]), &(dptr[true_idx])); 

        BOOST_TEST_EQ((std::get<0>(dptr[l.index(d, i, j)])), 17); 
        BOOST_TEST_EQ((std::get<1>(dptr[l.index(d, i, j)])), 42); 

        std::get<0>(dptr[l.index(d, i, j)]) = i;
        std::get<1>(dptr[l.index(d, i, j)]) = j;

        BOOST_TEST_EQ((std::get<0>(dptr[l.index(d, i, j)])), i); 
        BOOST_TEST_EQ((std::get<1>(dptr[l.index(d, i, j)])), j); 

        // Bound-checking.
        BOOST_TEST_EQ((std::get<0>(data.at(l.index(d, i, j)))), i); 
        BOOST_TEST_EQ((std::get<1>(data.at(l.index(d, i, j)))), j); 
    }
} // }}}

template <std::size_t X, std::size_t Y, std::size_t Z>
void test_3d_static()
{ // {{{
    dimensions<X, Y, Z> d;
    basic_layout_left<dimensions<1, 1, 1>, dimensions<0, 0, 0> > l;

    tuple<int, int, int> dptr[X*Y*Z];

    for (auto k = 0; k < d[2]; ++k)
    for (auto j = 0; j < d[1]; ++j)
    for (auto i = 0; i < d[0]; ++i)
    {
        auto const true_idx = i + j*d[0] + k*d[1]*d[0];

        BOOST_TEST_EQ((l.index(d, i, j, k)), true_idx);

        BOOST_TEST_EQ(&(dptr[l.index(d, i, j, k)]), &(dptr[true_idx])); 

        std::get<0>(dptr[l.index(d, i, j, k)]) = i;
        std::get<1>(dptr[l.index(d, i, j, k)]) = j;
        std::get<2>(dptr[l.index(d, i, j, k)]) = k;

        BOOST_TEST_EQ((std::get<0>(dptr[l.index(d, i, j, k)])), i); 
        BOOST_TEST_EQ((std::get<1>(dptr[l.index(d, i, j, k)])), j); 
        BOOST_TEST_EQ((std::get<2>(dptr[l.index(d, i, j, k)])), k); 
    }
} // }}}

template <std::size_t X, std::size_t Y, std::size_t Z>
void test_3d_dynamic()
{ // {{{
    dimensions<dyn, dyn, dyn> d(X, Y, Z);
    basic_layout_left<dimensions<1, 1, 1>, dimensions<0, 0, 0> > l;

    vector<tuple<int, int, int> > data(
        d[0]*d[1]*d[2], tuple<int, int, int>(17, 42, 73)
    );

    tuple<int, int, int>* dptr = data.data();

    for (auto k = 0; k < d[2]; ++k)
    for (auto j = 0; j < d[1]; ++j)
    for (auto i = 0; i < d[0]; ++i)
    {
        auto const true_idx = i + j*d[0] + k*d[1]*d[0];

        BOOST_TEST_EQ((l.index(d, i, j, k)), true_idx);

        BOOST_TEST_EQ(&(dptr[l.index(d, i, j, k)]), &(dptr[true_idx])); 

        BOOST_TEST_EQ((std::get<0>(dptr[l.index(d, i, j, k)])), 17); 
        BOOST_TEST_EQ((std::get<1>(dptr[l.index(d, i, j, k)])), 42); 
        BOOST_TEST_EQ((std::get<2>(dptr[l.index(d, i, j, k)])), 73); 

        std::get<0>(dptr[l.index(d, i, j, k)]) = i;
        std::get<1>(dptr[l.index(d, i, j, k)]) = j;
        std::get<2>(dptr[l.index(d, i, j, k)]) = k;

        BOOST_TEST_EQ((std::get<0>(dptr[l.index(d, i, j, k)])), i); 
        BOOST_TEST_EQ((std::get<1>(dptr[l.index(d, i, j, k)])), j); 
        BOOST_TEST_EQ((std::get<2>(dptr[l.index(d, i, j, k)])), k); 

        // Bound-checking.
        BOOST_TEST_EQ((std::get<0>(data.at(l.index(d, i, j, k)))), i); 
        BOOST_TEST_EQ((std::get<1>(data.at(l.index(d, i, j, k)))), j); 
        BOOST_TEST_EQ((std::get<2>(data.at(l.index(d, i, j, k)))), k); 
    }
} // }}}

int main()
{
    {
        dimensions<> d;
        basic_layout_left<dimensions<>, dimensions<> > l;

        int data = 42;
        int* dptr = &data;

        BOOST_TEST_EQ((l.index(d)), 0);

        BOOST_TEST_EQ((dptr[l.index(d)]), 42); 
        BOOST_TEST_EQ(&(dptr[l.index(d)]), dptr); 

        dptr[l.index(d)] = 17;

        BOOST_TEST_EQ((dptr[l.index(d)]), 17); 
    }

    // 1D Static
    test_1d_static<1 >();
    test_1d_static<30>();

    // 1D Dynamic
    test_1d_dynamic<1 >();
    test_1d_dynamic<30>();

    // 2D Static
    test_2d_static<1,  1 >();

    test_2d_static<30, 1 >();
    test_2d_static<1,  30>();

    test_2d_static<30, 15>();
    test_2d_static<15, 30>();

    test_2d_static<30, 30>();

    // 2D Dynamic
    test_2d_dynamic<1,  1 >();

    test_2d_dynamic<30, 1 >();
    test_2d_dynamic<1,  30>();

    test_2d_dynamic<30, 15>();
    test_2d_dynamic<15, 30>();

    test_2d_dynamic<30, 30>();

    // 2D Mixed
    test_2d_mixed<1,  1 >();

    test_2d_mixed<30, 1 >();
    test_2d_mixed<1,  30>();

    test_2d_mixed<30, 15>();
    test_2d_mixed<15, 30>();

    test_2d_mixed<30, 30>();

    // 3D Static
    test_3d_static<1,  1,  1 >();

    test_3d_static<30, 1,  1 >();
    test_3d_static<1,  30, 1 >();
    test_3d_static<1,  1,  30>();

    test_3d_static<1,  30, 30>();
    test_3d_static<30, 1,  30>();
    test_3d_static<30, 30, 1 >();

    test_3d_static<30, 15, 15>();
    test_3d_static<15, 30, 15>();
    test_3d_static<15, 15, 30>();

    test_3d_static<15, 30, 30>();
    test_3d_static<30, 15, 30>();
    test_3d_static<30, 30, 15>();

    test_3d_static<30, 30, 30>();

    // 3D Dynamic
    test_3d_dynamic<1,  1,  1 >();

    test_3d_dynamic<30, 1,  1 >();
    test_3d_dynamic<1,  30, 1 >();
    test_3d_dynamic<1,  1,  30>();

    test_3d_dynamic<1,  30, 30>();
    test_3d_dynamic<30, 1,  30>();
    test_3d_dynamic<30, 30, 1 >();

    test_3d_dynamic<30, 15, 15>();
    test_3d_dynamic<15, 30, 15>();
    test_3d_dynamic<15, 15, 30>();

    test_3d_dynamic<15, 30, 30>();
    test_3d_dynamic<30, 15, 30>();
    test_3d_dynamic<30, 30, 15>();

    test_3d_dynamic<30, 30, 30>();

    return boost::report_errors();
}
