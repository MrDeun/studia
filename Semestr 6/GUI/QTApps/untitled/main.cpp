//Ten projekt na moim komputerze musi byc kompilowany w wersji x64
//wynika to z dostepnych u mnie zrodel ODBC ktore sa 64 bit.
//nie mam dostepu do zrodel danych 32BIT takich jak Excel czy Access

//This project on my computer must be compiled using x64 version
//this is due to the sources of ODBC available which are 64 bit.
//I do not have access to 32BIT data sources such as Excel or Access

//DBQ: database qualifier
//SQL: Structured Query Language


#include <QCoreApplication>
#include <QtSql>

#include <iostream>
using namespace std;

void TestSQLite();
void TestExcel();
void TestAccess();
void TestCSV();

void DBInfo(QSqlDatabase& _db);
void RecordInfo(QSqlDatabase& _db, QString _name);

void DisplayQuery(QSqlDatabase& _db, QString _q);

void displayStringList(const QStringList& _list);


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    for(;;)
    {
        cout
            << endl << "|--------------------------------------|"
            << endl << "|    Data base access test             |"
            << endl << "|    Select an option:                 |"
            << endl << "|--------------------------------------|"
            << endl << "|                                      |"
            << endl << "|  1. Exit                             |"
            << endl << "|  2. Show driver's list               |"
            << endl << "|  3. Testof  SQLITE database          |"
            << endl << "|  4. Test excel access (ODBC)         |"
            << endl << "|  5. Test Access access (ODBC)        |"
            << endl << "|  6. Test CSV access (ODBC) (???)     |"
            << endl << "|--------------------------------------|"
            << endl << "|  ";

        int what;
        cin >> what;

        switch( what )
        {
        case 0:
        case 1:
            return 0;//a.exec();
        case 2:
            //wyswietlamy liste dostepnych driverow
            //print driver's list
            cout << "Driver names:" << endl;
            displayStringList(QSqlDatabase::drivers());
            break;
        case 3:
            TestSQLite();
            break;
        case 4:
            TestExcel();
            break;
        case 5:
            TestAccess();
            break;
        case 6:
            TestCSV();
            break;
        }
    }

    return a.exec();
}

void TestSQLite()
{
    QString name;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "bazatestowa");
        db.setDatabaseName(":memory:");
        // db.setDatabaseName("d:\\programs\\qt\\06_qtSQL\\test_baza.sqlite");
        if (!db.open())
        {
            cout << "error";

            return ;
        }

        cout << "Connection !\n";

        QSqlQuery query(db);
        query.exec("create table osoba (id int primary key, "
                   "imie varchar(20), nazwisko varchar(20))");
        /*query.exec("create table ksiazka (id int primary key, "
                   "autor varchar(40), tytul varchar(80))");
        query.exec("create table wypozyczenia (id int primary key, "
                   "osoba int, ksiazka int)");*/

        query.exec("insert into osoba values(101, 'Jan', 'Kowalski')");
        query.exec("insert into osoba values(102, 'Mariusz', 'Nowak')");
        query.exec("insert into osoba values(103, 'Krzysztof', 'Nowak')");
        query.exec("insert into osoba values(104, 'Robert', 'Kowalski')");
        query.exec("insert into osoba values(105, 'Marek', 'Cybulski')");
        query.exec("insert into osoba values(106, 'Wacek', 'Nowak')");

        /*query.exec("insert into ksiazka values(101, 'XX yyy', 'powrot do domu')");
        query.exec("insert into ksiazka values(102, 'kazik maliniak', 'zaginiony w akcji')");
        query.exec("insert into ksiazka values(103, 'marian wik', 'Trzask lamanych galezi')");

        query.exec("insert into wypozyczenia values(101, '101', '101')");
        query.exec("insert into wypozyczenia values(102, '101', '103')");*/


        DBInfo(db);
        RecordInfo(db, "osoba");

        //DisplayQuery(db, "Select * from wypozyczenia");

        //displayStringList(QSqlDatabase::connectionNames());

        name = db.connectionName();
        db.close();
        cout << "\n\n" << (const char*)name.toLatin1() << "\n\n";
    }

    QSqlDatabase::removeDatabase(name);
}

void TestExcel()
{
    QString name;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase( "QODBC3" ); //podlaczamy sie do ODBC; ODBC connection
        if ( db.isValid() )
        {
            //QTZAJECIA
            //otwieramy sterownik odbc; opening odbc driver
            db.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ="
                               + QString("d:\\programs\\qt\\06_qtSQL\\Zeszyt1.xls"));

            bool op = db.open();
            cout << "dbOpen status = " << op << endl;

            if(op)
            {
                DBInfo(db);
                RecordInfo(db, "[Arkusz2$]");


            }


            db.close();
        }
        else
            cout << "Cannot initialize ODBC driver\n";
        name = db.connectionName();
    }
    //QSqlDatabase::removeDatabase("bazatestowa");
}

void TestAccess()
{
    QString name;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase( "QODBC3" ); //podlaczamy sie do ODBC; ODBC connection
        if ( db.isValid() )
        {
            //QTZAJECIA
            //otwieramy sterownik odbc; opening odbc driver
            db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ="
                               + QString("d:\\programs\\qt\\06_qtSQL\\Database.accdb"));
            bool op = db.open();
            cout << "dbOpen status = " << op << endl;

            if(op)
            {
                DBInfo(db);
                RecordInfo(db, "Tabela1");

            }
            //nie dziala - nie potrafie dodac recordow do bazu uzywajac odbc
            // adding records does not work

            //QSqlQuery query;
            //query.exec("insert into [Arkusz2$] values('101', 'Jan', 'Kowalski', '123654')");
            db.close();
        }
        else
            cout << "Cannot initialize ODBC driver\n";
        name = db.connectionName();
    }
    //QSqlDatabase::removeDatabase("bazatestowa");
}


void TestCSV()
{
    QString name;
    {
        // QSqlDatabase db = QSqlDatabase::addDatabase( "QODBC3" ); //podlaczamy sie do ODBC; ODBC connection
        QSqlDatabase db = QSqlDatabase::addDatabase( "QODBC" ); //podlaczamy sie do ODBC; ODBC connection
        if ( db.isValid() )
        {
            //QTZAJECIA
            //otwieramy sterownik odbc; opening odbc driver
            db.setDatabaseName("DRIVER=Microsoft Access Text Driver (*.txt, *.csv);DBQ="
                               + QString("d:\\programs\\qt\\06_qtSQL\\;")
                               + QString("Extensions=csv;"));

            bool op = db.open();
            cout << "dbOpen status = " << op << endl;

            if(op)
            {
                DBInfo(db);
                RecordInfo(db, "test.csv");

            }
            db.close();
        }
        else
            cout << "Cannot initialize ODBC driver\n";
        name = db.connectionName();
    }
    //QSqlDatabase::removeDatabase("bazatestowa");
}


void DBInfo(QSqlDatabase& _db)
{
    cout << "databaseName = " << ((const char*)_db.databaseName().toLatin1())
    << ", driverName = " << ((const char*)_db.driverName().toLatin1()) << endl;


    if ( _db.isOpen() )
    {
        //wyswietlamy liste tabel
        //print list of tables

        displayStringList(_db.tables( QSql::Tables));
        // QStringList list = db.tables( QSql::Tables);

    }
    else
    {
        cout << "Database: " << ((const char*)_db.databaseName().toLatin1()) << " is closed\n"
             << "Error: " << ((const char*)_db.lastError().databaseText().toLatin1());

    }
}

void RecordInfo(QSqlDatabase& _db, QString _name)
{
    QSqlRecord rec = _db.record(_name);


    //
    //wyswietlamy podstawowe informacje o rekordzie; display basic information about record
    //

    cout << "---------------------\n"
         << "  Record information\n"
         << "---------------------\n"
         <<"Table " << ((const char*)_name.toLatin1()) << " conatins  " << rec.count() << " records:\n";



    //
    // wyswietlamy liste pol w rekordzie; number of elements in record
    //

    for (int i = 0; i < rec.count(); i++)
    {
        cout << "Element " << i << ": " << ((const char*)rec.fieldName(i).toLatin1()) << endl;
    }


    cout << "---------------------\n";


    //
    //budujemy zapytanie SQL; SQL query
    //
    DisplayQuery(_db, QString("select * from ") + _name);

    //
    //budujemy zapytanie SQL;  SQL query
    //
    DisplayQuery(_db, QString("select * from ") + _name + QString(" where nazwisko=\'Nowak\'"));

}

void DisplayQuery(QSqlDatabase& _db, QString _q)
{
    cout << "---------------------\n"
         << "  Query to database\n"
         << "---------------------\n";



    QSqlQuery query(_q, _db);

    cout << "isActive() = " << (query.isActive() ? "true" : "false") << endl
         << "isSelect() = " << (query.isSelect() ? "true" : "false") << endl
         << "size()= " << query.size() << endl
         << "numRowsAffected() = " << query.numRowsAffected() << endl
         << "executedQuery()= " << ((const char*)query.executedQuery().toLatin1()) << endl;



    cout << "---------------------\n";

    //
    // wyswietlamy zawartosc rekordu; record information
    //


    while(query.next())
    {
        cout << "Row " << query.at() << ": ";
        for(int i= 0; i < query.record().count(); i++)
        {
            cout << ((const char*)query.value(i).toString().toLatin1()) << "; ";
        }
        cout << endl;
    }

    query.finish();
}

void displayStringList(const QStringList& _list)
{
    int i =0;
    QStringList list = _list;
    cout << "Elements on the list: " << list.length() << endl;
    QStringList::Iterator it = list.begin();
    while( it != list.end() )
    {
        // we save the name of the first table for later
        //if (table.isEmpty()) table = *it;
        cout << "Item " << i << ":\t" << ((const char*)(*it).toLatin1()) << "\n";
        ++it;
        ++i;
    }
}
