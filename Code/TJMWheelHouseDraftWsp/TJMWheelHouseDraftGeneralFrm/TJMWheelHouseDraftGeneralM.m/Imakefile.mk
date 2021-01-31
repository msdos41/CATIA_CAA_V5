# COPYRIGHT Dassault Systemes 2020
#======================================================================
# Imakefile for module GACSeatPlaceCheckGeneralM.m
#======================================================================
#
#  Jun 2020  Creation: Code generated by the CAA wizard  Administrator
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES = JS0GROUP
# END WIZARD EDITION ZONE

LINK_WITH = $(WIZARD_LINK_MODULES)	\
                                   JS0FM \
                                   CATApplicationFrame \
                                   DI0PANV2 \
                                   CATDraftingInterfaces \
                                   CATSketcherInterfaces \
                                   CATMathematics \
                                   CATObjectSpecsModeler \
                                   CATObjectModelerBase \
                                   CATProductStructure1 \
                                   CATInteractiveInterfaces \
                                   CATVisualization \
                                   KnowledgeItf \
                                   CATMecModInterfaces \
                                   CATTopologicalObjects \
                                   CATGeometricObjects \
                                   CATMechanicalModeler \  
                                   CATSaiSpaceAnalysisItf \
                                   CATTopologicalOperators \
                                   CATBasicTopologicalOpe \
                                   CATObjectModelerBase \
                                   CATMechanicalModelerUI	\
                                   CATMeasureGeometryInterfaces  \
                                   CATGitInterfaces		\
                                   InfItf		\
                                   CATIAApplicationFrame	\
                                   ProductStructureItf		\
                                   CATTessellation	\
                                   CATNavigatorItf	\
                                   CATTPSItf		\
                                   CATTPSItfCPP		\
                                   CATTPSProIDL				\
								   CATTPSPubIDL				\

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
