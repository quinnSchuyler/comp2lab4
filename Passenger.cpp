// Passenger.cpp
// CPET-321 Lab 4 - Travel Manifest
//
// Implements the Passenger class declared in Passenger.h.

#include "Passenger.h"
#include <cctype> //isdigit

// Constructor - initializes all fields to empty std::strings
Passenger::Passenger(){
    firstName = "";
    lastName = "";
    cabinNumber = "";
}


// IsValidCabinFormat (private helper)
// Checks every rule for a cabin number in one place, instead of
// scattering separate single-line checks through SetCabinNumber.
// Valid format is exactly: one letter from {P, C, S}, a dash,
// then three digits (e.g. "P-000" through "S-999").
bool Passenger::IsValidCabinFormat(const std::string& Val){
    const size_t EXPECTED_LENGTH = 5;
    const size_t SECTION_INDEX = 0;
    const size_t DASH_INDEX = 1;
    const size_t DIGITS_START = 2;
    const size_t DIGITS_COUNT = 3;
    const std::string VALID_SECTIONS = "PCS";

    if (Val.length() != EXPECTED_LENGTH){
        return false;
    }

    bool sectionOk = (VALID_SECTIONS.find(Val[SECTION_INDEX]) != std::string::npos);
    bool dashOk = (Val[DASH_INDEX] == '-');
    bool digitsOk = true;

    for (size_t i = DIGITS_START; i < DIGITS_START + DIGITS_COUNT; i++){
        if (!std::isdigit(static_cast<unsigned char>(Val[i]))){
            digitsOk = false;
            break;
        }
    }

    return sectionOk && dashOk && digitsOk;
}

// SetFirstName
// Rejects empty std::strings. Returns 0 on success, 1 on error.
int Passenger::SetFirstName(std::string Val){
    if (Val.empty()){
        return 1; // error: name cannot be empty
    }

    firstName = Val;
    return 0; // success
}

// SetLastName
// Rejects empty std::strings. Returns 0 on success, 1 on error.
int Passenger::SetLastName(std::string Val){
    if (Val.empty()){
        return 1; // error: name cannot be empty
    }

    lastName = Val;
    return 0; // success
}

// SetCabinNumber
// Validates that Val matches the format x-nnn, where X is P, C, or S,
// and NNN is exactly 3 digits. Returns 0 on success, 1 on error.
int Passenger::SetCabinNumber(std::string Val){
    if (!IsValidCabinFormat(Val)){
        return 1; // error: does not match required x-nnn format
    }
    
    cabinNumber = Val;
    return 0; // success
}

// GetInfo
// Composite read accessor - fills in all three fields at once.
void Passenger::GetInfo(std::string& FirstName, std::string& LastName, std::string& CabinNumber){
    FirstName = firstName;
    LastName = lastName;
    CabinNumber = cabinNumber;
}
