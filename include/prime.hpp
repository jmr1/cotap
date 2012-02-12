
#ifndef COTAP_PRIME_HPP_INCLUDED
#define COTAP_PRIME_HPP_INCLUDED

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


#include <boost/mpl/filter_view.hpp>

#include <boost/mpl/not_equal_to.hpp>
#include <boost/mpl/modulus.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/times.hpp>

#include <boost/mpl/alias.hpp>

#include "range_c_ex.hpp"



namespace prime
{
    template <typename ValueDiv>
    struct DIVISION_BY_ZERO_ERROR :
        mpl::not_equal_to< mpl::int_<0>, 
                           ValueDiv 
        >::type
    {};

    template <typename Value, typename ValueDiv>
    struct is_divisible :
        mpl::equal_to< mpl::int_<0>, 
                       mpl::modulus< Value, 
                                     ValueDiv 
                       > 
        >::type
    {
#ifdef _COTAP_ERROR_CHECK_
        BOOST_MPL_ASSERT((DIVISION_BY_ZERO_ERROR<ValueDiv>));
#endif //_COTAP_ERROR_CHECK_
    };

    template <typename T, T Value, T ValueDiv>
    struct is_divisible_c :
        mpl::equal_to< mpl::integral_c< T, 0>, 
                       mpl::modulus< mpl::integral_c< T, Value >, 
                                     mpl::integral_c< T, ValueDiv >
                       > 
        >::type
    {
#ifdef _COTAP_ERROR_CHECK_
        BOOST_MPL_ASSERT((DIVISION_BY_ZERO_ERROR<mpl::int_<ValueDiv> >));
#endif //_COTAP_ERROR_CHECK_
    };

    template <typename ValueDiv>
    struct DIVISOR_LESS_THAN_2_ERROR :
        mpl::greater< ValueDiv, 
                      mpl::int_<1> 
        >::type
    {};

    template <typename Value>
    struct DIVIDENT_LESS_THAN_2_ERROR :
        mpl::greater< Value, 
                      mpl::int_<1> 
        >::type
    {};

    template <typename Value, typename ValueDiv>
    struct DIVIDER_GREATER_OR_EQUAL_TO_DIVIDENT_ERROR :
        mpl::eval_if< mpl::greater< Value, mpl::int_<2> >,
                      mpl::less< ValueDiv, Value >,
                      mpl::true_ // not raising error here because 
                                 // dividents less than or equal to 2 
                                 // are caught by DIVIDENT_LESS_THAN_2_ERROR 
        >::type
    {};

    template <typename Value, typename ValueDiv = mpl::int_<2> >
    struct is_prime :
        mpl::eval_if< mpl::greater< mpl::times< ValueDiv, ValueDiv >, 
                                    Value 
                      >,
                      mpl::true_,
                      mpl::eval_if< is_divisible< Value, ValueDiv >,
                                    mpl::false_,
                                    is_prime< Value, 
                                              typename ValueDiv::next
                                    >
                      >
        >::type
    {
#ifdef _COTAP_ERROR_CHECK_
        BOOST_MPL_ASSERT((DIVISOR_LESS_THAN_2_ERROR<ValueDiv>));
        BOOST_MPL_ASSERT((DIVIDENT_LESS_THAN_2_ERROR<Value>));
        BOOST_MPL_ASSERT((DIVIDER_GREATER_OR_EQUAL_TO_DIVIDENT_ERROR<Value, ValueDiv>));
#endif //_COTAP_ERROR_CHECK_
    };

    template <typename T, T Value, T ValueDiv = 2 >
    struct is_prime_c :
        mpl::eval_if< mpl::greater< mpl::times< mpl::integral_c< T, ValueDiv >, 
                                                mpl::integral_c< T, ValueDiv > 
                                                >, 
                                    mpl::integral_c< T, Value > 
                                    >,
                      mpl::true_,
                      mpl::eval_if< is_divisible< mpl::integral_c< T, Value >, 
                                                  mpl::integral_c< T, ValueDiv > 
                                                  >,
                                    mpl::false_,
                                    is_prime< mpl::integral_c< T, Value >, 
                                              typename mpl::integral_c< T, ValueDiv >::next
                                              >
                      >
        >::type
    {
#ifdef _COTAP_ERROR_CHECK_
        BOOST_MPL_ASSERT((DIVISOR_LESS_THAN_2_ERROR<mpl::int_<ValueDiv> >));
        BOOST_MPL_ASSERT((DIVIDENT_LESS_THAN_2_ERROR<mpl::int_<Value> >));
        BOOST_MPL_ASSERT((DIVIDER_GREATER_OR_EQUAL_TO_DIVIDENT_ERROR<mpl::int_<Value>, mpl::int_<ValueDiv> >));
#endif //_COTAP_ERROR_CHECK_
    };

    template <typename Value>
    struct START_VALUE_EVEN_NUMBER_ERROR :
        mpl::not_equal_to< mpl::int_<0>, 
                           mpl::modulus< Value, 
                                         mpl::int_<2> 
                                         > 
        >::type
    {};

    template <typename Step>
    struct STEP_ODD_NUMBER_ERROR :
        mpl::equal_to< mpl::int_<0>, 
                       mpl::modulus< Step, 
                                     mpl::int_<2> 
                                     > 
        >::type
    {};

    template <typename T, T StartValue, T EndValue, T Step = 2>
    struct prime_gen_c :
        mpl::filter_view<
            typename mpl::range_c_ex< T, StartValue, EndValue, Step>,
            is_prime< mpl::_ >
        >::type
    {
#ifdef _COTAP_ERROR_CHECK_
        BOOST_MPL_ASSERT((START_VALUE_EVEN_NUMBER_ERROR<mpl::int_<StartValue> >));
        BOOST_MPL_ASSERT((STEP_ODD_NUMBER_ERROR<mpl::int_<Step> >));
#endif //_COTAP_ERROR_CHECK_
    };


}

#endif // COTAP_PRIME_HPP_INCLUDED