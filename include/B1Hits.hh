//-------------------------------------------------------------------------------------------------------
//Application developed for studying the dispersion of muon in the Alice Frontal Absorber
//History of the code
//----------------------------
//Year; Author; Paper	
// 2021; M.A.O Derós, L.G Pareira ,G. Hoff; marcosderos78@gmail.com, lgp@ufrgs.br, ghoff.gesic@gmail.com
//----------------------------
//-------------------------------------------------------------------------------------------------------
//$ID: Hits
//--------------------------------------------------


#include "G4VHit.hh"
#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"

class B1Hits: public G4VHit {

public:
  B1Hits();
  ~B1Hits();

  void print();
  void set_partdef (const G4String particle_name);
  void set_energy (const G4double particle_en);
  void set_position (const G4ThreeVector particle_pos);
  void set_momentum(const G4ThreeVector particle_momentum);
  const G4String getParticleInTarget() {
    return fParticleInTarget;
  }
  const G4double getParticleEnergy() {
    return fparticle_energy;
  }
  const G4ThreeVector getParticlePos() {
    return fparticle_position;
  }
  const G4ThreeVector getParticleMomentum() {
    return fparticle_momentum;
  }
  
private:

 G4String fParticleInTarget;
 G4double fparticle_energy;
 G4ThreeVector fparticle_position;
 G4ThreeVector fparticle_momentum;

};

typedef G4THitsCollection<B1Hits> B1HitsCollection;

