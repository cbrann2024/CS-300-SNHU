//============================================================================
// Name        : Module 7 Project 2
// Author      : Clifton Brann      August 8,2025
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Project 2, ABCU Course List
//============================================================================

#include <iostream>     // Standard libraries that contain functions needed for the program to work.
#include <algorithm>
#include <string>      
#include <climits>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================


// defines a structure to hold course information
struct Course {
    string courseId;        // unique identifier
    string courseTitle;
    string coursePrereq1;
    string coursePrereq2;
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor - creates an empty node with left and right pointers pointing at nullptr.
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a dummy course
    Node(Course aCourse) {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Defines a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;                      // Private Binary Search Tree class function members
    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void destroyNode(Node* node);


public:                     // Public Binary Search Tree class  memebers.
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Course course);
    Course Search(string courseId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
   
    //Sets the root node equal to nullptr

    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {         // Default destructor.
  

    destroyNode(root);      // Default method to destroy the data structure, that will start at the root node.

    root = nullptr;

}

void BinarySearchTree::destroyNode(Node* node) {        // Helper function for the destructor function.

    if (node == nullptr) {              //The helper function will iterate through the tree  and destroy each node in order.
        return;
    }

    destroyNode(node->right);
    destroyNode(node->left);

    delete node;

}


/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {

    // calls the inOrder fuction and passes the root as a parameter.

    this->inOrder(root);
}


/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {      //Function to insert data into the BinarySearchTree

    // if root equarl to null ptr
      // root is equal to new node course
    // else
      // add Node root and course

    Node* current = root;               // Sets the current first node to the root position.

    if (root == nullptr) {              //If loop that checks id the node is nullptr

        root = new Node(course);       //Sets first node to nullptr


    }
    else {

        this->addNode(root, course);       //Adds a new node and puts data into it.
    }
}


/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseId) {
   
    // Sets current node equal to the root node to start the search.

    // The function will keep looping downwards until bottom reached or matching courseId found
        // if a match is found, and it returns  the current course value.

        // if the courseId is smaller than current node then the search will traverse left
        // or else if it is larger larger the search will traverse to the right



    Node* current = root;            // Sets curent node as the root node.

    while (current != nullptr) {        // Sets a while loop to work though each row on the CSV documnet.

        if (current->course.courseId.compare(courseId) == 0) {       // if the current course matches the course being searched for return it.

            return current->course;             //Retuns the course data to the main function.

        }
        if (courseId.compare(current->course.courseId) < 0) {        //if the search term is less than the current course, go dowm the left fork.

            current = current->left;                //Retuns the course data to the main function.

        }
        else
        {
            current = current->right;           // If the search term is greater than the previous node, go down the right fork. 

        }
    }
    Course course;
    return course;                 //Returns the course information if found to the main function.

}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course Course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {     // This function searches the tree to find where the new data belongs
    // if node is larger then add to left                       // And creates a new node and pointers there, and inserts the data 
        // if no left node                                      //  into the new node
            // this node becomes left
        // else recurse down the left node
    // else
        // if no right node
            // this node becomes right
        //else
            // recurse down the left node

    if (node->course.courseId.compare(course.courseId) > 0) {           // Is the logic to ad a node to the tree, it starts at the root and works its way down the tree
        if (node->left == nullptr) {                        // until it finds a place it fits i.e. its value is more than the left node but less than the parent node.
            node->left = new Node(course);
        }
        // If left node exists, keep traversing down left subtree
        else {
            this->addNode(node->left, course);
        }
    }
    // If node < course, add to right subtree
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        // If right node exists, keep traversing down right subtree
        else {
            this->addNode(node->right, course);
        }
    }




}
void BinarySearchTree::inOrder(Node* node) {        // This function searches the tree and prints the enteries in order from least to greatest
    //if node is not equal to null ptr
    //InOrder not left
    //output courseId, courseTitle, coursePrereq1, coursePrereq2
    //InOder right


 
        if (node != nullptr) {      // Checks to see is there is data in the tree

            //InOrder node left
            inOrder(node->left);

            //output courseID, courseTitle, coursePrereq1, coursePrereq2

            cout << node->course.courseId << ": " << node->course.courseTitle << " | " << node->course.coursePrereq1 << " | "
                << node->course.coursePrereq2 << endl;

            //InOder right
            inOrder(node->right);
        }
    
}




//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course) {     // Prints the course data on the screem

    if (course.courseId.empty()) {      // Checks to see if there is data in the data structure

        cout << "" << endl;
        cout << "Listing not found in table." << endl;      // Error message displayed if the data structure is empty
        cout << "" << endl;

    }
    else{                                   // Prints out the course data, along with prerequisites if there are any.
        cout << "Course ID: " << course.courseId << "  |  Course Title:  " << course.courseTitle << " | ";
    if (!course.coursePrereq1.empty()) {
        cout << " Prerequisite: " << course.coursePrereq1 << "  |  ";
    }
    if (!course.coursePrereq2.empty()) {
        cout << " Prerequisite: " << course.coursePrereq2 << "   |" << endl;
    }
}
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadCourses(string csvPath, BinarySearchTree* bst) {   // Loads a csv file data into the program

    cout << "" << endl;
    cout << "Loading CSV file " << csvPath << endl;     // Informs the user what data file is being loaded.
    cout << "" << endl;


    ifstream file(csvPath);            // C++ library utility that opens files and allows the program access to that data.

    if (!file.is_open()) {          // Checks to see if the file is open, and displays an error message if there areproblems opening the file.

        cout << endl;
        cerr << "Error opening file: " << csvPath << endl;
        cout << endl;

        return;

    }


    string line;

    unsigned rowCount = 0;

    while (getline(file, line)) {       // A while loop that enters the individual data fields from the file into
                                        // the variables in the data structure.

        string field;

        stringstream ss(line);

        Course course;

        getline(ss, field, ',');        // gets the data from the first field and assigns it into the courseId variable
        course.courseId = field;
        getline(ss, field, ',');        // gets the data from the second field and assigns it into the courseTitle variable.
        course.courseTitle = field;
        getline(ss, field, ',');
        course.coursePrereq1 = field;   // gets the data from the third field and assigns it into the coursePrereq1 variable.
        getline(ss, field, ',');
        course.coursePrereq2 = field;   // gets the data from the fourth field and assigns it into the coursePrereq2 variable.

        bst->Insert(course);            // akes the 4 fields and insets them into the tree as a group

        ++rowCount;                     // Advances the function to look atthe next line by index number
    }

    file.close();                   // Closes the open file, which should free up memory for other tasks.

    cout << "" << endl;             // Informs the user how many line entries were found in the file and tranferred into the data structure. 
    cout << "  " << rowCount << " lines of data have been read from the file and written into the data table." << endl;
    cout << "" << endl;

    return;

}
    


/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, searchKey;
    switch (argc) {             // Sets the default criteria for the switch case, which will be used later to make the menu work. 
    case 2:
        csvPath = argv[1];
        searchKey = "CSCI";
        break;
    case 3:
        csvPath = argv[1];
        searchKey = argv[2];
        break;
    default:
        csvPath = "CS 300 ABCU_Advising_Program_Input.csv";     // The file the data is loaded from. It must reside in the same directory as the program.
        searchKey = "CSCI";                                     // or the proper path must be entered, complete with \\ as needed to seperate the folder etc.
    }

    // Define a timer variable
    clock_t ticks;

    // Defines a binary search tree to hold all course data
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;

    int choice = 0;     // Sets choice default to 0, just in case.


    while (choice != 9) {       // A while loop that drives the mune functions - as long as 9 isn't entered it will continue to loop

        cout << "" << endl;
        cout << "           ---***   Menu   ***--- " << endl;       // Menu text for display.
        cout << "" << endl;
        cout << "  1. Load Data from file." << endl;
        cout << "  2. Print out all Computer Science Courses." << endl;
        cout << "  3. Find a Specific Course by Course Number." << endl;
        cout << "  9. Exit" << endl;
        cout << "" << endl;
       
                // A do while loop that vereifies that the user input is actually an integer .. non integer entries make crazy stuff happen.
        do {
            cout << "Enter your choice from the menu: ";
            if (!(cin >> choice)) { // Check if input failed
                cout << "Invalid input. Please enter a valid integer.\n";
                cin.clear(); // Clears the error flag 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discards invalid input
            }
            else {
                // Input was valid, now discard the remaining newline - handles the error if no input is given and the return button is pressed.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break; // Exit the loop if input is valid
            }
        } while (true);     // end of the DO WHile loop that contains the parameter for the loop to iterate. 
                            // When the user input is an integer nothing happens and hte value is passsed along to the 
                            // switch case. Id the input is no an integer, and error message is displayed. 
       


        switch (choice) {       // This is the switch case that makes the menu options work.

        case 1:

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the course data.

            loadCourses(csvPath, bst);      // Calls the loadCourses function to load the data from the specified file

                    // I ledft the clock and time printouts in each ase, to allow the user to see progres of some sort happened.

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            cout << "" << endl;

            break;

        case 2:         // Displays all the Computer Science cirriculum courses from the data in the file

            
                cout << endl;       // Prints a header for clarity
                cout << "Course ID  ||   Course Description       ||  Prerequisite          ||" << endl;
                cout << endl;


                bst->InOrder();     // Calls the InOrder function and displays the courses in order from the tree.

                cout << endl;
                cout << "       -- Complete Course List Displayed. -- " << endl;    // Lets the user know all the data has been displayed.
                cout << endl;
            
            
            break;

        case 3:
            ticks = clock();

            string searchTerm = "";

            cout << "" << endl;         // Requests the user to enter a course number to search the tree for a specific course.
            cout << "Please enter the full course number to be found: " << endl;
            cin >> searchTerm;
            cout << "" << endl;

            if (searchTerm.empty()) {       // Checks to see if the user entered anything in the search term, ans handles an empty search error.

                cout << "" << endl;
                cout << " You have to give me something to work with here...." << endl;
                cout << "" << endl;
            }

            cout << "" << endl;         // Confirms to \the user what course is being searched for.
            cout << "Searching for Course ID: " << searchTerm << " in data table." << endl;
            cout << "" << endl;
            
            
            course = bst->Search(searchTerm);   //Cal;ls the search function to find the course that mathches the search term.

            

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!course.courseId.empty()) {
                displayCourse(course);          // Displays the course if it has been found
            }
            else {

                cout << endl;   // Displays an error message if the file is not found, and allws the user to check their input.
                cout << "Course Id " << searchTerm << " not found in table." << endl;
                cout << endl;
            }

            cout << "" << endl;
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            cout << "" << endl;

            break;

        }
    }
            
    cout << "Good bye." << endl;        // Says good bye and exits the program. 

    return 0;
}
