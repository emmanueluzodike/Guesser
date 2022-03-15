/*
Name: Emmanuel Uzodike
Date: 3/30/2021

*/

#include <iostream>
#include <cstdlib>
//#include "HW5-CS1337-Emmanuel Uzodike-BST.h"
#include <string>
#include <fstream>
//ofstream outFile;

using namespace std;

struct animalNode { // structure of each node in the binary tree
        //string question;
    string guess_question;
    animalNode* yes;
    animalNode* no;
};

animalNode* root; // uncomment
animalNode* current; //uncomment

animalNode* CreateLeaf(string guess) { //this function creates a new node
    animalNode* n = new animalNode;
    //  n->question = "";
    n->guess_question = guess;
    n->yes = nullptr;
    n->no = nullptr;

    return n;
}

animalNode* CreateLeaf(string guess);

void printTheTree(ostream& outFile, animalNode* current) {
    if ((current->yes) == nullptr) {
        outFile << "G" << endl;
        outFile << current->guess_question << endl;
    }
    else {
        outFile << "Q" << endl;
        outFile << current->guess_question << endl;
        printTheTree(outFile, current->yes);
        printTheTree(outFile, current->no);
    }

}



void saveTheAnimalTree(animalNode* root) {
    ofstream outputFile("DB.txt");
    printTheTree(outputFile, root);
    outputFile << flush;
}

animalNode* loadTheAnimalTree(fstream&outFile) {
   // ifstream outFile("AnimalGameDB.txt");
    
    char QG;
    if (outFile.eof() == false) {
        outFile >> QG;
        outFile.ignore();
    }
    else {
        return nullptr;
    }
   
    string Question;
   // outFile >> QG;
    //cout << QG;
    if (QG == 'G') {
        getline(outFile, Question);
        animalNode* Node= new animalNode;
        Node->guess_question = Question;
        Node->yes = nullptr;
        Node->no = nullptr;
        return Node;
    }
    else {
        getline(outFile, Question);
        animalNode* Node = new animalNode;
        Node->guess_question = Question;
        if (outFile.eof()) {
            return Node;
        }
        Node->yes = loadTheAnimalTree(outFile);
        Node->no = loadTheAnimalTree(outFile);
        return Node;   

    }

}



int main() {
    
    char choice; //Gets user input (yes/no) for questions and guesses
    string guess_question, UsersAnimal; // guess_question-> String that cointains either a question or guess.  UsersAnimal-> The animal the user is thinking of
   // animalNode* root;
   // animalNode* current;

    current = new animalNode; // current node
    root = new animalNode; // root node
    char playAgain; // gets user input if they want to play again
     animalNode* current = root; // the current node points to the root node // changed animalNode*current
    root->guess_question = "Lizard"; // initializes the guess_question/root node to lizard
    root->yes = nullptr; // root node points to nothing
    root->no = nullptr; // root node points to nothing
    playAgain = 'y'; // initializes play again to yes

    fstream outFile;
    outFile.open("DB.txt", ios::out | ios::in);

    if (outFile.fail()) {
        cout << "File couldnt be open";
    }
    else
    {
        cout << "file opened successfully";
    }
    
    
    outFile.seekg(0, ios::end);
    //cout << outFile.tellg();
   
    if (outFile.tellg() != 0)
    {
        outFile.seekg(0, ios::beg);
        current = loadTheAnimalTree(outFile);
        root = current;
        cout << "\nfile is not empty\n";
    }
    else 
    {
        cout << "file is empty";
        current = root;
    }
;
    


    while (playAgain == 'y' || playAgain == 'Y') { // executes if user wants to play again


            cout << "Think of an animal. Press any key to continue: ";
            system("pause");

            while (current->yes != nullptr && current->no != nullptr) //executes if the current node points to something or rather if it is a question node
            {
                // cout << "Think of an animal. Press any key to continue: ";
                 //system("pause");

                cout << current->guess_question << endl; // prints out the string(question) in the current node
                cin >> choice;

                if (choice == 'y') { // if answer is yes, tree traverses to what the yes pointer of current node is pointing to.
                    current = current->yes;

                }
                else // if answer is no, tree traverses to what the no pointer of current node is pointing to.
                {
                    current = current->no;
                    //cout << current->guess_question << endl;
                }
            }

            cout << "Where you thinking of " << current->guess_question << "? (Enter y/n)" << endl; // executes if the current node points to nothing. (prints a guess)
            cin >> choice;
            while (choice != 'y' && choice != 'n' && choice != 'Y' && choice != 'N') // input validation. executes if user does not enter y or n
            {
                cout << "Invalid input. Enter y for yes and n for no" << endl;
                cin >> choice;
            }

            if (choice == 'y') { // executes if user enters yes to the guess
                cout << "Animal name is guessed " << endl;
                // EXIT_SUCCESS;
            }
            else // executes if user enters no to the guess
            {
                /*if user enters no the program ask the user what animal they were thinking of?, what question can be used to differeiciate the animal they
                where thinking of from the animal the program guessed and if the answer to the question is yes or no. A copy of the current node(which is currently the guess made by program) is made as well
                as a new node that will contain the animal the user was guessing. Then the current node is over written with the diffrientiation question. then depending on if the answer to the question is yes or no
                 the yes and no pointer of the newly re-written question node points to a guess node*/

                cout << "What animal where you thinking of? ";
                cin.clear();
                cin.ignore(10000, '\n');
                getline(cin, guess_question);
                animalNode* UsersAnimal = new animalNode; // creates a new node and stores the animal the user was thinking of in it
                UsersAnimal->guess_question = guess_question; //puts what animal user is thinking of in this new node
                cout << "What question can be used to diffrenctiate the two animals? ";
                // cin.clear();
                 //cin.ignore(10000, '\n');

                getline(cin, guess_question);
                //  cout << guess_question << endl;

                animalNode* copy = new animalNode; //cretaes a new node called copy
                copy->guess_question = current->guess_question; // this new node copies the contents of current node
                current->guess_question = guess_question; //Current node is re-written into the a question node, the question specified by user
               //current->yes = UsersAnimal;
               //current->no = copy;
                cout << "Is the answer to this question yes or no? (Enter y/n)";
                cin >> choice;
                while (choice != 'y' && choice != 'n' && choice != 'Y' && choice != 'N') //input validation. send error message if use doesnt enter y/n
                {
                    cout << "Invalid input. Enter y for yes and n for no" << endl;
                    cin >> choice;
                }

                if (choice == 'y') // if user enters yes, then the current node yes pointer points to the animal the user was guessing and no pointer points to the guess program made
                {

                    current->yes = UsersAnimal;
                    current->no = copy;

                }
                else { // if user enters no, then the current node no pointer points to the animal the user was guessing and yes pointer points to the guess program made

                    current->no = UsersAnimal;
                    current->yes = copy;

                }

                UsersAnimal->yes = nullptr; //guess node/leaf node points to nothing
                UsersAnimal->no = nullptr; //guess node/leaf node points to nothing
                copy->yes = nullptr; //guess node/leaf node points to nothing
                copy->no = nullptr; //guess node/leaf node points to nothing


                //current = root; // current node now points to the root

            }
            current = root; // current node now points to the root
            cout << "Play again? (Enter y to continue and any key to exit)"; // ask the user if they want to play again
            //cin.clear();
           // cin.ignore(10000, '\n');
            cin >> playAgain;

            cout << "\n\n";

        }
    
    cout << endl;
   // fstream outFile;

    //outFile.open("DB.txt" , ios::out | ios:: in | ios::app);
   // current = root;
    outFile.close();
    outFile.open("DB.txt", ios::out);
    printTheTree(outFile,  root);
    printTheTree(cout, root);
   // root = loadTheAnimalTree(outFile);
    //printTheTree(cout, root);
}