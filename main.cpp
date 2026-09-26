#include <iostream>
#include <string>
#include "Passenger.h"
#include "Manifest.h"


int askMode(){
    using std::cin, std::cout;
    int choice = 0;
    while((choice <1) or (choice >5)){
    cout << "Choose one of the following: \n";
    cout << "1. create a passenger \n";
    cout << "2. add most recent passenger to manifest \n";
    cout << "3. remove the most recently created passenger from the manifest \n";
    cout << "4. print out manifest \n";
    cout << "5. quit \n";
    cout << "\n";
    cin >> choice;
    } //end while
    return choice;
}

int main(){
    using std::cin, std::cout, std::string;

    Manifest travelManifest;
    std::vector<Passenger> createdPassengers;

    while(1){
        int mode = 0;
        mode = askMode();
        switch(mode){
            // Replace cases 1, 2, and 3 with this:
            case 1: {
                string fName, lName, cabin;
                cout << "enter first name: ";
                cin >> fName;
                cout << "enter last name: ";
                cin >> lName;
                cout << "enter cabin number (e.g., P-001, c-123, S-999): ";
                cin >> cabin;

                //uppercase that letter, was bothering me
                if (!cabin.empty()) {
                    cabin[0] = std::toupper(static_cast<unsigned char>(cabin[0]));
                }

                Passenger temp;
                if(temp.SetFirstName(fName) != 0){
                    cout << "can't have empty first name\n";
                } else if(temp.SetLastName(lName) != 0){
                    cout << "can't have empty last name\n";
                } else if(temp.SetCabinNumber(cabin) != 0){
                    cout << "bad cabin number format, try again\n";
                } else {
                    createdPassengers.push_back(temp);
                    cout << "successfully created passenger\n";
                }
                break;
            }
            case 2: {
                if(createdPassengers.empty()){
                    cout << "no passenger to add\n";
                } else {
                    int result = travelManifest.AddPassenger(createdPassengers.back());
                    if(result == 0){
                        cout << "successfully added passenger\n";
                    } else if(result == 1){
                        cout << "invalid passenger information\n";
                    } else if(result == 2){
                        cout << "Someone with this name is already a passenger\n";
                    }
                }
                break;
            }
            case 3: {
                if(createdPassengers.empty()){
                    cout << "no passenger exists\n";
                } else {
                    int result = travelManifest.RemovePassenger(createdPassengers.back());
                    if(result == 0){
                        cout << "successfully removed passenger\n";
                        createdPassengers.pop_back();
                    } else {
                        cout << "no matching passenger found on manifest\n";
                    }
                }
                break;
            }
            case 4: {
                travelManifest.Print();
                break;
            }
            case 5: {
                cout << "program terminated by user \n";
                exit(0);
            }
            default:
                cout << "something went wrong \n";
        }
        
        string pauseInput;
        cout << "\nenter any text or character and press enter to continue: ";
        cin >> pauseInput;
    }//while
}