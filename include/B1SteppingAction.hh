
//-------------------------------------------------------------------------------------------------------
//Application developed for studying the dispersion of muon in the Alice qrontal Absorber
//History of the code
//----------------------------
//Year; Author; Paper	
// 2021; M.A.O Derós, L.G Pareira ,G. Hoff; marcosderos78@gmail.com, lgp@ufrgs.br, ghoff.gesic@gmail.com
//----------------------------
//-------------------------------------------------------------------------------------------------------
//$ID: SteppingAction
//--------------------------------------------------


#ifndef B1SteppingAction_h
#define B1SteppingAction_h

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include <vector>
#include <map>
#include "G4TrackStatus.hh"

class B1EventAction;
class B1RunAction;
class G4LogicalVolume;

/// Stepping action class


using namespace std;
class B1SteppingAction : public G4UserSteppingAction
{
  public:
    B1SteppingAction(B1EventAction* eventAction);
    virtual ~B1SteppingAction();

    /// method from the base class
    virtual void UserSteppingAction(const G4Step*);
   
    std::map<G4String,int> getProcessCount() const {return processCount;};

  private:
    B1EventAction*  fEventAction;
    std::vector<G4LogicalVolume* > Log_volumes;
    G4LogicalVolume* fScoringVolume1;
    G4LogicalVolume* fScoringVolume2;
    std::map<G4String, int> processCount; 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
