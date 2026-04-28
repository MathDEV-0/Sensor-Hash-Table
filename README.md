Distributed Sensor Monitoring System with Static Hash Table
===========================================================


Description
-----------

This project implements a distributed sensor monitoring system using a static closed hash table with open addressing and double hashing for collision resolution.

The system simulates the registration and management of sensors distributed across different locations, allowing operations such as:

-   Registering sensors
-   Searching sensors by ID
-   Updating sensor readings
-   Removing sensors
-   Bulk insertion of sensors for stress testing
-   Collision analysis and performance evaluation

The implementation demonstrates the practical application of hash tables in real-time systems where fast access and efficient memory usage are required.

* * * * *

Project Structure
-----------------
```
main.cpp
├── Interactive menu system
├── Benchmark and timing analysis
├── Automatic insertion tests
└── Sensor management interface

Sensor.cpp / Sensor.h
├── Sensor class definition
├── Sensor attributes
├── Getters and setters
└── Sensor visualization

HashTable.cpp / HashTable.h
├── Static hash table implementation
├── Double hashing collision handling
├── Insert, search and delete operations
├── Collision statistics
├── Memory management
└── Bulk sensor updates
```
* * * * *

Compilation and Execution
-------------------------

### Compile:
```
g++ main.cpp HashTable.cpp Sensor.cpp -o main
```
### Run:
```
./main
```
* * * * *

System Features
---------------

### Available Operations
```
1 - Register sensor
2 - Update read from single sensor
3 - Search single sensor
4 - Remove single sensor
5 - Show sensors
6 - Insert 1000 sensors automatically
7 - Update read for all sensors
0 - Exit
```
* * * * *

Sample Output
-------------
```
Trying to insert 1523 at index [1489]
Successfully inserted key 1523 at index [1489]

Searching 1523 at index [1489]
Element with key 1523 found at the calculated index [1489]

id = 1523 | type = temperature_indicator | location = Porto Alegre | last read = 37.4
```
* * * * *

Implementation Details
----------------------

### Sensor Structure

Each sensor stores:
```
class Sensor {
    short int id;
    std::string type;
    std::string location;
    double lastRead;
};
```
Attributes explanation:

-   `id`: unique sensor identifier (positive 16 bit)
-   `type`: sensor category (temperature, humidity, pH, etc.)
-   `location`: geographical location
-   `lastRead`: latest measured value

* * * * *

### Hash Table Structure

The hash table uses:

-   Static array allocation
-   Open addressing
-   Double hashing probing
-   Pointer-based storage
-   Placeholder marker for deleted elements

Sensor* data[BUFFER_SIZE];

The table size is defined using:

#define BUFFER_SIZE 10037

A prime number was chosen to reduce clustering and improve key distribution.

* * * * *

### Collision Resolution Strategy

The implementation uses double hashing:
```
h(k, i) = (h1(k) + i * h2(k)) % M
```
Where:
```
h1(k) = k % M
h2(k) = 1 + (k % (M - 1))
```
This strategy minimizes clustering compared to linear probing and improves distribution across the table.

* * * * *

### Insert Operation

The insertion process:

-   Calculates the hash index
-   Detects collisions
-   Searches for the next available position
-   Prevents duplicate IDs
-   Counts collisions during probing

if(data[index] == nullptr || data[index] == REMOVED) {
    data[index] = new Sensor(sensor);
}

* * * * *

### Search Operation

The search operation:

-   Recalculates the probing sequence
-   Traverses positions using double hashing
-   Stops when:
    -   Sensor is found
    -   Empty position is reached
    -   Entire table is traversed

Returns:

Sensor* search(int key)

* * * * *

### Delete Operation

Deletion uses lazy deletion with a placeholder object:
```
static Sensor REMOVED_SENSOR(-1, "", "");
#define REMOVED (&REMOVED_SENSOR)
```
Advantages:

-   Preserves probing chains
-   Prevents search interruption
-   Allows future insertions in removed positions

* * * * *

### Automatic Bulk Insertion

The function:
```
tryInsert1000(HashTable& ht)
```
Automatically:

-   Generates random IDs
-   Avoids duplicate keys
-   Creates random sensor types and locations
-   Inserts up to 1000 sensors
-   Measures insertion performance
-   Tracks collisions

Mock sensor types:
```
temperature_indicator
humidity_indicator
ph_indicator
nutrients_indicator
pressure_indicator
```
Mock locations:
```
Porto Alegre
Sao Leopoldo
Novo Hamburgo
Pelotas
Viamao
Gravatai
```
* * * * *

Why Open Addressing Was Chosen
------------------------------

Advantages:

1.  Memory efficiency:
    -   Uses only one contiguous structure
    -   No linked lists required
2.  Cache locality:
    -   Better CPU cache performance
    -   Faster sequential access
3.  Simplicity:
    -   Easier memory management
    -   Compact implementation
4.  Fast lookup:
    -   Average complexity close to O(1)
    -   Efficient for real-time systems

This approach is especially suitable for monitoring systems where the approximate number of sensors is known beforehand.

* * * * *

Limitations
-----------

As the load factor increases:

-   Collisions become more frequent
-   Insertions become slower
-   Clustering effects appear
-   Search performance degrades

This behavior becomes significant when:

Load Factor (α) > 0.7

A possible improvement would be implementing:

-   Dynamic resizing
-   Rehashing
-   Alternative probing strategies

* * * * *

Performance Tests
-----------------

### Insertion Stress Test

The system was tested with progressive insertion batches of 1000 sensors.

Observed behavior:

-   Stable performance at low load factors
-   Collision growth near table saturation
-   Significant insertion slowdown near full occupancy

Example:

| Batch | Total Elements | Load Factor | Total Collisions |
| --- | --- | --- | --- |
| 1000 | 1000 | 0.1 | 34 |
| 5000 | 5000 | 0.498 | 1534 |
| 9000 | 9000 | 0.897 | 12576 |
| 10037 | 10037 | 1.0 | 81731 |

* * * * *

### Search Performance

Average search time remained low for moderate load factors, but increased progressively as occupancy grew.

| Elements | Load Factor | Avg Search Time (s) |
| --- | --- | --- |
| 1000 | 0.1 | 0.000225 |
| 5000 | 0.498 | 0.000547 |
| 8000 | 0.797 | 0.000868 |
| 9000 | 0.897 | 0.000855 |

* * * * *

What Happens Without Proper Collision Handling?
-----------------------------------------------

Without double hashing or probing:

index = key % M;

Problems:

-   Multiple keys overwrite the same position
-   Data loss
-   Failed searches
-   Severe clustering
-   Unstable lookup performance

Example:
```
Insert key 10 at index [5]
Insert key 20 at index [5]  // Collision
Insert key 30 at index [5]  // Overwrites previous value
```
Consequences:

-   Lost sensors
-   Corrupted table state
-   Incorrect search results

* * * * *

Testing Guide
-------------

### Test 1: Basic Sensor Management

Verify:

-   Sensor registration
-   Search correctness
-   Reading updates
-   Removal behavior

* * * * *

### Test 2: Bulk Insertion

Run:
```
Option 6 - Insert 1000 sensors automatically
```
Observe:

-   Collision growth
-   Insertion timing
-   Load factor impact

* * * * *

### Test 3: Search Benchmark

Insert thousands of sensors and measure:

-   Lookup speed
-   Collision effects
-   Scalability

* * * * *

### Test 4: Full Table Scenario

Fill the table completely.

Expected behavior:

Hash Table is full!

Demonstrates:

-   Saturation effects
-   Collision explosion
-   Open addressing limitations

* * * * *

Key Learning Points
-------------------

1.  Hash tables provide near O(1) average access time
2.  Double hashing reduces clustering compared to simpler probing methods
3.  Open addressing improves memory efficiency
4.  Load factor directly impacts performance
5.  Collision handling is essential for correctness
6.  Lazy deletion preserves probing chains
7.  Prime-sized tables improve key distribution
8.  Rehashing becomes necessary at high occupancy levels

* * * * *

Experimental Environment
------------------------
```
Language: C++
Compiler: g++
Architecture: Static Closed Hash Table
Collision Strategy: Double Hashing
Machine:
- AMD Ryzen 9700X3D
- 64 GB RAM
- Windows
```
