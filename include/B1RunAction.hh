
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

    void add_number_of_event(G4int detec_id);
    /// add nEvent value in vector
    void add_event(){nEvent++;}
    /// increase 1 in nEvent variable
    G4int get_n_event(G4int detec_id) {
        ///get the number of the event to store in the output file
        return num_event_detec[detec_id];
       // G4cout << num << G4endl;
       }
    const G4String getFilename() const {return filename;}

    G4double get_alpha(){return alpha;};
    G4double get_pz(){return Pz;};
    G4Timer* timer;
  private:

    G4int nEvent;
    G4double n_of_mu_plus;
    G4double  n_of_mu_minus;
    std::vector<G4int >num_event_detec;
    G4double alpha;
    G4double Pz;
    G4String filename;
};

#endif
