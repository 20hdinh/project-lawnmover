Group Members:
Harry Dinh 20hdinh@csu.fullerton.edu

Move Pseudocode into PDF later.

Pseudocode:
// Assumption - always an even number of disks (always in pairs)
// Because number of disks = 2n
// n disks light, n disks dark


Sort Alternate:
def sort_alternate(n, disks):
    begin = 0  
    end = 2n
        // begin and end will converge in the middle of the disks
        // while loop ends when begin > end
        while (begin HAS NOT PASSED end) do:
            for (i = begin to end) do:
                if <CURRENT AND NEXT DISK OUT OF ORDER> then <SWAP BOTH DISKS>
                i += 2
                // for loop ends when begin > end
            begin++
            end--
    return disks


Sort Lawnmower:
def sort_lawnmower(n, disks):
    // docx description sounds a lot like cocktail sort
    // EDIT: it is
    // TL;DR do bubble sort, but do both directions, left then right
    for (i = 0 to n / 2) do:
        // left to right
        for (j = 0 to 2n) do:
            if <CURRENT AND RIGHT DISK OUT OF ORDER> then <SWAP BOTH DISKS>
            j++
        // right to left
        for (i = 2n to 0) do:
            if <CURRENT AND LEFT DISK OUT OF ORDER> then <SWAP BOTH DISKS>
            j--
    return disks
