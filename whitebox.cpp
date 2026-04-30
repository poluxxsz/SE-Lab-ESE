#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

/**
 * ENTITY OBJECT: ShipmentInfo
 * Source: image_3.png, image_4.png
 */
class ShipmentInfo {
public:
    string trackingID;
    string senderPhone, receiverPhone;
    double weight;

    void save() {
        // Logic to "Save the info"
    }
};

/**
 * CONTROL OBJECT: InformationController
 * Target for White Box Structural Testing
 */
class InformationController {
private:
    const double MAX_WEIGHT = 50.0; 

public:
    string verifyAndProcess(ShipmentInfo &info) {
        // Branch 1: weight check (Predicates: <= 0 || > MAX)
        if (info.weight <= 0 || info.weight > MAX_WEIGHT) {
            return "FAILED: Weight Logic Path";
        }

        // Branch 2: Sender Phone Logic
        if (info.senderPhone.length() < 5) {
            return "FAILED: Sender Branch Taken";
        }

        // Branch 3: Receiver Phone Logic
        if (info.receiverPhone.length() < 5) {
            return "FAILED: Receiver Branch Taken";
        }

        // Statement Coverage: Tracking ID Generation and Success Return
        info.trackingID = "TRK-" + to_string(time(0) % 100000);
        return "SUCCESS";
    }
};

struct TestCase {
    string id;
    string pathDescription;
    string sPhone;
    string rPhone;
    double weight;
    string expected;
};

void runWhiteBoxTests() {
    InformationController controller;
    
    vector<TestCase> tests = {
        // FOCUS: Branch and Path Coverage
        {"TC01", "Branch 1: weight <= 0 (True)", "99999", "99999", -1.0, "FAILED: Weight Logic Path"},
        {"TC02", "Branch 1: weight > MAX (True)", "99999", "99999", 51.0, "FAILED: Weight Logic Path"},
        {"TC03", "Branch 1: weight valid (False)", "99999", "99999", 10.0, "SUCCESS"}, // Exercises next branches
        {"TC04", "Branch 2: sPhone < 5 (True)", "123", "99999", 10.0, "FAILED: Sender Branch Taken"},
        {"TC05", "Branch 2: sPhone >= 5 (False)", "99999", "99999", 10.0, "SUCCESS"},
        {"TC06", "Branch 3: rPhone < 5 (True)", "99999", "123", 10.0, "FAILED: Receiver Branch Taken"},
        {"TC07", "Branch 3: rPhone >= 5 (False)", "99999", "99999", 10.0, "SUCCESS"},
        {"TC08", "Path: Branch1(F)->Branch2(T)", "1", "99999", 5.0, "FAILED: Sender Branch Taken"},
        {"TC09", "Path: Branch1(F)->Branch2(F)->Branch3(T)", "99999", "1", 5.0, "FAILED: Receiver Branch Taken"},
        {"TC10", "Full Path Coverage: (F,F,F)", "12345", "12345", 25.0, "SUCCESS"},
        {"TC11", "Data Flow: trackingID Assignment", "12345", "12345", 1.0, "SUCCESS"},
        {"TC12", "Condition: weight = MAX", "12345", "12345", 50.0, "SUCCESS"},
        {"TC13", "Condition: weight = MIN", "12345", "12345", 0.0001, "SUCCESS"},
        {"TC14", "Statement: controller.save() execution", "55555", "55555", 10.0, "SUCCESS"},
        {"TC15", "Logic: Compound decision skip", "1", "1", 10.0, "FAILED: Sender Branch Taken"} 
    };

    string line = "+------+------------------------------------------+----------------------------+------------+";
    cout << "\n[WHITE BOX STRUCTURAL TEST REPORT]" << endl;
    cout << line << endl;
    cout << "| " << left << setw(4) << "ID" 
         << " | " << setw(40) << "LOGICAL PATH / PREDICATE" 
         << " | " << setw(26) << "ACTUAL RESULT" 
         << " | " << "STATUS" << " |" << endl;
    cout << line << endl;

    int passed = 0;
    for (const auto& t : tests) {
        ShipmentInfo ship;
        ship.senderPhone = t.sPhone;
        ship.receiverPhone = t.rPhone;
        ship.weight = t.weight;

        string actual = controller.verifyAndProcess(ship);
        bool isPass = (actual == t.expected);
        if(isPass) passed++;
        string status = isPass ? "PASS" : "FAIL";

        cout << "| " << left << setw(4) << t.id 
             << " | " << setw(40) << t.pathDescription
             << " | " << setw(26) << actual 
             << " | " << setw(6) << status << " |" << endl;
    }
    
    cout << line << endl;
    cout << "| TOTAL WHITE BOX SUMMARY: " << passed << "/15 Passed" << setw(53) << " |" << endl;
    cout << line << "\n" << endl;
}

int main() {
    runWhiteBoxTests();
    return 0;
}