
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

enum Status { VACANT, RESERVED, OCCUPIED };

string statusText(Status s) {
    switch (s) {
        case VACANT:   return "VACANT";
        case RESERVED: return "PARTIALLY OCCUPIED";
        default:       return "OCCUPIED";
    }
}

// BASE CLASS
class Table {
protected:
    int id, capacity, occupants;
    Status status;

public:
    Table(int i = 0, int c = 0)
        : id(i), capacity(c), occupants(0), status(VACANT) {}

    int getId() const { return id; }
    int getCapacity() const { return capacity; }
    int getOccupants() const { return occupants; }
    Status getStatus() const { return status; }

    bool isAvailable() const {
        return status == VACANT;
    }

    bool seatPeople(int count) {
        if (count <= 0 || count > capacity || status != VACANT)
            return false;

        occupants = count;
        status = (count == capacity) ? OCCUPIED : RESERVED;
        return true;
    }

    bool releaseTable() {
        if (status == VACANT)
            return false;

        occupants = 0;
        status = VACANT;
        return true;
    }

    // Operator overloading: compare capacity
    bool operator<(const Table& other) const {
        return capacity < other.capacity;
    }

    // Operator overloading: compare table IDs
    bool operator==(const Table& other) const {
        return id == other.id;
    }

    // Operator overloading: display a table
    friend ostream& operator<<(ostream& out, const Table& t) {
        out << left
            << setw(10) << t.id
            << setw(12) << t.capacity
            << setw(12) << t.occupants
            << statusText(t.status);
        return out;
    }
};

// DERIVED CLASS 1
class RegularTable : public Table {
public:
    RegularTable(int i, int c) : Table(i, c) {}
};

// DERIVED CLASS 2
class FamilyTable : public Table {
public:
    FamilyTable(int i, int c) : Table(i, c) {}
};

// FOOD COURT CLASS
class FoodCourt {
private:
    vector<Table> tables;

public:
    FoodCourt() {
        tables.push_back(RegularTable(1, 2));
        tables.push_back(RegularTable(2, 2));
        tables.push_back(RegularTable(3, 4));
        tables.push_back(FamilyTable(4, 6));
        tables.push_back(FamilyTable(5, 8));
        tables.push_back(RegularTable(6, 2));
        tables.push_back(RegularTable(7, 4));
        tables.push_back(RegularTable(8, 4));
        tables.push_back(FamilyTable(9, 6));
        tables.push_back(FamilyTable(10, 8));

        // TABLE 11: Capacity 5, initially vacant
        FamilyTable t11(11, 5);
        tables.push_back(t11);
    }

    friend ostream& operator<<(ostream& out, const FoodCourt& fc) {
        out << "\n========== FOOD COURT TABLES ==========\n";
        out << left << setw(10) << "Table ID"
            << setw(12) << "Capacity"
            << setw(12) << "People"
            << "Status\n";

        for (const Table& t : fc.tables)
            out << t << '\n';

        return out;
    }

    void showTables() const {
        cout << *this;
    }

    void findAvailableTables() const {
        bool found = false;
        cout << "\nAvailable Tables:\n";

        for (const Table& t : tables) {
            if (t.isAvailable()) {
                cout << "Table " << t.getId()
                     << " | Capacity: " << t.getCapacity() << '\n';
                found = true;
            }
        }

        if (!found)
            cout << "No vacant tables available.\n";
    }

    void seatCustomers() {
        int people;
        cout << "Enter number of people: ";

        if (!(cin >> people)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n";
            return;
        }

        if (people <= 0) {
            cout << "Invalid number of people.\n";
            return;
        }

        int best = -1;

        for (int i = 0; i < (int)tables.size(); i++) {
            if (tables[i].isAvailable() &&
                tables[i].getCapacity() >= people) {

                if (best == -1 || tables[i] < tables[best])
                    best = i;
            }
        }

        if (best == -1) {
            cout << "No suitable vacant table found.\n";
            return;
        }

        if (tables[best].seatPeople(people))
            cout << "Successfully assigned Table "
                 << tables[best].getId() << ".\n";
    }

    void releaseTable() {
        int id;
        cout << "Enter table ID to release: ";

        if (!(cin >> id)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n";
            return;
        }

        Table search(id, 0);

        for (Table& t : tables) {
            if (t == search) {
                if (t.releaseTable())
                    cout << "Table released successfully.\n";
                else
                    cout << "This table is already vacant.\n";
                return;
            }
        }

        cout << "Invalid table ID.\n";
    }

    void showSummary() const {
        int vacant = 0, reserved = 0, occupied = 0;

        for (const Table& t : tables) {
            switch (t.getStatus()) {
                case VACANT:   vacant++; break;
                case RESERVED: reserved++; break;
                case OCCUPIED: occupied++; break;
            }
        }

        cout << "\n========== SUMMARY ==========\n";
        cout << "Total tables: " << tables.size() << '\n';
        cout << "Vacant: " << vacant << '\n';
        cout << "Partially occupied: " << reserved << '\n';
        cout << "Occupied: " << occupied << '\n';
    }
};

int main() {
    FoodCourt fc;
    int choice;

    do {
        cout << "\n====================================\n";
        cout << " SMART FOOD COURT SEAT DISPLAY\n";
        cout << "====================================\n";
        cout << "1. Display all tables\n";
        cout << "2. Find available tables\n";
        cout << "3. Assign table to customers\n";
        cout << "4. Release a table\n";
        cout << "5. Show summary\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Exiting.\n";
            break;
        }

        switch (choice) {
            case 1: fc.showTables(); break;
            case 2: fc.findAvailableTables(); break;
            case 3: fc.seatCustomers(); break;
            case 4: fc.releaseTable(); break;
            case 5: fc.showSummary(); break;
            case 0: cout << "Thank you for using the system!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
