//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "VectorDirichletBC.h"

registerMooseObject("MooseApp", VectorDirichletBC);
registerMooseObjectRenamed("MooseApp",
                           LagrangeVecDirichletBC,
                           "05/01/2019 00:01",
                           VectorDirichletBC);

template <>
InputParameters
validParams<VectorDirichletBC>()
{
  InputParameters p = validParams<VectorNodalBC>();
  p.addRequiredParam<RealVectorValue>("values",
                                      "The values the components must take on the boundary");
  p.declareControllable("values");
  p.addClassDescription(
      "Imposes the essential boundary condition $\\vec{u}=\\vec{g}$, where $\\vec{g}$ "
      "are constant, controllable values.");
  return p;
}

VectorDirichletBC::VectorDirichletBC(const InputParameters & parameters)
  : VectorNodalBC(parameters), _values(getParam<RealVectorValue>("values"))
{
}

RealVectorValue
VectorDirichletBC::computeQpResidual()
{
  return _u - _values;
}
