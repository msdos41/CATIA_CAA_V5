# COPYRIGHT Dassault Systemes 2018
#======================================================================
# Imakefile for module TXTReadMod.m
#======================================================================
#
#  Nov 2018  Creation: Code generated by the CAA wizard  Administrator
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES = JS0GROUP \
JS0GROUP JS0FM DI0PANV2 CATApplicationFrame 
# END WIZARD EDITION ZONE

LINK_WITH = $(WIZARD_LINK_MODULES)  KnowledgeItf  \
CATObjectModelerBase  \
CATMecModInterfaces  \

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
