//-------------------------------------------------------------------------------------------------------
//Application developed for studying the dispersion of muon in the Alice Frontal Absorber
//History of the code
//----------------------------
//Year; Author; Paper	
// 2021; M.A.O Derós, L.G Pareira ,G. Hoff; marcosderos78@gmail.com, lgp@ufrgs.br, ghoff.gesic@gmail.com
//----------------------------
//-------------------------------------------------------------------------------------------------------
//$ID: SensitiveDetector
//--------------------------------------------------


#ifndef B1SD_h
#define B1SD_h 1

#include "G4VSensitiveDetector.hh"
#include "B1Hits.hh"
#include <vector>

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;
class B1Hits;


using namespace std;
///Sensitive Detector class. Store the hits in a hit collection
class B1SD: public G4VSensitiveDetector
{
public:
  //construtor
  B1SD(G4String SDname);
  //destrutor
  ~B1SD();
  ///Process hits
  G4bool ProcessHits(G4Step* step, G4TouchableHistory* ROhist);

  void Initialize(G4HCofThisEvent* HCE);

  //função chamada ao final do evento 
  void EndOfEvent(G4HCofThisEvent* HCE);

private:
  B1HitsCollection* hitCollection;
  G4int HCID;
  std::vector<G4int> tracks;
  G4int track_id;
  G4String sdname;
};

#endif

