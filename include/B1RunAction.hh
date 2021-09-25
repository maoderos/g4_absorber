
//-------------------------------------------------------------------------------------------------------
//Application developed for studying the dispersion of muon in the Alice Frontal Absorber
//History of the code
//----------------------------
//Year; Author; Paper	
// 2021; M.A.O Derós, L.G Pareira ,G. Hoff; marcosderos78@gmail.com, lgp@ufrgs.br, ghoff.gesic@gmail.com
//----------------------------
//-------------------------------------------------------------------------------------------------------
//$ID: RunAction
//--------------------------------------------------


#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"
#include <G4Timer.hh>
#include <vector>
#include <map>
#include "G4Run.hh"

class B1Run;
class B1DetectorConstruction;

using namespace std;
/// Run action class
class B1RunAction : public G4UserRunAction
{
  public:
    B1RunAction();
    virtual ~B1RunAction();
    G4Run* GenerateRun();
    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

    

    const G4String getFilename() const {return filename;}

    G4double get_alpha() const {return alpha;};
    G4double get_pz() const {return Pz;};
    G4Timer* timer;
  private:

    G4double alpha;
    G4double Pz;
    G4String filename;
    G4String file_Pphysics;
    B1Run* arun;
	};

#endif
