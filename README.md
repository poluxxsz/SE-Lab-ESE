## README: Courier Tracking System - Book Shipment Testing

This project implements the **Book Shipment** subsystem for a Courier Tracking System and provides an automated testing suite using **Black Box** and **White Box** methodologies.

---

### ### Project Components

*   **`bookShipApp.cpp`**: The core implementation of the Book Shipment use case. It follows the **Entity-Boundary-Control (EBC)** architecture, separating data (`ShipmentInfo`), logic (`InformationController`), and user interface simulation (`BookShipmentApp`).
*   **`blackbox.cpp`**: Automated testing suite focusing on functional requirements. It uses **Equivalence Class Partitioning (ECP)** and **Boundary Value Analysis (BVA)** to validate weight limits (0.01kg - 50kg) and phone number lengths.
*   **`whitebox.cpp`**: Automated testing suite focusing on the internal logical paths of the `InformationController`. It ensures **Statement** and **Branch Coverage** for all decision predicates within the code.
*   **`.csv` Files**: Data files containing the 15 test cases for both Black Box and White Box testing, including inputs and expected outcomes.
*   **`.png` Files**: Screenshots of the terminal output showing the generated "PASS/FAIL" testing reports for verification.

---

#### **1. Running the Base Application**
To interact with the Book Shipment CLI manually:
```bash
g++ bookShipApp.cpp -o bookShipApp
./bookShipApp
```

#### **2. Running Black Box Tests**
To execute the automated functional test suite and view the results table:
```bash
g++ blackbox.cpp -o blackbox
./blackbox
```

#### **3. Running White Box Tests**
To execute the structural logic test suite and verify branch coverage:
```bash
g++ whitebox.cpp -o whitebox
./whitebox
```

---

### ### Testing Logic Summary

| Testing Type | Methodology Used | Focus Area |
| :--- | :--- | :--- |
| **Black Box** | ECP & BVA | Validating that package weights (0.01kg to 50kg) and phone numbers meet functional requirements. |
| **White Box** | Branch & Path Coverage | Testing internal `if/else` logic and successful execution of the `trackingID` generation statement. |

---
