#pragma once

#include <memory>
#include <tuple>
#include "spectral/basis/basis_types.hpp"


namespace boltzmann {

// ----------------------------------------------------------------------
/**
 * @brief Evaluator wrapper for 1D normalized physicts' Hermite
 *        polynomials
 *
 */
template <typename POLY_T, typename ELEM = typename hermite_basis_t::elem_t>
class HermiteEvalHandler2d
{
 public:
  HermiteEvalHandler2d(std::shared_ptr<POLY_T> ptr)
      : _poly_evaldx(ptr),
        _poly_evaldy(ptr)
  { /* empty */ }

  HermiteEvalHandler2d(std::shared_ptr<POLY_T> ptrx, std::shared_ptr<POLY_T> ptry)
      : _poly_evaldx(ptrx),
        _poly_evaldy(ptry)
  { /* empty */ }


  /**
   * @param e  Element
   * @param q0 Quadrature point ID! in 0-th dimension
   * @param q1 Quadrature point ID! in 1-th dimension
   *
   * @return function element e evaluated at quadrature points
   */
  typename POLY_T::numeric_t operator()(const ELEM& e, unsigned int q0, unsigned int q1) const
  {
    assert((q0 < _poly_evaldx->get_npoints()) && (q1 < _poly_evaldy->get_npoints()));
    return _poly_evaldx->get(get_h0(e).get_degree())[q0] *
           _poly_evaldy->get(get_h1(e).get_degree())[q1];
  }

 private:
  typedef typename std::tuple_element<0, typename ELEM::container_t>::type h0_t;
  typedef typename std::tuple_element<1, typename ELEM::container_t>::type h1_t;

 private:
  std::shared_ptr<POLY_T> _poly_evaldx;
  std::shared_ptr<POLY_T> _poly_evaldy;

  typename ELEM::Acc::template get<h0_t> get_h0;
  typename ELEM::Acc::template get<h1_t> get_h1;
};

}  // end namespace boltzmann
