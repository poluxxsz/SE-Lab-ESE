#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

/**
 * ENTITY OBJECT: ShipmentInfo
 */
class ShipmentInfo {
public:
    string trackingID;
    string senderName, senderPhone;
    string receiverName, receiverPhone;
    double weight;
    string serviceType;
    string deliveryDate;

    void save() {
        // Logic to "Save the info" as per image_3.png
    }
};

/**
 * CONTROL OBJECT: InformationController
 */
class InformationController {
private:
    const double MAX_WEIGHT = 50.0; // BVA Limit

public:
    string verifyAndProcess(ShipmentInfo &info) {
        // White Box Testing: Weight limits (BVA)
        if (info.weight <= 0 || info.weight > MAX_WEIGHT) {
            return "FAILED: Weight Limit Error";
        }

        // Logic for "Verifies the information" (Phone length check)
        if (info.senderPhone.length() < 5 || info.receiverPhone.length() < 5) {
            return "FAILED: Invalid Phone";
        }

        info.trackingID = "TRK-" + to_string(time(0) % 100000);
        info.save();
        return "SUCCESS";
    }
};

struct TestCase {
    string id;
    string sPhone;
    string rPhone;
    double weight;
    string expected;
};

void runAutomatedTests() {
    InformationController controller;
    
    // Hardcoded 15 Black Box Test Cases
    vector<TestCase> tests = {
        {"BB01", "98765", "54321", 2.0, "SUCCESS"},
        {"BB02", "98765", "54321", 50.0, "SUCCESS"},
        {"BB03", "98765", "54321", 0.01, "SUCCESS"},
        {"BB04", "98765", "54321", 50.1, "FAILED: Weight Limit Error"},
        {"BB05", "98765", "54321", 0.0, "FAILED: Weight Limit Error"},
        {"BB06", "987", "54321", 5.0, "FAILED: Invalid Phone"},
        {"BB07", "98765", "543", 10.0, "FAILED: Invalid Phone"},
        {"BB08", "98765", "54321", -5.0, "FAILED: Weight Limit Error"},
        {"BB09", "123456", "654321", 49.9, "SUCCESS"},
        {"BB10", "123456", "654321", 0.1, "SUCCESS"},
        {"BB11", "00000", "11111", 25.0, "SUCCESS"},
        {"BB12", "123", "12345", 10.0, "FAILED: Invalid Phone"},
        {"BB13", "99999", "88888", 50.001, "FAILED: Weight Limit Error"},
        {"BB14", "11111", "22222", 0.001, "SUCCESS"},
        {"BB15", "55555", "44444", 5.5, "SUCCESS"}
    };

    // Table Header Construction
    string line = "+--------+---------------------------+---------------------------+--------+";
    cout << "\n" << line << endl;
    cout << "| " << left << setw(6) << "ID" 
         << " | " << setw(25) << "EXPECTED OUTCOME" 
         << " | " << setw(25) << "ACTUAL RESULT" 
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

        cout << "| " << left << setw(6) << t.id 
             << " | " << setw(25) << t.expected 
             << " | " << setw(25) << actual 
             << " | " << setw(6) << status << " |" << endl;
    }
    
    cout << line << endl;
    cout << "| SUMMARY: " << passed << "/15 Test Cases Passed" << setw(46) << " |" << endl;
    cout << line << "\n" << endl;
}

int main() {
    runAutomatedTests();
    return 0;
}