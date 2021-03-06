/*****  Vxa_VType Implementation  *****/

/************************
 ************************
 *****  Interfaces  *****
 ************************
 ************************/

/********************
 *****  System  *****
 ********************/

#include "Vk.h"

/******************
 *****  Self  *****
 ******************/

#include "Vxa_VType.h"

/************************
 *****  Supporting  *****
 ************************/

#include "V_VRTTI.h"
#include "V_VString.h"


/************************
 ************************
 *****              *****
 *****  Vxa::VType  *****
 *****              *****
 ************************
 ************************/

/**************************
 **************************
 *****  Construction  *****
 **************************
 **************************/

Vxa::VType::VType () {
}

/*************************
 *************************
 *****  Destruction  *****
 *************************
 *************************/

Vxa::VType::~VType () {
}

/*************************
 *************************
 *****  Description  *****
 *************************
 *************************/

V::VString &Vxa::VType::getDescription_(V::VString &rResult) const {
    V::VRTTI iRTTI (typeid (*this));
    return rResult << iRTTI.name ();
}
