#include <iostream>
#include <string>
#include<fstream>
using namespace std;

enum RelationType { LESS, GREATER, EQUAL };

class Flight
{
public:
    int FlightID;
    string source;
    string Destination;
    string Airline;
    string DepartureTime;
    string ArrivalTime;
    int Duration;
    double TicketPrice;
    string Status;

    RelationType ComparedTo(Flight f) const
    {
        if (FlightID < f.FlightID)
            return LESS;
        else if (FlightID > f.FlightID)
            return GREATER;
        else
            return EQUAL;
    }

    void print() const
    {
        cout << "Flight ID: " << FlightID << endl;
        cout << "Source: " << source << endl;
        cout << "Destination: " << Destination << endl;
        cout << "Airline: " << Airline << endl;
        cout << "Departure Time: " << DepartureTime << endl;
        cout << "Arrival Time: " << ArrivalTime << endl;
        cout << "Duration: " << Duration << endl;
        cout << "Ticket Price: " << TicketPrice << endl;
        cout << "Status: " << Status << endl;
        cout << endl;
    }
};

class Node
{
public:
    Flight data;
    Node* left;
    Node* right;

    Node(Flight f)
    {
        data = f;
        left = nullptr;
        right = nullptr;
    }
};

class BST
{
private:
    Node* root;

    Node* Insertion(Node* current, Flight f)
    {
        if (current == nullptr)
            return new Node(f);

        if (f.FlightID < current->data.FlightID)
            current->left = Insertion(current->left, f);

        else if (f.FlightID > current->data.FlightID)
            current->right = Insertion(current->right, f);

        return current;
    }

    Node* Search(Node* current, int ID)
    {
        if (current == nullptr)
            return nullptr;

        if (ID == current->data.FlightID)
            return current;

        if (ID < current->data.FlightID)
            return Search(current->left, ID);

        return Search(current->right, ID);
    }

    Node* Min(Node* current)
    {
        while (current && current->left)
            current = current->left;

        return current;
    }

    Node* Deletion(Node* current, int ID)
    {
        if (current == nullptr)
            return nullptr;

        if (ID < current->data.FlightID)
            current->left = Deletion(current->left, ID);

        else if (ID > current->data.FlightID)
            current->right = Deletion(current->right, ID);

        else
        {
            if (current->left == nullptr)
            {
                Node* temp = current->right;
                delete current;
                return temp;
            }

            else if (current->right == nullptr)
            {
                Node* temp = current->left;
                delete current;
                return temp;
            }

            Node* temp = Min(current->right);
            current->data = temp->data;
            current->right = Deletion(current->right, temp->data.FlightID);
        }

        return current;
    }

    void Inorder(Node* current)
    {
        if (current != nullptr)
        {
            Inorder(current->left);
            current->data.print();
            Inorder(current->right);
        }
    }
    void SaveToFile(Node* current, ofstream& file)
    {
        if (current != nullptr)
        {
            SaveToFile(current->left, file);

            file << current->data.FlightID << " "
                << current->data.source << " "
                << current->data.Destination << " "
                << current->data.Airline << " "
                << current->data.DepartureTime << " "
                << current->data.ArrivalTime << " "
                << current->data.Duration << " "
                << current->data.TicketPrice << " "
                << current->data.Status << endl;

            SaveToFile(current->right, file);
        }
    }
    void BudgetFlights(Node* current, double budget)
    {
        if (current != nullptr)
        {
            BudgetFlights(current->left, budget);

            if (current->data.TicketPrice <= budget)
            {
                current->data.print();
            }

            BudgetFlights(current->right, budget);
        }
    }

public:
    BST()
    {
        root = nullptr;
    }

    void insertFlight(Flight f)
    {
        if (Search(root, f.FlightID) != nullptr)
        {
            cout << "ID already exists." << endl;
            return;
        }

        root = Insertion(root, f);
        cout << "Flight added successfully!" << endl;
    }

    void searchFlight(int ID)
    {
        Node* found = Search(root, ID);

        if (found == nullptr)
        {
            cout << "Flight not found." << endl;
            return;
        }

        found->data.print();
    }

    void deleteFlight(int ID)
    {
        if (Search(root, ID) == nullptr)
        {
            cout << "Flight not found." << endl;
            return;
        }

        root = Deletion(root, ID);
        cout << "Flight deleted successfully!" << endl;
    }

    void displayFlights()
    {
        if (root == nullptr)
        {
            cout << "No flights available." << endl;
            return;
        }

        Inorder(root);
    }


    void saveRecords()
      {
            ofstream file("flights.txt", ios::out);

            if (!file)
            {
                cout << "File not opened!" << endl;
                return;
            }

            SaveToFile(root, file);

            file.close();

            cout << "Records Saved Successfully!" << endl;
      }


     void loadRecords()
        {
            ifstream file("flights.txt", ios::in);

            if (!file)
            {
                cout << "File not found!" << endl;
                return;
            }

            Flight f;

            while (file >> f.FlightID
                >> f.source
                >> f.Destination
                >> f.Airline
                >> f.DepartureTime
                >> f.ArrivalTime
                >> f.Duration
                >> f.TicketPrice
                >> f.Status)
            {
                root = Insertion(root, f);
            }

            file.close();

            cout << "Records Loaded Successfully!" << endl;
      }

    int calculateFlightDuration()
    {
        int depHour, depMin, arrHour, arrMin;

        cout << "Enter Departure Hour: ";
        cin >> depHour;

        cout << "Enter Departure Minutes: ";
        cin >> depMin;

        cout << "Enter Arrival Hour: ";
        cin >> arrHour;

        cout << "Enter Arrival Minutes: ";
        cin >> arrMin;

        int departure = depHour * 60 + depMin;
        int arrival = arrHour * 60 + arrMin;

        int duration = arrival - departure;

        cout << "Flight Duration: " << duration << " minutes" << endl;

        return duration;
    }
    void calculateETA()
    {
        int duration = calculateFlightDuration();

        int hour, min;

        cout << "Enter Departure Hour: ";
        cin >> hour;

        cout << "Enter Departure Minutes: ";
        cin >> min;

        int total = hour * 60 + min + duration;

        int ETAHour = (total / 60) % 24;
        int ETAMin = total % 60;

        cout << "ETA: " << ETAHour << ":" << ETAMin << endl;
    }
    void showFlightsByBudget()
    {
        if (root == nullptr)
        {
            cout << "No flights available!" << endl;
            return;
        }

        double budget;

        cout << "Enter Your Budget: ";
        cin >> budget;

        cout << "Flights Within Your Budget:";

        BudgetFlights(root, budget);
    }
};

Flight inputFlight()
{
    Flight f;

    cout << "Enter Flight ID: ";
    cin >> f.FlightID;

    cout << "Enter Source: ";
    cin >> f.source;

    cout << "Enter Destination: ";
    cin >> f.Destination;

    cout << "Enter Airline: ";
    cin >> f.Airline;

    cout << "Enter Departure Time: ";
    cin >> f.DepartureTime;

    cout << "Enter Arrival Time: ";
    cin >> f.ArrivalTime;

    cout << "Enter Duration: ";
    cin >> f.Duration;

    cout << "Enter Ticket Price: ";
    cin >> f.TicketPrice;

    cout << "Enter Status: ";
    cin >> f.Status;

    return f;
}

int main()
{
    BST tree;
    tree.loadRecords();
    int choice;

    do
    {
        cout << "====FLIGHT MANAGEMENT SYSTEM====" << endl;
        cout << "1.Add Flight" << endl;
        cout << "2.Search Flight" << endl;
        cout << "3.Delete Flight" << endl;
        cout << "4.Display Flights" << endl;
        cout << "5.Calculate Flight Duration and ETA" << endl;
        cout << "6.Save Records" << endl;
        cout << "7.Load Records" << endl;
        cout << "8.Show flights by budgets" << endl;
        cout << "9.Exit" << endl;

        cout << "Enter choice:" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            Flight f = inputFlight();
            tree.insertFlight(f);
            break;
        }

        case 2:
        {
            int ID;
            cout << "Enter Flight ID: ";
            cin >> ID;
            tree.searchFlight(ID);
            break;
        }

        case 3:
        {
            int ID;
            cout << "Enter Flight ID: ";
            cin >> ID;
            tree.deleteFlight(ID);
            break;
        }

        case 4:
            tree.displayFlights();
            break;

        case 5:
            tree.calculateFlightDuration();
            tree.calculateETA();
            break;

        case 6:
            tree.saveRecords();
            break;

        case 7:
            tree.loadRecords();
            break;

        case 8:

            tree.showFlightsByBudget();
            break;

        case 9:
            tree.saveRecords();
            cout << "Thanks for using the Flight Management System!" << endl;
            break;

        default:
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 9);

    return 0;
}
