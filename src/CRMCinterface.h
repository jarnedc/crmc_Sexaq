#ifndef __CRMC_INTERFACE_H
#define __CRMC_INTERFACE_H

#include <CRMCconfig.h>

// to exchange data between fortran and c++

#ifdef __CRMCSTATIC__
extern "C"
{

  void crmc_f_( const int&, const int&, int&, double&, int&, double&,
                double&, double&,double&, double&, int&);
  void crmc_set_f_( const int&, const int&, const double&, const double&,
                    const int&, const int&, const int&, const int&, const int&,
                    const char*);
  void crmc_init_f_(const char*,const int&);
  void crmc_xsection_f_(double&, double&, double&, double&, double&, double&, double&, double&, double&);
}
#endif


struct CRMCdata {

  CRMCdata() :
    fNParticles(0),
    fImpactParameter(0),
    sigtot(-1),
    sigine(-1),
    sigela(-1),
    sigdd(-1),
    sigsd(-1),
    sloela(-1),
    sigtotaa(-1),
    sigineaa(-1),
    sigelaaa(-1),
    npjevt(-1),
    ntgevt(-1),
    kolevt(-1),
    npnevt(-1),
    ntnevt(-1),
    nppevt(-1),
    ntpevt(-1),
    nglevt(-1),
    ng1evt(-1),
    ng2evt(-1),
    bimevt(-1),
    phievt(-1),
    fglevt(-1) {}
  void Clean() { fNParticles = 0; }

  // fortran output
  const static unsigned int fMaxParticles = 10000;

  int    fNParticles;
  double fImpactParameter;
  int    fPartId[fMaxParticles];
  double fPartPx[fMaxParticles];
  double fPartPy[fMaxParticles];
  double fPartPz[fMaxParticles];
  double fPartEnergy[fMaxParticles];
  double fPartMass[fMaxParticles];
  int    fPartStatus[fMaxParticles];

  double sigtot;
  double sigine;
  double sigela;
  double sigdd;
  double sigsd;
  double sloela;
  double sigtotaa;
  double sigineaa;
  double sigelaaa;
  int npjevt;
  int ntgevt;
  int kolevt;
  int kohevt;
  int npnevt;
  int ntnevt;
  int nppevt;
  int ntpevt;
  int nglevt;
  int ng1evt;
  int ng2evt;
  double bimevt;
  double phievt;
  double fglevt;
  int typevt;

};
extern CRMCdata gCRMC_data;

// --------------  forward declarations

extern "C"
{
  extern struct
  {
    float sigtot;    // ........ h-p total cross section in mb
    float sigcut;    // ........ h-p cut cross section in mb : in principle it is the non-diffractive xs but the definition depends on the model
    float sigela;    // ........ h-p elastic cross section in mb
    float sloela;    // ........ h-p elastic slope
    float sigsd;     // ........ h-p single diffractive cross section in mb (both side)
    float sigine;    // ........ h-p inelastic cross section in mb (all inelastic processes=sigtot-sigela)
    float sigdif;    // ........ h-p diffractive cross section in mb (SD+DD+DPE) (in principle sigdif+sigcut=sigine but it depends how DPE xs is counted (in EPOS 1.99 it is counted as elastic because nothing was produced but in EPOS LHC DPE are produced)
    float sigineaa;  // ........ h-A or A-A cross section in mb (inelastic cross section to be used as CURRENT EVENT XS for defined projectile and target, previous h-p xs are really for h-p even if the projectile/target were defined as a nuclei)
    float sigtotaa;  // ........ h-A or A-A total cross section in mb
    float sigelaaa;  // ........ h-A or A-A elastic cross section in mb
    float sigcutaa;  // ........ h-A or A-A ND xs or production xs mb
    float sigdd;     // ........ h-p double diffractive cross section in mb (both side)
  } hadr5_; //crmc-aaa.f
}

extern "C"
{
  extern struct
  {
    float phievt; // ........ angle of impact parameter
    int   nevt;   // ........ error code. 1=valid event, 0=invalid event
    float bimevt; // ........ absolute value of impact parameter
    int   kolevt; // ........ number of collisions
    int   koievt; // ........ number of inelastic collisions
    float pmxevt; // ........ reference momentum
    float egyevt; // ........ pp cm energy (hadron) or string energy (lepton)
    int   npjevt; // ........ number of primary projectile participants
    int   ntgevt; // ........ number of primary target participants
    int   npnevt; // ........ number of primary projectile neutron spectators
    int   nppevt; // ........ number of primary projectile proton spectators
    int   ntnevt; // ........ number of primary target neutron spectators
    int   ntpevt; // ........ number of primary target proton spectators
    int   jpnevt; // ........ number of absolute projectile neutron spectators
    int   jppevt; // ........ number of absolute projectile proton spectators
    int   jtnevt; // ........ number of absolute target neutron spectators
    int   jtpevt; // ........ number of absolute target proton spectators
    float xbjevt; // ........ bjorken x for dis
    float qsqevt; // ........ q**2 for dis
    int   nglevt; // ........ number of collisions acc to  Glauber
    float zppevt; // ........ average Z-parton-proj
    float zptevt; // ........ average Z-parton-targ
    int   minfra; // ........
    int   maxfra; // ........
    int   kohevt; // ........ number of inelastic hard collisions
  } cevt_; //epos.inc
}

extern "C"
{
  extern struct
  {
    int   ng1evt; // ........ number of collisions acc to  Glauber
    int   ng2evt; // ........ number of Glauber participants with at least two IAs
    float rglevt; // ........
    float sglevt; // ........
    float eglevt; // ........
    float fglevt; // ........
    int   ikoevt; // ........ number of elementary parton-parton scatterings
    float typevt; // ........ type of event (1=Non Diff, 2=Double Diff, 3=Central Diff, 4=AB->XB, -4=AB->AX)
  } c2evt_; //epos.inc
}

class CRMCinterface
{

 public:
  CRMCinterface();
  ~CRMCinterface();
  
  bool init(int HEmodel);
  void (*crmc_generate)( const int&, const int&, int&, double&, int&, double&,
                    double&, double&,double&, double&, int&); //crmc_f
  void (*crmc_set)( const int&, const int&, const double&, const double&,
                    const int&, const int&, const int&, const int&, const int&,
                    const char*);
  void (*crmc_init)(const char*,const int&);
  void (*crmc_xsection)(double&, double&, double&, double&, double&, double&, double&, double&, double&);
    
 private:
  void* fLibrary;

};

#endif
