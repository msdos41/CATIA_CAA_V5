# COPYRIGHT Dassault Systemes 2020
#======================================================================
# Imakefile for module TestExtendUIMod.m
#======================================================================
#
#  Apr 2020  Creation: Code generated by the CAA wizard  Administrator
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
TestExtendPtItfCPP	\
CATObjectModelerBase	\
CATObjectSpecsModeler	\
CATMecModInterfaces		\
CATGeometricObjects		\
CATTopologicalObjects	\
CATBasicTopologicalOpe	\
CATMathStream	\
CATProductStructure1	\
CATGitInterfaces	\
CATViz		\

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
