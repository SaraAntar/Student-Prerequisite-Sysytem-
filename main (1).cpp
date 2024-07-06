#include <iostream>
#include <fstream>
#include <sstream>
#define GLOBALSPACE 5 // the space between the nodes are 5
#define MAX_SIZE 10   // maximum size of arrays used in main function

using namespace std;
ifstream file;

class BT {

public:
    struct Node {
        string data;
        // pointers for tree nodes
        Node *left, *right;
        // pointer for linked list nodes
        Node *next;

        // constructor for initializing pointers
        Node() {
            left = right = next = NULL;
        }
    };

    // defining root of tree
    Node *root = NULL;

    // Function to create a new node
    Node *CreateNode(string data) {

        Node *newNode = new Node();
        newNode->data = data;
        newNode->left = newNode->right = NULL;

        return newNode;
    }

    // Function to extract numbers from file and building the tree
    void Extract_from_file() {

        // initializing variables and pointers to build the tree
        string course_code,parent_code, line;
        Node *current_parent=NULL, *crt_node=NULL, *tail=NULL;

        // opening file for courses extraction
        file.open("C:\\Users\\lenovo\\CLionProjects\\BT project\\Courses tree.txt");

        // looping the file till its end to extract courses codes
        while (!file.eof()){
            // function that reads the file line by line
            getline(file, line);

            // extracting first 3 characters in the line and insert them to course_code variable
            course_code = line.substr(0, 3);
            // extracting first 3 characters after ',' and insert them to parent_code variable
            parent_code = line.substr(line.find(',') + 1, 3);

            // if the parent_code = "Non", this means that the first course code will be the root
            if (parent_code == "Non") {
                root = CreateNode(course_code);
                // creating pointers that point to the root
                current_parent = crt_node = tail =root;
                continue;
            }

            // In case parent code is no longer the same as the data stored in current parent and it hasn't reached
            // the end of the linked list, we will point to the new parent
            else if (parent_code != current_parent-> data && current_parent->next != NULL){
                    // pointing to the new parent to insert its children
                    current_parent = current_parent-> next;
            }

            // condition in case an error occurs when changing the arrangement of courses in file,
            // so that program doesn't break down
            if (current_parent->data != parent_code)
            {
                cout<<"Error reading data, parent node not found"<<endl;
                exit(-1);
            }

            // creating child node
            crt_node  = CreateNode(course_code);

            // inserting child node at the left of the parent in case it's empty
            if (current_parent->left == NULL) {
                current_parent->left = crt_node;
            }

            // condition occurs when left is full and right is empty
            else {
                current_parent->right = crt_node;
            }

            // using linked list to help in building tree
            if (tail->data != crt_node ->data){
                tail->next = crt_node;
                tail = crt_node;
            }
        }

        // closing the file after iterating in it
        file.close();
    }

    // function that helps get prerequisite of the course and returns it to be compared with other courses
    Node* Get_Prerequisite(Node* node, int course){

        // stopping condition, when the pointer reaches the end of the tree it returns null
        if (node==NULL){
            return NULL;
        }

        //progressing condition
        // if the left child is the course we are searching for, then return its prerequisite
        if (node->left != NULL && node->left->data == to_string(course))
            return node;
        // if the right child is the course we are searching for, then return its prerequisite
        if (node-> right != NULL && node->right-> data == to_string(course))
            return node;

        // recursion functions for checking the left and right subtrees to find the prerequisite course if any
        Node* LEFT = Get_Prerequisite(node->left, course);
        Node* RIGHT = Get_Prerequisite(node-> right, course);

        // if the left side of the tree doesn't reach the end, then complete iterating through the left side
        // otherwise, iterate through the right side of the tree
        return  LEFT !=NULL ? LEFT: RIGHT;
    }

    //BONUS PART for printing the graphical representation of the tree
    void print2D(Node * root, int space) {
	// Line 1
    if (root == NULL) // Base case
        return;
    // Line 2 // related to the space
    space += GLOBALSPACE; // Increase distance between levels

    // Line 3 // recursion (it will recall the function print2D and Process right child first)
    print2D(root -> right, space);
    // Line 4 // related to the space
    cout << endl;

    // Line 5 // related to the space
    for (int i = GLOBALSPACE; i < space; i++) // Print current node after space count
        cout << " "; // 5.1
    // Line 6
    cout << root -> data << "\n";
    // Line 7 // recursion (it will recall the function print2D and Process left child)
    print2D(root -> left, space);
}
};

int main()
{
    // creating object variable with the type of BT class to be used in accessing class variables and functions
    BT object;
    // calling Extract_from_file function in order to build the tree of the courses
    object.Extract_from_file();

    // Asking the user for the courses he took and assigning them in Taken_Courses array with size taken_crs
    int taken_crs;
    cout<<"Please enter the number of courses you took: ";
    cin>> taken_crs;
    int Taken_Courses[taken_crs], course;

    cout<<"Please enter the courses you took: ";
    for (int i=0; i< taken_crs; i++){
        cin>>course;
        Taken_Courses[i]= course;
    }

    // Asking the users for the courses he wants to take and assigning them in Needed_Courses array with size MAX_SIZE
    int needed_crs;
    cout<<"\nPlease enter the number of courses you want to take: ";
    cin>> needed_crs;
    int Needed_Courses[MAX_SIZE];

    cout<<"Please enter the courses you want to take: ";
    for (int i=0; i< needed_crs; i++){
        cin>>course;
        Needed_Courses[i]= course;
    }

    cout<<"\nProcessing"<<endl;

    //creating arrays for the allowed and not-allowed courses for him to take where they have the size MAX_SIZE
    int Allowed_courses[MAX_SIZE], NotAllowed_courses[MAX_SIZE];

    // identifying flag variable to check whether there are any not-allowed courses for the user to take or not
    int flag=0, flag3=0, counter=0, counter1=0;

    // defining parent variable of node type to receive prerequisite course from Get_Prerequisite function
    BT::Node* parent;

    for (int i=0; i< needed_crs; i++){

        // calling get_parent function to get the prerequisite of the needed courses and storing it in the parent variable
        parent =object.Get_Prerequisite(object.root, Needed_Courses[i]);
        // identifying flag2 variable to determine whether the needed course is allowed to be taken or not
        int flag2=0;

        //loop for comparing the prerequisites with the taken courses to check whether the user can take the courses he
        // wants or not and to store allowed courses in an array
        for (int j=0; j<taken_crs; j++){
            if (parent != NULL && parent->data== to_string(Taken_Courses[j])){
                Allowed_courses[counter1++]= Needed_Courses[i];
                flag3=1;
                flag2=1;
                break;
            }
        }

        // condition for storing not-allowed courses in another array
        if (flag2==0){
            NotAllowed_courses[counter++]= Needed_Courses[i];
            flag=1;
        }
    }

    // condition to print the allowed courses for the user to take if any
    if(flag3==1) {
        cout << "The following courses are OK to take: " << endl;
        for (int i = 0; i < counter1; i++) {
            cout << Allowed_courses[i] << endl;
        }
    }

    // condition to print the not-allowed courses for the user to take if any
    if (flag==1){
    cout<<"The following courses CANNOT be taken: "<<endl;
    for(int i=0; i<counter; i++) {
        cout << NotAllowed_courses[i] << endl;
    }
    }

    cout<<"\n\n";
    // calling the function for printing the graphical representation of the courses tree
    object.print2D(object.root, 5);

    return 0;
}