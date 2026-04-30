#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <stdexcept>

using namespace std;

/**
 * ENTITY OBJECT: ShipmentInfo
 * Ref: image_3.png, image_4.png
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
 * Ref: image_3.png, image_4.png
 */
class InformationController {
private:
    const double MAX_WEIGHT = 50.0; // BVA Limit

public:
    string verifyAndProcess(ShipmentInfo &info) {
        // White Box: Branch Coverage for Weight Limits
        if (info.weight <= 0 || info.weight > MAX_WEIGHT) {
            return "FAILED: Weight Limit Error";
        }

        // White Box: Branch Coverage for Phone Validation
        if (info.senderPhone.length() < 5 || info.receiverPhone.length() < 5) {
            return "FAILED: Invalid Phone";
        }

        // Unique tracking ID generation
        info.trackingID = "TRK-" + to_string(time(0) % 100000);
        return "SUCCESS";
    }
};

struct TestCase {
    string id;
    string description;
    string sPhone;
    string rPhone;
    double weight;
    string expected;
};

void runAutomatedTests() {
    InformationController controller;
    
    // 15 Black Box Test Cases
    vector<TestCase> tests = {
        {"TC01", "Valid Standard Case", "98765", "54321", 2.0, "SUCCESS"},
        {"TC02", "BVA: Max Weight Limit", "98765", "54321", 50.0, "SUCCESS"},
        {"TC03", "BVA: Min Weight Limit", "98765", "54321", 0.01, "SUCCESS"},
        {"TC04", "BVA: Above Max Weight", "98765", "54321", 50.1, "FAILED: Weight Limit Error"},
        {"TC05", "BVA: Zero Weight", "98765", "54321", 0.0, "FAILED: Weight Limit Error"},
        {"TC06", "ECP: Short Sender Phone", "987", "54321", 5.0, "FAILED: Invalid Phone"},
        {"TC07", "ECP: Short Receiver Phone", "98765", "543", 10.0, "FAILED: Invalid Phone"},
        {"TC08", "ECP: Negative Weight", "98765", "54321", -5.0, "FAILED: Weight Limit Error"},
        {"TC09", "ECP: Valid Mid-Weight", "123456", "654321", 49.9, "SUCCESS"},
        {"TC10", "ECP: Valid Lower-Weight", "123456", "654321", 0.1, "SUCCESS"},
        {"TC11", "Valid Express Case", "00000", "11111", 25.0, "SUCCESS"},
        {"TC12", "BVA: Min Phone Length", "123", "12345", 10.0, "FAILED: Invalid Phone"},
        {"TC13", "BVA: Extreme High Weight", "99999", "88888", 50.001, "FAILED: Weight Limit Error"},
        {"TC14", "BVA: Extreme Low Weight", "11111", "22222", 0.001, "SUCCESS"},
        {"TC15", "Valid Typical Case", "55555", "44444", 5.5, "SUCCESS"}
    };

    // Table Header Construction (Total width increased to 105 chars)
    string line = "+------+--------------------------+-------------------------+--------------------------------+------------+";
    cout << "\n" << line << endl;
    cout << "| " << left << setw(4) << "ID" 
         << " | " << setw(24) << "TEST DESCRIPTION" 
         << " | " << setw(23) << "EXPECTED OUTCOME" 
         << " | " << setw(30) << "ACTUAL RESULT" 
         << " | " << setw(10) << "STATUS" << " |" << endl;
    cout << line << endl;

    int passedCount = 0;
    for (const auto& t : tests) {
        ShipmentInfo ship;
        ship.senderPhone = t.sPhone;
        ship.receiverPhone = t.rPhone;
        ship.weight = t.weight;

        string actual;
        try {
            actual = controller.verifyAndProcess(ship);
        } catch (...) {
            actual = "EXCEPTION CAUGHT";
        }

        bool isPass = (actual == t.expected);
        if(isPass) passedCount++;
        string status = isPass ? "PASS" : "FAIL";

        cout << "| " << left << setw(4) << t.id 
             << " | " << setw(24) << t.description
             << " | " << setw(23) << t.expected 
             << " | " << setw(30) << actual 
             << " | " << setw(10) << status << " |" << endl;
    }
    
    cout << line << endl;
    string summary = "| SUMMARY: " + to_string(passedCount) + "/15 Test Cases Passed";
    // Total line width is 105, accounting for borders and padding
    cout << left << setw(103) << summary << " |" << endl;
    cout << line << "\n" << endl;
}

int main() {
    runAutomatedTests();
    return 0;
}