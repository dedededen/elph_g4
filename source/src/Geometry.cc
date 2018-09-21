
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Geometry.cc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Geometry.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"


#include "SensitiveVolume.hh"
#include "G4SDManager.hh"

//------------------------------------------------------------------------------
Geometry::Geometry(G4int argv1_width) { width = argv1_width; }
Geometry::~Geometry() {}

//------------------------------------------------------------------------------
G4VPhysicalVolume* Geometry::Construct()
{
  // Get pointer to 'Material Manager'
  G4NistManager* materi_Man = G4NistManager::Instance();
  
  // Define 'World Volume'
  G4double leng_X_World = 300.0*mm;
  G4double leng_Y_World = 300.0*mm;
  G4double leng_Z_World = 300.0*mm;

  // Define the shape of solid
  G4Box* solid_World = 
    new G4Box("Solid_World", leng_X_World/2.0, leng_Y_World/2.0, leng_Z_World/2.0);
  
  // Define logical volume
  G4Material* materi_World = materi_Man->FindOrBuildMaterial("G4_AIR");
  G4LogicalVolume* logVol_World = 
    new G4LogicalVolume(solid_World, materi_World, "LogVol_World");
  logVol_World->SetVisAttributes (G4VisAttributes::Invisible);
  
  // Placement of logical volume
  G4int copyNum_World = 0; 
  G4PVPlacement* physVol_World  = 
    new G4PVPlacement(G4Transform3D(), "PhysVol_World", logVol_World, 0, 
                      false, copyNum_World);
  
  // Define emt?
  G4double leng_X = 13.0*mm;
  G4double leng_Y = 13.0*mm;   
  G4double leng_Z = width*mm;
  // Define the shape of solid
  G4Box* solid_emt = new G4Box("emt",leng_X/2.0,leng_Y/2.0,leng_Z/2.0); 

  // Define logical volume
  G4Material* materi_emt = materi_Man->FindOrBuildMaterial("G4_STAINLESS-STEEL");//si hitimazu
  G4LogicalVolume* logVol_emt = 
    new G4LogicalVolume( solid_emt, materi_emt, "LV_emt", 0, 0, 0 );
  
  G4VisAttributes *emt = new G4VisAttributes(G4Color::Yellow());
  emt -> SetVisibility(true);
  logVol_emt -> SetVisAttributes(emt);
  
  // Placement of logical volume
  G4double pos_L_X = 0.0*m;
  G4double pos_L_Y= 0.0*m;
  G4double pos_L_Z = 0.0*m;
   
  G4ThreeVector threeVect_LV;
  G4RotationMatrix rotMtrx_LogV = G4RotationMatrix();;
  G4Transform3D trans3D_LogV;
  G4int copyNum_LogV = 1000;

  threeVect_LV = G4ThreeVector(pos_L_X, pos_L_Y, pos_L_Z);
  trans3D_LogV = G4Transform3D(rotMtrx_LogV, threeVect_LV);
  new G4PVPlacement(trans3D_LogV, "PhysVol_emt", logVol_emt, physVol_World,false, copyNum_LogV);

  // Define Detector
  G4double leng_X_de = 280*mm;
  G4double leng_Y_de = 280*mm;   
  G4double leng_Z_de = 1*mm;
  G4double pos_X_de = 0*mm;
  G4double pos_Y_de = 0*mm;   
  G4double pos_Z_de = width/2.0 + 10.5*mm;
  G4Box* solid_de = new G4Box("Detector",leng_X_de/2.0,leng_Y_de/2.0,leng_Z_de/2.0); 
  G4Material* materi_de = materi_Man->FindOrBuildMaterial("G4_AIR");
  G4LogicalVolume* logVol_de = 
     new G4LogicalVolume( solid_de, materi_de, "LVde", 0, 0, 0 );
  G4VisAttributes *de = new G4VisAttributes(G4Color::Grey());
  de -> SetVisibility(true);
  logVol_de -> SetVisAttributes(de);
  G4ThreeVector threeVect_de=G4ThreeVector(pos_X_de,pos_Y_de,pos_Z_de); 
  G4Transform3D trans3D_de=G4Transform3D(rotMtrx_LogV,threeVect_de);
  G4int copyNum_de=777;
  new G4PVPlacement(trans3D_de, "PhysVol_De", logVol_de, physVol_World,false, copyNum_de);
  
  //senstive ditector
  SensitiveVolume * SD = new SensitiveVolume("/SentiveVolume");
  logVol_de->SetSensitiveDetector(SD);
  G4SDManager * SDman = G4SDManager::GetSDMpointer();
  SDman -> AddNewDetector(SD);
  
  // Return the physical world
  return physVol_World;
}
