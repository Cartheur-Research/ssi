/*F***************************************************************************
 * openSMILE - the open-Source Multimedia Interpretation by Large-scale
 * feature Extraction toolkit
 * 
 * (c) 2008-2011, Florian Eyben, Martin Woellmer, Bjoern Schuller: TUM-MMK
 * 
 * (c) 2012-2013, Florian Eyben, Felix Weninger, Bjoern Schuller: TUM-MMK
 * 
 * (c) 2013-2014 audEERING UG, haftungsbeschränkt. All rights reserved.
 * 
 * Any form of commercial use and redistribution is prohibited, unless another
 * agreement between you and audEERING exists. See the file LICENSE.txt in the
 * top level source directory for details on your usage rights, copying, and
 * licensing conditions.
 * 
 * See the file CREDITS in the top level directory for information on authors
 * and contributors. 
 ***************************************************************************E*/


/*  openSMILE component:

functionals container

passes unsorted row data array AND (if required) sorted row data array to functional processors

*/


#ifndef __CFUNCTIONALS_HPP
#define __CFUNCTIONALS_HPP

#include <core/smileCommon.hpp>
#include <core/winToVecProcessor.hpp>
#include <functionals/functionalComponent.hpp>

#define BUILD_COMPONENT_Functionals
#define COMPONENT_DESCRIPTION_CFUNCTIONALS "computes functionals from input frames, this component uses various cFunctionalXXXX sub-components, which implement the actual functionality"
#define COMPONENT_NAME_CFUNCTIONALS "cFunctionals"
#define COMPONENT_NAME_CFUNCTIONALS_LENGTH 12

#undef class
class DLLEXPORT cFunctionals : public cWinToVecProcessor {
  private:
    int nFunctTp, nFunctTpAlloc;  // number of cFunctionalXXXX types found
    char **functTp;  // type names (without cFunctional prefix)
    int *functTpI;   // index of cFunctionalXXXX type in componentManager
    int *functI;   // index of cFunctionalXXXX type in componentManager
    int *functN;   // number of output values of each functional object
    cFunctionalComponent **functObj;
    int requireSorted;
    int nonZeroFuncts;
    const char * functNameAppend;
    int timeNorm;

  protected:
    int nFunctionalsEnabled;
    int nFunctValues;  // size of output vector

    SMILECOMPONENT_STATIC_DECL_PR

//    virtual void fetchConfig();
    virtual int myConfigureInstance();

    //virtual int myFinaliseInstance();
    //virtual int myTick(long long t);

    virtual int getMultiplier();
    //virtual int configureWriter(const sDmLevelConfig *c);
    virtual int setupNamesForElement(int idxi, const char*name, long nEl);
    virtual int doProcess(int i, cMatrix *row, FLOAT_DMEM*x);
    virtual int doProcessMatrix(int i, cMatrix *in, FLOAT_DMEM *out, long nOut);

//    virtual int doProcess(int i, cMatrix *row, INT_DMEM*x);

  public:
    SMILECOMPONENT_STATIC_DECL
    static int rAcounter;
    cFunctionals(const char *_name);

    virtual ~cFunctionals();
};




#endif // __CFUNCTIONALS_HPP
