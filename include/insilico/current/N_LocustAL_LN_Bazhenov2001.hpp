/*
 neuron/N_LocustAL_LN_Bazhenov2001.hpp - 

 (C) 2014 Pranav Kulkarni, Collins Assisi Lab,
                    IISER, Pune <pranavcode@gmail.com>
 Copyright (C) 2014 Nishant Singh, Suhita Nadkarni Lab,
                    IISER, Pune <nishant.singh@students.iiserpune.ac.in>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef INCLUDED_N_LOCUSTAL_LN_BAZHENOV2001_HPP
#define INCLUDED_N_LOCUSTAL_LN_BAZHENOV2001_HPP

#include "insilico/core/engine.hpp"
#include "insilico/neuron/spike_list.hpp"

#include "insilico/current/I_LTCA_LocustAL_LN_Bazhenov2001.hpp"
#include "insilico/current/I_KCA_LocustAL_LN_Bazhenov2001.hpp"
#include "insilico/current/I_Kv_LocustAL_LN_Bazhenov2001.hpp"
#include "insilico/current/I_Ca_LocustAL_LN_Bazhenov2001.hpp"

namespace insilico{

class N_LocustAL_LN_Bazhenov2001:public Neuron{
public:
void ode_set(state_type &variables, state_type &dxdt, const double t, unsigned index){

}
}
}
