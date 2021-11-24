# COPYRIGHT Dassault Systemes 2021
#======================================================================
# Imakefile for module TestMechanismMod.m
#======================================================================
#
#  Nov 2021  Creation: Code generated by the CAA wizard  Administrator
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES = JS0GROUP \
JS0GROUP JS0FM DI0PANV2 CATMathematics CATDialogEngine 
# END WIZARD EDITION ZONE

LINK_WITH = $(WIZARD_LINK_MODULES)	\
GeneralClassMod		\
CATProductStructure1	\
KinematicsItf		\
ProductStructureItf		\
CATObjectSpecsModeler	\
CATApplicationFrame	\
CATObjectModelerBase	\
CATVisualization	\
InfItf		\

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
