/* This file is part of COVISE.

   You can use it under the terms of the GNU Lesser General Public License
   version 2.1 or later, see lgpl-2.1.txt.

 * License: LGPL 2+ */

/* -*- c++ -*- (enables emacs c++ mode)                                    */
/* *********************************************************************** */
/*                                                                         */
/* Library :  Generic Matrix Methods  (gmm)                                */
/* File    :  gmm_blas_interface.h : specialization of operations for      */
/*                    dense matrices calling blas.                         */
/*     									   */
/* Date : October 7, 2003.                                                 */
/* Authors : Caroline Lecalvez, Caroline.Lecalvez@gmm.insa-tlse.fr         */
/*           Yves Renard, Yves.Renard@gmm.insa-tlse.fr                     */
/*                                                                         */
/* *********************************************************************** */
/*                                                                         */
/* Copyright (C) 2003-2004  Yves Renard.                                   */
/*                                                                         */
/* This file is a part of GMM++                                            */
/*                                                                         */
/* This program is free software; you can redistribute it and/or modify    */
/* it under the terms of the GNU Lesser General Public License as          */
/* published by the Free Software Foundation; version 2.1 of the License.  */
/*                                                                         */
/* This program is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           */
/* GNU Lesser General Public License for more details.                     */
/*                                                                         */
/* You should have received a copy of the GNU Lesser General Public        */
/* License along with this program; if not, write to the Free Software     */
/* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,  */
/* USA.                                                                    */
/*                                                                         */
/* *********************************************************************** */

#if defined(GETFEM_USES_BLAS) || defined(GMM_USES_BLAS) \
    || defined(GMM_USES_LAPACK) || defined(GMM_USES_ATLAS)

#ifndef GMM_BLAS_INTERFACE_H
#define GMM_BLAS_INTERFACE_H

#include <ext/gmm/gmm_blas.h>
#include <ext/gmm/gmm_interface.h>
#include <ext/gmm/gmm_matrix.h>

namespace gmm
{

#define GMMLAPACK_TRACE(f)
// #define GMMLAPACK_TRACE(f) cout << "function " << f << " called" << endl;

/* ********************************************************************* */
/* Operations interfaced for T = float, double, std::complex<float>      */
/*    or std::complex<double> :                                          */
/*                                                                       */
/* vect_norm2(std::vector<T>)                                            */
/*                                                                       */
/* vect_sp(std::vector<T>, std::vector<T>)                               */
/* vect_sp(scaled(std::vector<T>), std::vector<T>)                       */
/* vect_sp(std::vector<T>, scaled(std::vector<T>))                       */
/* vect_sp(scaled(std::vector<T>), scaled(std::vector<T>))               */
/*                                                                       */
/* vect_hp(std::vector<T>, std::vector<T>)                               */
/* vect_hp(scaled(std::vector<T>), std::vector<T>)                       */
/* vect_hp(std::vector<T>, scaled(std::vector<T>))                       */
/* vect_hp(scaled(std::vector<T>), scaled(std::vector<T>))               */
/*                                                                       */
/* add(std::vector<T>, std::vector<T>)                                   */
/* add(scaled(std::vector<T>, a), std::vector<T>)                        */
/*                                                                       */
/* mult(dense_matrix<T>, dense_matrix<T>, dense_matrix<T>)               */
/* mult(transposed(dense_matrix<T>), dense_matrix<T>, dense_matrix<T>)   */
/* mult(dense_matrix<T>, transposed(dense_matrix<T>), dense_matrix<T>)   */
/* mult(transposed(dense_matrix<T>), transposed(dense_matrix<T>),        */
/*      dense_matrix<T>)                                                 */
/* mult(conjugated(dense_matrix<T>), dense_matrix<T>, dense_matrix<T>)   */
/* mult(dense_matrix<T>, conjugated(dense_matrix<T>), dense_matrix<T>)   */
/* mult(conjugated(dense_matrix<T>), conjugated(dense_matrix<T>),        */
/*      dense_matrix<T>)                                                 */
/*                                                                       */
/* mult(dense_matrix<T>, std::vector<T>, std::vector<T>)                 */
/* mult(transposed(dense_matrix<T>), std::vector<T>, std::vector<T>)     */
/* mult(conjugated(dense_matrix<T>), std::vector<T>, std::vector<T>)     */
/* mult(dense_matrix<T>, scaled(std::vector<T>), std::vector<T>)         */
/* mult(transposed(dense_matrix<T>), scaled(std::vector<T>),             */
/*      std::vector<T>)                                                  */
/* mult(conjugated(dense_matrix<T>), scaled(std::vector<T>),             */
/*      std::vector<T>)                                                  */
/*                                                                       */
/* mult_add(dense_matrix<T>, std::vector<T>, std::vector<T>)             */
/* mult_add(transposed(dense_matrix<T>), std::vector<T>, std::vector<T>) */
/* mult_add(conjugated(dense_matrix<T>), std::vector<T>, std::vector<T>) */
/* mult_add(dense_matrix<T>, scaled(std::vector<T>), std::vector<T>)     */
/* mult_add(transposed(dense_matrix<T>), scaled(std::vector<T>),         */
/*          std::vector<T>)                                              */
/* mult_add(conjugated(dense_matrix<T>), scaled(std::vector<T>),         */
/*          std::vector<T>)                                              */
/*                                                                       */
/* mult(dense_matrix<T>, std::vector<T>, std::vector<T>, std::vector<T>) */
/* mult(transposed(dense_matrix<T>), std::vector<T>, std::vector<T>,     */
/*      std::vector<T>)                                                  */
/* mult(conjugated(dense_matrix<T>), std::vector<T>, std::vector<T>,     */
/*      std::vector<T>)                                                  */
/* mult(dense_matrix<T>, scaled(std::vector<T>), std::vector<T>,         */
/*      std::vector<T>)                                                  */
/* mult(transposed(dense_matrix<T>), scaled(std::vector<T>),             */
/*      std::vector<T>, std::vector<T>)                                  */
/* mult(conjugated(dense_matrix<T>), scaled(std::vector<T>),             */
/*      std::vector<T>, std::vector<T>)                                  */
/* mult(dense_matrix<T>, std::vector<T>, scaled(std::vector<T>),         */
/*      std::vector<T>)                                                  */
/* mult(transposed(dense_matrix<T>), std::vector<T>,                     */
/*      scaled(std::vector<T>), std::vector<T>)                          */
/* mult(conjugated(dense_matrix<T>), std::vector<T>,                     */
/*      scaled(std::vector<T>), std::vector<T>)                          */
/* mult(dense_matrix<T>, scaled(std::vector<T>), scaled(std::vector<T>), */
/*   std::vector<T>)                                                     */
/* mult(transposed(dense_matrix<T>), scaled(std::vector<T>),             */
/*      scaled(std::vector<T>), std::vector<T>)                          */
/* mult(conjugated(dense_matrix<T>), scaled(std::vector<T>),             */
/*      scaled(std::vector<T>), std::vector<T>)                          */
/*                                                                       */
/* lower_tri_solve(dense_matrix<T>, std::vector<T>, k, b)                */
/* upper_tri_solve(dense_matrix<T>, std::vector<T>, k, b)                */
/* lower_tri_solve(transposed(dense_matrix<T>), std::vector<T>, k, b)    */
/* upper_tri_solve(transposed(dense_matrix<T>), std::vector<T>, k, b)    */
/* lower_tri_solve(conjugated(dense_matrix<T>), std::vector<T>, k, b)    */
/* upper_tri_solve(conjugated(dense_matrix<T>), std::vector<T>, k, b)    */
/*                                                                       */
/* ********************************************************************* */

/* ********************************************************************* */
/* Basic defines.                                                        */
/* ********************************************************************* */

#define BLAS_S float
#define BLAS_D double
#define BLAS_C std::complex<float>
#define BLAS_Z std::complex<double>

/* ********************************************************************* */
/* BLAS functions used.                                                  */
/* ********************************************************************* */
extern "C" void daxpy_(const int *n, const double *alpha, const double *x, const int *incx, double *y, const int *incy);
extern "C" {
void sgemm_(...);
void dgemm_(...);
void cgemm_(...);
void zgemm_(...);
void sgemv_(...);
void dgemv_(...);
void cgemv_(...);
void zgemv_(...);
void strsv_(...);
void dtrsv_(...);
void ctrsv_(...);
void ztrsv_(...);
void saxpy_(...); /*void daxpy_(...); */
void caxpy_(...);
void zaxpy_(...);
BLAS_S sdot_(...);
BLAS_D ddot_(...);
BLAS_C cdotu_(...);
BLAS_Z zdotu_(...);
BLAS_C cdotc_(...);
BLAS_Z zdotc_(...);
BLAS_S snrm2_(...);
BLAS_D dnrm2_(...);
BLAS_S scnrm2_(...);
BLAS_D dznrm2_(...);
}

/* ********************************************************************* */
/* vect_norm2(x).                                                        */
/* ********************************************************************* */

#define nrm2_interface(param1, trans1, blas_name, base_type)                      \
    inline number_traits<base_type>::magnitude_type vect_norm2(param1(base_type)) \
    {                                                                             \
        GMMLAPACK_TRACE("nrm2_interface");                                        \
        int inc(1), n(vect_size(x));                                              \
        trans1(base_type);                                                        \
        return blas_name(&n, &x[0], &inc);                                        \
    }

#define nrm2_p1(base_type) const std::vector<base_type> &x
#define nrm2_trans1(base_type)

nrm2_interface(nrm2_p1, nrm2_trans1, snrm2_, BLAS_S)
    nrm2_interface(nrm2_p1, nrm2_trans1, dnrm2_, BLAS_D)
        nrm2_interface(nrm2_p1, nrm2_trans1, scnrm2_, BLAS_C)
            nrm2_interface(nrm2_p1, nrm2_trans1, dznrm2_, BLAS_Z)

/* ********************************************************************* */
/* vect_sp(x, y).                                                        */
/* ********************************************************************* */

#define dot_interface(param1, trans1, mult1, param2, trans2, mult2, blas_name, base_type) \
    inline base_type vect_sp(param1(base_type), param2(base_type))                        \
    {                                                                                     \
        GMMLAPACK_TRACE("dot_interface");                                                 \
        trans1(base_type);                                                                \
        trans2(base_type);                                                                \
        int inc(1), n(vect_size(y));                                                      \
        return mult1 mult2 blas_name(&n, &x[0], &inc, &y[0], &inc);                       \
    }

#define dot_p1(base_type) const std::vector<base_type> &x
#define dot_trans1(base_type)
#define dot_p1_s(base_type) \
    const scaled_vector_const_ref<std::vector<base_type>, base_type> &x_
#define dot_trans1_s(base_type)                                                             \
    std::vector<base_type> &x = const_cast<std::vector<base_type> &>(*(linalg_origin(x_))); \
    base_type a(x_.r)

#define dot_p2(base_type) const std::vector<base_type> &y
#define dot_trans2(base_type)
#define dot_p2_s(base_type) \
    const scaled_vector_const_ref<std::vector<base_type>, base_type> &y_
#define dot_trans2_s(base_type)                                                             \
    std::vector<base_type> &y = const_cast<std::vector<base_type> &>(*(linalg_origin(y_))); \
    base_type b(y_.r)

                dot_interface(dot_p1, dot_trans1, , dot_p2, dot_trans2, , sdot_, BLAS_S)
                    dot_interface(dot_p1, dot_trans1, , dot_p2, dot_trans2, , ddot_, BLAS_D)
                        dot_interface(dot_p1, dot_trans1, , dot_p2, dot_trans2, , cdotu_, BLAS_C)
                            dot_interface(dot_p1, dot_trans1, , dot_p2, dot_trans2, , zdotu_, BLAS_Z)

                                dot_interface(dot_p1_s, dot_trans1_s, a *, dot_p2, dot_trans2, , sdot_, BLAS_S)
                                    dot_interface(dot_p1_s, dot_trans1_s, a *, dot_p2, dot_trans2, , ddot_, BLAS_D)
                                        dot_interface(dot_p1_s, dot_trans1_s, a *, dot_p2, dot_trans2, , cdotu_, BLAS_C)
                                            dot_interface(dot_p1_s, dot_trans1_s, a *, dot_p2, dot_trans2, , zdotu_, BLAS_Z)

                                                dot_interface(dot_p1, dot_trans1, , dot_p2_s, dot_trans2_s, b *, sdot_, BLAS_S)
                                                    dot_interface(dot_p1, dot_trans1, , dot_p2_s, dot_trans2_s, b *, ddot_, BLAS_D)
                                                        dot_interface(dot_p1, dot_trans1, , dot_p2_s, dot_trans2_s, b *, cdotu_, BLAS_C)
                                                            dot_interface(dot_p1, dot_trans1, , dot_p2_s, dot_trans2_s, b *, zdotu_, BLAS_Z)

                                                                dot_interface(dot_p1_s, dot_trans1_s, a *, dot_p2_s, dot_trans2_s, b *, sdot_,
                                                                              BLAS_S)
                                                                    dot_interface(dot_p1_s, dot_trans1_s, a *, dot_p2_s, dot_trans2_s, b *, ddot_,
                                                                                  BLAS_D)
                                                                        dot_interface(dot_p1_s, dot_trans1_s, a *, dot_p2_s, dot_trans2_s, b *, cdotu_,
                                                                                      BLAS_C)
                                                                            dot_interface(dot_p1_s, dot_trans1_s, a *, dot_p2_s, dot_trans2_s, b *, zdotu_,
                                                                                          BLAS_Z)

/* ********************************************************************* */
/* vect_hp(x, y).                                                        */
/* ********************************************************************* */

#define dotc_interface(param1, trans1, mult1, param2, trans2, mult2, blas_name, base_type) \
    inline base_type vect_hp(param1(base_type), param2(base_type))                         \
    {                                                                                      \
        GMMLAPACK_TRACE("dotc_interface");                                                 \
        trans1(base_type);                                                                 \
        trans2(base_type);                                                                 \
        int inc(1), n(vect_size(y));                                                       \
        return mult1 mult2 blas_name(&n, &x[0], &inc, &y[0], &inc);                        \
    }

#define dotc_p1(base_type) const std::vector<base_type> &x
#define dotc_trans1(base_type)
#define dotc_p1_s(base_type) \
    const scaled_vector_const_ref<std::vector<base_type>, base_type> &x_
#define dotc_trans1_s(base_type)                                                            \
    std::vector<base_type> &x = const_cast<std::vector<base_type> &>(*(linalg_origin(x_))); \
    base_type a(x_.r)

#define dotc_p2(base_type) const std::vector<base_type> &y
#define dotc_trans2(base_type)
#define dotc_p2_s(base_type) \
    const scaled_vector_const_ref<std::vector<base_type>, base_type> &y_
#define dotc_trans2_s(base_type)                                                            \
    std::vector<base_type> &y = const_cast<std::vector<base_type> &>(*(linalg_origin(y_))); \
    base_type b(gmm::conj(y_.r))

                                                                                dotc_interface(dotc_p1, dotc_trans1, , dotc_p2, dotc_trans2, , sdot_, BLAS_S)
                                                                                    dotc_interface(dotc_p1, dotc_trans1, , dotc_p2, dotc_trans2, , ddot_, BLAS_D)
                                                                                        dotc_interface(dotc_p1, dotc_trans1, , dotc_p2, dotc_trans2, , cdotc_, BLAS_C)
                                                                                            dotc_interface(dotc_p1, dotc_trans1, , dotc_p2, dotc_trans2, , zdotc_, BLAS_Z)

                                                                                                dotc_interface(dotc_p1_s, dotc_trans1_s, a *, dotc_p2, dotc_trans2, , sdot_,
                                                                                                               BLAS_S)
                                                                                                    dotc_interface(dotc_p1_s, dotc_trans1_s, a *, dotc_p2, dotc_trans2, , ddot_,
                                                                                                                   BLAS_D)
                                                                                                        dotc_interface(dotc_p1_s, dotc_trans1_s, a *, dotc_p2, dotc_trans2, , cdotc_,
                                                                                                                       BLAS_C)
                                                                                                            dotc_interface(dotc_p1_s, dotc_trans1_s, a *, dotc_p2, dotc_trans2, , zdotc_,
                                                                                                                           BLAS_Z)

                                                                                                                dotc_interface(dotc_p1, dotc_trans1, , dotc_p2_s, dotc_trans2_s, b *, sdot_,
                                                                                                                               BLAS_S)
                                                                                                                    dotc_interface(dotc_p1, dotc_trans1, , dotc_p2_s, dotc_trans2_s, b *, ddot_,
                                                                                                                                   BLAS_D)
                                                                                                                        dotc_interface(dotc_p1, dotc_trans1, , dotc_p2_s, dotc_trans2_s, b *, cdotc_,
                                                                                                                                       BLAS_C)
                                                                                                                            dotc_interface(dotc_p1, dotc_trans1, , dotc_p2_s, dotc_trans2_s, b *, zdotc_,
                                                                                                                                           BLAS_Z)

                                                                                                                                dotc_interface(dotc_p1_s, dotc_trans1_s, a *, dotc_p2_s, dotc_trans2_s, b *, sdot_,
                                                                                                                                               BLAS_S)
                                                                                                                                    dotc_interface(dotc_p1_s, dotc_trans1_s, a *, dotc_p2_s, dotc_trans2_s, b *, ddot_,
                                                                                                                                                   BLAS_D)
                                                                                                                                        dotc_interface(dotc_p1_s, dotc_trans1_s, a *, dotc_p2_s, dotc_trans2_s, b *, cdotc_,
                                                                                                                                                       BLAS_C)
                                                                                                                                            dotc_interface(dotc_p1_s, dotc_trans1_s, a *, dotc_p2_s, dotc_trans2_s, b *, zdotc_,
                                                                                                                                                           BLAS_Z)

/* ********************************************************************* */
/* add(x, y).                                                            */
/* ********************************************************************* */

#define axpy_interface(param1, trans1, blas_name, base_type)      \
    inline void add(param1(base_type), std::vector<base_type> &y) \
    {                                                             \
        GMMLAPACK_TRACE("axpy_interface");                        \
        int inc(1), n(vect_size(y));                              \
        trans1(base_type);                                        \
        blas_name(&n, &a, &x[0], &inc, &y[0], &inc);              \
    }

#define axpy_p1(base_type) const std::vector<base_type> &x
#define axpy_trans1(base_type) base_type a(1)
#define axpy_p1_s(base_type) \
    const scaled_vector_const_ref<std::vector<base_type>, base_type> &x_
#define axpy_trans1_s(base_type)                                                            \
    std::vector<base_type> &x = const_cast<std::vector<base_type> &>(*(linalg_origin(x_))); \
    base_type a(x_.r)

                                                                                                                                                axpy_interface(axpy_p1, axpy_trans1, saxpy_, BLAS_S)
                                                                                                                                                    axpy_interface(axpy_p1, axpy_trans1, daxpy_, BLAS_D)
                                                                                                                                                        axpy_interface(axpy_p1, axpy_trans1, caxpy_, BLAS_C)
                                                                                                                                                            axpy_interface(axpy_p1, axpy_trans1, zaxpy_, BLAS_Z)

                                                                                                                                                                axpy_interface(axpy_p1_s, axpy_trans1_s, saxpy_, BLAS_S)
                                                                                                                                                                    axpy_interface(axpy_p1_s, axpy_trans1_s, daxpy_, BLAS_D)
                                                                                                                                                                        axpy_interface(axpy_p1_s, axpy_trans1_s, caxpy_, BLAS_C)
                                                                                                                                                                            axpy_interface(axpy_p1_s, axpy_trans1_s, zaxpy_, BLAS_Z)

/* ********************************************************************* */
/* mult_add(A, x, z).                                                    */
/* ********************************************************************* */

#define gemv_interface(param1, trans1, param2, trans2, blas_name, base_type, orien)                   \
    inline void mult_add_spec(param1(base_type), param2(base_type), std::vector<base_type> &z, orien) \
    {                                                                                                 \
        GMMLAPACK_TRACE("gemv_interface");                                                            \
        trans1(base_type);                                                                            \
        trans2(base_type);                                                                            \
        base_type beta(1);                                                                            \
        int m(mat_nrows(A)), lda(m), n(mat_ncols(A)), inc(1);                                         \
        if (m && n)                                                                                   \
            blas_name(&t, &m, &n, &alpha, &A(0, 0), &lda, &x[0], &inc, &beta, &z[0], &inc);           \
        else                                                                                          \
            gmm::clear(z);                                                                            \
    }

// First parameter
#define gem_p1_n(base_type) const dense_matrix<base_type> &A
#define gem_trans1_n(base_type) const char t = 'N'
#define gem_p1_t(base_type) \
    const transposed_col_ref<dense_matrix<base_type> *> &A_
#define gem_trans1_t(base_type)                                                               \
    dense_matrix<base_type> &A = const_cast<dense_matrix<base_type> &>(*(linalg_origin(A_))); \
    const char t = 'T'
#define gem_p1_tc(base_type) \
    const transposed_col_ref<const dense_matrix<base_type> *> &A_
#define gem_p1_c(base_type) \
    const conjugated_col_matrix_const_ref<dense_matrix<base_type> > &A_
#define gem_trans1_c(base_type)                                                               \
    dense_matrix<base_type> &A = const_cast<dense_matrix<base_type> &>(*(linalg_origin(A_))); \
    const char t = 'C'

// second parameter
#define gemv_p2_n(base_type) const std::vector<base_type> &x
#define gemv_trans2_n(base_type) base_type alpha(1)
#define gemv_p2_s(base_type) \
    const scaled_vector_const_ref<std::vector<base_type>, base_type> &x_
#define gemv_trans2_s(base_type)                                                            \
    std::vector<base_type> &x = const_cast<std::vector<base_type> &>(*(linalg_origin(x_))); \
    base_type alpha(x_.r)

                                                                                                                                                                                // Z <- AX + Z.
    gemv_interface(gem_p1_n, gem_trans1_n, gemv_p2_n, gemv_trans2_n, sgemv_,
                   BLAS_S, col_major)
        gemv_interface(gem_p1_n, gem_trans1_n, gemv_p2_n, gemv_trans2_n, dgemv_,
                       BLAS_D, col_major)
            gemv_interface(gem_p1_n, gem_trans1_n, gemv_p2_n, gemv_trans2_n, cgemv_,
                           BLAS_C, col_major)
                gemv_interface(gem_p1_n, gem_trans1_n, gemv_p2_n, gemv_trans2_n, zgemv_,
                               BLAS_Z, col_major)

                    // Z <- transposed(A)X + Z.
    gemv_interface(gem_p1_t, gem_trans1_t, gemv_p2_n, gemv_trans2_n, sgemv_,
                   BLAS_S, row_major)
        gemv_interface(gem_p1_t, gem_trans1_t, gemv_p2_n, gemv_trans2_n, dgemv_,
                       BLAS_D, row_major)
            gemv_interface(gem_p1_t, gem_trans1_t, gemv_p2_n, gemv_trans2_n, cgemv_,
                           BLAS_C, row_major)
                gemv_interface(gem_p1_t, gem_trans1_t, gemv_p2_n, gemv_trans2_n, zgemv_,
                               BLAS_Z, row_major)

                    // Z <- transposed(const A)X + Z.
    gemv_interface(gem_p1_tc, gem_trans1_t, gemv_p2_n, gemv_trans2_n, sgemv_,
                   BLAS_S, row_major)
        gemv_interface(gem_p1_tc, gem_trans1_t, gemv_p2_n, gemv_trans2_n, dgemv_,
                       BLAS_D, row_major)
            gemv_interface(gem_p1_tc, gem_trans1_t, gemv_p2_n, gemv_trans2_n, cgemv_,
                           BLAS_C, row_major)
                gemv_interface(gem_p1_tc, gem_trans1_t, gemv_p2_n, gemv_trans2_n, zgemv_,
                               BLAS_Z, row_major)

                    // Z <- conjugated(A)X + Z.
    gemv_interface(gem_p1_c, gem_trans1_c, gemv_p2_n, gemv_trans2_n, sgemv_,
                   BLAS_S, row_major)
        gemv_interface(gem_p1_c, gem_trans1_c, gemv_p2_n, gemv_trans2_n, dgemv_,
                       BLAS_D, row_major)
            gemv_interface(gem_p1_c, gem_trans1_c, gemv_p2_n, gemv_trans2_n, cgemv_,
                           BLAS_C, row_major)
                gemv_interface(gem_p1_c, gem_trans1_c, gemv_p2_n, gemv_trans2_n, zgemv_,
                               BLAS_Z, row_major)

                    // Z <- A scaled(X) + Z.
    gemv_interface(gem_p1_n, gem_trans1_n, gemv_p2_s, gemv_trans2_s, sgemv_,
                   BLAS_S, col_major)
        gemv_interface(gem_p1_n, gem_trans1_n, gemv_p2_s, gemv_trans2_s, dgemv_,
                       BLAS_D, col_major)
            gemv_interface(gem_p1_n, gem_trans1_n, gemv_p2_s, gemv_trans2_s, cgemv_,
                           BLAS_C, col_major)
                gemv_interface(gem_p1_n, gem_trans1_n, gemv_p2_s, gemv_trans2_s, zgemv_,
                               BLAS_Z, col_major)

                    // Z <- transposed(A) scaled(X) + Z.
    gemv_interface(gem_p1_t, gem_trans1_t, gemv_p2_s, gemv_trans2_s, sgemv_,
                   BLAS_S, row_major)
        gemv_interface(gem_p1_t, gem_trans1_t, gemv_p2_s, gemv_trans2_s, dgemv_,
                       BLAS_D, row_major)
            gemv_interface(gem_p1_t, gem_trans1_t, gemv_p2_s, gemv_trans2_s, cgemv_,
                           BLAS_C, row_major)
                gemv_interface(gem_p1_t, gem_trans1_t, gemv_p2_s, gemv_trans2_s, zgemv_,
                               BLAS_Z, row_major)

                    // Z <- transposed(const A) scaled(X) + Z.
    gemv_interface(gem_p1_tc, gem_trans1_t, gemv_p2_s, gemv_trans2_s, sgemv_,
                   BLAS_S, row_major)
        gemv_interface(gem_p1_tc, gem_trans1_t, gemv_p2_s, gemv_trans2_s, dgemv_,
                       BLAS_D, row_major)
            gemv_interface(gem_p1_tc, gem_trans1_t, gemv_p2_s, gemv_trans2_s, cgemv_,
                           BLAS_C, row_major)
                gemv_interface(gem_p1_tc, gem_trans1_t, gemv_p2_s, gemv_trans2_s, zgemv_,
                               BLAS_Z, row_major)

                    // Z <- conjugated(A) scaled(X) + Z.
    gemv_interface(gem_p1_c, gem_trans1_c, gemv_p2_s, gemv_trans2_s, sgemv_,
                   BLAS_S, row_major)
        gemv_interface(gem_p1_c, gem_trans1_c, gemv_p2_s, gemv_trans2_s, dgemv_,
                       BLAS_D, row_major)
            gemv_interface(gem_p1_c, gem_trans1_c, gemv_p2_s, gemv_trans2_s, cgemv_,
                           BLAS_C, row_major)
                gemv_interface(gem_p1_c, gem_trans1_c, gemv_p2_s, gemv_trans2_s, zgemv_,
                               BLAS_Z, row_major)

/* ********************************************************************* */
/* mult(A, x, y).                                                        */
/* ********************************************************************* */

#define gemv_interface2(param1, trans1, param2, trans2, blas_name, base_type, orien)              \
    inline void mult_spec(param1(base_type), param2(base_type), std::vector<base_type> &z, orien) \
    {                                                                                             \
        GMMLAPACK_TRACE("gemv_interface2");                                                       \
        trans1(base_type);                                                                        \
        trans2(base_type);                                                                        \
        base_type beta(0);                                                                        \
        int m(mat_nrows(A)), lda(m), n(mat_ncols(A)), inc(1);                                     \
        if (m && n)                                                                               \
            blas_name(&t, &m, &n, &alpha, &A(0, 0), &lda, &x[0], &inc, &beta, &z[0], &inc);       \
        else                                                                                      \
            gmm::clear(z);                                                                        \
    }

                    // Y <- AX.
    gemv_interface2(gem_p1_n, gem_trans1_n, gemv_p2_n, gemv_trans2_n, sgemv_,
                    BLAS_S, col_major)
        gemv_interface2(gem_p1_n, gem_trans1_n, gemv_p2_n, gemv_trans2_n, dgemv_,
                        BLAS_D, col_major)
            gemv_interface2(gem_p1_n, gem_trans1_n, gemv_p2_n, gemv_trans2_n, cgemv_,
                            BLAS_C, col_major)
                gemv_interface2(gem_p1_n, gem_trans1_n, gemv_p2_n, gemv_trans2_n, zgemv_,
                                BLAS_Z, col_major)

                    // Y <- transposed(A)X.
    gemv_interface2(gem_p1_t, gem_trans1_t, gemv_p2_n, gemv_trans2_n, sgemv_,
                    BLAS_S, row_major)
        gemv_interface2(gem_p1_t, gem_trans1_t, gemv_p2_n, gemv_trans2_n, dgemv_,
                        BLAS_D, row_major)
            gemv_interface2(gem_p1_t, gem_trans1_t, gemv_p2_n, gemv_trans2_n, cgemv_,
                            BLAS_C, row_major)
                gemv_interface2(gem_p1_t, gem_trans1_t, gemv_p2_n, gemv_trans2_n, zgemv_,
                                BLAS_Z, row_major)

                    // Y <- transposed(const A)X.
    gemv_interface2(gem_p1_tc, gem_trans1_t, gemv_p2_n, gemv_trans2_n, sgemv_,
                    BLAS_S, row_major)
        gemv_interface2(gem_p1_tc, gem_trans1_t, gemv_p2_n, gemv_trans2_n, dgemv_,
                        BLAS_D, row_major)
            gemv_interface2(gem_p1_tc, gem_trans1_t, gemv_p2_n, gemv_trans2_n, cgemv_,
                            BLAS_C, row_major)
                gemv_interface2(gem_p1_tc, gem_trans1_t, gemv_p2_n, gemv_trans2_n, zgemv_,
                                BLAS_Z, row_major)

                    // Y <- conjugated(A)X.
    gemv_interface2(gem_p1_c, gem_trans1_c, gemv_p2_n, gemv_trans2_n, sgemv_,
                    BLAS_S, row_major)
        gemv_interface2(gem_p1_c, gem_trans1_c, gemv_p2_n, gemv_trans2_n, dgemv_,
                        BLAS_D, row_major)
            gemv_interface2(gem_p1_c, gem_trans1_c, gemv_p2_n, gemv_trans2_n, cgemv_,
                            BLAS_C, row_major)
                gemv_interface2(gem_p1_c, gem_trans1_c, gemv_p2_n, gemv_trans2_n, zgemv_,
                                BLAS_Z, row_major)

                    // Y <- A scaled(X).
    gemv_interface2(gem_p1_n, gem_trans1_n, gemv_p2_s, gemv_trans2_s, sgemv_,
                    BLAS_S, col_major)
        gemv_interface2(gem_p1_n, gem_trans1_n, gemv_p2_s, gemv_trans2_s, dgemv_,
                        BLAS_D, col_major)
            gemv_interface2(gem_p1_n, gem_trans1_n, gemv_p2_s, gemv_trans2_s, cgemv_,
                            BLAS_C, col_major)
                gemv_interface2(gem_p1_n, gem_trans1_n, gemv_p2_s, gemv_trans2_s, zgemv_,
                                BLAS_Z, col_major)

                    // Y <- transposed(A) scaled(X).
    gemv_interface2(gem_p1_t, gem_trans1_t, gemv_p2_s, gemv_trans2_s, sgemv_,
                    BLAS_S, row_major)
        gemv_interface2(gem_p1_t, gem_trans1_t, gemv_p2_s, gemv_trans2_s, dgemv_,
                        BLAS_D, row_major)
            gemv_interface2(gem_p1_t, gem_trans1_t, gemv_p2_s, gemv_trans2_s, cgemv_,
                            BLAS_C, row_major)
                gemv_interface2(gem_p1_t, gem_trans1_t, gemv_p2_s, gemv_trans2_s, zgemv_,
                                BLAS_Z, row_major)

                    // Y <- transposed(const A) scaled(X).
    gemv_interface2(gem_p1_tc, gem_trans1_t, gemv_p2_s, gemv_trans2_s, sgemv_,
                    BLAS_S, row_major)
        gemv_interface2(gem_p1_tc, gem_trans1_t, gemv_p2_s, gemv_trans2_s, dgemv_,
                        BLAS_D, row_major)
            gemv_interface2(gem_p1_tc, gem_trans1_t, gemv_p2_s, gemv_trans2_s, cgemv_,
                            BLAS_C, row_major)
                gemv_interface2(gem_p1_tc, gem_trans1_t, gemv_p2_s, gemv_trans2_s, zgemv_,
                                BLAS_Z, row_major)

                    // Y <- conjugated(A) scaled(X).
    gemv_interface2(gem_p1_c, gem_trans1_c, gemv_p2_s, gemv_trans2_s, sgemv_,
                    BLAS_S, row_major)
        gemv_interface2(gem_p1_c, gem_trans1_c, gemv_p2_s, gemv_trans2_s, dgemv_,
                        BLAS_D, row_major)
            gemv_interface2(gem_p1_c, gem_trans1_c, gemv_p2_s, gemv_trans2_s, cgemv_,
                            BLAS_C, row_major)
                gemv_interface2(gem_p1_c, gem_trans1_c, gemv_p2_s, gemv_trans2_s, zgemv_,
                                BLAS_Z, row_major)

/* ********************************************************************* */
/* dense matrix x dense matrix multiplication.                           */
/* ********************************************************************* */

#define gemm_interface_nn(blas_name, base_type)                                                                                              \
    inline void mult_spec(const dense_matrix<base_type> &A, const dense_matrix<base_type> &B, dense_matrix<base_type> &C, c_mult, col_major) \
    {                                                                                                                                        \
        GMMLAPACK_TRACE("gemm_interface_nn");                                                                                                \
        const char t = 'N';                                                                                                                  \
        int m = mat_nrows(A), lda = m, k = mat_ncols(A), n = mat_ncols(B);                                                                   \
        int ldb = k, ldc = m;                                                                                                                \
        base_type alpha(1), beta(0);                                                                                                         \
        if (m && k && n)                                                                                                                     \
            blas_name(&t, &t, &m, &n, &k, &alpha, &A(0, 0), &lda, &B(0, 0), &ldb, &beta, &C(0, 0), &ldc);                                    \
        else                                                                                                                                 \
            gmm::clear(C);                                                                                                                   \
    }

                    gemm_interface_nn(sgemm_, BLAS_S)
                        gemm_interface_nn(dgemm_, BLAS_D)
                            gemm_interface_nn(cgemm_, BLAS_C)
                                gemm_interface_nn(zgemm_, BLAS_Z)

/* ********************************************************************* */
/* transposed(dense matrix) x dense matrix multiplication.               */
/* ********************************************************************* */

#define gemm_interface_tn(blas_name, base_type, is_const)                                                                                                         \
    inline void mult_spec(const transposed_col_ref<is_const dense_matrix<base_type> *> &A_, const dense_matrix<base_type> &B, dense_matrix<base_type> &C, rcmult) \
    {                                                                                                                                                             \
        GMMLAPACK_TRACE("gemm_interface_tn");                                                                                                                     \
        dense_matrix<base_type> &A = const_cast<dense_matrix<base_type> &>(*(linalg_origin(A_)));                                                                 \
        const char t = 'T', u = 'N';                                                                                                                              \
        int m = mat_ncols(A), k = mat_nrows(A), n = mat_ncols(B), lda = k;                                                                                        \
        int ldb = k, ldc = m;                                                                                                                                     \
        base_type alpha(1), beta(0);                                                                                                                              \
        if (m && k && n)                                                                                                                                          \
            blas_name(&t, &u, &m, &n, &k, &alpha, &A(0, 0), &lda, &B(0, 0), &ldb, &beta, &C(0, 0), &ldc);                                                         \
        else                                                                                                                                                      \
            gmm::clear(C);                                                                                                                                        \
    }

                                    gemm_interface_tn(sgemm_, BLAS_S, )
                                        gemm_interface_tn(dgemm_, BLAS_D, )
                                            gemm_interface_tn(cgemm_, BLAS_C, )
                                                gemm_interface_tn(zgemm_, BLAS_Z, )
                                                    gemm_interface_tn(sgemm_, BLAS_S, const)
                                                        gemm_interface_tn(dgemm_, BLAS_D, const)
                                                            gemm_interface_tn(cgemm_, BLAS_C, const)
                                                                gemm_interface_tn(zgemm_, BLAS_Z, const)

/* ********************************************************************* */
/* dense matrix x transposed(dense matrix) multiplication.               */
/* ********************************************************************* */

#define gemm_interface_nt(blas_name, base_type, is_const)                                                                                                                    \
    inline void mult_spec(const dense_matrix<base_type> &A, const transposed_col_ref<is_const dense_matrix<base_type> *> &B_, dense_matrix<base_type> &C, c_mult, row_major) \
    {                                                                                                                                                                        \
        GMMLAPACK_TRACE("gemm_interface_nt");                                                                                                                                \
        dense_matrix<base_type> &B = const_cast<dense_matrix<base_type> &>(*(linalg_origin(B_)));                                                                            \
        const char t = 'N', u = 'T';                                                                                                                                         \
        int m = mat_nrows(A), lda = m, k = mat_ncols(A), n = mat_nrows(B);                                                                                                   \
        int ldb = n, ldc = m;                                                                                                                                                \
        base_type alpha(1), beta(0);                                                                                                                                         \
        if (m && k && n)                                                                                                                                                     \
            blas_name(&t, &u, &m, &n, &k, &alpha, &A(0, 0), &lda, &B(0, 0), &ldb, &beta, &C(0, 0), &ldc);                                                                    \
        else                                                                                                                                                                 \
            gmm::clear(C);                                                                                                                                                   \
    }

                                                                    gemm_interface_nt(sgemm_, BLAS_S, )
                                                                        gemm_interface_nt(dgemm_, BLAS_D, )
                                                                            gemm_interface_nt(cgemm_, BLAS_C, )
                                                                                gemm_interface_nt(zgemm_, BLAS_Z, )
                                                                                    gemm_interface_nt(sgemm_, BLAS_S, const)
                                                                                        gemm_interface_nt(dgemm_, BLAS_D, const)
                                                                                            gemm_interface_nt(cgemm_, BLAS_C, const)
                                                                                                gemm_interface_nt(zgemm_, BLAS_Z, const)

/* ********************************************************************* */
/* transposed(dense matrix) x transposed(dense matrix) multiplication.   */
/* ********************************************************************* */

#define gemm_interface_tt(blas_name, base_type, isA_const, isB_const)                                                                                                                               \
    inline void mult_spec(const transposed_col_ref<isA_const dense_matrix<base_type> *> &A_, const transposed_col_ref<isB_const dense_matrix<base_type> *> &B_, dense_matrix<base_type> &C, r_mult) \
    {                                                                                                                                                                                               \
        GMMLAPACK_TRACE("gemm_interface_tt");                                                                                                                                                       \
        dense_matrix<base_type> &A = const_cast<dense_matrix<base_type> &>(*(linalg_origin(A_)));                                                                                                   \
        dense_matrix<base_type> &B = const_cast<dense_matrix<base_type> &>(*(linalg_origin(B_)));                                                                                                   \
        const char t = 'T', u = 'T';                                                                                                                                                                \
        int m = mat_ncols(A), k = mat_nrows(A), n = mat_nrows(B), lda = k;                                                                                                                          \
        int ldb = n, ldc = m;                                                                                                                                                                       \
        base_type alpha(1), beta(0);                                                                                                                                                                \
        if (m && k && n)                                                                                                                                                                            \
            blas_name(&t, &u, &m, &n, &k, &alpha, &A(0, 0), &lda, &B(0, 0), &ldb, &beta, &C(0, 0), &ldc);                                                                                           \
        else                                                                                                                                                                                        \
            gmm::clear(C);                                                                                                                                                                          \
    }

                                                                                                    gemm_interface_tt(sgemm_, BLAS_S, , )
                                                                                                        gemm_interface_tt(dgemm_, BLAS_D, , )
                                                                                                            gemm_interface_tt(cgemm_, BLAS_C, , )
                                                                                                                gemm_interface_tt(zgemm_, BLAS_Z, , )
                                                                                                                    gemm_interface_tt(sgemm_, BLAS_S, const, )
                                                                                                                        gemm_interface_tt(dgemm_, BLAS_D, const, )
                                                                                                                            gemm_interface_tt(cgemm_, BLAS_C, const, )
                                                                                                                                gemm_interface_tt(zgemm_, BLAS_Z, const, )
                                                                                                                                    gemm_interface_tt(sgemm_, BLAS_S, , const)
                                                                                                                                        gemm_interface_tt(dgemm_, BLAS_D, , const)
                                                                                                                                            gemm_interface_tt(cgemm_, BLAS_C, , const)
                                                                                                                                                gemm_interface_tt(zgemm_, BLAS_Z, , const)
                                                                                                                                                    gemm_interface_tt(sgemm_, BLAS_S, const, const)
                                                                                                                                                        gemm_interface_tt(dgemm_, BLAS_D, const, const)
                                                                                                                                                            gemm_interface_tt(cgemm_, BLAS_C, const, const)
                                                                                                                                                                gemm_interface_tt(zgemm_, BLAS_Z, const, const)

/* ********************************************************************* */
/* conjugated(dense matrix) x dense matrix multiplication.               */
/* ********************************************************************* */

#define gemm_interface_cn(blas_name, base_type)                                                                                                                      \
    inline void mult_spec(const conjugated_col_matrix_const_ref<dense_matrix<base_type> > &A_, const dense_matrix<base_type> &B, dense_matrix<base_type> &C, rcmult) \
    {                                                                                                                                                                \
        GMMLAPACK_TRACE("gemm_interface_cn");                                                                                                                        \
        dense_matrix<base_type> &A = const_cast<dense_matrix<base_type> &>(*(linalg_origin(A_)));                                                                    \
        const char t = 'C', u = 'N';                                                                                                                                 \
        int m = mat_ncols(A), k = mat_nrows(A), n = mat_ncols(B), lda = k;                                                                                           \
        int ldb = k, ldc = m;                                                                                                                                        \
        base_type alpha(1), beta(0);                                                                                                                                 \
        if (m && k && n)                                                                                                                                             \
            blas_name(&t, &u, &m, &n, &k, &alpha, &A(0, 0), &lda, &B(0, 0), &ldb, &beta, &C(0, 0), &ldc);                                                            \
        else                                                                                                                                                         \
            gmm::clear(C);                                                                                                                                           \
    }

                                                                                                                                                                    gemm_interface_cn(sgemm_, BLAS_S)
                                                                                                                                                                        gemm_interface_cn(dgemm_, BLAS_D)
                                                                                                                                                                            gemm_interface_cn(cgemm_, BLAS_C)
                                                                                                                                                                                gemm_interface_cn(zgemm_, BLAS_Z)

/* ********************************************************************* */
/* dense matrix x conjugated(dense matrix) multiplication.               */
/* ********************************************************************* */

#define gemm_interface_nc(blas_name, base_type)                                                                                                                                 \
    inline void mult_spec(const dense_matrix<base_type> &A, const conjugated_col_matrix_const_ref<dense_matrix<base_type> > &B_, dense_matrix<base_type> &C, c_mult, row_major) \
    {                                                                                                                                                                           \
        GMMLAPACK_TRACE("gemm_interface_nc");                                                                                                                                   \
        dense_matrix<base_type> &B = const_cast<dense_matrix<base_type> &>(*(linalg_origin(B_)));                                                                               \
        const char t = 'N', u = 'C';                                                                                                                                            \
        int m = mat_nrows(A), lda = m, k = mat_ncols(A), n = mat_nrows(B);                                                                                                      \
        int ldb = n, ldc = m;                                                                                                                                                   \
        base_type alpha(1), beta(0);                                                                                                                                            \
        if (m && k && n)                                                                                                                                                        \
            blas_name(&t, &u, &m, &n, &k, &alpha, &A(0, 0), &lda, &B(0, 0), &ldb, &beta, &C(0, 0), &ldc);                                                                       \
        else                                                                                                                                                                    \
            gmm::clear(C);                                                                                                                                                      \
    }

                                                                                                                                                                                    gemm_interface_nc(sgemm_, BLAS_S)
                                                                                                                                                                                        gemm_interface_nc(dgemm_, BLAS_D)
                                                                                                                                                                                            gemm_interface_nc(cgemm_, BLAS_C)
                                                                                                                                                                                                gemm_interface_nc(zgemm_, BLAS_Z)

/* ********************************************************************* */
/* conjugated(dense matrix) x conjugated(dense matrix) multiplication.   */
/* ********************************************************************* */

#define gemm_interface_cc(blas_name, base_type)                                                                                                                                                         \
    inline void mult_spec(const conjugated_col_matrix_const_ref<dense_matrix<base_type> > &A_, const conjugated_col_matrix_const_ref<dense_matrix<base_type> > &B_, dense_matrix<base_type> &C, r_mult) \
    {                                                                                                                                                                                                   \
        GMMLAPACK_TRACE("gemm_interface_cc");                                                                                                                                                           \
        dense_matrix<base_type> &A = const_cast<dense_matrix<base_type> &>(*(linalg_origin(A_)));                                                                                                       \
        dense_matrix<base_type> &B = const_cast<dense_matrix<base_type> &>(*(linalg_origin(B_)));                                                                                                       \
        const char t = 'C', u = 'C';                                                                                                                                                                    \
        int m = mat_ncols(A), k = mat_nrows(A), lda = k, n = mat_nrows(B);                                                                                                                              \
        int ldb = n, ldc = m;                                                                                                                                                                           \
        base_type alpha(1), beta(0);                                                                                                                                                                    \
        if (m && k && n)                                                                                                                                                                                \
            blas_name(&t, &u, &m, &n, &k, &alpha, &A(0, 0), &lda, &B(0, 0), &ldb, &beta, &C(0, 0), &ldc);                                                                                               \
        else                                                                                                                                                                                            \
            gmm::clear(C);                                                                                                                                                                              \
    }

                                                                                                                                                                                                    gemm_interface_cc(sgemm_, BLAS_S)
                                                                                                                                                                                                        gemm_interface_cc(dgemm_, BLAS_D)
                                                                                                                                                                                                            gemm_interface_cc(cgemm_, BLAS_C)
                                                                                                                                                                                                                gemm_interface_cc(zgemm_, BLAS_Z)

/* ********************************************************************* */
/* Tri solve.                                                            */
/* ********************************************************************* */

#define trsv_interface(f_name, loru, param1, trans1, blas_name, base_type)                      \
    inline void f_name(param1(base_type), std::vector<base_type> &x, size_type k, bool is_unit) \
    {                                                                                           \
        GMMLAPACK_TRACE("trsv_interface");                                                      \
        loru;                                                                                   \
        trans1(base_type);                                                                      \
        char d = is_unit ? 'U' : 'N';                                                           \
        int lda(mat_nrows(A)), inc(1), n(k);                                                    \
        if (lda)                                                                                \
            blas_name(&l, &t, &d, &n, &A(0, 0), &lda, &x[0], &inc);                             \
    }

#define trsv_upper const char l = 'U'
#define trsv_lower const char l = 'L'

                                                                                                                                                                                                                    // X <- LOWER(A)^{-1}X.
    trsv_interface(lower_tri_solve, trsv_lower, gem_p1_n, gem_trans1_n,
                   strsv_, BLAS_S)
        trsv_interface(lower_tri_solve, trsv_lower, gem_p1_n, gem_trans1_n,
                       dtrsv_, BLAS_D)
            trsv_interface(lower_tri_solve, trsv_lower, gem_p1_n, gem_trans1_n,
                           ctrsv_, BLAS_C)
                trsv_interface(lower_tri_solve, trsv_lower, gem_p1_n, gem_trans1_n,
                               ztrsv_, BLAS_Z)

                    // X <- UPPER(A)^{-1}X.
    trsv_interface(upper_tri_solve, trsv_upper, gem_p1_n, gem_trans1_n,
                   strsv_, BLAS_S)
        trsv_interface(upper_tri_solve, trsv_upper, gem_p1_n, gem_trans1_n,
                       dtrsv_, BLAS_D)
            trsv_interface(upper_tri_solve, trsv_upper, gem_p1_n, gem_trans1_n,
                           ctrsv_, BLAS_C)
                trsv_interface(upper_tri_solve, trsv_upper, gem_p1_n, gem_trans1_n,
                               ztrsv_, BLAS_Z)

                    // X <- LOWER(transposed(A))^{-1}X.
    trsv_interface(lower_tri_solve, trsv_upper, gem_p1_t, gem_trans1_t,
                   strsv_, BLAS_S)
        trsv_interface(lower_tri_solve, trsv_upper, gem_p1_t, gem_trans1_t,
                       dtrsv_, BLAS_D)
            trsv_interface(lower_tri_solve, trsv_upper, gem_p1_t, gem_trans1_t,
                           ctrsv_, BLAS_C)
                trsv_interface(lower_tri_solve, trsv_upper, gem_p1_t, gem_trans1_t,
                               ztrsv_, BLAS_Z)

                    // X <- UPPER(transposed(A))^{-1}X.
    trsv_interface(upper_tri_solve, trsv_lower, gem_p1_t, gem_trans1_t,
                   strsv_, BLAS_S)
        trsv_interface(upper_tri_solve, trsv_lower, gem_p1_t, gem_trans1_t,
                       dtrsv_, BLAS_D)
            trsv_interface(upper_tri_solve, trsv_lower, gem_p1_t, gem_trans1_t,
                           ctrsv_, BLAS_C)
                trsv_interface(upper_tri_solve, trsv_lower, gem_p1_t, gem_trans1_t,
                               ztrsv_, BLAS_Z)

                    // X <- LOWER(transposed(const A))^{-1}X.
    trsv_interface(lower_tri_solve, trsv_upper, gem_p1_tc, gem_trans1_t,
                   strsv_, BLAS_S)
        trsv_interface(lower_tri_solve, trsv_upper, gem_p1_tc, gem_trans1_t,
                       dtrsv_, BLAS_D)
            trsv_interface(lower_tri_solve, trsv_upper, gem_p1_tc, gem_trans1_t,
                           ctrsv_, BLAS_C)
                trsv_interface(lower_tri_solve, trsv_upper, gem_p1_tc, gem_trans1_t,
                               ztrsv_, BLAS_Z)

                    // X <- UPPER(transposed(const A))^{-1}X.
    trsv_interface(upper_tri_solve, trsv_lower, gem_p1_tc, gem_trans1_t,
                   strsv_, BLAS_S)
        trsv_interface(upper_tri_solve, trsv_lower, gem_p1_tc, gem_trans1_t,
                       dtrsv_, BLAS_D)
            trsv_interface(upper_tri_solve, trsv_lower, gem_p1_tc, gem_trans1_t,
                           ctrsv_, BLAS_C)
                trsv_interface(upper_tri_solve, trsv_lower, gem_p1_tc, gem_trans1_t,
                               ztrsv_, BLAS_Z)

                    // X <- LOWER(conjugated(A))^{-1}X.
    trsv_interface(lower_tri_solve, trsv_upper, gem_p1_c, gem_trans1_c,
                   strsv_, BLAS_S)
        trsv_interface(lower_tri_solve, trsv_upper, gem_p1_c, gem_trans1_c,
                       dtrsv_, BLAS_D)
            trsv_interface(lower_tri_solve, trsv_upper, gem_p1_c, gem_trans1_c,
                           ctrsv_, BLAS_C)
                trsv_interface(lower_tri_solve, trsv_upper, gem_p1_c, gem_trans1_c,
                               ztrsv_, BLAS_Z)

                    // X <- UPPER(conjugated(A))^{-1}X.
    trsv_interface(upper_tri_solve, trsv_lower, gem_p1_c, gem_trans1_c,
                   strsv_, BLAS_S)
        trsv_interface(upper_tri_solve, trsv_lower, gem_p1_c, gem_trans1_c,
                       dtrsv_, BLAS_D)
            trsv_interface(upper_tri_solve, trsv_lower, gem_p1_c, gem_trans1_c,
                           ctrsv_, BLAS_C)
                trsv_interface(upper_tri_solve, trsv_lower, gem_p1_c, gem_trans1_c,
                               ztrsv_, BLAS_Z)
}

#endif // GMM_BLAS_INTERFACE_H

#endif // GMM_USES_BLAS
