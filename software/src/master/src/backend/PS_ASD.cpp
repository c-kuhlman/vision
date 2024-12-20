/*****  PS_ASD Implementation  *****/

/************************
 ************************
 *****  Interfaces  *****
 ************************
 ************************/

/********************
 *****  System  *****
 ********************/

#include "Vk.h"

#include "vstdio.h"

/******************
 *****  Self  *****
 ******************/

#include "PS_ASD.h"

/************************
 *****  Supporting  *****
 ************************/

/**************************
 **************************
 *****  Construction  *****
 **************************
 **************************/


/********************
 ********************
 *****  Access  *****
 ********************
 ********************/

unsigned int PS_ASD::CTHighestInUseIndex () const {
    unsigned int highUsedIndex = 0; // Always a container table at slot 0
    unsigned int ctIndex;
    PS_CTE iCTE;

    for (ctIndex = 1; ctIndex < CTEntryCount (); ctIndex++) {
      if (GetLiveCTE (ctIndex, iCTE)) highUsedIndex = ctIndex;
    }
#ifdef DEBUG_CTable
    IO_printf ("\n\tSpace: %u, Entry Count: %u, highUsed: %u FL: %i\n",
	       spaceIndex (), CTEntryCount (), highUsedIndex, PS_CT_FreeList (m_pCT)); 
#endif
    return highUsedIndex;
}

int PS_ASD::CTFreeList () const {
    unsigned int highUsedIndex = CTHighestInUseIndex ();
    //   int ctIndex;
    int freeList = (highUsedIndex > 0 && PS_CT_FreeList (m_pCT) > highUsedIndex)
	? PS_CT_FreeListNil 
	: PS_CT_FreeList (m_pCT);
#if 0
    PS_CTE iCTE;

    for (ctIndex = PS_CT_FreeList (m_pCT);
	 ctIndex != PS_CT_FreeListNil && ctIndex < highUsedIndex;
	 ctIndex = PS_CTE_NextFree (PS_CT_Entry (m_pCT, ctIndex))) {
      freeList = ctIndex;
    }
#endif
    // if freeList is Nil, should adjust it if possible
    return freeList;
}

bool PS_ASD::GetCTE (unsigned int xContainer, PS_CTE &rResult) const {
    if (xContainer < CTEntryCount ()) {
	rResult = PS_ASD_CTEntry (this, xContainer);
	return true;
    }

    return false;
}


/******************************
 ******************************
 *****  Settings Control  *****
 ******************************
 ******************************/

void PS_ASD::SetLargeContainerSizeTo (double iValue) {
    if (iValue >= 100)
	m_iLargeContainerSize = iValue < UINT_MAX ? (unsigned int)iValue : UINT_MAX;
}

void PS_ASD::SetLargeContainerSizeTo (int iValue) {
    if (iValue >= 100)
	m_iLargeContainerSize = iValue;
}

void PS_ASD::SetMaxCompactionSegmentsTo (double iValue) {
    if (iValue > 0)
	m_iMaxCompactionSegs = iValue < UINT_MAX ? (unsigned int)iValue : UINT_MAX;
}

void PS_ASD::SetMaxCompactionSegmentsTo (int iValue) {
    if (iValue > 0)
	m_iMaxCompactionSegs = iValue;
}

void PS_ASD::SetMaxSegmentSizeTo (double iValue) {
    if (iValue > 0)
	m_iMaxSegmentSize = iValue < UINT_MAX ? (unsigned int)iValue : UINT_MAX;
}

void PS_ASD::SetMaxSegmentSizeTo (int iValue) {
    if (iValue > 0)
	m_iMaxSegmentSize = iValue;
}

void PS_ASD::SetMSSOverrideTo (double iValue) {
    if (iValue < PS_ASD_MinSegment (this) || iValue > PS_ASD_RootSegment (this) + 1)
	m_bMinSMDSet = false;
    else {
	m_xMinSMD = (unsigned int)iValue - m_xBaseSegment;
	m_bMinSMDSet = true;
    }
}

void PS_ASD::SetMSSOverrideTo (int iValue) {
    if (iValue < PS_ASD_MinSegment (this) || iValue > PS_ASD_RootSegment (this) + 1)
	m_bMinSMDSet = false;
    else {
	m_xMinSMD = iValue - m_xBaseSegment;
	m_bMinSMDSet = true;
    }
}
