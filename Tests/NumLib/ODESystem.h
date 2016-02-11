#pragma once

#include "ODETypes.h"

template<ODESystemTag ODETag, NonlinearSolverTag NLTag>
class ODESystem;

template<>
class ODESystem<ODESystemTag::FirstOrderImplicitQuasilinear,
                NonlinearSolverTag::Picard>
{
public:
    static constexpr ODESystemTag ODETag = ODESystemTag::FirstOrderImplicitQuasilinear;


    virtual bool isLinear() const = 0;
    virtual IndexType getMatrixSize() const = 0;

    virtual void assemble(const double t, Vector const& x,
                          Matrix& M, Matrix& K, Vector& b) = 0;

    virtual ~ODESystem() = default;
};

template<>
class ODESystem<ODESystemTag::FirstOrderImplicitQuasilinear,
                NonlinearSolverTag::Newton>
        : public ODESystem<ODESystemTag::FirstOrderImplicitQuasilinear,
                           NonlinearSolverTag::Picard>
{
public:
    virtual void assembleJacobian(const double t, Vector const& x,
                                  const double dxdot_dx,
                                  const double dx_dx,
                                  Matrix& Jac) = 0;
};
