
#ifndef PASSENGER_H
#define PASSENGER_H
 
#include <string>
 
class Passenger{
    private:
        // Local variables of passenger information
        std::string firstName;
        std::string lastName;
        std::string cabinNumber;
        bool IsValidCabinFormat(const std::string& Val);
    
    public:
        // Constructor - initializes all fields to empty std::strings
        Passenger();
    
        // Accessor methods - write-only
        // Each returns 0 on success, or a nonzero error code if Val is invalid.
        int SetFirstName(std::string Val);
        int SetLastName(std::string Val);
        int SetCabinNumber(std::string Val);
    
        // Composite read access method
        // Fills in FirstName, LastName, and CabinNumber with the passenger's
        // current information.
        void GetInfo(std::string& FirstName, std::string& LastName, std::string& CabinNumber);
};
    
#endif // PASSENGER_H
