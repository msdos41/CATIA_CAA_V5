# COPYRIGHT Dassault Systemes 2019
#======================================================================
# Imakefile for module TestMultiListMod.m
#======================================================================
#
#  Nov 2019  Creation: Code generated by the CAA wizard  Administrator
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES = JS0GROUP \
JS0GROUP JS0FM DI0PANV2 CATApplicationFrame  \
CATMathematics CATDialogEngine 
# END WIZARD EDITION ZONE

LINK_WITH = $(WIZARD_LINK_MODULES)	\
GeneralClassMod	\
CATMechanicalModelerUI  \
CATMecModInterfaces  \
CATObjectModelerBase   \
CATProductStructure1  \
CATObjectSpecsModeler  \
CATGeometricObjects  \
CATNewTopologicalObjects  \
CATMeasureGeometryInterfaces  \
CATViz  \
CATInteractiveInterfaces  \
CATGitInterfaces  \
KnowledgeItf  \
CATTopologicalOperators  \
CATBasicTopologicalOpe  \
GUIDVPMInterfaces	\
YFAirventViewFeedbackM	\
YFDatumTempM	\

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
