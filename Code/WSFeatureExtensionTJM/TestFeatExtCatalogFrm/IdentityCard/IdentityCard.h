// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// IdentityCard.h
// Supplies the list of prerequisite components for framework TestFeatExtCatalogFrm
//
//===================================================================
//
// Usage notes:
//   For every prereq framework FW, use the syntax:
//   AddPrereqComponent ("FW", Public);
//
//===================================================================
//
//  Apr 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
// DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
AddPrereqComponent("System",Protected);
AddPrereqComponent("TestExtendPtInterfaces",Protected);
AddPrereqComponent("ObjectSpecsModeler",Public);
AddPrereqComponent("ApplicationFrame",Protected);
AddPrereqComponent("InteractiveInterfaces",Protected);
// END WIZARD EDITION ZONE
AddPrereqComponent("ObjectModelerBase",Public);
AddPrereqComponent("MecModInterfaces ",Public);
AddPrereqComponent("GeometricObjects",Public);
AddPrereqComponent("NewTopologicalObjects",Public);
AddPrereqComponent("BasicTopologicalOpe",Public);
AddPrereqComponent("Mathematics",Public);