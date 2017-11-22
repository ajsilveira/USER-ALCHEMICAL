/* -*- c++ -*- ----------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   http://lammps.sandia.gov, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under 
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

#ifdef PAIR_CLASS

PairStyle(coul/damp/sf/linear,PairCoulDampSFLinear)

#else

#ifndef LMP_PAIR_COUL_DAMP_SF_LINEAR_H
#define LMP_PAIR_COUL_DAMP_SF_LINEAR_H

#include "pair_alchemical.h"

#define EWALD_P   0.3275911
#define EWALD_F   1.128379167
#define A_1        0.254829592
#define A_2       -0.284496736
#define A_3        1.421413741
#define A_4       -1.453152027
#define A_5        1.061405429

namespace LAMMPS_NS {

class PairCoulDampSFLinear : public PairAlchemical {
 public:
  PairCoulDampSFLinear(class LAMMPS *);
  ~PairCoulDampSFLinear();
  void compute(int, int);
  void settings(int, char **);
  void coeff(int, char **);
  virtual void init_style();
  virtual double init_one(int, int);
  void reinit();
  void modify_params(int, char **);
  void write_restart(FILE *);
  void read_restart(FILE *);
  void write_restart_settings(FILE *);
  void read_restart_settings(FILE *);
  double single(int, int, int, int, double, double, double, double &);
  void *extract(const char *, int &);
  double derivative();

 protected:
  double cut_coul,cut_coulsq;
  double alpha;
  double f_shift,e_shift;
  double e_self;
  int self_flag;
  double dEdl;

  virtual void allocate();

  inline void unshifted( double r, double &v, double &f )
  {
    double ar = alpha*r;
    f = exp(-ar*ar)/r;
    v = 1.0 / (1.0 + EWALD_P*ar);
    v *= (A_1 + v*(A_2 + v*(A_3 + v*(A_4 + v*A_5))))*f;
    f = v/r + EWALD_F*alpha*f;
  }
};

}

#endif
#endif

/* ERROR/WARNING messages:

E: Illegal ... command

Self-explanatory.  Check the input script syntax and compare to the
documentation for the command.  You can use -echo screen as a
command-line option when running LAMMPS to see the offending line.

E: Incorrect args for pair coefficients

Self-explanatory.  Check the input script or data file.

E: Pair style lj/cut/coul/dsf requires atom attribute q

The atom style defined does not have these attributes.

*/
