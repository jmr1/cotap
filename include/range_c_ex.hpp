
#ifndef BOOST_MPL_RANGE_C_EX_HPP_INCLUDED
#define BOOST_MPL_RANGE_C_EX_HPP_INCLUDED

// Copyright Janusz Rupar 2012
//
// Distributed under the Boost Software License, Version 1.0. 
//
// Boost Software License - Version 1.0 - August 17th, 2003
// 
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.


#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/aux_/range_c/front.hpp>
#include <boost/mpl/aux_/range_c/back.hpp>
#include <boost/mpl/aux_/range_c/size.hpp>
#include <boost/mpl/aux_/range_c/O1_size.hpp>
#include <boost/mpl/aux_/range_c/empty.hpp>
#include <boost/mpl/aux_/range_c/iterator.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {


template< typename N, typename T > struct r_iter_ex :
	r_iter<N>
{

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
	typedef r_iter_ex< typename mpl::plus< N, T >::type > next;
#endif
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename N, typename T
    >
struct next< r_iter_ex<N,T> >
{
	typedef r_iter_ex< typename mpl::plus< N, T >::type, T > type;
};

#endif




template<
      typename T
    , T Start
    , T Finish
	, T Step
    >
struct range_c_ex
{
    typedef aux::half_open_range_tag tag;
    typedef T value_type;
    typedef range_c_ex type;

    typedef integral_c<T,Start> start;
    typedef integral_c<T,Finish> finish;
	typedef integral_c<T,Step> step;

    typedef r_iter_ex<start, step> begin;
    typedef r_iter_ex<finish, step> end;
};

}}

#endif // BOOST_MPL_RANGE_C_EX_HPP_INCLUDED
