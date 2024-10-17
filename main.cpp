
#include <odb/database.hxx>
#include <odb/sqlite/database.hxx>
#include <odb/schema-catalog.hxx>
#include <odb/sqlite/exceptions.hxx>
#include <odb/transaction.hxx>
#include <iostream>
#include <string>
#include <QCoreApplication>

// Include your ODB-generated header file(s) here if you have any
#include "person-odb.hxx"

using namespace std;

// Define your persistent class here if you have any
#include "person.hpp"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    cout << "Hello, world!" << endl;

    try
    {

        // Open or create the SQLite database file
        odb::sqlite::database db0("example.db", SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
        odb::transaction t(db0.begin());

        // Define your table schema and map it to a persistent class if you have any

        // Execute SQL commands to create the table
        db0.execute("CREATE TABLE IF NOT EXISTS Person (id INTEGER PRIMARY KEY, first TEXT, last TEXT, age INTEGER)");


        // Demonstrate a few different ways of adding objects to the database
        // Create a few persistent person objects (using classes)
        {
            unsigned long john_id, jane_id, joe_id; // store the IDs
            person john("John", "Doe", 33);
            person jane("Jane", "Doe", 32);
            person joe("Joe", "Dirt", 30);

            // Make objects persistent and save their IDs for later use.
            //
            john_id = db0.persist(john);
            jane_id = db0.persist(jane);
            joe_id = db0.persist(joe);
        }


        // Insert some data into the table (raw SQL)
        db0.execute("INSERT INTO Person (first, last, age) VALUES ('Alice', 'Jones', 30)");
        db0.execute("INSERT INTO Person (first, last, age) VALUES ('Bob', 'Guy', 25)");

        // Create a transaction

        // Commit the transaction
        t.commit();


        odb::transaction u(db0.begin());
        // Query the data
        odb::core::result<person> people = db0.query<person>();

        cout << "People in the database:" << endl;
        for (const auto& person : people)
        {
            cout << "ID: " << person.first() << ", Name: " << person.last() << ", Age: " << person.age() << endl;
        }
    }
    catch (const odb::sqlite::database_exception& e)
    {
        cerr << "SQLite database error: " << e.what() << endl;
        return 1;
    }
    catch (const odb::exception& e)
    {
        cerr << "ODB error: " << e.what() << endl;
        return 1;
    }
    catch (const std::exception& e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return a.exec();
}
