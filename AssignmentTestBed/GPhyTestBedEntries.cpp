/*
GPhyTestBedEntries.cpp
Objective: Interface to the Box2D TestBed framework
TGD2251 Game Physics
Copyright (C) by Ya-Ping Wong <ypwong@mmu.edu.my>
Faculty of Computing & Informatics
Multimedia University
*/

#include "Framework/Test.h"
#include "Framework/Render.h"
#include <freeglut/freeglut.h>
#include <cstring>
using namespace std;
#include "Assignment\Assignment.h"

TestEntry g_testEntries[] =
{
    {"Assignment", Assignment::Create},
    {NULL, NULL}
};
