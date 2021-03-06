
//-------------------------------------------------------------------------------------------------------
//Application developed for studying the dispersion of muon in the Alice Frontal Absorber
//History of the code
//----------------------------
//Year; Author; Paper	
// 2021; M.A.O Derós, L.G Pareira ,G. Hoff; marcosderos78@gmail.com, lgp@ufrgs.br, ghoff.gesic@gmail.com
//----------------------------
//-------------------------------------------------------------------------------------------------------
//$ID: EventAction
//--------------------------------------------------


#ifndef B1EventAction_h
#define B1EventAction_h 1
#include "B1PrimaryGeneratorAction.hh"
#include "G4UserEventAction.hh"
#include "globals.hh"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

class B1RunAction;
class B1DetectorConstruction;
/// Event action class
///
class G4Run;
using namespace std;
/// Event action class. The muon data stored in the hit collection is writeen in the .dat file.
class B1EventAction : public G4UserEventAction
{
  public:
    B1EventAction(B1RunAction* runAction);
    virtual ~B1EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);



  private:
    B1RunAction* fRunAction;
    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
