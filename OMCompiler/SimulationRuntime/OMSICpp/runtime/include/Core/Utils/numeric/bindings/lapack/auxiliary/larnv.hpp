//
// Copyright (c) 2002--2010
// Toon Knapen, Karl Meerbergen, Kresimir Fresl,
// Thomas Klimpel and Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// THIS FILE IS AUTOMATICALLY GENERATED
// PLEASE DO NOT EDIT!
//

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_AUXILIARY_LARNV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_AUXILIARY_LARNV_HPP

#include <boost/assert.hpp>
#include <Core/Utils/numeric/bindings/begin.hpp>
#include <Core/Utils/numeric/bindings/is_mutable.hpp>
#include <Core/Utils/numeric/bindings/remove_imaginary.hpp>
#include <Core/Utils/numeric/bindings/size.hpp>
#include <Core/Utils/numeric/bindings/stride.hpp>
#include <Core/Utils/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for larnv is the netlib-compatible backend.
//
#include <Core/Utils/numeric/bindings/lapack/detail/lapack.h>
#include <Core/Utils/numeric/bindings/lapack/detail/lapack_option.hpp>

namespace boost
{
    namespace numeric
    {
        namespace bindings
        {
            namespace lapack
            {
                //
                // The detail namespace contains value-type-overloaded functions that
                // dispatch to the appropriate back-end LAPACK-routine.
                //
                namespace detail
                {
                    //
                    // Overloaded function for dispatching to
                    // * netlib-compatible LAPACK backend (the default), and
                    // * float value-type.
                    //
                    inline std::ptrdiff_t larnv(const fortran_int_t idist, fortran_int_t* iseed,
                                                const fortran_int_t n, float* x)
                    {
                        fortran_int_t info(0);
                        LAPACK_SLARNV(&idist, iseed, &n, x);
                        return info;
                    }

                    //
                    // Overloaded function for dispatching to
                    // * netlib-compatible LAPACK backend (the default), and
                    // * double value-type.
                    //
                    inline std::ptrdiff_t larnv(const fortran_int_t idist, fortran_int_t* iseed,
                                                const fortran_int_t n, double* x)
                    {
                        fortran_int_t info(0);
                        LAPACK_DLARNV(&idist, iseed, &n, x);
                        return info;
                    }

                    //
                    // Overloaded function for dispatching to
                    // * netlib-compatible LAPACK backend (the default), and
                    // * complex<float> value-type.
                    //
                    inline std::ptrdiff_t larnv(const fortran_int_t idist, fortran_int_t* iseed,
                                                const fortran_int_t n, std::complex<float>* x)
                    {
                        fortran_int_t info(0);
                        LAPACK_CLARNV(&idist, iseed, &n, x);
                        return info;
                    }

                    //
                    // Overloaded function for dispatching to
                    // * netlib-compatible LAPACK backend (the default), and
                    // * complex<double> value-type.
                    //
                    inline std::ptrdiff_t larnv(const fortran_int_t idist, fortran_int_t* iseed,
                                                const fortran_int_t n, std::complex<double>* x)
                    {
                        fortran_int_t info(0);
                        LAPACK_ZLARNV(&idist, iseed, &n, x);
                        return info;
                    }
                } // namespace detail

                //
                // Value-type based template class. Use this class if you need a type
                // for dispatching to larnv.
                //
                template <typename Value>
                struct larnv_impl
                {
                    typedef Value value_type;
                    typedef typename remove_imaginary<Value>::type real_type;

                    //
                    // Static member function, that
                    // * Deduces the required arguments for dispatching to LAPACK, and
                    // * Asserts that most arguments make sense.
                    //
                    template <typename VectorISEED, typename VectorX>
                    static std::ptrdiff_t invoke(const fortran_int_t idist,
                                                 VectorISEED& iseed, const fortran_int_t n, VectorX& x)
                    {
                        namespace bindings = ::boost::numeric::bindings;
                        BOOST_STATIC_ASSERT((bindings::is_mutable<VectorISEED>::value));
                        BOOST_STATIC_ASSERT((bindings::is_mutable<VectorX>::value));
                        BOOST_ASSERT(bindings::size(iseed) >= 4);
                        BOOST_ASSERT(bindings::size(x) >= n);
                        return detail::larnv(idist, bindings::begin_value(iseed), n,
                                             bindings::begin_value(x));
                    }
                };


                //
                // Functions for direct use. These functions are overloaded for temporaries,
                // so that wrapped types can still be passed and used for write-access. In
                // addition, if applicable, they are overloaded for user-defined workspaces.
                // Calls to these functions are passed to the larnv_impl classes. In the
                // documentation, most overloads are collapsed to avoid a large number of
                // prototypes which are very similar.
                //

                //
                // Overloaded function for larnv. Its overload differs for
                //
                template <typename VectorISEED, typename VectorX>
                inline std::ptrdiff_t larnv(const fortran_int_t idist,
                                            VectorISEED& iseed, const fortran_int_t n, VectorX& x)
                {
                    return larnv_impl<typename bindings::value_type<
                        VectorX>::type>::invoke(idist, iseed, n, x);
                }
            } // namespace lapack
        } // namespace bindings
    } // namespace numeric
} // namespace boost

#endif