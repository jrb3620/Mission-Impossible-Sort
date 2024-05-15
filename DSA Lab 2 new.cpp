#include <iostream>
#include <string>
using namespace std;


const int MAX_JOB_TYPES = 8;
const int MAX_VEHICLES = 10;
const int NO_EMP = -1;
const int MAX_EMPLOYEES = 200;
enum class JobType {
    Programmer, Manager, Accountant, Analysist,
    Sales, Manufacturing, Inventory, SoftwareEnginner

};

enum class EmpName {
    David, Kevin, Sam, Mary, Bob, Marty, Sable, Betty,
    Tom, Teddy, Jerry, Ben, Sara, Donald, Damon, Darlene, Dustin, Desire
};

class VehicleType {
public:
    string manufacturer;
    string model;
    string color;

    VehicleType(string m, string mo, string c)
        : manufacturer(move(m)), model(move(mo)), color(move(c)) {}

    virtual ~VehicleType() = default;
    virtual void printDetails() const = 0;
};

class Car : public VehicleType {
public:
    int doors;

    Car(string m, string mo, string c, int d)
        : VehicleType(move(m), move(mo), move(c)), doors(d) {}

    void printDetails() const override {
        cout << "Car: " << manufacturer << " " << model << ", Color: " << color << ", Doors: " << doors << endl;
    }
};

class Plane : public VehicleType {
public:
    int numEngines;

    Plane(string m, string mo, string c, int ne)
        : VehicleType(move(m), move(mo), move(c)), numEngines(ne) {}

    void printDetails() const override {
        cout << "Plane: " << manufacturer << " " << model << ", Color: " << color << ", Engines: " << numEngines << endl;
    }
};

class Motorcycle : public VehicleType {
public:
    Motorcycle(string m, string mo, string c)
        : VehicleType(move(m), move(mo), move(c)) {}

    void printDetails() const override {
        cout << "Motorcycle: " << manufacturer << " " << model << ", Color: " << color << endl;
    }
};


// Convert JobType to string for display
string jobTypeToString(JobType job) {
    switch (job) {
    case JobType::Programmer: return "Programmer";
    case JobType::Manager: return "Manager";
    case JobType::Accountant: return "Accountant";
    case JobType::Analysist: return "Analysist";
    case JobType::Sales: return "Sales";
    case JobType::Manufacturing: return "Manufacturing";
    case JobType::Inventory: return "Inventory";
    case JobType::SoftwareEnginner: return "Software Enginneer";
    default: return "Unknown";
    }
}

// Convert EmpName to string for display
string empNameToString(EmpName name) {
    switch (name) {
    case EmpName::Kevin: return "Kevin";
    case EmpName::Ben: return "Ben";
    case EmpName::Sable: return "Sable";
    case EmpName::Bob: return "Bob";
    case EmpName::Teddy: return "Teddy";
    case EmpName::Donald: return "Donald";
    case EmpName::Dustin: return "Dustin";
    case EmpName::Betty: return "Betty";
    case EmpName::Tom: return "Tom";
    default: return "Unknown";
    }
}

EmpName stringToEmpName(const string& name) {
    if (name == "Kevin") return EmpName::Kevin;
    else if (name == "Ben") return EmpName::Ben;
    else if (name == "Sable") return EmpName::Sable;
    else if (name == "Bob") return EmpName::Bob;
    else if (name == "Teddy") return EmpName::Teddy;
    else if (name == "Donald") return EmpName::Donald;
    else if (name == "Dustin") return EmpName::Dustin;
    else if (name == "Betty") return EmpName::Betty;
    else if (name == "Tom") return EmpName::Tom;
    else {
        cout << "Unknown name. Please try again.\n";
        return static_cast<EmpName>(-1);
    }
}

JobType stringToJobType(const string& job) {
    if (job == "Programmer") return JobType::Programmer;
    else if (job == "Manager") return JobType::Manager;
    else if (job == "Accountant") return JobType::Accountant;
    else if (job == "Analysist") return JobType::Analysist;
    else if (job == "Sales") return JobType::Sales;
    else if (job == "Manufacturing") return JobType::Manufacturing;
    else if (job == "Inventory") return JobType::Inventory;
    else if (job == "Software Enginner" || job == "SoftwareEnginner") return JobType::SoftwareEnginner;
    else {
        cout << "Unknown job type. Please try again.\n";
        return static_cast<JobType>(-1);
    }
}

struct Emp {
    EmpName name = EmpName::David; // Default 
    JobType job = JobType::Programmer; // Default
    int age = 0;
    VehicleType* vehicles[MAX_VEHICLES]; // Holds up to MAX_VEHICLES
    int vehicleCount = 0;
    int prev = -1;
    int next = -1;

    // Default constructor
    Emp() {
        for (int i = 0; i < MAX_VEHICLES; ++i) {
            vehicles[i] = nullptr;
        }
    }
    Emp(EmpName n, JobType j, int a) : name(n), job(j), age(a), prev(-1), next(-1), vehicleCount(0) {
        for (int i = 0; i < MAX_VEHICLES; ++i) {
            vehicles[i] = nullptr;
        }
    }

    // Method to add a vehicle to this employee
    void addVehicle(VehicleType* vehicle) {
        if (vehicleCount < MAX_VEHICLES) {
            vehicles[vehicleCount++] = vehicle;
        }
        else {
            cout << "Cannot add more vehicles to this employee.\n";
        }
    }
};


class EmpList {
private:
    Emp employees[MAX_EMPLOYEES];
    int headIndices[MAX_JOB_TYPES]; // Indices of the head of each job type list
    int empCount = 0; // Current count of employees, used as the next free index

public:
    EmpList() {
        for (int i = 0; i < MAX_JOB_TYPES; ++i) {
            headIndices[i] = NO_EMP; // Initialize all heads to NO_EMP
        }
    }

    int insertEmp(EmpName name, JobType job, int age) {
        if (empCount >= MAX_EMPLOYEES) {
            cerr << "Maximum number of employees reached." << endl;
            return NO_EMP;
        }

        int jobIndex = static_cast<int>(job);
        int current = headIndices[jobIndex];
        int prev = NO_EMP;
        int newEmpIndex = empCount++; // Get index for new employee

        employees[newEmpIndex] = Emp(name, job, age); // Initialize the new employee

        if (current == NO_EMP) { // List is empty
            headIndices[jobIndex] = newEmpIndex;
            employees[newEmpIndex].next = newEmpIndex; 
            employees[newEmpIndex].prev = newEmpIndex; // Point to itself
        }
        else {
            // Find position to insert
            do {
                prev = current;
                current = employees[current].next;
            } while (current != headIndices[jobIndex] && (employees[current].age < age || (employees[current].age == age && employees[current].name < name)));

            employees[newEmpIndex].next = current;
            employees[newEmpIndex].prev = prev;

            employees[prev].next = newEmpIndex;
            employees[current].prev = newEmpIndex;

            if (current == headIndices[jobIndex] && (age < employees[current].age || (age == employees[current].age && name < employees[current].name))) {
                // New head of the list
                headIndices[jobIndex] = newEmpIndex;
            }
        }

        // Make it circular
        int head = headIndices[jobIndex];
        int tail = employees[head].prev;
        employees[head].prev = tail;
        employees[tail].next = head;

        return newEmpIndex; // Return the index of the newly added employee
    }

    void addVehicleToEmp(int empIndex, VehicleType* vehicle) {
        if (empIndex >= 0 && empIndex < empCount) {
            employees[empIndex].addVehicle(vehicle);
        }
        else {
            cerr << "Invalid employee index." << endl;
        }
    }

    void display() const {
        for (int i = 0; i < MAX_JOB_TYPES; ++i) {
            cout << "Job Type = " << jobTypeToString(static_cast<JobType>(i)) << endl;
            int start = headIndices[i];
            if (start == NO_EMP) { // Check if the list is empty
                cout << "No employees under this job title." << endl;
            }
            else {


                int currentIndex = start;
                do {
                    const Emp& currentEmp = employees[currentIndex];
                    cout << "Name: " << empNameToString(currentEmp.name) << ", Job: " << jobTypeToString(currentEmp.job) << ", Age: " << currentEmp.age;
                    for (int v = 0; v < currentEmp.vehicleCount; ++v) {
                        cout << "\n\tVehicle #" << v + 1 << ": ";
                        currentEmp.vehicles[v]->printDetails();
                    }
                    cout << endl;
                    currentIndex = employees[currentIndex].next;
                } while (currentIndex != start); // Loop until we return to the start
            }

        }
    }

    void displayReverse() const {
        for (int i = 0; i < MAX_JOB_TYPES; ++i) {
            cout << "Job Type = " << jobTypeToString(static_cast<JobType>(i)) << " (Reverse)" << endl;
            int start = headIndices[i];
            if (start == NO_EMP) { // Check if the list is empty
                cout << "No employees under this job title." << endl;
            }
            else {
                // Start from the element before the head (the tail, in a circular list)
                int currentIndex = employees[start].prev;
                do {
                    const Emp& currentEmp = employees[currentIndex];
                    cout << "Name: " << empNameToString(currentEmp.name) << ", Job: " << jobTypeToString(currentEmp.job) << ", Age: " << currentEmp.age;
                    for (int v = 0; v < currentEmp.vehicleCount; ++v) {
                        cout << "\n\tVehicle #" << v + 1 << ": ";
                        currentEmp.vehicles[v]->printDetails();
                    }
                    cout << endl;
                    currentIndex = employees[currentIndex].prev;
                } while (currentIndex != employees[start].prev); // Loop until we return to the start (tail)
            }
        }
    }


};

int main() {
    EmpList list;
    string inputName, inputJob;
    int inputAge = 0;
    string make, model, type, color;
    int numDoors = 0;
    int numEngines = 0;
    char continueInput = 'y';

    while (continueInput == 'y' || continueInput == 'Y') {
        cout << "Enter employee name: ";
        cin >> inputName;
        cout << "Enter job type: ";
        cin >> inputJob;
        cout << "Enter age: ";
        cin >> inputAge;

        EmpName nameEnum = stringToEmpName(inputName);
        JobType jobEnum = stringToJobType(inputJob);
        int newEmpIndex = list.insertEmp(nameEnum, jobEnum, inputAge);

        if (newEmpIndex == NO_EMP) {
            cerr << "Failed to insert employee. List may be full." << endl;
            continue;
        }

        int numVehicles = 0;
        cout << "How many vehicles does the employee have? ";
        cin >> numVehicles;
        for (int i = 0; i < numVehicles; ++i) {
            cout << "Enter vehicle #" << (i + 1) << " type (Plane, Car, Motorcycle): ";
            cin >> type;
            VehicleType* veh = nullptr;
            if (type == "Plane" || type == "plane") {
                cout << "Enter plane manufacturer: ";
                cin >> make;
                cout << "Enter number of engines: ";
                cin >> numEngines;
                cout << "Enter the color: ";
                cin >> color;
                veh = new Plane(make, model, color, numEngines);
            }
            else if (type == "Car" || type == "car") {
                cout << "Enter car make: ";
                cin >> make;
                cout << "Enter car model: ";
                cin >> model;
                cout << "Enter number of doors: ";
                cin >> numDoors;
                cout << "Enter the color: ";
                cin >> color;
                veh = new Car(make, model, color, numDoors);
            }
            else if (type == "Motorcycle" || type == "motorcycle") {
                cout << "Enter motorcycle manufacturer: ";
                cin >> make;
                cout << "Enter the color: ";
                cin >> color;

                veh = new Motorcycle(make, model, color);
            }
            if (veh != nullptr) {
                list.addVehicleToEmp(newEmpIndex, veh); // Use function that's public (can't directly access emp (professional grade?))
            }
        }
        cout << "Do you want to enter another employee? (y/n): ";
        cin >> continueInput;
    }

    list.display();
    cout << "============================" << endl;
    list.displayReverse();

    return 0;
}
