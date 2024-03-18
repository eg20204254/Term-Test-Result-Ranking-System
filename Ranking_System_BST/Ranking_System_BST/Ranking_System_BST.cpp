
#include "Header.h"
#include <iostream>
using namespace std;


int calcTotal(int a ,int b, int c)
{
    int tot = a + b + c;
    return tot;


}

int main()
{
    nodeBST bst, * root = NULL;

    double a;
    int b, c, d;
    string k, p;
    root = bst.insertFunc(root, 60, "St_2201", 10, 20, 30);
    root = bst.insertFunc(root, 202, "St_2203", 90, 34, 78);
    root = bst.insertFunc(root, 164, "St_4502", 98, 64, 2);
    root = bst.insertFunc(root, 111, "St_6667", 21, 34, 56);
    root = bst.insertFunc(root, 137, "St_1245", 99, 5, 33);
    root = bst.insertFunc(root, 131, "St_8874", 76, 33, 22);
    bst.showRankings(root, bst);
    cout << "Enter the Student_ID of the student: ";
    cin >> k;
    cout << "Enter the marks for Mathematics : ";
    cin >> b;
    cout << "Enter the marks for Chemistry : ";
    cin >> c;
    cout << "Enter the marks for English : ";
    cin >> d;
   

    root = bst.insertFunc(root, calcTotal(b,c,d), k, b, c, d);
    bst.showRankings(root, bst);

   

    cout << endl;


    cout << "Enter the Student ID of the student you want to delete: ";
    cin >> p;
    cout << endl;
    root = bst.deleteNode(&root, p);
    bst.showRankings(root, bst);



    string up_name;
    int mth, che, eg;
    cout << "Enter the Student ID of the student you want to update: ";
    cin >> up_name;
    cout << "Enter the marks for Mathematics : ";
    cin >> mth;
    cout << "Enter the marks for Chemistry : ";
    cin >> che;
    cout << "Enter the marks for English : ";
    cin >> eg;
    root = bst.updateNode(root, up_name, calcTotal(mth,che,eg), mth, che, eg);
    bst.showRankings(root, bst);



    string find_s;
    cout << "\nEnter the Student ID of the student you want Find: ";
    cin >> find_s;
    nodeBST* find = bst.searchby_id(root, find_s);
    if (find == NULL) {
        cout << "\nNo student found\n" << endl;

    }
    else
    {
        cout << "\n\nStudent found>>>>\n\n ";
        cout << "Student ID             " << find_s << endl;
        cout << " Mathematics marks      " << find->m_marks << endl;
        cout << " Chemistry marks        " << find->ch_marks << endl;
        cout << " English marks          " << find->en_marks << endl;
        cout << " Total Marks            " << calcTotal(find->en_marks,find->ch_marks, find->m_marks) << endl;
        cout << " Rank                   " << find->rank << endl;
        cout << "\n\n";

    }
    int upper,lower;
    cout << "\nEnter the upper limit of the range you want to filter : ";
    cin >> upper;
    cout << "\nEnter the lower limit of the range you want to filter : ";
    cin >> lower;
    cout << "\n\n";
    bst.printValueRange(root, lower, upper);

    

    return 0;
}