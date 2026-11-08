# Flight Management System (C++)

A console-based Flight Management System written in C++ that stores and manages flight records using a **Binary Search Tree (BST)** keyed on Flight ID. Records are saved to and loaded from a text file, so data persists between runs.

## Features

- **Add Flight**: insert a new flight (duplicate Flight IDs are rejected)
- **Search Flight**: find a flight by its ID
- **Delete Flight**: remove a flight from the tree
- **Display Flights**: list all flights in sorted order (inorder traversal)
- **Flight Duration & ETA**: calculate duration and estimated arrival time from departure and arrival times
- **Save / Load Records**: store flights in `flights.txt` and read them back
- **Filter by Budget**: show all flights with a ticket price within your budget
- Records are loaded automatically on startup and saved on exit

## Flight Data

Each flight record contains:

| Field | Type |
|-------|------|
| Flight ID | int |
| Source | string |
| Destination | string |
| Airline | string |
| Departure Time | string |
| Arrival Time | string |
| Duration | int |
| Ticket Price | double |
| Status | string |

## Concepts Used

- Binary Search Tree (insertion, search, deletion, inorder traversal)
- Classes and objects (`Flight`, `Node`, `BST`)
- Recursion
- File handling (`ifstream`, `ofstream`)
- Menu-driven programming with `switch`

## How to Run

```bash
g++ FlightsManagementSystem.cpp -o flight_system
./flight_system
```

On Windows, you can also open the file in Visual Studio, Code::Blocks or Dev-C++ and run it.

## Menu

```
====FLIGHT MANAGEMENT SYSTEM====
1. Add Flight
2. Search Flight
3. Delete Flight
4. Display Flights
5. Calculate Flight Duration and ETA
6. Save Records
7. Load Records
8. Show flights by budgets
9. Exit
```

## Notes

- Input fields are read with `cin >>`, so values must not contain spaces (use `New_York` instead of `New York`).
- Times are entered as hours and minutes when calculating duration and ETA.

## Possible Improvements

- Support multi-word names using `getline`
- Handle flights that arrive after midnight when calculating duration
- Add input validation
- Add update/edit flight option
