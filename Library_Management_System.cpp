#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
using namespace std;

int id = 10;




class book
{
private:
    string title;
    string ISBN;
    string author;
    string publisher;
    string year;
    string status;
    string towhom="none";
    int borroweddate;

public:
    // Public constructor to initialize book object
    book(const string &title, const string &ISBN, string author, string publisher, string year,string status,string towhom,int borroweddate)
        : title(title), ISBN(ISBN), author(author),publisher(publisher),year(year), status(status),towhom(towhom),borroweddate(borroweddate) {}
   
 void displayDetailsIfAvailable() const
    {
        // cout<<isAvailable;
        if (status == "available")
        {
            cout << "title: " << title << "\n";
            cout << "ISBN: " <<ISBN << "\n";
            cout << "author: " << author << "\n";
            cout << "publisher: " << publisher<< "\n";
            cout << "year: " << year<< "\n";
            cout << "Is Available: Yes\n";
            cout << "-------------------------\n";
        }
    }
    void displayDetailsofRentedbook(const string &renter) const
    {
       
        if (towhom == renter)
        {
            cout << "title: " << title << "\n";
            cout << "ISBN: " <<ISBN << "\n";
            cout << "author: " << author << "\n";
            cout << "publisher: " << publisher<< "\n";
            cout << "year: " << year<< "\n";
            cout << "Is Available: NO\n";
            cout << "-------------------------\n";
        }
    }
    int hasuserRentedbook(const string &renter) const
    {
       
        if (towhom == renter)
        {
           return 1;
        }return 0;
    }
    static void displayDetails()
    {
        ifstream file("book.txt");
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            string title, ISBN, towhom,status;
            string author, publisher, year;
            int borroweddate;

            getline(ss, title, ',');
            getline(ss, ISBN, ',');
            getline(ss,author, ',');
            getline(ss, publisher, ',');
            getline(ss,year, ',');
            getline(ss,status, ',');


            char comma;
            ss >> borroweddate>>comma;
            getline(ss, towhom);
            
            // cout<<days<<" ";
            cout << "title : " << title << endl;
            cout << "ISBN " << ISBN << endl;
            cout << "author: " << author << endl;
            cout << "publisher: " << publisher << endl;
            cout << "year: " << year<< endl;
            cout << "status: " <<status<< endl;
            cout << "rented to : " << towhom << endl;
            cout << "--------------\n";
            // book.rentbook();  // Assume the book is being rented when reading from file
            // book.displayDetailsIfAvailable();
        }

        file.close();
        return;
    }

    bool checkAvailability() const
    {
        return status=="available";
    }
    string getISBN()
    {
        return ISBN;
    }
    string getpublisher()
    {
        return publisher;
    }
    string getyear()
    {
        return year;
    }
    string gettowhom() const
    {
        return towhom;
    }

    string gettitle()
    {
        return title;
    }
};       


//user class being made
class user
{
protected:
    string username;
    string password;
    string ID;

public:
    user() {}
    user(const std::string &uname, const std::string &pwd, const std::string &id)
        : username(uname), password(pwd), ID(id) {}
};

class Librarian : private user
{
public:
    Librarian(const std::string &uname, const std::string &pwd, const std::string &id)
        : user(uname, pwd, id) {}

    Librarian() {}
    string getUsername() const
    {
        return username;
    }
    string getPassword()
    {
        return password;
    }
    string getID()
    {
        return ID;
    }
    bool authenticate(const string &enteredPassword) const
    {
        return (password == enteredPassword);
    }
    static vector<Librarian> readLibrarianData()
    {
        vector<Librarian> Librarians;
        ifstream file("Librarian.txt");
        if (!file.is_open())
        {
            cerr << "Error opening file: Librarian.txt" << endl;
            return Librarians; // Return empty vector if file can't be opened
        }
    
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            Librarian st; // local student object
    
            // 1) Read basic fields: username, password, ID
            getline(ss, st.username, ',');
            getline(ss, st.password, ',');
            getline(ss, st.ID);
    
            // 2) Read fineDue (integer)
           
    
            // 3) If there's still a comma left, ignore it before reading borrowed books
            
    
            // 4) Read the rest of the line as borrowed books
            
         
    
            // Add the student object to the vector
            Librarians.push_back(st);
        }
    
        file.close();
        return Librarians;
    }
    

    static void writeLibrarianData(const vector<Librarian> &Librarians)
    {
        ofstream file("Librarian.txt");
        for (size_t i = 0; i < Librarians.size(); ++i)
        {
            const auto &Librarian = Librarians[i];
            file << Librarian.username << ","
                 << Librarian.password << ","
                 << Librarian.ID ;
                 
                 // Ensure proper formatting
            


            // Do not write a newline character if it's the last entry
            if (i != Librarians.size() - 1)
            {
                file << "\n";
            }
        }
        file.close();
    }

    void registerNewstudent() const;
    void registerNewLibrarian() const;
    void registerNewfaculty() const;
    void Deletebook(const string &filename, const string &uni);
    void deletestudent(const string &filename, const string &username);
    void Searchstudent(const string &filename, const string &username);
    void deletefaculty(const string &filename, const string &username);
    void Searchfaculty(const string &filename, const string &username);
};
void Librarian::Deletebook(const string &filename,const string &uni)
{
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string title, ISBN, towhom,status;
        string author, publisher, year;
        int borroweddate;

        getline(ss, title, ',');
        getline(ss, ISBN, ',');
        getline(ss,author, ',');
        getline(ss, publisher, ',');
        getline(ss,year, ',');
        getline(ss,status, ',');


        char comma;
        ss >> borroweddate>>comma;
        getline(ss, towhom);
        if (ISBN == uni)
        {
            // Update the line with new information
            if (status == "borrowed")
            {
                cout << "book is rented so not possible to delete!";
            }
            else
                updated = true;
            continue;
        }
        else
        {
            // Write the original line to the temporary file
            tempFile << line;
        }
        if (!inFile.eof())
        {
            tempFile << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated)
    {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
    else
    {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}

class Account {
    public:
    int fineDue=0;
    vector<string>borr;
    vector<string>borr_History;
    int borr_Historysize=0;

} ;



class student : private user
{
private:
   Account account;
    
public:
    student(const string &uname, const string &pwd, const string &id)
        : user(uname, pwd, id){}

    student() {}
    // int studentRec()const
    // {
    //     return studentRecord;
    // }
    string getUsername() const
    {
        return username;
    }
    string getPassword()
    {
        return password;
    }
    string getID()
    {
        return ID;
    }
    int getFineDue()
    {
        return account.fineDue;
    }
    
    int getnoofbooksrented()
    {
        return account.borr.size();
    }
    bool authenticate(const string &enteredPassword) const
    {
        return (password == enteredPassword);
    }
    static vector<student> readstudentData()
    {
        vector<student> students;
        ifstream file("student.txt");
        if (!file.is_open())
        {
            cerr << "Error opening file: student.txt" << endl;
            return students; // Return empty vector if file can't be opened
        }
    
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            student st; // local student object
    
            // 1) Read basic fields: username, password, ID
            getline(ss, st.username, ',');
            getline(ss, st.password, ',');
            getline(ss, st.ID, ',');
    
           char comma;
            ss >> st.account.fineDue>>comma>>st.account.borr_Historysize;
            string borrowedBookhis;
            for(int i=1;i<=st.account.borr_Historysize;i++){
                if (ss.peek() == ',')
                {
                    ss.ignore();
                }
                getline(ss,borrowedBookhis,',');
                
                st.account.borr_History.push_back(borrowedBookhis);
            }
            if (ss.peek() == ',')
                {
                    ss.ignore();
                }

    
            // 3) If there's still a comma left, ignore it before reading borrowed books
            
            // 4) Read the rest of the line as borrowed books
            st.account.borr.clear(); // Make sure it's empty before pushing back
            string borrowedBook;
            while (getline(ss, borrowedBook, ','))
            {
                st.account.borr.push_back(borrowedBook);
            }
            

            if (getline(ss, borrowedBook)) {
                if (!borrowedBook.empty()) {
                    st.account.borr.push_back(borrowedBook);
                }
            }
    


            // Add the student object to the vector
            students.push_back(st);
        }
    
        file.close();
        return students;
    }
    

    static void writestudentData(const vector<student> &students)
    {
        ofstream file("student.txt");
        for (size_t i = 0; i < students.size(); ++i)
        {
            const auto &student = students[i];
            file << student.username << ","
                 << student.password << ","
                 << student.ID << ","
                 << student.account.fineDue<< ","
                 << student.account.borr_Historysize;
                 for (size_t j = 0; j < student.account.borr_History.size(); j++)
            {
                file << "," << student.account.borr_History[j]; // Ensure proper formatting
            }
                 for (size_t j = 0; j < student.account.borr.size(); j++)
            {
                file << "," << student.account.borr[j]; // Ensure proper formatting
            }


            // Do not write a newline character if it's the last entry
            if (i != students.size() - 1)
            {
                file << "\n";
            }
        }
        file.close();
    }
};
class faculty : private user
{
private:
Account account;

    // vector<book> booksRented;

public:
    faculty(const string &uname, const string &pwd, const string &id)
        : user(uname, pwd, id) {}

    faculty() {}
    // int facultyRec()const
    // {
    //     return facultyRecord;
    // }
    string getUsername() const
    {
        return username;
    }
    string getPassword()
    {
        return password;
    }
    string getID()
    {
        return ID;
    }
    int getFineDue()
    {
        return account.fineDue;
    }
    int getnoofbooksrented()
    {
        return account.borr.size();
    }
   
    bool authenticate(const string &enteredPassword) const
    {
        return (password == enteredPassword);
    }
    static vector<faculty> readfacultyData()
    {
        vector<faculty> faculties;
        ifstream file("faculty.txt");
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            faculty faculty;
            getline(ss, faculty.username, ',');
            getline(ss, faculty.password, ',');
            getline(ss, faculty.ID, ',');
            char comma;
            ss >> faculty.account.fineDue>>comma>>faculty.account.borr_Historysize;
            string borrowedBookhis;
            for(int i=1;i<=faculty.account.borr_Historysize;i++){
                if (ss.peek() == ',')
                {
                    ss.ignore();
                }
                getline(ss,borrowedBookhis,',');
               
                faculty.account.borr_History.push_back(borrowedBookhis);
            }
            if (ss.peek() == ',')
            {
                ss.ignore();
            }
    
            // 4) Read the rest of the line as borrowed books
            faculty.account.borr.clear(); // Make sure it's empty before pushing back
            string borrowedBook;
            while (getline(ss, borrowedBook, ','))
            {
                faculty.account.borr.push_back(borrowedBook);
            }
            if (getline(ss, borrowedBook)) {
                if (!borrowedBook.empty()) {
                    faculty.account.borr.push_back(borrowedBook);
                }
            }
            // Add the student object to the vector
            
            faculties.push_back(faculty);
        }

        file.close();
        return faculties;
    }

    static void writefacultyData(const vector<faculty> &faculties)
    {
        ofstream file("faculty.txt");
        for (size_t i = 0; i < faculties.size(); ++i)
        {
            const auto &faculty = faculties[i];
            file << faculty.username << ","
                 << faculty.password << ","
                 << faculty.ID << ","
                 << faculty.account.fineDue<<","
                 << faculty.account.borr_Historysize;
                 for (size_t j = 0; j < faculty.account.borr_History.size(); j++)
            {
                file << "," << faculty.account.borr_History[j]; // Ensure proper formatting
            }
                 for (size_t j = 0; j < faculty.account.borr.size(); j++)
            {
                file << "," << faculty.account.borr[j]; // Ensure proper formatting
            }


            // Do not write a newline character if it's the last entry
          

            // Do not write a newline character if it's the last entry
         if (i != faculties.size() - 1)
            {
                file << "\n";
            }
        }
        file.close();
    }
};
void Librarian::registerNewLibrarian() const
{
    vector<Librarian> Librarians = Librarian::readLibrarianData();
    cout << "Enter username(without spaces): ";
    string username;
    cin >> username;

    auto it = find_if(Librarians.begin(), Librarians.end(),
                      [username](const Librarian &c)
                      { return c.getUsername() == username; });

    if (it != Librarians.end())
    {
        cout << "This username already exists. Try Again.\n";
    }
    else
    {
        string password;
        cout << "Enter password: ";
        cin >> password;

        string confirmPassword;
        cout << "Confirm password: ";
        cin >> confirmPassword;

        if (password == confirmPassword)
        {   ifstream inFile("data.txt");
            int loadedValue;
            inFile >> loadedValue;
            inFile.close();
            id=loadedValue;
            Librarian newLibrarian(username, password, to_string(id));
            id++;
            ofstream outFile("data.txt");
            outFile << id;
            outFile.close();
        
            // Later, to retrieve the value:
           
            Librarians.push_back(newLibrarian);
            Librarian::writeLibrarianData(Librarians);
            cout << "Registration successful! Please log in again.\n";
        }
        else
        {
            cout << "Password and Confirm Password do not match. Registration failed.\n";
        }
    }
}
void Librarian::registerNewstudent() const
{
    vector<student> students = student::readstudentData();
    cout << "Enter username(without spaces): ";
    string username;
    cin >> username;

    auto it = find_if(students.begin(), students.end(),
                      [username](const student &c)
                      { return c.getUsername() == username; });

    if (it != students.end())
    {
        cout << "This username already exists. Try Again.\n";
    }
    else
    {
        string password;
        cout << "Enter password: ";
        cin >> password;

        string confirmPassword;
        cout << "Confirm password: ";
        cin >> confirmPassword;

        if (password == confirmPassword)
        {
            ifstream inFile("data.txt");
            int loadedValue;
            inFile >> loadedValue;
            inFile.close();
            id=loadedValue;
            
            
     student newstudent(username, password, to_string(id));
            id++;
             ofstream outFile("data.txt");
            outFile << id;
            outFile.close();
            students.push_back(newstudent);
            student::writestudentData(students);
            cout << "Registration successful! Please log in again.\n";
        }
        else
        {
            cout << "Password and Confirm Password do not match. Registration failed.\n";
        }
    }
}
void Librarian::registerNewfaculty() const
{
    vector<faculty> faculties = faculty::readfacultyData();
    cout << "Enter username(without spaces): ";
    string username;
    cin >> username;

    auto it = find_if(faculties.begin(), faculties.end(),
                      [username](const faculty &c)
                      { return c.getUsername() == username; });

    if (it != faculties.end())
    {
        cout << "This username already exists. Try Again.\n";
    }
    else
    {
        string password;
        cout << "Enter password: ";
        cin >> password;

        string confirmPassword;
        cout << "Confirm password: ";
        cin >> confirmPassword;

        if (password == confirmPassword)
        {
            ifstream inFile("data.txt");
            int loadedValue;
            inFile >> loadedValue;
            inFile.close();
            id=loadedValue;
            faculty newfaculty(username, password, to_string(id));
            id++;
            ofstream outFile("data.txt");
            outFile << id;
            outFile.close();
            faculties.push_back(newfaculty);
            faculty::writefacultyData(faculties);
            cout << "Registration successful! Please log in again.\n";
        }
        else
        {
            cout << "Password and Confirm Password do not match. Registration failed.\n";
        }
    }
}

// Assuming the file format is:
// title,ISBN,author,publisher,year,status,borroweddate,towhom
// in exactly this order.

static vector<book> readbookData()
{
    vector<book> books;
    ifstream file("book.txt");
    if (!file.is_open())
    {
        cerr << "Error opening file: book.txt" << endl;
        return books; // Return empty vector if file can't be opened
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);

        // According to your book class:
        // string title, ISBN, author, publisher, year, status, towhom="none";
        // int borroweddate;

        string title, ISBN, author, publisher, year, status, towhom;
        int borroweddate = 0;

        // 1) Read the string fields
        getline(ss, title, ',');
        getline(ss, ISBN, ',');
        getline(ss, author, ',');
        getline(ss, publisher, ',');
        getline(ss, year, ',');
        getline(ss, status, ',');

        // 2) Read the integer borroweddate
        ss >> borroweddate;

        // 3) If there's still a comma left, ignore it before reading "towhom"
        if (ss.peek() == ',')
        {
            ss.ignore();
        }

        // 4) Finally read the "towhom" field (default "none" if not borrowed)
        getline(ss, towhom);

        // 5) Create a book object with these values
        // Make sure your book constructor matches these parameters
        book bk(title, ISBN, author, publisher, year, status, towhom, borroweddate);

        // 6) Add to the books vector
        books.push_back(bk);
    }

    file.close();
    return books;
}

void updatebookInfo(const string &filename, const string &uni, string newAvailability,int date, const string &newToWhom)
{
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string title, ISBN, towhom,status;
        string author, publisher, year;
        int borroweddate;

        getline(ss, title, ',');
        getline(ss, ISBN, ',');
        getline(ss,author, ',');
        getline(ss, publisher, ',');
        getline(ss,year, ',');
        getline(ss,status, ',');


        char comma;
        ss >> borroweddate>>comma;
        getline(ss, towhom);

        // Print the values to check if they are read correctly
        // cout << "title: " << title << ", Registration Number: " << regNum << ", Condition in stars: " << condition
        //      << ", Cost: " << cost << ", Available: " << available << ", To Whom: " << towhom
        //      << ", Days: " << days <<  endl;

        if (ISBN== uni)
        {
            // Update the line with new information
            tempFile << title << "," << ISBN << "," << author << "," << publisher << ","
                     << year<< "," <<newAvailability<<","<<date<<","<< newToWhom;
            updated = true;
        }
        else
        {
            // Write the original line to the temporary file
            tempFile << line;
        }
        if (!inFile.eof())
        {
            tempFile << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated)
    {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
    else
    {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}
void updatefacultyInfoafterreturning(const string &filename, const string &username, string book,int fine)
{
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string uname, password, id;
        int  fineDue;
        vector<string>books;
        vector<string>borr_History;
        
        int borr_Historysize;

        // Read each field separated by commas
        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        char comma;
        ss >> fineDue>>comma>>borr_Historysize;
        string borrowedBookhis;
        for(int i=1;i<=borr_Historysize;i++){
            if (ss.peek() == ',')
            {
                ss.ignore();
            }
            getline(ss,borrowedBookhis,',');
           
            borr_History.push_back(borrowedBookhis);
        }
        if (ss.peek() == ',')
            {
                ss.ignore();
            }
    
            // 4) Read the rest of the line as borrowed books
            // Make sure it's empty before pushing back
            string borrowedBook;
            while (getline(ss, borrowedBook, ','))
            {
                books.push_back(borrowedBook);
            }
            if (getline(ss, borrowedBook)) {
                if (!borrowedBook.empty()) {
                    books.push_back(borrowedBook);
                }
            }

        // Print the values to check if they are read correctly
        // cout << "Username: " << uname << ", Password: " << password << ", ID: " << id
        //<< ", studentRecord: " << studentRecord << ", FineDue: " << fineDue << endl;
        if (uname == username)
        {
            // Update the line with new information
            tempFile << uname << "," << password << "," << id << "," <<fineDue+fine<<","<<borr_Historysize+1;
            for (size_t j = 0; j < borr_Historysize; j++)
            {
                tempFile << "," << borr_History[j]; // Ensure proper formatting
            }
            tempFile << "," << book;
            
            
            for (size_t j = 0; j < books.size(); j++)
            {
                if(books[j]!=book){
                tempFile << "," << books[j];} // Ensure proper formatting
            }
            
            updated = true;
        }
        else
        {
            // Write the original line to the temporary file
            tempFile << line;
        }
        if (!inFile.eof())
        {
            tempFile << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated)
    {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
    else
    {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}

int daysBetweenDates(int start, int end)
{
    struct tm startDate = {0}, endDate = {0};

    // Extract day, month, and year from the start date (format DDMMYYYY)
    int day = start / 1000000;              // First two digits
    int month = (start / 10000) % 100;        // Next two digits
    int year = start % 10000;                 // Last four digits

    startDate.tm_mday = day;
    startDate.tm_mon = month - 1;             // tm_mon is 0-indexed (0 = January)
    startDate.tm_year = year - 1900;          // tm_year is years since 1900

    // Extract day, month, and year from the end date (format DDMMYYYY)
    day = end / 1000000;
    month = (end / 10000) % 100;
    year = end % 10000;

    endDate.tm_mday = day;
    endDate.tm_mon = month - 1;
    endDate.tm_year = year - 1900;

    // Convert tm structures to time_t values
    time_t start_time = mktime(&startDate);
    time_t end_time = mktime(&endDate);

    // Calculate difference in days
    return (end_time - start_time) / (60 * 60 * 24);
}

void updatestudentInfoafterreturning(const string &filename, const string &username, string book,int fine)
{
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string uname, password, id;
        int  fineDue;
        vector<string>books;
        vector<string>borr_History;
        
        int borr_Historysize;

        // Read each field separated by commas
        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        char comma;
            ss >> fineDue>>comma>>borr_Historysize;
            string borrowedBookhis;
            for(int i=1;i<=borr_Historysize;i++){
                if (ss.peek() == ',')
                {
                    ss.ignore();
                }
                getline(ss,borrowedBookhis,',');
               
                borr_History.push_back(borrowedBookhis);
            }
            if (ss.peek() == ',')
                {
                    ss.ignore();
                }
    
            // 4) Read the rest of the line as borrowed books
            // Make sure it's empty before pushing back
            string borrowedBook;
            while (getline(ss, borrowedBook, ','))
            {
                books.push_back(borrowedBook);
            }
            if (getline(ss, borrowedBook)) {
                if (!borrowedBook.empty()) {
                    books.push_back(borrowedBook);
                }
            }

        // Print the values to check if they are read correctly
        // cout << "Username: " << uname << ", Password: " << password << ", ID: " << id
        //<< ", studentRecord: " << studentRecord << ", FineDue: " << fineDue << endl;
        if (uname == username)
        {
            // Update the line with new information
            tempFile << uname << "," << password << "," << id << "," <<fineDue+fine<<","<<borr_Historysize+1;
            for (size_t j = 0; j < borr_Historysize; j++)
            {
                tempFile << "," << borr_History[j]; // Ensure proper formatting
            }
            tempFile << "," << book;
            
            
            for (size_t j = 0; j < books.size(); j++)
            {
                if(books[j]!=book){
                tempFile << "," << books[j]; }// Ensure proper formatting
            }
            
            updated = true;
        }
        else
        {
            // Write the original line to the temporary file
            tempFile << line;
        }
        if (!inFile.eof())
        {
            tempFile << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated)
    {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
    else
    {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}

void updatestudentInfo(const string &filename, const string &username, string newbook)
{
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line))
    {
        
        stringstream ss(line);
        string uname, password, id;
        int  fineDue;
        vector<string>books;
        vector<string>borr_History;
        
        int borr_Historysize;

        // Read each field separated by commas
        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        char comma;
        ss >> fineDue>>comma>>borr_Historysize;
        string borrowedBookhis;
        for(int i=1;i<=borr_Historysize;i++){
            if (ss.peek() == ',')
            {
                ss.ignore();
            }
            getline(ss,borrowedBookhis,',');
           
            borr_History.push_back(borrowedBookhis);
        }
        if (ss.peek() == ',')
            {
                ss.ignore();
            }
    
            // 4) Read the rest of the line as borrowed books
            // Make sure it's empty before pushing back
            string borrowedBook;
            while (getline(ss, borrowedBook, ','))
            {
                books.push_back(borrowedBook);
            }
            if (getline(ss, borrowedBook)) {
                if (!borrowedBook.empty()) {
                    books.push_back(borrowedBook);
                }
            }
        // Print the values to check if they are read correctly
        // cout << "Username: " << uname << ", Password: " << password << ", ID: " << id
        //<< ", studentRecord: " << studentRecord << ", FineDue: " << fineDue << endl;
        if (uname == username)
        {
            // Update the line with new information
            tempFile << uname << "," << password << "," << id << "," <<fineDue<<","<<borr_Historysize;
            for (size_t j = 0; j < borr_Historysize; j++)
            {
                tempFile << "," << borr_History[j]; // Ensure proper formatting
            }
           
            
            
            for (size_t j = 0; j < books.size(); j++)
            {
               
            tempFile << "," << books[j]; // Ensure proper formatting
            }
            tempFile << "," << newbook;
            updated = true;
        }
        else
        {
            // Write the original line to the temporary file
            tempFile << line;
        }
        if (!inFile.eof())
        {
            tempFile << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated)
    {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
    else
    {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}

void clearfinedue(const string &filename, const string &username, int amount)
{
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string uname, password, id;
        int  fineDue;
        vector<string>books;
        vector<string>borr_History;
        
        int borr_Historysize;

        // Read each field separated by commas
        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        char comma;
        ss >> fineDue>>comma>>borr_Historysize;
        string borrowedBookhis;
        for(int i=1;i<=borr_Historysize;i++){
            if (ss.peek() == ',')
            {
                ss.ignore();
            }
            getline(ss,borrowedBookhis,',');
           
            borr_History.push_back(borrowedBookhis);
        }
        if (ss.peek() == ',')
            {
                ss.ignore();
            }
    
            // 4) Read the rest of the line as borrowed books
            // Make sure it's empty before pushing back
            string borrowedBook;
            while (getline(ss, borrowedBook, ','))
            {
                books.push_back(borrowedBook);
            }
            if (getline(ss, borrowedBook)) {
                if (!borrowedBook.empty()) {
                    books.push_back(borrowedBook);
                }
            }

        // Print the values to check if they are read correctly
        // cout << "Username: " << uname << ", Password: " << password << ", ID: " << id
        //<< ", studentRecord: " << studentRecord << ", FineDue: " << fineDue << endl;
        if (uname == username)
        {
            // Update the line with new information
            tempFile << uname << "," << password << "," << id << "," <<fineDue-amount<<","<<borr_Historysize;
            for (size_t j = 0; j < borr_Historysize; j++)
            {
                tempFile << "," << borr_History[j]; // Ensure proper formatting
            }
           
            
            
            for (size_t j = 0; j < books.size(); j++)
            {
               
            tempFile << "," << books[j]; // Ensure proper formatting
            }
          
            updated = true;
        }
        else
        {
            // Write the original line to the temporary file
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated)
    {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
    else
    {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}
void Librarian ::deletestudent(const string &filename, const string &username)
{
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string uname, password, id;
        int  fineDue;
        vector<string>books;
        vector<string>borr_History;
       
        int borr_Historysize;

        // Read each field separated by commas
        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        char comma;
        ss >> fineDue>>comma>>borr_Historysize;
        string borrowedBookhis;
        for(int i=1;i<=borr_Historysize;i++){
            if (ss.peek() == ',')
            {
                ss.ignore();
            }
            getline(ss,borrowedBookhis,',');
           
            borr_History.push_back(borrowedBookhis);
        }
        if (ss.peek() == ',')
            {
                ss.ignore();
            }
    
            // 4) Read the rest of the line as borrowed books
            // Make sure it's empty before pushing back
            string borrowedBook;
            while (getline(ss, borrowedBook, ','))
            {
                books.push_back(borrowedBook);
            }
            if (getline(ss, borrowedBook)) {
                if (!borrowedBook.empty()) {
                    books.push_back(borrowedBook);
                }
            }
        // Print the values to check if they are read correctly
        // cout << "Username: " << uname << ", Password: " << password << ", ID: " << id
        //<< ", studentRecord: " << studentRecord << ", FineDue: " << fineDue << endl;
        if (uname == username)
        {
            // Update the line with new information
            updated = true;
            continue;
        }
        else
        {
            // Write the original line to the temporary file
            tempFile << line;
        }
        if (!inFile.eof())
        {
            tempFile << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated)
    {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
    else
    {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}
void Librarian ::Searchstudent(const string &filename, const string &username)
{
    ifstream inFile(filename);

    if (!inFile)
    {
        cerr << "Error opening file." << endl;
        return; // Error condition or default value
    }
    int flag = 0;
    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string uname, password, id;
        int  fineDue;
        vector<string>books;
        vector<string>borr_History;
        
        int borr_Historysize;

        // Read each field separated by commas
        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        char comma;
        ss >> fineDue>>comma>>borr_Historysize;
        string borrowedBookhis;
        for(int i=1;i<=borr_Historysize;i++){
            if (ss.peek() == ',')
            {
                ss.ignore();
            }
            getline(ss,borrowedBookhis,',');
           
            borr_History.push_back(borrowedBookhis);
        }
        if (ss.peek() == ',')
            {
                ss.ignore();
            }
            // 4) Read the rest of the line as borrowed books
            // Make sure it's empty before pushing back
            string borrowedBook;
            while (getline(ss, borrowedBook, ','))
            {
                books.push_back(borrowedBook);
            }
            if (getline(ss, borrowedBook)) {
                if (!borrowedBook.empty()) {
                    books.push_back(borrowedBook);
                }
            }
        if (uname == username)
        {
            cout << "username: " << username << endl;
            cout << "id: " << id << endl;
            cout << "fine Due: " << fineDue << endl;
            flag = 1;
            break;
        }
        if (flag == 0)
            cout << "User doesn't exist \n";
        inFile.close();
        return;
    }
}

vector<string> displayborrowedbookhistory(const string &filename, const string &username)
{
    ifstream inFile(filename);
    
vector<string>d;

    if (!inFile)
    {
        cerr << "Error opening file." << endl;
        
        return d; // Error condition or default value
    }
    int flag = 0;
    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string uname, password, id;
        int  fineDue;
        vector<string>books;
        vector<string>borr_History;
        
        int borr_Historysize;

        // Read each field separated by commas
        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        char comma;
        ss >> fineDue>>comma>>borr_Historysize;
        string borrowedBookhis;
        for(int i=1;i<=borr_Historysize;i++){
            if (ss.peek() == ',')
            {
                ss.ignore();
            }
            getline(ss,borrowedBookhis,',');
           
            borr_History.push_back(borrowedBookhis);
        }
        if (ss.peek() == ',')
            {
                ss.ignore();
            }
            // 4) Read the rest of the line as borrowed books
            // Make sure it's empty before pushing back
            string borrowedBook;
            while (getline(ss, borrowedBook, ','))
            {
                books.push_back(borrowedBook);
            }
            if (getline(ss, borrowedBook)) {
                if (!borrowedBook.empty()) {
                    books.push_back(borrowedBook);
                }
            }
        if (uname == username)
        {
            return borr_History;
        }
        
        
    }
    inFile.close();
        return d;
}
void updatefacultyInfo(const string &filename, const string &username, string newbook)
{
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string uname, password, id;
        int  fineDue;
        vector<string>books;
        vector<string>borr_History;
        
        int borr_Historysize;

        // Read each field separated by commas
        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        char comma;
        ss >> fineDue>>comma>>borr_Historysize;
        string borrowedBookhis;
        for(int i=1;i<=borr_Historysize;i++){
            if (ss.peek() == ',')
            {
                ss.ignore();
            }
            getline(ss,borrowedBookhis,',');
           
            borr_History.push_back(borrowedBookhis);
        }
        if (ss.peek() == ',')
            {
                ss.ignore();
            }
    
            // 4) Read the rest of the line as borrowed books
            // Make sure it's empty before pushing back
            string borrowedBook;
            while (getline(ss, borrowedBook, ','))
            {
                books.push_back(borrowedBook);
            }
            if (getline(ss, borrowedBook)) {
                if (!borrowedBook.empty()) {
                    books.push_back(borrowedBook);
                }
            }

        // Print the values to check if they are read correctly
        // cout << "Username: " << uname << ", Password: " << password << ", ID: " << id
        //<< ", facultyRecord: " << facultyRecord << ", FineDue: " << fineDue << endl;
        if (uname == username)
        {
            // Update the line with new information
            tempFile << uname << "," << password << "," << id << "," <<fineDue<<","<<borr_Historysize;
            for (size_t j = 0; j < borr_Historysize; j++)
            {
                tempFile << "," << borr_History[j]; // Ensure proper formatting
            }
           
            
            
            for (size_t j = 0; j < books.size(); j++)
            {
               
            tempFile << "," << books[j]; // Ensure proper formatting
            }
            tempFile << "," << newbook;
            updated = true;
        }
        else
        {
            // Write the original line to the temporary file
            tempFile << line;
        }
        if (!inFile.eof())
        {
            tempFile << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated)
    {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
    else
    {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}

void Librarian ::deletefaculty(const string &filename, const string &username)
{
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line))
    {
       
        stringstream ss(line);
        string uname, password, id;
        int  fineDue;
        vector<string>books;
        vector<string>borr_History;
        
        int borr_Historysize;

        // Read each field separated by commas
        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        char comma;
        ss >> fineDue>>comma>>borr_Historysize;
        string borrowedBookhis;
        for(int i=1;i<=borr_Historysize;i++){
            if (ss.peek() == ',')
            {
                ss.ignore();
            }
            getline(ss,borrowedBookhis,',');
           
            borr_History.push_back(borrowedBookhis);
        }
        if (ss.peek() == ',')
            {
                ss.ignore();
            }
            // 4) Read the rest of the line as borrowed books
            // Make sure it's empty before pushing back
            string borrowedBook;
            while (getline(ss, borrowedBook, ','))
            {
                books.push_back(borrowedBook);
            }
            if (getline(ss, borrowedBook)) {
                if (!borrowedBook.empty()) {
                    books.push_back(borrowedBook);
                }
            }

        // Print the values to check if they are read correctly
        // cout << "Username: " << uname << ", Password: " << password << ", ID: " << id
        //<< ", facultyRecord: " << facultyRecord << ", FineDue: " << fineDue << endl;
        if (uname == username)
        {
            // Update the line with new information

            updated = true;
            continue;
        }
        else
        {
            // Write the original line to the temporary file
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated)
    {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
    else
    {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}
//has to be done
void Librarian ::Searchfaculty(const string &filename, const string &username)
{
    ifstream inFile(filename);

    if (!inFile)
    {
        cerr << "Error opening file." << endl;
        return; // Error condition or default value
    }
    int flag = 0;
    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string uname, password, id;
        int  fineDue;
        vector<string>books;
        vector<string>borr_History;
        
        int borr_Historysize;

        // Read each field separated by commas
        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        char comma;
        ss >> fineDue>>comma>>borr_Historysize;
        string borrowedBookhis;
        for(int i=1;i<=borr_Historysize;i++){
            if (ss.peek() == ',')
            {
                ss.ignore();
            }
            getline(ss,borrowedBookhis,',');
           
            borr_History.push_back(borrowedBookhis);
        }
        if (ss.peek() == ',')
            {
                ss.ignore();
            }
    
            // 4) Read the rest of the line as borrowed books
            // Make sure it's empty before pushing back
            string borrowedBook;
            while (getline(ss, borrowedBook, ','))
            {
                books.push_back(borrowedBook);
            }
            if (getline(ss, borrowedBook)) {
                if (!borrowedBook.empty()) {
                    books.push_back(borrowedBook);
                }
            }
             if (uname == username)
        {
            cout << "username: " << username << endl;
            cout << "id: " << id << endl;
            
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        cout << "User doesn't exist \n";
    inFile.close();
    return;
}

int getBookAvailability(const string &filename, const string &isbn_entering)
{
    ifstream inFile(filename);
    if (!inFile.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return -1; // Error code for file not found or inaccessible
    }

    string line;
    // We'll return -1 if we don't find the book at all
    int availability = -1;

    // Read each line from the file
    while (getline(inFile, line))
    {
        stringstream ss(line);

        // According to your screenshot, each line is:
        // title,ISBN,author,publisher,year,status,borroweddate,towhom
        string title, ISBN, author, publisher, year, status, towhom;
        int borroweddate = 0;

        // 1. Extract the string fields in the correct order
        getline(ss, title, ',');
        getline(ss, ISBN, ',');
        getline(ss, author, ',');
        getline(ss, publisher, ',');
        getline(ss, year, ',');
        getline(ss, status, ',');

        // 2. Extract the integer borroweddate
        ss >> borroweddate;

        // 3. If there's still a comma left, ignore it before reading towhom
        if (ss.peek() == ',')
        {
            ss.ignore();
        }

        // 4. Finally read the towhom field (which might be "none" or a username)
        getline(ss, towhom);

        // Compare the ISBN from the file with the parameter
        if (ISBN == isbn_entering)
        {
            // Convert the string 'status' to an integer availability
            // Example: 1 if status == "available", 0 otherwise
            if (status == "available")
                availability = 1;
            else
                availability = 0;

            // Book found, no need to check further
            break;
        }
    }

    inFile.close();
    return availability;
}
int getBookborroweddate(const string &filename, const string &isbn_entering)
{
    ifstream inFile(filename);
    if (!inFile.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return -1; // Error code for file not found or inaccessible
    }

    string line;
    // We'll return -1 if we don't find the book at all
    

    // Read each line from the file
    while (getline(inFile, line))
    {
        stringstream ss(line);

        // According to your screenshot, each line is:
        // title,ISBN,author,publisher,year,status,borroweddate,towhom
        string title, ISBN, author, publisher, year, status, towhom;
        int borroweddate = 0;

        // 1. Extract the string fields in the correct order
        getline(ss, title, ',');
        getline(ss, ISBN, ',');
        getline(ss, author, ',');
        getline(ss, publisher, ',');
        getline(ss, year, ',');
        getline(ss, status, ',');

        // 2. Extract the integer borroweddate
        ss >> borroweddate;

        // 3. If there's still a comma left, ignore it before reading towhom
        if (ss.peek() == ',')
        {
            ss.ignore();
        }

        // 4. Finally read the towhom field (which might be "none" or a username)
        getline(ss, towhom);

        // Compare the ISBN from the file with the parameter
        if (ISBN == isbn_entering)
        {
            // Convert the string 'status' to an integer availability
            // Example: 1 if status == "available", 0 otherwise
            return borroweddate;
        }
    }

    inFile.close();
    return 0;
}

int hasUserRentedbook(const string &filename, const string &username)
{
    ifstream inFile(filename);

    if (!inFile)
    {
        cerr << "Error opening file." << endl;
        return false; // Error condition or default value
    }

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);

        // According to your screenshot, each line is:
        // title,ISBN,author,publisher,year,status,borroweddate,towhom
        string title, ISBN, author, publisher, year, status, towhom;
        int borroweddate = 0;

        // 1. Extract the string fields in the correct order
        getline(ss, title, ',');
        getline(ss, ISBN, ',');
        getline(ss, author, ',');
        getline(ss, publisher, ',');
        getline(ss, year, ',');
        getline(ss, status, ',');

        // 2. Extract the integer borroweddate
        ss >> borroweddate;

        // 3. If there's still a comma left, ignore it before reading towhom
        if (ss.peek() == ',')
        {
            ss.ignore();
        }

        // 4. Finally read the towhom field (which might be "none" or a username)
        getline(ss, towhom);

        if (towhom == username)
        {
            inFile.close();
            return 1;
        }
    }

    inFile.close();
    return 0;
}

string getBookRenter(const string &filename, const string &isbn_entering)
{
    ifstream inFile(filename);
    if (!inFile.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return ""; // Return empty if there's an error
    }

    string line;
    // Go through each line in the file
    while (getline(inFile, line))
    {
        stringstream ss(line);

        // Parse CSV fields in the same order they're written
        string title, ISBN, author, publisher, year, status, towhom;
        int borroweddate;

        // Read each field, separated by commas
        getline(ss, title, ',');
        getline(ss, ISBN, ',');
        getline(ss, author, ',');
        getline(ss, publisher, ',');
        getline(ss, year, ',');
        getline(ss, status, ',');
        ss >> borroweddate;

        // If there's still a comma, ignore it before reading the next field
        if (ss.peek() == ',')
        {
            ss.ignore();
        }
        // Read the 'towhom' field
        getline(ss, towhom);

        // Compare ISBN to find the matching book
        if (isbn_entering == ISBN)
        {
            inFile.close();
            return towhom; // Return the owner of the matching book
        }
    }

    inFile.close();
    // If no matching ISBN is found, return a default value
    return "none";
}


void addBookToFile(const string &filename,
    const string &title,
    const string &ISBN,
    const string &author,
    const string &publisher,
    const string &year,
    const string &status,
    int borroweddate,
    const string &towhom = "none")
{
ofstream file(filename, ios::app); // Open in append mode
if (!file.is_open())
{
cerr << "Error: Unable to open file " << filename << endl;
return;
}

// Write book data in CSV format
file << title << "," 
<< ISBN << "," 
<< author << "," 
<< publisher << "," 
<< year << "," 
<< status << "," 
<< borroweddate << "," 
<< towhom 
<< "\n";

file.close();
}

int main()
{
    vector<book> books = readbookData();
    vector<student> students = student::readstudentData();
    vector<faculty> faculties = faculty::readfacultyData();
    vector<Librarian> Librarians = Librarian::readLibrarianData();
   
    while (true)
{
    cout << "====================================\n"
         << "           Library Portal           \n"
         << "====================================\n"
         << "1. Student\n"
         << "2. Faculty\n"
         << "3. Librarian\n"
         << "Any other number to exit\n"
         << "====================================\n"
         << "Enter your choice: ";
    int verification;
    if (!(cin >> verification))
    {
        cout << "\n------------------------------------\n"
             << "Error: Invalid input. Please enter an integer.\n"
             << "------------------------------------\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
    }
    if (verification != 1 && verification != 2 && verification != 3)
    {
        cout << "\n====================================\n"
             << "         Thank you! See you again!  \n"
             << "====================================\n";
        return 0;
    }
    
    string username;
    if (verification == 1)
    {
        cout << "\n====================================\n"
             << "Are you already registered? (Type YES or NO): ";
        string answer;
        while (true)
        {
            cin >> answer;
            transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
            if (answer == "YES" || answer == "NO")
            {
                break;
            }
            else
            {
                cout << "\n------------------------------------\n"
                     << "Error: Invalid input. Please type YES or NO.\n"
                     << "------------------------------------\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        if (answer == "YES")
        {
            cout << "\n====================================\n"
                 << "Enter username: ";
            cin >> username;

            vector<student> students = student::readstudentData();
            auto it = find_if(students.begin(), students.end(),
                              [username](const student &c)
                              { return c.getUsername() == username; });
            if (it != students.end())
            {
                cout << "\n====================================\n"
                     << "Enter password: ";
                string password;
                cin >> password;
                books = readbookData();

                if (it->authenticate(password))
                {
                    cout << "\n====================================\n"
                         << "Login successful! Welcome, " << it->getUsername() << "!\n"
                         << "====================================\n";

                    // 1) Show all available books
                    cout << "\n====================================\n"
                         << "          Available Books           \n"
                         << "====================================\n";
                    for (auto &bk : books)
                    {
                        if (bk.checkAvailability())
                            bk.displayDetailsIfAvailable();
                    }

                    // 2) Show books currently rented by this user
                    cout << "\n====================================\n"
                         << "         Your Rented Books          \n"
                         << "====================================\n";
                    for (auto &bk : books)
                    {
                        bk.displayDetailsofRentedbook(username);
                    }

                    cout << "\n------------------------------------\n"
                         << "Enter the number of books you want to return: ";
                    int bookreturno;
                    while (true)
                    {
                        cin >> bookreturno;
                        if (cin.fail())
                        {
                            cout << "\n------------------------------------\n"
                                 << "Error: Invalid input. Please enter a valid integer.\n"
                                 << "------------------------------------\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        else
                        {
                            break;
                        }
                    }

                    // 3) Returning books
                    for (int a = 0; a < bookreturno; a++)
                    {
                        cout << "\n====================================\n"
                             << "Enter ISBN of book to return: ";
                        string ISBN;
                        cin >> ISBN;

                        string user = getBookRenter("book.txt", ISBN);
                        if (username != user)
                        {
                            cout << "\n------------------------------------\n"
                                 << "Notice: You have not rented this book.\n"
                                 << "------------------------------------\n";
                            continue;
                        }

                        int days;
                        cout << "\n====================================\n"
                             << "Enter the number of days after which you are returning the book: ";
                        while (true)
                        {
                            cin >> days;
                            if (cin.fail())
                            {
                                cout << "\n------------------------------------\n"
                                     << "Error: Invalid input. Please enter a valid integer.\n"
                                     << "------------------------------------\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            else
                            {
                                break;
                            }
                        }

                        if (days > 15)
                        {
                            cout << "\n------------------------------------\n"
                                 << "Notice: You are " << (days - 15)
                                 << " day(s) late in returning the book.\n"
                                 << "------------------------------------\n";
                        }
                        updatestudentInfoafterreturning("student.txt", username, ISBN, 10 * (max(0, days - 15)));
                        updatebookInfo("book.txt", ISBN, "available", 0, "none");
                        cout << "\n====================================\n"
                             << "Success: Book successfully returned!\n"
                             << "====================================\n";
                    }
                    int date;
                    cout << "\n====================================\n"
                         << "Enter today's date in xx|xx|xxxx format (without slash): ";
                    while (true)
                    {
                        cin >> date;
                        if (cin.fail())
                        {
                            cout << "\n------------------------------------\n"
                                 << "Error: Invalid input. Please enter a valid integer.\n"
                                 << "------------------------------------\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        else
                        {
                            break;
                        }
                    }
                    int flag = 0;
                    books = readbookData();
                    for (auto &bk : books)
                    {
                        if (bk.hasuserRentedbook(username))
                        {
                            if (daysBetweenDates(getBookborroweddate("book.txt", bk.getISBN()), date) > 15)
                                flag = 1;
                        }
                    }
                    if (flag == 1)
                    {
                        cout << "\n====================================\n"
                             << "Alert: You have an overdue book. Please return it and clear your fine dues.\n"
                             << "====================================\n";
                    }
                    else
                    {
                        vector<student> students = student::readstudentData();
                        int studentcheck = 0;
                        for (auto &st : students)
                        {
                            if (username == st.getUsername())
                            {
                                if (st.getFineDue() > 0 || st.getnoofbooksrented() == 3)
                                    studentcheck = 0;
                                else
                                    studentcheck = 3 - st.getnoofbooksrented();
                                break;
                            }
                        }

                        books = readbookData();
                        cout << "\n====================================\n"
                             << "You are eligible to rent " << studentcheck << " book(s).\n"
                             << "====================================\n"
                             << "Enter the number of books you want to rent: ";
                        int bookrent;
                        while (true)
                        {
                            cin >> bookrent;
                            if (cin.fail())
                            {
                                cout << "\n------------------------------------\n"
                                     << "Error: Invalid input. Please enter a valid integer.\n"
                                     << "------------------------------------\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            else if (bookrent > studentcheck)
                            {
                                cout << "\n------------------------------------\n"
                                     << "Notice: You can't rent this many books. Try again.\n"
                                     << "------------------------------------\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                bookrent = 0;
                                break;
                            }
                            else
                            {
                                break;
                            }
                        }

                        // 5) Rent the specified number of books
                        for (int a = 0; a < bookrent; a++)
                        {
                            cout << "\n====================================\n"
                                 << "Enter ISBN of book to rent: ";
                            string ISBN;
                            cin >> ISBN;

                            int availability = getBookAvailability("book.txt", ISBN);
                            if (availability != 1)
                            {
                                cout << "\n------------------------------------\n"
                                     << "Notice: Book is not available to rent.\n"
                                     << "------------------------------------\n";
                                continue;
                            }

                            updatestudentInfo("student.txt", username, ISBN);
                            updatebookInfo("book.txt", ISBN, "borrowed", date, username);
                            cout << "\n====================================\n"
                                 << "Success: Book successfully rented!\n"
                                 << "====================================\n";
                        }
                    
                        // 6) Display fine info
                        int fine = 0;
                        auto it2 = find_if(students.begin(), students.end(),
                                           [username](const student &c)
                                           { return c.getUsername() == username; });
                        if (it2 != students.end())
                        {
                            fine = it2->getFineDue();
                        }
                        cout << "\n====================================\n"
                             << "Your current fine dues: " << fine << "\n"
                             << "====================================\n";
                        if (fine != 0)
                        {
                            cout << "Enter the amount by which you want to clear your fine: ";
                            int amount;
                            while (true)
                            {
                                cin >> amount;
                                if (cin.fail())
                                {
                                    cout << "\n------------------------------------\n"
                                         << "Error: Invalid input. Please enter a valid integer.\n"
                                         << "------------------------------------\n";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                                else
                                {
                                    break;
                                }
                            }
                            clearfinedue("student.txt", username, amount);
                            cout << "\n====================================\n"
                                 << "Success: Your fine has been updated!\n"
                                 << "====================================\n";
                        }
                    }
                    cout << "\n====================================\n"
                         << "Press 1 to see your borrowed history details: ";
                    int inp;
                    while (true)
                    {
                        cin >> inp;
                        if (cin.fail())
                        {
                            cout << "\n------------------------------------\n"
                                 << "Error: Invalid input. Please enter a valid integer.\n"
                                 << "------------------------------------\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        else
                        {
                            break;
                        }
                    }
                    if (inp == 1){vector<string> history;
                    history=displayborrowedbookhistory("student.txt", username);
                    cout << "\n========================================\n";
                    cout << "         Borrowed Books' ISBNs\n";
                    cout << "========================================\n";
                
                    // Loop through the history vector and print each ISBN with an index
                    for (size_t i = 0; i < history.size(); i++) {
                        // setw to align the numbering and ISBNs
                        cout << (i + 1) << ". " 
<< history[i] << "\n";
                    }
                
                    cout << "========================================\n";
                }
                }
                else
                {
                    cout << "\n------------------------------------\n"
                         << "Error: Incorrect password. Please try again.\n"
                         << "------------------------------------\n";
                }
            }
            else
            {
                cout << "\n------------------------------------\n"
                     << "Notice: Username not found. Please register.\n"
                     << "------------------------------------\n";
            }
        }
        else
        {
            cout << "\n====================================\n"
                 << "Proceeding to Student Registration...\n"
                 << "====================================\n";
            Librarian Librarian;
            Librarian.registerNewstudent();
        }
    }
    // Additional code for handling Faculty or Librarian verification values can be added here.


    else if (verification == 3)
    {   
        cout << "\n====================================\n"
             << "   Librarian Registration Check     \n"
             << "====================================\n"
             << "Are you already registered? (Type YES or NO): ";
        string answer;
        while (true)
        {
            cin >> answer;
            transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
            if (answer == "YES" || answer == "NO")
            {
                break; // Valid input, exit the loop
            }
            else
            {
                cout << "\n------------------------------------\n"
                     << "Error: Invalid input. Please type YES or NO.\n"
                     << "------------------------------------\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    
        if (answer == "YES")
        {
            cout << "\n====================================\n"
                 << "Enter username: ";
            cin >> username;
            Librarian Librariane;
            vector<Librarian> Librarians = Librarian::readLibrarianData();
    
            auto it = find_if(Librarians.begin(), Librarians.end(),
                              [username](const Librarian &c)
                              { return c.getUsername() == username; });
    
            if (it != Librarians.end())
            {
                cout << "\n====================================\n"
                     << "Enter password: ";
                string password;
                cin >> password;
                books = readbookData();
    
                if (it->authenticate(password))
                {
                    cout << "\n====================================\n"
                         << "Login successful! Welcome, " << it->getUsername() << "!\n"
                         << "====================================\n";
                    cout << "\n====================================\n"
                         << "Press 1 to see the book database details: ";
                    int inp;
                    while (true)
                    {
                        cin >> inp;
                        if (cin.fail())
                        {
                            cout << "\n------------------------------------\n"
                                 << "Error: Invalid input. Please enter a valid integer.\n"
                                 << "------------------------------------\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        else
                        {
                            break;
                        }
                    }
                    if (inp == 1)
                        book::displayDetails();
    
                    string input;
                    cout << "\n====================================\n"
                         << "Do you want to register a new student? (yes/no): ";
                    while (true)
                    {
                        cin >> input;
                        transform(input.begin(), input.end(), input.begin(), ::tolower);
                        if (input == "yes" || input == "no")
                        {
                            break;
                        }
                        else
                        {
                            cout << "\n------------------------------------\n"
                                 << "Error: Invalid input. Please type yes or no.\n"
                                 << "------------------------------------\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    }
                    if (input == "yes")
                        Librariane.registerNewstudent();
    
                    cout << "\n====================================\n"
                         << "Do you want to delete a student? (yes/no): ";
                    while (true)
                    {
                        cin >> input;
                        transform(input.begin(), input.end(), input.begin(), ::tolower);
                        if (input == "yes" || input == "no")
                        {
                            break;
                        }
                        else
                        {
                            cout << "\n------------------------------------\n"
                                 << "Error: Invalid input. Please type yes or no.\n"
                                 << "------------------------------------\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    }
                    if (input == "yes")
                    {
                        cout << "\n====================================\n"
                             << "Enter username to delete: ";
                        string username;
                        cin >> username;
                        if (hasUserRentedbook("book.txt", username))
                        {
                            cout << "\n------------------------------------\n"
                                 << "Notice: Cannot delete because the user is renting a book.\n"
                                 << "------------------------------------\n";
                        }
                        else
                        {
                            Librariane.deletestudent("student.txt", username);
                            cout << "\n====================================\n"
                                 << "Success: Student deleted successfully.\n"
                                 << "====================================\n";
                        }
                    }
    
                    cout << "\n====================================\n"
                         << "Do you want to get the info of a specific student? (yes/no): ";
                    while (true)
                    {
                        cin >> input;
                        transform(input.begin(), input.end(), input.begin(), ::tolower);
                        if (input == "yes" || input == "no")
                        {
                            break;
                        }
                        else
                        {
                            cout << "\n------------------------------------\n"
                                 << "Error: Invalid input. Please type yes or no.\n"
                                 << "------------------------------------\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    }
                    if (input == "yes")
                    {
                        cout << "\n====================================\n"
                             << "Enter username for student info: ";
                        string username;
                        cin >> username;
                        Librariane.Searchfaculty("student.txt", username);
                    }
                    
                    cout << "\n====================================\n"
                         << "Do you want to register new faculty? (yes/no): ";
                    while (true)
                    {
                        cin >> input;
                        transform(input.begin(), input.end(), input.begin(), ::tolower);
                        if (input == "yes" || input == "no")
                        {
                            break;
                        }
                        else
                        {
                            cout << "\n------------------------------------\n"
                                 << "Error: Invalid input. Please type yes or no.\n"
                                 << "------------------------------------\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    }
                    if (input == "yes")
                        Librariane.registerNewfaculty();
    
                    cout << "\n====================================\n"
                         << "Do you want to delete a faculty? (yes/no): ";
                    while (true)
                    {
                        cin >> input;
                        transform(input.begin(), input.end(), input.begin(), ::tolower);
                        if (input == "yes" || input == "no")
                        {
                            break;
                        }
                        else
                        {
                            cout << "\n------------------------------------\n"
                                 << "Error: Invalid input. Please type yes or no.\n"
                                 << "------------------------------------\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    }
                    if (input == "yes")
                    {
                        cout << "\n====================================\n"
                             << "Enter username to delete: ";
                        string username;
                        cin >> username;
                        if (hasUserRentedbook("book.txt", username))
                        {
                            cout << "\n------------------------------------\n"
                                 << "Notice: Cannot delete because the user is renting a book.\n"
                                 << "------------------------------------\n";
                        }
                        else
                        {
                            Librariane.deletefaculty("faculty.txt", username);
                            cout << "\n====================================\n"
                                 << "Success: Faculty deleted successfully.\n"
                                 << "====================================\n";
                        }
                    }
    
                    cout << "\n====================================\n"
                         << "Do you want to get the info of a specific faculty? (yes/no): ";
                    while (true)
                    {
                        cin >> input;
                        transform(input.begin(), input.end(), input.begin(), ::tolower);
                        if (input == "yes" || input == "no")
                        {
                            break;
                        }
                        else
                        {
                            cout << "\n------------------------------------\n"
                                 << "Error: Invalid input. Please type yes or no.\n"
                                 << "------------------------------------\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    }
                    if (input == "yes")
                    {
                        cout << "\n====================================\n"
                             << "Enter username for faculty info: ";
                        string username;
                        cin >> username;
                        Librariane.Searchfaculty("faculty.txt", username);
                    }
                    
                    cout << "\n====================================\n"
                         << "Do you want to add a book? (yes/no): ";
                    while (true)
                    {
                        cin >> input;
                        transform(input.begin(), input.end(), input.begin(), ::tolower);
                        if (input == "yes" || input == "no")
                        {
                            break;
                        }
                        else
                        {
                            cout << "\n------------------------------------\n"
                                 << "Error: Invalid input. Please type yes or no.\n"
                                 << "------------------------------------\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    }
    
                    if (input == "yes")
                    {
                        // Variables for user input
                        string title, ISBN, author, publisher, year, status, towhom;
                        int borroweddate;
    
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer before getline
    
                        cout << "\n====================================\n"
                             << "Enter book title: ";
                        getline(cin, title);
    
                        cout << "Enter ISBN: ";
                        getline(cin, ISBN);
    
                        cout << "Enter author: ";
                        getline(cin, author);
    
                        cout << "Enter publisher: ";
                        getline(cin, publisher);
    
                        cout << "Enter year: ";
                        getline(cin, year);
    
                        cout << "Enter book status (e.g available, borrowed and reserved): ";
                        getline(cin, status);
    
                        cout << "Enter borrowed date (as integer DDMMYYYY): ";
                        while (true)
                        {
                            cin >> borroweddate;
                            if (cin.fail())
                            {
                                cout << "\n------------------------------------\n"
                                     << "Error: Invalid input. Please enter a valid integer (e.g., 20250303).\n"
                                     << "------------------------------------\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            else
                            {
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                break;
                            }
                        }
    
                        cout << "Enter to whom the book is issued (press Enter for 'none'): ";
                        getline(cin, towhom);
                        if (towhom.empty())
                        {
                            towhom = "none";
                        }
    
                        addBookToFile("book.txt", title, ISBN, author, publisher, year, status, borroweddate, towhom);
                        cout << "\n====================================\n"
                             << "Success: Book added successfully.\n"
                             << "====================================\n";
                    }
                    
                    cout << "\n====================================\n"
                         << "Do you want to update any book property? (yes/no): ";
                    while (true)
                    {
                        cin >> input;
                        transform(input.begin(), input.end(), input.begin(), ::tolower);
                        if (input == "yes" || input == "no")
                        {
                            break;
                        }
                        else
                        {
                            cout << "\n------------------------------------\n"
                                 << "Error: Invalid input. Please type yes or no.\n"
                                 << "------------------------------------\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    }
                    if (input == "yes")
                    {
                        cout << "\n====================================\n"
                             << "Enter ISBN: ";
                        string ISBN;
                        cin >> ISBN;
                        cout << "Enter new Availability (available, reserved, borrowed): ";
                        string status;
                        while (true)
                        {
                            cin >> status;
                            if (cin.fail())
                            {
                                cout << "\n------------------------------------\n"
                                     << "Error: Invalid input. Please enter a valid string.\n"
                                     << "------------------------------------\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            else
                            {
                                break;
                            }
                        }
                       
                        cout << "Enter new renter: ";
                        string newwhom;
                        cin >> newwhom;
                        int date = 0;
                        if (newwhom != "none")
                        {
                            cout << "Enter today's date in xx|xx|xxxx format (without slash): ";
                            while (true)
                            {
                                cin >> date;
                                if (cin.fail())
                                {
                                    cout << "\n------------------------------------\n"
                                         << "Error: Invalid input. Please enter a valid integer.\n"
                                         << "------------------------------------\n";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                                else
                                {
                                    break;
                                }
                            }
                            updatestudentInfo("student.txt", username, ISBN);
                        }
                        updatebookInfo("book.txt", ISBN, status, date, newwhom);
                        cout << "\n====================================\n"
                             << "Success: Book information updated successfully.\n"
                             << "====================================\n";
                    }
                    
                    cout << "\n====================================\n"
                         << "Do you want to delete any book? (yes/no): ";
                    while (true)
                    {
                        cin >> input;
                        transform(input.begin(), input.end(), input.begin(), ::tolower);
                        if (input == "yes" || input == "no")
                        {
                            break;
                        }
                        else
                        {
                            cout << "\n------------------------------------\n"
                                 << "Error: Invalid input. Please type yes or no.\n"
                                 << "------------------------------------\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    }
                    if (input == "yes")
                    {
                        string ISBN;
                        cout << "\n====================================\n"
                             << "Enter ISBN: ";
                        cin >> ISBN;
                        Librariane.Deletebook("book.txt", ISBN);
                        cout << "\n====================================\n"
                             << "Success: Book deleted successfully.\n"
                             << "====================================\n";
                    }
                }
                else
                {
                    cout << "\n------------------------------------\n"
                         << "Error: Incorrect password. Please try again.\n"
                         << "------------------------------------\n";
                }
            }
            else
            {
                cout << "\n------------------------------------\n"
                     << "Notice: Username not found. Please register.\n"
                     << "------------------------------------\n";
            }
        }
        else
        {
            cout << "\n====================================\n"
                 << "Proceeding to Librarian Registration...\n"
                 << "====================================\n";
            Librarian Librarian;
            Librarian.registerNewLibrarian();
        }
    }
    
    else {
        cout << "\n====================================\n"
             << "       Faculty Registration Check       \n"
             << "====================================\n"
             << "Are you already registered? (Type YES if registered or NO if not): ";
        string answer;
        while (true)
        {
            cin >> answer;
            transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
            if (answer == "YES" || answer == "NO")
            {
                break; // Valid input, exit the loop
            }
            else
            {
                cout << "\n------------------------------------\n"
                     << "Error: Invalid input. Kindly type either YES or NO.\n"
                     << "------------------------------------\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    
        if (answer == "YES")
        {
            cout << "\n====================================\n"
                 << "Enter your username: ";
            cin >> username;
    
            vector<faculty> faculties = faculty::readfacultyData();
    
            auto it = find_if(faculties.begin(), faculties.end(),
                              [username](const faculty &c)
                              { return c.getUsername() == username; });
    
            if (it != faculties.end())
            {
                cout << "\n====================================\n"
                     << "Enter your password: ";
                string password;
                cin >> password;
                books = readbookData();
    
                if (it->authenticate(password))
                {
                    cout << "\n====================================\n"
                         << "Login successful! Welcome, " << it->getUsername() << "!\n"
                         << "====================================\n";
    
                    // 1) Show all available books
                    cout << "\n====================================\n"
                         << "          Available Books           \n"
                         << "====================================\n";
                    for (auto &bk : books)
                    {
                        if (bk.checkAvailability())
                            bk.displayDetailsIfAvailable();
                    }
    
                    // 2) Show books currently rented by this user
                    cout << "\n====================================\n"
                         << "         Your Rented Books          \n"
                         << "====================================\n";
                    for (auto &bk : books)
                    {
                        bk.displayDetailsofRentedbook(username);
                    }
    
                    cout << "\n------------------------------------\n"
                         << "Enter the number of books you wish to return: ";
                    int bookreturno;
                    while (true)
                    {
                        cin >> bookreturno;
                        if (cin.fail())
                        {
                            cout << "\n------------------------------------\n"
                                 << "Error: Invalid input. Kindly enter a valid integer.\n"
                                 << "------------------------------------\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        else
                        {
                            break; // valid integer
                        }
                    }
    
                    // 3) Returning books
                    for (int a = 0; a < bookreturno; a++)
                    {
                        cout << "\n====================================\n"
                             << "Enter the ISBN of the book to return: ";
                        string ISBN;
                        cin >> ISBN;
                        int days;
                        string user = getBookRenter("book.txt", ISBN);
                        if (username != user)
                        {
                            cout << "\n------------------------------------\n"
                                 << "Notice: It appears that you have not rented this book.\n"
                                 << "------------------------------------\n";
                            continue;
                        }
                        cout << "\n====================================\n"
                             << "Enter the number of days after which you are returning the book: ";
                        while (true)
                        {
                            cin >> days;
                            if (cin.fail())
                            {
                                cout << "\n------------------------------------\n"
                                     << "Error: Invalid input. Kindly enter a valid integer.\n"
                                     << "------------------------------------\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            else
                            {
                                break; // valid integer
                            }
                        }
                        if (days > 30)
                        {
                            cout << "\n------------------------------------\n"
                                 << "Notice: You are late to return the book by " << (days - 30) 
                                 << " day(s).\n"
                                 << "------------------------------------\n";
                        }
                        // Update user & book info after returning
                        updatefacultyInfoafterreturning("faculty.txt", username, ISBN, 0);
                        updatebookInfo("book.txt", ISBN, "available", 0, "none");
                        cout << "\n====================================\n"
                             << "Success: The book has been successfully returned.\n"
                             << "====================================\n";
                    }
    
                    cout << "\n====================================\n"
                         << "Enter today's date in xx|xx|xxxx format (without slash): ";
                    int date;
                    while (true)
                    {
                        cin >> date;
                        if (cin.fail())
                        {
                            cout << "\n------------------------------------\n"
                                 << "Error: Invalid input. Please enter a valid integer.\n"
                                 << "------------------------------------\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        else
                        {
                            break;
                        }
                    }
                    int flag = 0;
                    books = readbookData();
                    for (auto &bk : books)
                    {
                        if (bk.hasuserRentedbook(username))
                        {
                            // Optionally, display days since the book was borrowed
                            cout << "\n------------------------------------\n"
                                 << "Days since borrowed for ISBN " << bk.getISBN() << ": "
                                 << daysBetweenDates(getBookborroweddate("book.txt", bk.getISBN()), date) << "\n"
                                 << "------------------------------------\n";
                            if (daysBetweenDates(getBookborroweddate("book.txt", bk.getISBN()), date) > 60)
                            {
                                flag = 1;
                            }
                        }
                    }
                    if (flag == 1)
                    {
                        cout << "\n====================================\n"
                             << "Alert: You have an overdue book. Please return it.\n"
                             << "====================================\n";
                    }
                    else
                    {
                        vector<faculty> faculties = faculty::readfacultyData();
                        int facultycheck = 0;
                        for (auto &st : faculties)
                        {
                            if (username == st.getUsername())
                            {
                                if (st.getnoofbooksrented() == 5)
                                {
                                    facultycheck = 0;
                                }
                                else
                                {
                                    facultycheck = 5 - st.getnoofbooksrented();
                                }
                                break; // Found the matching faculty
                            }
                        }
    
                        books = readbookData();
                        cout << "\n====================================\n"
                             << "You are eligible to rent " << facultycheck << " book(s).\n"
                             << "====================================\n"
                             << "Enter the number of books you wish to rent: ";
                        int bookrent;
                        while (true)
                        {
                            cin >> bookrent;
                            if (cin.fail())
                            {
                                cout << "\n------------------------------------\n"
                                     << "Error: Invalid input. Kindly enter a valid integer.\n"
                                     << "------------------------------------\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            else if (bookrent > facultycheck)
                            {
                                cout << "\n------------------------------------\n"
                                     << "Notice: You are not permitted to rent that many books. Please try again.\n"
                                     << "------------------------------------\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                bookrent = 0;
                                break;
                            }
                            else
                            {
                                break;
                            }
                        }
    
                        // 5) Rent the specified number of books
                        for (int a = 0; a < bookrent; a++)
                        {
                            cout << "\n====================================\n"
                                 << "Enter the ISBN of the book to rent: ";
                            string ISBN;
                            cin >> ISBN;
    
                            int availability = getBookAvailability("book.txt", ISBN);
                            if (availability != 1)
                            {
                                cout << "\n------------------------------------\n"
                                     << "Notice: This book is currently not available for rent.\n"
                                     << "------------------------------------\n";
                                continue;
                            }
    
                            cout << "\n====================================\n"
                                 << "Enter today's date in the format xx|xx|xxxx (without slashes): ";
                            int date;
                            while (true)
                            {
                                cin >> date;
                                if (cin.fail())
                                {
                                    cout << "\n------------------------------------\n"
                                         << "Error: Invalid input. Kindly enter a valid integer.\n"
                                         << "------------------------------------\n";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                                else
                                {
                                    break;
                                }
                            }
    
                            updatefacultyInfo("faculty.txt", username, ISBN);
                            updatebookInfo("book.txt", ISBN, "borrowed", date, username);
                            cout << "\n====================================\n"
                                 << "Success: The book has been successfully rented.\n"
                                 << "====================================\n";
                        }
                    }
                    cout << "\n====================================\n"
                    << "Press 1 to see your borrowed history details: ";
               int inp;
               while (true)
               {
                   cin >> inp;
                   if (cin.fail())
                   {
                       cout << "\n------------------------------------\n"
                            << "Error: Invalid input. Please enter a valid integer.\n"
                            << "------------------------------------\n";
                       cin.clear();
                       cin.ignore(numeric_limits<streamsize>::max(), '\n');
                   }
                   else
                   {
                       break;
                   }
               }
               if (inp == 1){vector<string> history;
               history=displayborrowedbookhistory("faculty.txt", username);
               cout << "\n========================================\n";
               cout << "         Borrowed Books' ISBNs\n";
               cout << "========================================\n";
           
               // Loop through the history vector and print each ISBN with an index
               for (size_t i = 0; i < history.size(); i++) {
                   // setw to align the numbering and ISBNs
                   cout << (i + 1) << ". " 
<< history[i] << "\n";
               }
           
               cout << "========================================\n";
           }
                }
                else
                {
                    cout << "\n------------------------------------\n"
                         << "Error: Incorrect password. Please try again.\n"
                         << "------------------------------------\n";
                }
            }
            else
            {
                cout << "\n------------------------------------\n"
                     << "Notice: Username not found. Please register.\n"
                     << "------------------------------------\n";
            }
        }
        else
        {
            cout << "\n====================================\n"
                 << "Proceeding to Faculty Registration...\n"
                 << "====================================\n";
            Librarian Librarian;
            Librarian.registerNewfaculty();
        }
    }
    
    }}