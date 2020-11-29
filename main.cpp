#include <iostream>
#include <string.h>

using namespace std;

struct Node
{
    char data;
    Node *left, *right;
};
typedef Node *PNode;

int Priority (char c)
{
    switch (c)
    {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
    }
    return 100; // это не арифметическая операция
}

//Построить дерево по выражению
PNode MakeTree (char Expr[], int first, int last)
{
    int MinPrt, i, k, prt;
    int nest = 0; // счетчик открытых скобок
    PNode Tree = new Node;
    if (first == last)
    {
        Tree->data = Expr[first];
        Tree->left = NULL;
        Tree->right = NULL;
        return Tree;
    }
    MinPrt = 100;
    for (i = first; i <= last; i ++)
    {
        if (Expr[i] == '(')
        {
            nest ++;
            continue;
        }
        if (Expr[i] == ')')
        {
            nest --;
            continue;
        }
        if (nest > 0) continue;

        prt = Priority (Expr[i]);
        if (prt <= MinPrt)
        {
            MinPrt = prt;
            k = i;
        }
    }
    if (MinPrt == 100 && Expr[first]== '(' && Expr[last]==')')
    {
        delete Tree;
        return MakeTree(Expr, first+1, last-1);
    }

    Tree->data = Expr[k];
    Tree->left = MakeTree (Expr,first,k-1);
    Tree->right = MakeTree (Expr,k+1,last);
    return Tree;
}

//Вычислить значение выражения
float CalcTree (PNode Tree)
{
    float num1, num2;
    if (! Tree->left)
        return Tree->data - '0';
    num1 = CalcTree(Tree->left);
    num2 = CalcTree(Tree->right);
    switch ( Tree->data )
    {
        case '+': return num1+num2;
        case '-': return num1-num2;
        case '*': return num1*num2;
        case '/': return num1/num2;
    }
}


//Напечатать дерево
void print (Node *t, int u)
{
    if (t == NULL)
        return;
    else
    {
        print(t->left, ++u);
        for (int i=0; i<u; ++i)
            cout << "   ";
        cout << t->data << endl;
        u--;
    }
    print(t->right, ++u);
}


int main()
{
    char s[80];
    PNode Tree;
    cout << "Enter an example:   " ;
    cin >> s;
    Tree = MakeTree(s, 0, strlen(s)-1);
    cout << "Answer:   ";
    cout << CalcTree (Tree) <<endl;
    cout << "\n";
    print (Tree, 0);
    return 0;
}

