# COPYRIGHT Dassault Systemes 2019
#======================================================================
# Imakefile for module GeneralClassMod.m
#======================================================================
#
#  Jan 2019  Creation: Code generated by the CAA wizard  Administrator
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES = JS0GROUP \
JS0GROUP 
# END WIZARD EDITION ZONE

LINK_WITH = $(WIZARD_LINK_MODULES)  \
CATProductStructure1  \
CATApplicationFrame  \
CATObjectModelerBase  \
DI0PANV2  \
JS0FM  \
CATVisualization	\
CATObjectModelerNavigator	\
CATIAApplicationFrame	\
CATMecModInterfaces	\
CATTopologicalObjects	\
CATGeometricObjects	\
CATMathematics	\
CATMechanicalModelerUI	\
CATObjectSpecsModeler	\
KnowledgeItf	\
CATTopologicalOperators	\
CATInteractiveInterfaces	\
CATInfInterfaces	\
CATDraftingInterfaces	\
CATSketcherInterfaces	\
CATSaiSpaceAnalysisItf	\
TrainingXMLM		\
CATGeometricOperators \
GUIDVPMInterfaces	\
CATMechanicalModeler	\
CATBasicTopologicalOpe \
CATGitInterfaces \

# System dependant variables
#
OS = AIX
#
OS = HP-UX
#
OS = IRIX
#
OS = SunOS
#
OS = Windows_NT
