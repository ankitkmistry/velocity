#include <iostream>
#include <cassert>
#include "ee/vm.hpp"

struct Contact {
    int phoneNumber;
    string address;
    string email;
};

struct Person {
    string name;
    int age;
    Contact *contact;
};

class PersonTable {
private:
    vector<Person> persons;
    // ... other members ...
public:
    PersonTable() = default;

    void addPerson(Person person) { persons.push_back(person); }

    void setContact(int index, Contact *contact) { persons[index].contact = contact; }

    Person getPerson(int index) { return persons[index]; }
    // ... other important members ....
};

int main() {
    PersonTable table;
    auto *contact1 = new Contact{1234567890, "NY", "me@email.com"};
    table.addPerson({"Me", 18, contact1});
    auto *contact2 = new Contact{278456123, "London", "me123@email.com"};
    table.setContact(0, contact2);
    assert(table.getPerson(0).contact == contact2);

    std::ios_base::sync_with_stdio(false);
    try {
        VM vm;
#if defined(OS_LINUX)
        vm.start("/mnt/h/Programming (Ankit)/Projects/spade/1.0/velocity/fact.xp", {});
#elif defined(OS_WINDOWS)
        vm.start(R"(H:\Programming (Ankit)\Projects\spade\1.0\velocity\fact.xp)", {});
#endif
    } catch (const FatalError &error) {
        cout << "VM Error: " << error.what();
    }
}
