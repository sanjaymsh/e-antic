/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2014 William Hart

******************************************************************************/

#include "e-antic/nf_elem.h"

int _nf_elem_invertible_check(nf_elem_t a, const nf_t nf)
{
   int res;
      
   if (nf->flag & NF_LINEAR)
   {
      const fmpz * const anum = QNF_ELEM_NUMREF(a);
      
      if (fmpz_is_zero(anum))
         res = 0;
      else
      {
         fmpz * t = _fmpz_vec_init(2);
      
         _fmpq_poly_gcd(t, t + 1, 
            fmpq_poly_numref(nf->pol), 2, anum, 1);

         res = fmpz_is_one(t);

         _fmpz_vec_clear(t, 2);
      }
   } else if (nf->flag & NF_QUADRATIC)
   {
      const fmpz * const anum = QNF_ELEM_NUMREF(a);
      fmpz * t = _fmpz_vec_init(3);
      slong len = 2;

      while (len > 0 && fmpz_is_zero(anum + len - 1))
         len--;

      _fmpq_poly_gcd(t, t + 2, 
          fmpq_poly_numref(nf->pol), 3, anum, len);
      
      while (len > 0 && fmpz_is_zero(t + len - 1))
         len--;
      
      res = len == 1 && fmpz_is_one(t);

      _fmpz_vec_clear(t, 3);
   } else
   {
      fmpq_poly_t g;
      
      fmpq_poly_init(g);
      fmpq_poly_gcd(g, NF_ELEM(a), nf->pol);
      res = fmpq_poly_is_one(g);

      fmpq_poly_clear(g);
   }
      
   return res;
}
