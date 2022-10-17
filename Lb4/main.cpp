#include"RBTree.h"
#include<iostream>
#include<vector>
using namespace std;
int main() 
{
    setlocale(LC_ALL, "Russian");
	vector<int> nums{ 10,40,30,60,90,70,20,50,80,100};
	RBTree<int> tree;
	for (auto num : nums)
		tree.insert(num);
	tree.preOrder();
	cout << endl;
	tree.inOrder();
	cout << endl;
	tree.postOrder();
	cout << endl;
	cout << "Найти узел с ключом 30: \n";
	cout << endl<<tree.search(30)->key<<endl;
	cout << "Удалить узел с ключом 100 \n";
	tree.remove(100);
	tree.preOrder();
	cout << endl;
	cout << "\nДерево: \n";
	tree.print();
	return 0;
}
