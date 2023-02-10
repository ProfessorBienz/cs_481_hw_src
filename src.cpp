#include "src.hpp"


void protection_fault()
{
    throw "Protection Fault!";
}

void segmentation_fault()
{
    throw "Segmentation Fault!";
}

void page_fault()
{
    throw "Page Fault!";
}

void tlb_miss()
{
    throw "TLB Miss!";
}


