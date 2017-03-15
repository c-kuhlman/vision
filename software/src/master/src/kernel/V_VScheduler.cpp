/*****  V_VScheduler Implementation  *****/

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

#include "V_VScheduler.h"

/************************
 *****  Supporting  *****
 ************************/


/***************************
 ***************************
 *****                 *****
 *****  V::VScheduler  *****
 *****                 *****
 ***************************
 ***************************/

/**************************
 **************************
 *****  Construction  *****
 **************************
 **************************/

V::VScheduler::VScheduler () {
}

/*************************
 *************************
 *****  Destruction  *****
 *************************
 *************************/

V::VScheduler::~VScheduler () {
}

/************************
 ************************
 *****  Scheduling  *****
 ************************
 ************************/

void V::VScheduler::schedule (VSchedulable *pSchedulable) {
    if (m_iQueue.enqueue (pSchedulable)) {
	do {
	    m_iQueue.head ()->run ();
	} while (m_iQueue.dequeueAndTest ());
    }
}