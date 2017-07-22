#include <iostream>
#include "container.h"
#include "array.h"
#include "dlist.h"
#include "exception_handler.h"

#define DLIST 1
#define ARRAY 2

Container_t<int>* container;

using namespace std;

void Prompt(int _choice);

int main()
{
  int choice;
  while(choice != 3)
  {
    cout << "Welcome to our container tester! What would you like to do?" << endl;
    cout << "1. Let's start with a dynamic linked list!" << endl;
    cout << "2. Let's start with an array!" << endl;
    cout << "3. Ya know what? Let's get out of here." << endl;
    cin >> choice;
    switch(choice)
    {
      case 1:
        Prompt(DLIST);
        break;
      case 2:
        Prompt(DLIST);
        break;
      case 3:
        cout << "Come again!" << endl;
        break;
      default:
        cout << "I didn't catch that. Could you try again?" << endl;
        break;
    }
  }
  return 0;
}

/* ---------------------------------------------------------- */

void RunList();
void TESTAppend();
void TESTPrepend();
void TESTEmpty();
void TESTCount();
void TESTContains();
void TESTFind();
void TESTIndex();
void TESTInsert();
void TESTRemove();
void TESTRemoveAll();
void TESTRemoveAndDelete();
void TESTRemoveAndDeleteAll();

void Prompt(int _choice)
{
  if (_choice == DLIST)
  {
   container = new Dlist_t<int>();
  }
  container = new Array_t<int>();

  int userChoice;
  try
  {
    while(userChoice != 12)
    {
      cout << "1.  Insert a new element" << endl
           << "2.  Append to your container" << endl
           << "3.  Prepend to your container" << endl
           << "4.  Check if your container is empty" << endl
           << "5.  Count the number of elements in your container" << endl
           << "6.  Check if your container contains a value" << endl
           << "7.  Get the index of an element by variable" << endl
           << "8.  Remove an element" << endl
           << "9.  Remove all existing elements" << endl
           << "10.  Remove and delete an element" << endl
           << "11.  Remove and delete all existing elements" << endl
           << "12. Hit up the previous menu" << endl << endl;
      cin >> userChoice;
      system ("clear");
      switch(userChoice)
      {
          case 1:
            TESTInsert();
            break;
          case 2:
            TESTAppend();
            break;
          case 3:
            TESTPrepend();
            break;
          case 4:
            TESTEmpty();
            break;
          case 5:
            TESTCount();
            break;
          case 6:
            TESTContains();
            break;
          case 7:
            TESTIndex();
            break;
          case 8:
            TESTRemove();
            break;
          case 9:
            TESTRemoveAll();
            break;
          case 10:
            TESTRemoveAndDelete();
            break;
          case 11:
            TESTRemoveAndDeleteAll();
            break;
          case 12:
            break;
          default:
            cout << "Sorry, I didn't catch that. Try again!" << endl;
            break;
      }

    }
  }catch(TException_t<int>& _t)
    {
      cout << "Your guess: "  << _t.GetObject()      << endl;
      cout << "File: "        << _t.GetFile()        << endl;
      cout << "Line: "        << _t.GetLine()        << endl;
      cout << "Description: " << _t.GetDescription() << endl;
      return;
    }
}

/* ---------------------------------------------------------- */

void TESTAppend()
{
  int* userInsert = new int();
  size_t index;
  cout << "Enter integer" << endl;
  cin >> *userInsert;
  cout << "Enter index" << endl;
  cin >> index;
  (1 == container->append(userInsert, index)) ? cout << "Success" << endl : cout << "Fail" << endl;
}

/* ---------------------------------------------------------- */

void TESTPrepend()
{
  int* userInsert = new int();
  size_t index;
  cout << "Enter integer" << endl;
  cin >> *userInsert;
  cout << "Enter index" << endl;
  cin >> index;
  (container->prepend(userInsert, index)) ? cout << "Success" << endl : cout << "Fail" << endl;
}
/* ---------------------------------------------------------- */

void TESTEmpty()
{
  (!container->isEmpty()) ? cout << "It's not empty!" << endl : cout << "It's empty!" << endl;
}

/* ---------------------------------------------------------- */

void TESTCount()
{
  cout << "You have: " << container->count() << " elements!"<< endl;
}

/* ---------------------------------------------------------- */

void TESTContains()
{
  cout << "Enter integer" << endl;
  int userInsert;
  cin >> userInsert;
  (container->contains(userInsert)) ? cout << "Found" << endl : cout << "Not found" << endl;
}

/* ---------------------------------------------------------- */

void TESTFind()
{
  cout << "Enter integer" << endl;
  int userInsert;
  cin >> userInsert;
  (container->find(userInsert)) ? cout << "Found" << endl : cout << "Not found" << endl;
}

/* ---------------------------------------------------------- */

void TESTIndex()
{
  cout << "Enter integer" << endl;
  int userInsert;
  cin >> userInsert;
  (container->find(userInsert) && container->index(userInsert) != -1) ? cout << "Index: " << container->index(userInsert) << endl : cout << "Not found" << endl;
}

/* ---------------------------------------------------------- */

void TESTInsert()
{
  int* userInsert = new int();
  cout << "Enter integer" << endl;
  cin >> *userInsert;
  container->insert(userInsert);
  cout << "Alright, it's in there!" << endl;
}

/* ---------------------------------------------------------- */

void TESTRemove()
{
  int userInsert;
  cout << "Enter integer" << endl;
  cin >> userInsert;
  (container->remove(&userInsert, userInsert)) ? cout << "Success" << endl : cout << "Failure" << endl;
}

/* ---------------------------------------------------------- */

void TESTRemoveAll()
{
  container->removeAll();
  (container->isEmpty()) ? cout << "All your elements have been removed." << endl : cout << "Something went wrong." << endl;
}

/* ---------------------------------------------------------- */

void TESTRemoveAndDelete()
{
  int userInsert;
  cout << "Enter integer" << endl;
  cin >> userInsert;
  (container->contains(userInsert)) ? cout << "We didn't manage to delete your elements." << endl : cout << "All gone!" << endl;
}

/* ---------------------------------------------------------- */

void TESTRemoveAndDeleteAll()
{
  container->removeAndDeleteAll();
  cout << "Done" << endl;
}

/* ---------------------------------------------------------- */
