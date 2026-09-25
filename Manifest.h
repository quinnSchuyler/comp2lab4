
#ifndef MANIFEST_H
#define MANIFEST_H
 
#include <vector>
#include "Passenger.h"
#include <string>
 
class Manifest{
    private:
        // Local variables of manifest information
        std::vector<Passenger> passengerList;
        int portCount;
        int centerCount;
        int starboardCount;
        
        static const int NUM_SECTIONS = 3;
        int cabinCounts[NUM_SECTIONS];
        
        int GetCabinIndex(char section);
        std::string GetSectionLabel(int index);
    
    public:
        // Constructor - initializes an empty manifest with zeroed statistics
        Manifest();
    
        // Manifest manipulation methods
        // Returns 0 on success.
        // AddPassenger returns a nonzero error code if ThePassenger is invalid
        // empty cabin number or if a passenger with the same name
        // already exists in the manifest.
        int AddPassenger(Passenger ThePassenger);
    
        // Returns 0 on success, nonzero if no matching passenger was found.
        int RemovePassenger(Passenger ThePassenger);
    
        //print
        void Print(void);
};
 
 
#endif // MANIFEST_H
