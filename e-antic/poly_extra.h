/*
   Copyright (C) 2016 Vincent Delecroix

    This file is part of e-antic

    e-antic is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3.0 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#ifndef FMPQ_POLY_EXTRA_H
#define FMPQ_POLY_EXTRA_H

#include <flint/flint.h>
#include <flint/fmpz_poly.h>
#include <flint/fmpq_poly.h>
#include <arb.h>

#ifdef __cplusplus
 extern "C" {
#endif

void arb_add_fmpq(arb_t a, const arb_t b, const fmpq_t c, slong prec);
void arb_sub_fmpq(arb_t a, const arb_t b, const fmpq_t c, slong prec);
void arb_fmpq_sub(arb_t a, const fmpq_t c, const arb_t b, slong prec);
void arb_mul_fmpq(arb_t a, const arb_t b, const fmpq_t c, slong prec);
void arb_div_fmpq(arb_t a, const arb_t b, const fmpq_t c, slong prec);
void arb_fmpq_div(arb_t a, const fmpq_t c, const arb_t b, slong prec);

/* TODO: submit to FLINT */
int fmpq_set_str(fmpq_t x, const char *str, int base);
void _fmpz_poly_scale_0_1_fmpq(fmpz * pol, slong len, fmpq_t a, fmpq_t b);

void fmpz_poly_randtest_irreducible(fmpz_poly_t p, flint_rand_t state, slong len, mp_bitcnt_t bits);

/* sets a polynomial from a string and a variable name */
/* (converse to fmpq_poly_get_str_pretty) */
int fmpq_poly_set_str_pretty(fmpq_poly_t p, const char * s, const char * var);


static __inline__
void fmpq_add_ui(fmpq_t a, fmpq_t b, ulong c)
{
    fmpz_t tmp;
    fmpz_init(tmp);
    fmpz_set_ui(tmp, c);
    fmpq_add_fmpz(a, b, tmp);
    fmpz_clear(tmp);
}

static __inline__
void fmpq_sub_ui(fmpq_t a, fmpq_t b, ulong c)
{
    fmpz_t tmp;
    fmpz_init(tmp);
    fmpz_set_ui(tmp, c);
    fmpq_sub_fmpz(a, b, tmp);
    fmpz_clear(tmp);
}

static __inline__
void fmpq_mul_si(fmpq_t a, fmpq_t b, slong c)
{
    fmpz_t tmp;
    fmpz_init(tmp);
    fmpz_set_si(tmp, c);
    fmpq_mul_fmpz(a, b, tmp);
    fmpz_clear(tmp);
}

static __inline__
void fmpq_mul_ui(fmpq_t a, fmpq_t b, ulong c)
{
    fmpz_t tmp;
    fmpz_init(tmp);
    fmpz_set_ui(tmp, c);
    fmpq_mul_fmpz(a, b, tmp);
    fmpz_clear(tmp);
}

static __inline__
void fmpq_div_si(fmpq_t a, fmpq_t b, slong c)
{
    fmpz_t tmp;
    fmpz_init(tmp);
    fmpz_set_si(tmp, c);
    fmpq_div_fmpz(a, b, tmp);
    fmpz_clear(tmp);
}

static __inline__
void fmpq_div_ui(fmpq_t a, fmpq_t b, ulong c)
{
    fmpz_t tmp;
    fmpz_init(tmp);
    fmpz_set_ui(tmp, c);
    fmpq_div_fmpz(a, b, tmp);
    fmpz_clear(tmp);
}

/* polynomial evaluation */
static __inline__
void fmpz_poly_evaluate_at_one(fmpz_t res, fmpz * p, slong len)
{
    slong i;

    fmpz_set(res, p);
    for (i = 1; i < len; i++)
        fmpz_add(res, res, p + i);
}

void _fmpz_poly_evaluate_arb(arb_t res, const fmpz * pol, slong len, const arb_t a, slong prec);

void fmpz_poly_evaluate_arb(arb_t b, const fmpz_poly_t pol, const arb_t a, slong prec);

void fmpq_poly_evaluate_arb(arb_t b, const fmpq_poly_t pol, const arb_t a, slong prec);


/* parse several kind of strings:     */
/* integers :  23 or -2               */
/* rationals:  123/45 or -2/5         */
/* fmpq polynomials: 2  -3 5/2        */
/* plain polynomial: 2*a^5 + 5/3*a - 2 */
int fmpq_poly_magic_parse(fmpq_poly_t p, char * s);

void _fmpz_poly_evaluate_arf(arf_t res, const fmpz * pol, slong len, const arf_t a, slong prec);

void fmpz_poly_evaluate_arf(arf_t res, const fmpz_poly_t pol, const arf_t a, slong prec);

void fmpq_poly_evaluate_arf(arf_t b, const fmpq_poly_t pol, const arf_t a, slong prec);

/* root refinement */
int fmpq_poly_check_unique_real_root(const fmpq_poly_t pol, const arb_t a, slong prec);

int _fmpz_poly_newton_step_arb(arb_t res, const fmpz * pol, const fmpz * der, slong len, arb_t a, slong prec);

int _fmpz_poly_bisection_step_arb(arb_t res, fmpz * pol, slong len, arb_t a, slong prec);

int fmpz_poly_newton_step_arb(arb_t res, const fmpz_poly_t pol, const fmpz_poly_t der, arb_t a, slong prec);

void _fmpz_poly_bisection_step_arf(arf_t l, arf_t r, const fmpz * pol, slong len, int sl, int sr, slong prec);

int fmpz_poly_bisection_step_arb(arb_t res, const fmpz_poly_t pol, arb_t a, slong prec);

void fmpz_poly_squarefree_part(fmpz_poly_t res, fmpz_poly_t poly);

/* root isolation */

/* TODO: submit to FLINT */
int _fmpz_poly_has_real_root(fmpz * pol, slong len);

/* TODO: submit to FLINT */
int fmpz_poly_has_complex_root(fmpz_poly_t pol);

static __inline__
int fmpz_poly_has_real_root(fmpz_poly_t pol)
{
    return _fmpz_poly_has_real_root(pol->coeffs, pol->length);
}


/* TODO: submit to FLINT */
slong fmpz_poly_positive_root_upper_bound_2exp(const fmpz_poly_t pol);
slong _fmpz_poly_positive_root_upper_bound_2exp(const fmpz * pol, slong len);
slong _fmpz_poly_positive_root_upper_bound_2exp_local_max(const fmpz * pol, slong len);

/* TODO: submit to FLINT */
slong _fmpz_poly_descartes_bound_0_1(fmpz * p, slong len, slong bound);
slong _fmpz_poly_descartes_bound(fmpz * p, slong len, slong bound);

/* TODO: submit to FLINT */
slong fmpz_poly_num_real_roots_upper_bound(fmpz_poly_t pol);

/* TODO: submit to FLINT */
void _fmpz_poly_isolate_real_roots_0_1_vca(fmpq * exact_roots, slong * n_exact_roots, fmpz * c_array, slong * k_array, slong * n_intervals, fmpz * pol, slong len);

/* TODO: submit to FLINT */
void fmpz_poly_isolate_real_roots(fmpq * exact_roots, slong * n_exact, fmpz * c_array, slong * k_array, slong * n_interval, fmpz_poly_t pol);

/* TODO: submit to FLINT */
slong fmpz_poly_num_real_roots_vca(fmpz_poly_t pol);

slong fmpz_poly_num_real_roots_0_1_sturm(fmpz_poly_t pol);
slong fmpz_poly_num_real_roots_0_1_vca(fmpz_poly_t pol);
static __inline__
slong fmpz_poly_num_real_roots_0_1(fmpz_poly_t pol)
{
    return fmpz_poly_num_real_roots_0_1_vca(pol);
}

/* slong fmpz_poly_num_real_roots_interval_fmpq_sturm(fmpz_poly_t p, fmpq_t a, fmpq_t b);*/
/* slong fmpz_poly_num_real_roots_interval_fmpq_vca(fmpz_poly_t p, fmpq_t a, fmpq_t b);*/
/* slong fmpz_poly_num_real_roots_interval_fmpq(fmpz_poly_t p, fmpq_t a, fmpq_t b); */


/* OLD ****************************************************************/

/* Backports from flint development version */
void fmpz_nextprime(fmpz_t res, const fmpz_t n, int proved);
void fmpz_randprime(fmpz_t f, flint_rand_t state, mp_bitcnt_t bits, int proved);
void _fmpq_poly_resultant_div(fmpz_t rnum, fmpz_t rden, 
                          const fmpz *poly1, const fmpz_t den1, slong len1, 
                          const fmpz *poly2, const fmpz_t den2, slong len2,
                          const fmpz_t divisor, slong nbits);
void fmpq_poly_resultant_div(fmpq_t r, const fmpq_poly_t f, const fmpq_poly_t g, const fmpz_t divisor, slong nbits);
void fmpq_poly_get_coeff_fmpz(fmpz_t x, const fmpq_poly_t poly, slong n);
slong _fmpz_poly_num_real_roots(const fmpz * pol, slong len);
slong fmpz_poly_num_real_roots(const fmpz_poly_t pol);
void _fmpz_poly_num_real_roots_sturm(slong * n_neg, slong * n_pos, const fmpz * pol, slong len);
slong fmpz_poly_num_real_roots_sturm(const fmpz_poly_t pol);
void _fmpz_poly_resultant_modular_div(fmpz_t res, 
        const fmpz * poly1, slong len1, 
        const fmpz * poly2, slong len2, const fmpz_t divisor, slong nbits);
void
fmpz_poly_resultant_modular_div(fmpz_t res, const fmpz_poly_t poly1,
              const fmpz_poly_t poly2, const fmpz_t divisor, slong nbits);
slong _fmpz_poly_remove_content_2exp(fmpz * pol, slong len);
void _fmpz_poly_scale_2exp(fmpz * pol, slong len, slong k);
int fmpq_set_str(fmpq_t x, const char *str, int base);
int _fmpq_vec_fprint(FILE * file, const fmpq * vec, slong len);

static __inline__
int _fmpq_vec_print(const fmpq * vec, slong len)
{
    return _fmpq_vec_fprint(stdout, vec, len);
}

void _fmpq_vec_randtest_uniq_sorted(fmpq * vec, flint_rand_t state, slong len, mp_bitcnt_t bits);
void _fmpq_vec_sort(fmpq * vec, slong len);

/* submitted to FLINT (#308) */
/* slong _fmpz_poly_remove_content_2exp(fmpz * pol, slong len); */
/* void _fmpz_poly_scale_2exp(fmpz * pol, slong len, slong k);  */

/* merged in FLINT (#282) */
/* void _fmpq_vec_sort(fmpq * vec, slong len); */
/* void _fmpq_vec_randtest_uniq_sorted(fmpq * vec, flint_rand_t state, slong len, mp_bitcnt_t bits); */
FLINT_DLL void fmpz_poly_randtest_no_real_root(fmpz_poly_t p, flint_rand_t state,
                                                slong len, mp_bitcnt_t bits);
/* void _fmpz_poly_num_real_roots_sturm(slong * n_neg, slong * n_pos, const fmpz * pol, slong len); */
/* slong fmpz_poly_num_real_roots_sturm(const fmpz_poly_t poly); */
/* slong _fmpz_poly_num_real_roots(const fmpz * pol, slong len); */
/* slong fmpz_poly_num_real_roots(const fmpz_poly_t poly); */

/* merged in FLINT (#279 and #295) */
void fmpz_poly_product_roots_fmpq_vec(fmpz_poly_t poly, const fmpq * xs, slong n);

/* merged in FLINT (#278) */
/*int _fmpq_vec_fprint(FILE * file, const fmpq * vec, slong len);*/
/*void _fmpq_vec_print(const fmpq * vec, slong len);*/

#ifdef __cplusplus
 }
#endif

#endif
