#include<iostream>
#include<string>
#include<map>
#include<set>
#include<sstream>
#include<iomanip>
#include<algorithm>

using namespace std;
class Date {
public:
    Date(int new_year, int new_month, int new_day) {
        if (new_month < 1 || new_month > 12) {
            throw runtime_error("Month value is invalid: " + to_string(new_month));
           
        }
        if (new_day < 1 || new_day >31) {
            throw runtime_error("Day value is invalid : " + to_string(new_day));
         }
        
        year = new_year;
        month = new_month;
        day = new_day;
    }
    int GetYear() const {
        return year;
    }
    int GetMonth() const {
        return month;
    }
    int GetDay() const {
        return day;
    }
private:
    int year;
    int month;
    int day;
};
Date ParsDate(const string& data) {
    stringstream stream(data);
    int year, month, day;
    stream >> year;
    bool flage = true;
    flage = flage && (stream.peek() == '-');
    stream.ignore(1);
    flage = flage && (stream >> month);
    flage = flage && (stream.peek() == '-');
    stream.ignore(1);
    flage = flage && (stream >> day);
    if (flage == false) {
        throw logic_error("Wrong date format: " + data);
    }
    Date new_date = { year, month, day };
    return new_date;
}

bool operator<(const Date& lhs, const Date& rhs)
{
    if (lhs.GetYear() != rhs.GetYear()) {
        return lhs.GetYear() < rhs.GetYear();
    }
    else if (lhs.GetMonth()!=rhs.GetMonth()) {
          return lhs.GetMonth() < rhs.GetMonth();
        }
    else {
        return lhs.GetDay() < rhs.GetDay();
    }
}

ostream& operator<< (ostream& stream, const Date& date) {
    stream << setfill('0') << setw(4) << to_string(date.GetYear());
    stream << "-";
    stream << setfill('0') << setw(2) << to_string(date.GetMonth());
    stream << "-";
    stream << setfill('0') << setw(2) << to_string(date.GetDay());

    return stream;
}

class Database {
public:
    void AddEvent(const Date& date, const string& event) {
        events[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event) {
        if  (events.count(date) > 0 && events[date].count(event) > 0)
        {
            events[date].erase(event);
            return true;
        }
        return false;
    }
       
    
    int  DeleteDate(const Date& date) {
        int count = 0;
        if (events.count(date) > 0)
        {
            count = events.at(date).size();
            events.erase(date);
        }
        
        return count;
    }

    set<string>  Find(const Date& date) const {
        set<string> all_events;
        if (events.count(date) > 0)
            all_events = events.at(date);
        
       return all_events;
  }

    void Print() const {
        for (const auto& item : events) {
            for (const auto& doing : item.second) {
                cout << item.first << " " << doing << endl;
            }
        }

    }
private:
    map<Date, set<string>> events;
};

int main() {
    try {
        Database db;
        string command;
        while (getline(cin, command)) {
            if (command == "") {
                continue;
            }
            stringstream stream(command);
            string task;
            stream >> task;
            map < string, char > index = {{"Add", 'A'}, { "Del",'D' }, { "Find", 'F' }, { "Print",'P' }};
            char symbol = index[task];
            switch (symbol) {
            case 'A': {
                string date, event;
                cin >> date >> event;
                const Date new_date = ParsDate(date);
                db.AddEvent(new_date, event);
                break;
            }
            case 'D': {
                string date, event;
                stream >> date;
                if (!stream.eof()) {
                    stream >> event;
                }
                const Date new_date = ParsDate(date);
                if (event.empty()) {
                    int k = db.DeleteDate(new_date);
                    cout << "Deleted " << k << " events";
                }
                else {
                    bool flag = db.DeleteEvent(new_date, event);
                    if (flag == true) {
                        cout << "Deleted successfully" << endl;
                    }
                    else {
                        cout << "Event not found" << endl;
                    }
                }
                break;
            }
            case 'F': {
                string new_date;
                cin >> new_date;
                const Date date = ParsDate(new_date);
                set<string> events = db.Find(date);
                for (const string& doing : events) {
                    cout << doing << endl;
                }

                break;
            }
            case 'P': {
                db.Print();
                break;
            }
            }
        }
        

        
    }
    catch (exception& e) {
        cout << e.what() << endl;
        return 0;
    }

    return 0;
}