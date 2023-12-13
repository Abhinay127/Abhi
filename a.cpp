#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>
#include <algorithm>
#include <cstdlib>

using namespace std;

class Person {
protected:
    string name;
    int age;

public:
    Person(const string& n, int a) : name(n), age(a) {}

    virtual void displayInfo() const {
        cout << "Name: " << name << "\nAge: " << age << endl;
        if(age<=0){
            cerr<<"invalid age";
        }
    }
};

class Doctor : public Person {
private:
    string specialty;

public:
    Doctor(const string& n, int a, const string& spec) : Person(n, a), specialty(spec) {}

    void displayInfo() const override {
        Person::displayInfo();
        cout << "Specialty: " << specialty << endl;
    }

    const string& getSpecialty() const {
        return specialty;
    }
};

class Patient : public Person {
private:
    int patientId;
    string illness;

public:
    Patient(const string& n, int a, int pid, const string& ill) : Person(n, a), patientId(pid), illness(ill) {}

    void displayInfo() const override {
        Person::displayInfo();
        cout << "Patient ID: " << patientId << "\nIllness: " << illness << endl;
    }

    const string& getIllness() const {
        return illness;
    }
};

class Hospital {
private:
    static map<string, vector<string>> specializedDoctors;
    static map<string, string> doctorSpecialties;

public:
    static void initializeSpecializedDoctors() {
        specializedDoctors["Homiopathy"] = {"Dr. Shashikant Apte", "Dr. Homi Specialist 2", "Dr. Homi Specialist 3"};
        specializedDoctors["Alopathy"] = {"Dr. Tushar Patil", "Dr. Alo Specialist 2", "Dr. Alo Specialist 3"};
        specializedDoctors["Orthopedic"] = {"Dr. Shona Milon Nag", "Dr. Ortho Specialist 2", "Dr. Ortho Specialist 3"};
        specializedDoctors["Cardiologist"] = {"Dr. Kannan Subramanian", "Dr. Cardio Specialist 2", "Dr. Cardio Specialist 3"};
        specializedDoctors["Neuro Surgeon"] = {"Dr. Chandrakant Lahane", "Dr. Neuro Specialist 2", "Dr. Neuro Specialist 3"};
        specializedDoctors["Child Specialist"] = {"Dr. Joy Debasis Ghose", "Dr. Child Specialist 2", "Dr. Child Specialist 3"};
        specializedDoctors["Cytologist"] = {"Dr. Snita Sinukumar", "Dr. Cytology Specialist 2", "Dr. Cytology Specialist 3"};
    }

    static void suggestSpecializedDoctor(const string& illness) {
        auto it = specializedDoctors.find(illness);
        if (it != specializedDoctors.end() && !it->second.empty()) {
            cout << "Suggested Specialized Doctors for " << illness << ":\n";
            for (size_t i = 0; i < 3 && i < it->second.size(); ++i) {
                cout << i + 1 << ". " << it->second[i] << endl;
            }

            cout << "\nRecommended Doctor: ";
            if (it->second.size() > 0) {
                cout << it->second[0] << endl;
            } else {
                cout << "No recommendation available.\n";
            }
        } else {
            cout << "No specialized doctor found for the given illness.\n";
        }
    }

    static Person* getPerson(const string& name) {
        auto specialtyIt = doctorSpecialties.find(name);
        if (specialtyIt != doctorSpecialties.end()) {
            return new Doctor(name, 0, specialtyIt->second);
        } else {
            return new Person(name, 0);
        }
    }

    static void displayIllnessList() {
        cout << "Choose illness from the options:\n"
                "1. Homiopathy\n"
                "2. Alopathy\n"
                "3. Orthopedic\n"
                "4. Cardiologist\n"
                "5. Neuro Surgeon\n"
                "6. Child Specialist\n"
                "7. Cytologist\n";
    }
};

map<string, vector<string>> Hospital::specializedDoctors;
map<string, string> Hospital::doctorSpecialties;

bool isAlpha(const string& str) {
    return all_of(str.begin(), str.end(), ::isalpha);
}

bool isInteger(const string& str) {
    return all_of(str.begin(), str.end(), ::isdigit);
}

int main() {
    do {
        Hospital::initializeSpecializedDoctors();

        vector<Person*> hospitalStaff;

        string patientName, illness;
        int patientAge, patientId;

        do {
            cout << "Name: ";
            cin >> patientName;
        } while (!isAlpha(patientName));

        do {
            cout << "Age: ";
            string ageInput;
            cin >> ageInput;
            if(stoi(ageInput)<=0){
                cerr<<"enter valid age\n";
                exit(1);
            }
            if (isInteger(ageInput)) {
                patientAge = stoi(ageInput);
                break;
            } else {
                cout << "Invalid input. Please enter a valid integer for age.\n";
            }
        } while (true);

        do {
            cout << "Patient ID: ";
            string idInput;
            cin >> idInput;
            if (isInteger(idInput)) {
                patientId = stoi(idInput);
                break;
            } else {
                cout << "Invalid input. Please enter a valid integer for patient ID.\n";
            }
        } while (true);

        Hospital::displayIllnessList();

        cout << "Enter the number corresponding to the illness: ";
        int illnessChoice;
        cin >> illnessChoice;

        switch (illnessChoice) {
            case 1:
                illness = "Homiopathy";
                break;
            case 2:
                illness = "Alopathy";
                break;
            case 3:
                illness = "Orthopedic";
                break;
            case 4:
                illness = "Cardiologist";
                break;
            case 5:
                illness = "Neuro Surgeon";
                break;
            case 6:
                illness = "Child Specialist";
                break;
            case 7:
                illness = "Cytologist";
                break;
            default:
                cerr << "Invalid choice.\n";
                return 1;
        }

        hospitalStaff.push_back(new Patient(patientName, patientAge, patientId, illness));

        cout << "\nPatient Information:" << endl;
        for (auto& staff : hospitalStaff) {
            staff->displayInfo();
            cout << endl;
        }

        if (auto patient = dynamic_cast<Patient*>(hospitalStaff[0])) {
            Hospital::suggestSpecializedDoctor(patient->getIllness());
        } else {
            cerr << "Failed to cast to Patient.\n";
        }

        for (auto& staff : hospitalStaff) {
            delete staff;
        }

        cout << "Do you want to enter another patient? (y/n): ";
        char outerChoice;
        cin >> outerChoice;

        if (outerChoice != 'y' && outerChoice != 'Y') {
            break;
        }

    } while (true);

    return 0;
}
