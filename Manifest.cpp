#include "Manifest.h"
#include <iostream>

// Constructor - initializes an empty manifest with zeroed statistics
Manifest::Manifest(){
    for (int i = 0; i < NUM_SECTIONS; i++){
        cabinCounts[i] = 0;
    }
    // passengerList starts empty by default (std::vector default ctor)
}

// GetCabinIndex (private helper)
// Maps a section letter to its slot in cabinCounts, so AddPassenger and
//RemovePassenger don't each need their own P/C/S if-else chain.
int Manifest::GetCabinIndex(char section){
    switch (section){
        case 'P': return 0;
        case 'C': return 1;
        case 'S': return 2;
        default:  return -1; // unrecognized section letter
    }
}

// GetSectionLabel (private helper)
// Returns the display name for a cabinCounts index, used by Print.
std::string Manifest::GetSectionLabel(int index){
    static const std::string labels[NUM_SECTIONS] = { "Port", "Center", "Starboard" };

    if (index < 0 || index >= NUM_SECTIONS){
        return "Unknown";
    }
    return labels[index];
}

// AddPassenger
//Adds ThePassenger to the manifest if it is valid and its name is not
// already present. Updates the Port/Center/Starboard statistics.
//
// Return codes:
//0 = success
//1 = invalid passenger (e.g. cabin number was never set)
// 2 = duplicate passenger name already exists in the manifest
int Manifest::AddPassenger(Passenger ThePassenger){
    std::string newFirst, newLast, newCabin;
    ThePassenger.GetInfo(newFirst, newLast, newCabin);

    if (newCabin.empty()){
        return 1; // error: invalid passenger
    }

    for (size_t i = 0; i < passengerList.size(); i++){
        std::string exFirst, exLast, exCabin;
        passengerList[i].GetInfo(exFirst, exLast, exCabin);

        if (exFirst == newFirst && exLast == newLast){
            return 2; // error: duplicate name
        }
    }

    passengerList.push_back(ThePassenger);

    int index = GetCabinIndex(newCabin[0]);
    if (index >= 0){
        cabinCounts[index]++;
    }

    return 0; // success
}

// RemovePassenger
//Removes the passenger from the manifest whose first/last name matches
// ThePassenger. Updates the Port/Center/Starboard statistics.
//
//Return codes:
// 0 = success
// 1 = no matching passenger found
int Manifest::RemovePassenger(Passenger ThePassenger){

    //grab info to look for
    std::string targetFirst, targetLast, targetCabin;
    ThePassenger.GetInfo(targetFirst, targetLast, targetCabin);

    // check each passenger against the name
    for (size_t i = 0; i < passengerList.size(); i++){
        std::string exFirst, exLast, exCabin;
        passengerList[i].GetInfo(exFirst, exLast, exCabin);

        //if it matches decrease that section's count
        if (exFirst == targetFirst && exLast == targetLast){
            int index = GetCabinIndex(exCabin[0]);
            if (index >= 0){
                cabinCounts[index]--;
            }

            //remove that passenger from vector
            passengerList.erase(passengerList.begin() + i);
            return 0; // success
        }
    }

    return 1; // error: passenger not found
}

// Print
// Prints every passenger currently in the manifest along with the
//Port/Center/Starboard passenger counts.
void Manifest::Print(void){
    using std::cout;
    cout << "Travel Manifest" << "\n";

    if (passengerList.empty()){
        cout << "(no passengers currently on the manifest)" << "\n";
    }else{
        for (size_t i = 0; i < passengerList.size(); i++){
            std::string f, l, c;
            passengerList[i].GetInfo(f, l, c);
            cout << (i + 1) << ". " << f << " " << l << "  cabin: " << c << "\n";
        }
    }

    cout << "\n" << "\n";

    for (int i = 0; i < NUM_SECTIONS; i++){
        cout << GetSectionLabel(i) << " passengers: ";
        cout << cabinCounts[i] <<"\n";
    }

    cout << "total passengers: " << passengerList.size() << "\n";
    cout << "\n" << "\n";
}