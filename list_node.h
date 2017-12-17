//2017.11.17
//严恩伟
//2017.12.05
#ifndef _LIST_NODE_
#define _LIST_NODE_
#include<string>
#include <iostream>
using namespace std;
extern  double TIME_BREAK;
typedef struct num_pack pack;

class list_node
{
private:
	char data;
	list_node* prev;	//prev，上一个指针
	list_node* aftr;	//aftr ，下一个指针，堆对象，需要删除
	pair<char , char> operator_bit(char c1, char c2, char bit_operator);
	/*
	list_node* estimated(list_node* number, list_node* opd_number);
	*/
	pair<char, list_node*> estimatedv2(list_node* number, pack* numberpack);
	list_node* sublist(list_node* begins, list_node* ends);
	friend  int rtn_length(list_node* p);
	bool is_zero();
	//void set_data(const char &data);
	//void set_prev(const list_node* p);
	//void set_aftr(const list_node* p);
public:
	//-------construct and destruct class-------//
	friend list_node* create_list();							//default ctor, return by header.
	friend list_node* create_list(const string str);		//ctor.
	friend list_node* create_list(list_node* header);	//copy ctor, return by header.
	list_node* destructor();												//dtor, delete all pointer

	//-------get private data/pointer------//
	int get_data() const;
	list_node* get_prev() const;
	list_node* get_aftr() const;
	//-------Insert/Delete Item---------------//
	void InsertItem(const char item, list_node*p);		//insert an item after pointer
	list_node* DeleteItem(list_node*p);					//delete the item,return a pointer after the item
	void push_back(const char item);						//insert an item at the back of the list
	void pop_back();												//delete the final item
	//-------Operator-------------------------//
	list_node* operator=(list_node data);
	list_node* operator=(string str);
	list_node* operator+(list_node &data);
	pair<bool, list_node*> operator-(list_node &data);			//when the number is negtive , bool = false;
	list_node* operator*(list_node &data);
	list_node* operator/(list_node &data);
	list_node* operator%(list_node &modulus);
	list_node* operator^(int power);
	bool operator==(list_node &data);
	pair<list_node*, list_node*> d_m(list_node* opt);
	//-------Compare--------------------------//
	friend int compare(list_node* data1, list_node* data2);
	//-------Print------------------------------//
	friend string printl(list_node* list);
	friend string printl(pair<bool, list_node*>);
};
list_node* create_list();
list_node* create_list(const string str);
list_node* create_list(list_node* header);
int compare(list_node* data1, list_node* data2);
string printl(list_node* list);
string printl(pair<bool, list_node*>);	//print negitive number
int rtn_length(list_node* p);

void init_pack(pack* numpack, list_node* num);
void rm_pack(pack* numpack);
#endif
