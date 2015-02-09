#root.cmake
#
# Created on: Oct 11, 2010
#     Author: Vannuccini Elena



set(ROOTLIBS
    Core
    Cint 
    RIO 
    Net 
    Hist 
    Graf 
    Graf3d 
    Gpad 
    Tree 
    Rint 
    Postscript 
    Matrix 
    Physics 
    MathCore 
    Thread 
    m 
    dl)

find_path(ROOT_INCLUDE_DIR TObject.h $ENV{ROOTSYS}/include $ENV{ROOTSYS}/include/root $ENV{ROOTSYS}/inc $ENV{ROOTSYS}/inc/root)
include_directories(${ROOT_INCLUDE_DIR})
find_path(ROOT_LIB libCore.so $ENV{ROOTSYS}/lib $ENV{ROOTSYS}/lib/root)
link_directories(${ROOT_LIB})