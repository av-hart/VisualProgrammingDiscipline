#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // Для використання remove_if
using namespace std;

struct Person {
    string name;
    Person* parent;
    vector<Person*> children;

    Person(string personName) {
        this->name = personName;
        this->parent = nullptr;
    }
};

class FamilyTree {
    private:
        vector<Person> people;

    public:
        void addPerson(string name) {
            people.push_back(Person(name));
        }

        Person* findPerson(string name) {
            for (Person& p : people) {
                if (p.name == name) return &p;
            }
            return nullptr;
        }

        void linkParent(string childName, string parentName) {
            Person* child = findPerson(childName);
            Person* parent = findPerson(parentName);
            if (child && parent) {
                child->parent = parent;
                parent->children.push_back(child);
            } else {
                cout << "One of the persons not found!" << endl;
            }
        }

        void displayTree(Person* person, int level = 0) {
            if (!person) return;
            for (int i = 0; i < level; i++) cout << "  ";
            cout << "- " << person->name << endl;
            for (Person* child : person->children) {
                displayTree(child, level + 1);
            }
        }

        void showTree(string rootName) {
            Person* root = findPerson(rootName);
            if (root) displayTree(root);
            else cout << "Person not found!" << endl;
        }

        void removePerson(string name) {
            Person* person = findPerson(name);
            if (!person) {
                cout << "Person not found!" << endl;
                return;
            }
            if (person->parent) {
                vector<Person*>& siblings = person->parent->children;
                siblings.erase(remove_if(siblings.begin(), siblings.end(), [person](Person* p) {
                    return p == person;
                }), siblings.end());
            }
            auto it = find_if(people.begin(), people.end(), [person](const Person& p) {
                return p.name == person->name;
            });
            if (it != people.end()) {
                people.erase(it);
            }
        }

        void clearTree() {
            people.clear();
        }
};

int main() {
    FamilyTree tree;
    tree.addPerson("Anna Hart");
    tree.addPerson("Liudmyla Hart (Tavadze)");
    tree.addPerson("Victor Holikov");
    tree.addPerson("Galina Makarova");
    tree.addPerson("Lavrentiy Hart (Tavadze)");
    tree.addPerson("Alina Taranushchenko");
    tree.addPerson("Sergiy Holikov");
    tree.addPerson("Iren Dehent");
    tree.addPerson("Volodymyr Makarov");
    tree.addPerson("Amalia Hart");
    tree.addPerson("Yermolay Tavadze");
    tree.addPerson("Anastasia Aksenova");
    tree.addPerson("Fridrih Dehent");
    tree.addPerson("Carolina");
    tree.addPerson("Vilhelm Hart");

    tree.linkParent("Liudmyla Hart (Tavadze)", "Anna Hart");
    tree.linkParent("Victor Holikov", "Anna Hart");
    tree.linkParent("Galina Makarova", "Liudmyla Hart (Tavadze)");
    tree.linkParent("Lavrentiy Hart (Tavadze)", "Liudmyla Hart (Tavadze)");
    tree.linkParent("Alina Taranushchenko", "Victor Holikov");
    tree.linkParent("Sergiy Holikov", "Victor Holikov");
    tree.linkParent("Iren Dehent", "Galina Makarova");
    tree.linkParent("Volodymyr Makarov", "Galina Makarova");
    tree.linkParent("Amalia Hart", "Lavrentiy Hart (Tavadze)");
    tree.linkParent("Yermolay Tavadze", "Lavrentiy Hart (Tavadze)");
    tree.linkParent("Anastasia Aksenova", "Iren Dehent");
    tree.linkParent("Fridrih Dehent", "Iren Dehent");
    tree.linkParent("Carolina", "Amalia Hart");
    tree.linkParent("Vilhelm Hart", "Amalia Hart");

    cout << "FamilyTree:" << endl;
    tree.showTree("Anna Hart");

    int choice;
    string name, childName, parentName;
    while (true) {
        cout << "\nChoose an option:\n";
        cout << "1. Add a person\n";
        cout << "2. Remove a person\n";
        cout << "3. Show the tree\n";
        cout << "4. Clear the tree\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the name of the person to add: ";
                cin.ignore();
                getline(cin, name);
                tree.addPerson(name);
                
                cout << "Do you want to add a child/parent for this person? (y/n): ";
                char addChild;
                cin >> addChild;
                if (addChild == 'y' || addChild == 'Y') {
                    cout << "Enter the name of the child: ";
                    cin.ignore();
                    getline(cin, childName);
                    cout << "Enter the name of the parent: ";
                    getline(cin, parentName);
                    tree.linkParent(parentName, childName);
                }
                break;
            case 2:
                cout << "Enter the name of the person to remove: ";
                cin.ignore();
                getline(cin, name);
                tree.removePerson(name);
                break;
            case 3:
                cout << "Enter the name to show the tree: ";
                cin.ignore();
                getline(cin, name);
                cout << "\nFamilyTree:" << endl;
                tree.showTree(name);
                break;
            case 4:
                tree.clearTree();
                cout << "The tree has been cleared!" << endl;
                break;
            case 5:
                cout << "Exiting program..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    //  Гарт А.
    return 0;
}