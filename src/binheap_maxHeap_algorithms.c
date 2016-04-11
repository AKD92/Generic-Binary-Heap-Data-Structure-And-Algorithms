

/************************************************************************************
    Implementation of Algorithms for Binary MAX Heap Creation & Manipulation
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "binheap.h"







int binheap_sinkLightElement(BinHeap *heap, unsigned int index) {     /* This is MAX-HEAPIFY operation */
    
    int nSwaps;
    unsigned int iLargest;
    unsigned int iLeft, iRight;
    
    unsigned char *pArray;
    unsigned char *pCurrent, *pLeft, *pRight, *pLargest;
    
    
    /* Check for invalid index argument */
    if (index >= binheap_size(heap))
        return -1;
    if (index == binheap_size(heap) - 1)
        return 0;
    
    
    /* nSwaps = Number of shifts/swaps needed so far */
    nSwaps = 0;
    pArray = (unsigned char *) binheap_array(heap);
    
    
    /********************************************************************************
        Recursive call to binheap_sinkLightElement() with a different index 'iLargest'
        For the sake of efficiency, an iterative approach might be helpful
        Utilizing simple GOTO statement as a way of iteration/looping.
    ********************************************************************************/
    
    
    /* Execution of SINK Algorithm begins now */
    REPEAT:                                                           /* Code in iterative approach */
    iLargest = index;
    iLeft = binheap_leftChildIndex(index);
    iRight = binheap_rightChildIndex(index);
    
    pLeft = pArray + (binheap_width(heap) * iLeft);
    pRight = pArray + (binheap_width(heap) * iRight);
    pCurrent = pArray + (binheap_width(heap) * index);
    pLargest = pArray + (binheap_width(heap) * iLargest);
    
    if ( iLeft < binheap_size(heap)
        && heap->fpCompare((const void*) pLeft, (const void*) pCurrent) > 0 )
    {
        iLargest = iLeft;
        pLargest = pArray + (binheap_width(heap) * iLargest);
    }
    if ( iRight < binheap_size(heap)
        && heap->fpCompare((const void*) pRight, (const void*) pLargest) > 0 )
    {
        iLargest = iRight;
        pLargest = pArray + (binheap_width(heap) * iLargest);
    }
    
    if ( iLargest != index ) {
        
        binheap_swapElements(index, iLargest, heap);
        nSwaps = nSwaps + 1;                                          /* Code in iterative approach */
        
        /********************************************************************************
            Recursive call to binheap_sinkLightElement() with a different index 'iLargest'
            Can be done through an iterative approach (more efficient for computers)
            By stating 'index = iLargest' and then repeat again. Revision required.
        ********************************************************************************/
        
        /* nSwaps = 1 + binheap_sinkLightElement(heap, iLargest); */  /* Code in recursive approach */
        
        index = iLargest;                                             /* Code in iterative approach */
        goto REPEAT;                                                  /* Code in iterative approach */
    }
    
    return nSwaps;
}



int binheap_swimHeavyElement(BinHeap *heap, unsigned int index) {     /* This is HEAP-SWIM operation */
    
    int iCompareVal, nSwaps;
    unsigned int iParent;
    register unsigned int iCurrent;
    unsigned char *pArray, *pParent, *pCurrent;
    
    
    /* Check for invalid index argument */
    if (index >= binheap_size(heap))
        return -1;
    if (index == 0)
        return 0;
    
    
    /* nSwaps = Number of shifts/swaps needed so far */
    nSwaps = 0;
    iCompareVal = 0;
    iCurrent = index;
    pArray = (unsigned char *) binheap_array(heap);
    
    
    /* Execution of SWIM Algorithm begins now */
    REPEAT:
    iParent = binheap_parentIndex(iCurrent);
    pParent = pArray + (binheap_width(heap) * iParent);
    pCurrent = pArray + (binheap_width(heap) * iCurrent);
    iCompareVal = heap->fpCompare((const void*) pParent, (const void*) pCurrent);
    
    if (iCompareVal < 0) {
        
        binheap_swapElements(iParent, iCurrent, heap);
        nSwaps = nSwaps + 1;
        iCurrent = iParent;
        if (iCurrent > 0) goto REPEAT;
    }
    
    return nSwaps;
}



int binheap_buildBinaryMaxHeap(BinHeap *heap) {
    
    register unsigned int index;
    
    
    /* Check for invalid function argument */
    if (heap == 0)
        return -1;
    
    index = 1;
    while ( index < binheap_size(heap) ) {
        binheap_swimHeavyElement(heap, index);                        /* Perform a HEAP-SWIM operation */
        index = index + 1;
    }
    
    /*************************************************************************************
        Or, we could also perform a MAX-HEAPIFY operation to achieve same goal
        
        index = (binheap_size(heap) / 2);
        while (index >= 1) {
            binheap_sinkLightElement(heap, index - 1);      // Perform a MAX-HEAPIFY operation
            index = index - 1;
        }
    *************************************************************************************/
    
    return 0;
}


