
//-------------------------------------------------------------------------------------------------------
//Application developed for studying the dispersion of muon in the Alice Frontal Absorber
//History of the code
//----------------------------
//Year; Author; Paper	
// 2021; M.A.O Derós, L.G Pareira ,G. Hoff; marcosderos78@gmail.com, lgp@ufrgs.br, ghoff.gesic@gmail.com
//----------------------------
//-------------------------------------------------------------------------------------------------------
//$ID: DetectorConstruction
//--------------------------------------------------


#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4SDManager.hh"
#include "G4VisAttributes.hh"
#include <vector>
#include "G4Material.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class B1SD;
class G4VSensitiveDetector;


using namespace std;

///brief Class that build the absorber Geometry. It is a structure composed of Carbon, Concrete, Lead, Magnesium and Polyethilene. 

class B1DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    B1DetectorConstruction();
    virtual ~B1DetectorConstruction();
   
    virtual void ConstructSDandField();
    /// Add magnetic field to a specific logical volume.

    void SetupConstructor();
  
    virtual G4VPhysicalVolume* Construct();
    
    G4LogicalVolume* GetScoringVolume1() const { return fScoringVolume1; }
    G4LogicalVolume* GetScoringVolume2() const { return fScoringVolume2; }

    G4bool get_sim_state() const {return build_abs;}
    /** Returns the boolean value to know if the absorber should be constructed or not */
 
    std::vector<G4LogicalVolume* > GetVolumes() const {return Logical_volumes;}
    /** Put all Logical volume in a vector */    
    G4int getNV() const {return names.size();}

    G4int getNumDetec() const {return num_detec;}
   /** Get the number of detectors */


   std::vector<G4String> GetNames() const {return names;}
   std::vector<G4String> GetPhyNames() const {return physic_names;}
   G4String GetSD1name() const {return SD1_name;}
   G4String GetSD2name() const {return SD2_name;}
	    
  private:
    void DefineMaterials();
    G4LogicalVolume*  fScoringVolume1;
    G4bool build_abs;
    G4int num_detec;
    G4LogicalVolume* fScoringVolume2;
    G4LogicalVolume* detec_volume2;
    G4LogicalVolume* detec_volume1;
    std::vector<G4LogicalVolume *> Logical_volumes;
    std::vector<G4LogicalVolume *> volumes;
    std::vector<G4String> names;
    std::vector<G4String> physic_names;
    G4LogicalVolume* logicMag;
    G4LogicalVolume* logicWorld;
    G4bool build_magnetic;
    G4Region* aRegion;
    G4Material* kMedCSh;
    G4Material* kMedPb;
    G4Material* kMedConcSh; 
    G4Material* kMedSteel;
    G4Material* kMedNiW;
    G4Material* KmedCH2Sh;
    G4Material* kMedMg;
    G4String SD1_name;
    G4String SD2_name;
};
    

#endif
