#ifndef TEST_SRC_HPP
#define TEST_SRC_HPP

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

/***********************************
 * PTE : Page Table Entry
 ***********************************/
class PTE
{
    public:
        PTE()
        {
            PFN = 0;
            protect_bit = 0;
            present_bit = 0;
        }

        ~PTE()
        {

        }

        bool can_access()
        {
            return not protect_bit;
        }

        int PFN;
        int protect_bit;
        int present_bit;
};


/***********************************
 * Page Table
 ***********************************/
class PageTable
{
    public:
        PageTable(int _num_pages)
        {
            num_pages = _num_pages;
            if (num_pages)
            {
                entries = new PTE[num_pages];
                valid_bits = new int[num_pages]();
            }
            else
            {
                entries = NULL;
                valid_bits = NULL;
            }
        }

        ~PageTable()
        {
            if (num_pages)
            {
                delete[] entries;
                delete[] valid_bits;
            }
        }

        void add_page(int VPN, int PFN, int protect_bit = 0)
        {
            entries[VPN].PFN = _PFN;
            entries[VPN].protect_bit = _protect_bit;
            valid_bits[VPN] = 1;
        }

        void remove_page(int VPN)
        {
            valid_bits[VPN] = 0;
        }

        PTE& lookup(int VPN)
        {
            return entries[VPN];
        }

        PTE* entries;
        int* valid_bits;
        int num_pages;
};


/***********************************
 * TLB Set 
 ***********************************/
class TLB_set
{
    public:
        TLB_set(int _set_size)
        {
            set_size = _set_size;
            if (set_size)
            {
                entries = new PTE[set_size];
                valid_bits = new int[set_size]();
                tags = new int[set_size];
                indices = new int[set_size];
            }
        }

        ~TLB_set()
        {
            for (int i = 0; i < set_size; i++)
                delete entries[i];
            delete[] entries;
        }

        void add_entry(int tag, PTE& entry)
        {
            // If available spot in set, add TLB entry
            for (int i = 0; i < set_size; i++)
            {
                if (valid_bits[i] == 0)
                {
                    valid_bits[i] = 1;
                    tags[i] = tag;
                    entries[i]->PFN = entry.PFN;
                    entries[i]->protect_bit = entry.protect_bit;
                    entries[i]->present_bit = entry.present_bit;
                    return;
                }
            }

            // If no available spots in set, 
            //    1. remove entry with lowest idx
            //    2. add TLB entry to this position
            int idx = 0;
            int min_counter;
            while (idx < set_size)
            {
                if (valid_bits[i])
                {
                    min_counter = indices[i];
                    break;
                }
                idx++;
            }
            for (int i = idx+1; i < set_size; i++)
            {
                if (min_counter > indices[i])
                {
                    min_counter = indices[i];
                    idx = i;
                }
            }

            // Reset Entry at Min IDX
            entries[min_idx]->PFN = entry->PFN;
            entries[min_idx]->protect_bit = entry->protect_bit;
            entries[min_idx]->present_bit = entry->present_bit;
            valid_bits[min_idx] = 1;
            tags[min_idx] = tag;
        }

        bool lookup(int tag, TLB_entry& entry)
        {
            for (int i = 0; i < set_size; i++)
            {
                if (tags[i] == tag && valid_bits[i] == 1)
                {
                    entry.PFN = entries[i].PFN;
                    entry.protect_bit = entries[i].protect_bit;
                    entry.present_bit = entries[i].present_bit;
                    return true;
                }
            }
            return false;
        }

        PTE* entries;
        int* valid_bits;
        int* tag;
        int* indices;
};

/***********************************
 * TLB K-Way Set-Associative Cache 
 ***********************************/
class TLB
{
    public:
        TLB(int _k, int set_size)
        {
            k = _k;
            if (k > 0)
            {
                sets = new TLB_set[k];
                for (int i = 0; i < k; i++)
                    sets[i].create_set(set_size);
            }
        }

        ~TLB()
        {
            if (k)
            {
                delete[] sets;
            }
        }

        void add_entry(int idx, int tag, int PFN, int protect_bit = 0)
        {
            sets[idx].add_entry(tag, PFN, protect_bit);
        }
        
        bool lookup(int idx, int tag, TLB_entry** entry)
        {
            return sets[idx].lookup(tag, entry); 
        }

        TLB_set* sets;
        int k;
};



/***********************************
 * Frame List : 
 *    for replacment algorithm
 **********************************/
class FrameList
{
    public:
        FrameList(int _idx)
        {
            next = NULL;
            clock_bit = 1;
            idx = _idx;
        }

        ~FrameList()
        {

        }


        void access(int _idx)
        {
            clock_bit = 1;
            idx = _idx;
        }

        FrameList* next;
        int idx;
        int clock_bit;
};

/***********************************
 * To be implemented by you
 **********************************/
// translation.cpp
void split_virtual_address(int virtual_address, int page_size, int* VPN, int* offset);
void split_VPN(int VPN, int k, int* index, int* tag);
int TLB_lookup(TLB* tlb, int VPN);
int table_lookup(PageTable* table, TLB* tlb, int VPN);
int get_physical_address(int PFN, int offset, int page_size);
int virtual_to_physical(int virtual_address, int page_size, TLB* tlb, PageTable* table);
// replacement.cpp
int fifo(FrameList* active_frames, FrameList** frame_to_remove_ptr);
int lru(FrameList* active_frames, FrameList** frame_to_remove_ptr);
int clock_lru(FrameList* active_frames, FrameList** frame_to_remove_ptr);



/***********************************
 * Implemented in src.cpp 
 ***********************************/
void protection_fault();
void segmentation_fault();
void page_fault();
void tlb_miss();




#endif
