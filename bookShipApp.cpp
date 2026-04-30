#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

/**
 * ENTITY OBJECT: ShipmentInfo
 * Ref: image_3.png, image_4.png
 */
class ShipmentInfo {
public:
    string trackingID;
    string senderName, senderPhone;
    string receiverName, receiverPhone;
    double weight;
    string serviceType;
    string deliveryDate; // Formatted as YYYY-MM-DD

    void save() {
        // Logic to "Save the info" as per image_3.png
        cout << "\n[System] Saving shipment details to database..." << endl;
        cout << "[System] Success! Tracking ID generated: " << trackingID << endl;
    }
};

/**
 * CONTROL OBJECT: InformationController
 * Ref: image_3.png, image_4.png
 */
class InformationController {
private:
    const double MAX_WEIGHT = 50.0;

public:
    string verifyAndProcess(ShipmentInfo &info) {
        // White Box Testing: Weight limits (BVA)
        if (info.weight <= 0 || info.weight > MAX_WEIGHT) {
            return "FAILED: Weight must be between 0.01kg and 50kg.";
        }

        // Logic for "Verifies the information" as per image_3.png
        if (info.senderPhone.length() < 5 || info.receiverPhone.length() < 5) {
            return "FAILED: Invalid phone number format.";
        }

        // Generate Tracking ID (Simulated)
        info.trackingID = "TRK-" + to_string(time(0) % 100000);
        
        info.save();
        return "SUCCESS";
    }
};

/**
 * BOUNDARY OBJECTS: InfoForm & PackageForm simulation
 * Ref: image_4.png
 */
int main() {
    cout << "=== COURIER TRACKING SYSTEM: BOOK SHIPMENT ===" << endl;

    ShipmentInfo shipment;
    InformationController controller;

    // 1. InfoForm: Accept Sender/Recipient Info
    cout << "\n--- InfoForm ---" << endl;
    cout << "Enter Sender Name: ";
    getline(cin, shipment.senderName);
    cout << "Enter Sender Phone: ";
    getline(cin, shipment.senderPhone);
    cout << "Enter Receiver Name: ";
    getline(cin, shipment.receiverName);
    cout << "Enter Receiver Phone: ";
    getline(cin, shipment.receiverPhone);

    // 2. PackageForm: Accept Package Details
    cout << "\n--- PackageForm ---" << endl;
    cout << "Enter Package Weight (kg): ";
    cin >> shipment.weight;
    cin.ignore(); // Clear buffer

    cout << "Enter Service Type (Standard/Express): ";
    getline(cin, shipment.serviceType);

    cout << "Enter Requested Delivery Date (YYYY-MM-DD): ";
    getline(cin, shipment.deliveryDate);

    // 3. Controller Interaction
    string result = controller.verifyAndProcess(shipment);

    if (result == "SUCCESS") {
        cout << "\n-----------------------------------------" << endl;
        cout << "BOOKING CONFIRMED FOR: " << shipment.senderName << endl;
        cout << "TRACKING ID: " << shipment.trackingID << endl;
        cout << "-----------------------------------------" << endl;
    } else {
        cout << "\n[Error] " << result << endl;
    }

    return 0;
}
