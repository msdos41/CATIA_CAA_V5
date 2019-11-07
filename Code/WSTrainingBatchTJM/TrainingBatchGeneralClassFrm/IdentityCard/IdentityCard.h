// COPYRIGHT Dassault Systemes 2019
//===================================================================
//
// IdentityCard.h
// Supplies the list of prerequisite components for framework TrainingBatchGeneralClassFrm
//
//===================================================================
//
// Usage notes:
//   For every prereq framework FW, use the syntax:
//   AddPrereqComponent ("FW", Public);
//
//===================================================================
//
//  Sep 2019  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
// DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
AddPrereqComponent ("System", Public);
// END WIZARD EDITION ZONE
AddPrereqComponent ("GSMInterfaces",		        Public);
AddPrereqComponent ("GSOInterfaces",		        Public);
AddPrereqComponent ("PartInterfaces",      	        Public);
AddPrereqComponent ("LiteralFeatures",		        Public);
AddPrereqComponent ("KnowledgeInterfaces",	        Public);
AddPrereqComponent ("ObjectModelerBase",	        Public);
AddPrereqComponent ("ObjectSpecsModeler",	        Public);
AddPrereqComponent ("MecModInterfaces",   	        Public);
AddPrereqComponent ("MechanicalModelerUI",	        Public); // Added Pey 25/08/2006 
AddPrereqComponent ("MechanicalModeler",	        Public);
AddPrereqComponent ("MechanicalCommands",  	        Public);
AddPrereqComponent ("ApplicationFrame",             Public);
AddPrereqComponent ("InteractiveInterfaces",        Public); // Added Pey 25/08/2006 
AddPrereqComponent ("DialogEngine",                 Public); // Added Pey 25/08/2006  
AddPrereqComponent ("Dialog",                       Public); // Added Pey 25/08/2006 
AddPrereqComponent ("Mathematics",                  Public);
AddPrereqComponent ("GeometricObjects",             Public);
AddPrereqComponent ("GeometricOperators",           Public); // Added Pey 25/08/2006 
AddPrereqComponent ("AdvancedTopologicalOpe",       Public); // Added Pey 25/08/2006 
AddPrereqComponent ("NewTopologicalObjects",        Public);
AddPrereqComponent ("TopologicalOperators",         Public); 
AddPrereqComponent ("Visualization",                Public);
AddPrereqComponent ("VisualizationBase",            Public);