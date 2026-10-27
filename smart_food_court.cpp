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

class Table {
protected:
    int id;
    int capacity;
    int occupants;
    Status status;

public:
    Table(int id, int cap)
        : id(id), capacity(cap), occupants(0), status(VACANT) {}

    virtual ~Table() {}
    virtual void display() const = 0;

    bool operator<(const Table& other) const {
        return capacity < other.capacity;
    }

    bool operator==(const Table& other) const {
        return id == other.id;
    }

    int getId() const { return id; }
    int getCapacity() const { return capacity; }
    int getOccupants() const { return occupants; }
    Status getStatus() const { return status; }

    bool isAvailable() const { return status == VACANT; }

    virtual bool seatPeople(int count) {
        if (count <= 0 || count > capacity || status != VACANT)
            return false;

        occupants = count;
        status = (count == capacity) ? OCCUPIED : RESERVED;
        return true;
    }

    virtual bool releaseTable() {
        if (status == VACANT)
            return false;

        occupants = 0;
        status = VACANT;
        return true;
    }
};

class RegularTable : public Table {
public:
    RegularTable(int id, int cap) : Table(id, cap) {}

    void display() const override {
        cout << left << setw(10) << id << setw(12) << capacity
             << setw(12) << occupants << statusText(status) << '\\n';
    }
};

class FamilyTable : public Table {
public:
    FamilyTable(int id, int cap) : Table(id, cap) {}

    void display() const override {
        cout << left << setw(10) << id << setw(12) << capacity
             << setw(12) << occupants << statusText(status) << '\\n';
    }
};

class FoodCourt {
private:
    vector<Table*> tables;

public:
    FoodCourt() {
        tables.push_back(new RegularTable(1, 2));
        tables.push_back(new RegularTable(2, 2));
        tables.push_back(new RegularTable(3, 4));
        tables.push_back(new FamilyTable(4, 6));
        tables.push_back(new FamilyTable(5, 8));
        tables.push_back(new RegularTable(6, 2));
        tables.push_back(new RegularTable(7, 4));
        tables.push_back(new RegularTable(8, 4));
        tables.push_back(new FamilyTable(9, 6));
        tables.push_back(new FamilyTable(10, 8));
    }

    ~FoodCourt() {
        for (Table* t : tables) delete t;
    }

    friend ostream& operator<<(ostream& out, const FoodCourt& fc) {
        out << "\\n========== FOOD COURT TABLES ==========\\n";
        out << left << setw(10) << "Table ID" << setw(12) << "Capacity"
             << setw(12) << "People" << "Status\\n";
        for (const Table* t : fc.tables) t->display();
        return out;
    }

    void showTables() const { cout << *this; }

    void findAvailableTables() const {
        cout << "\\nAvailable Tables:\\n";
        bool found = false;
        for (const Table* t : tables) {
            if (t->isAvailable()) {
                cout << "Table " << t->getId()
                     << " | Capacity: " << t->getCapacity() << '\\n';
                found = true;
            }
        }
        if (!found) cout << "No vacant tables available.\\n";
    }

    void seatCustomers() {
        int people;
        cout << "Enter number of people: ";
        cin >> people;
        if (people <= 0) {
            cout << "Invalid number of people.\\n";
            return;
        }

        Table* best = nullptr;
        for (Table* t : tables) {
            if (t->isAvailable() && t->getCapacity() >= people) {
                if (best == nullptr || *t < *best) best = t;
            }
        }
        if (best == nullptr) {
            cout << "No suitable vacant table found.\\n";
            return;
        }
        if (best->seatPeople(people))
            cout << "Successfully assigned Table " << best->getId() << ".\\n";
    }

    void releaseTable() {
        int tableId;
        cout << "Enter table ID to release: ";
        cin >> tableId;
        for (Table* t : tables) {
            if (t->getId() == tableId) {
                if (t->releaseTable()) cout << "Table released successfully.\\n";
                else cout << "This table is already vacant.\\n";
                return;
            }
        }
        cout << "Invalid table ID.\\n";
    }

    void showSummary() const {
        int vacant = 0, reserved = 0, occupied = 0;
        for (const Table* t : tables) {
            switch (t->getStatus()) {
                case VACANT: vacant++; break;
                case RESERVED: reserved++; break;
                case OCCUPIED: occupied++; break;
            }
        }
        cout << "\\n========== SUMMARY ==========\\n";
        cout << "Total tables: " << tables.size() << '\\n';
        cout << "Vacant:       " << vacant << '\\n';
        cout << "Partially occupied: " << reserved << '\\n';
        cout << "Occupied:     " << occupied << '\\n';
    }
};

int main() {
    FoodCourt fc;
    int choice;
    do {
        cout << "\\n====================================\\n";
        cout << " SMART FOOD COURT SEAT DISPLAY\\n";
        cout << "====================================\\n";
        cout << "1. Display all tables\\n";
        cout << "2. Find available tables\\n";
        cout << "3. Assign table to customers\\n";
        cout << "4. Release a table\\n";
        cout << "5. Show summary\\n";
        cout << "0. Exit\\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            cout << "Invalid input. Exiting.\\n";
            break;
        }
        switch (choice) {
            case 1: fc.showTables(); break;
            case 2: fc.findAvailableTables(); break;
            case 3: fc.seatCustomers(); break;
            case 4: fc.releaseTable(); break;
            case 5: fc.showSummary(); break;
            case 0: cout << "Thank you for using the system!\\n"; break;
            default: cout << "Invalid choice. Try again.\\n";
        }
    } while (choice != 0);
    return 0;
}
