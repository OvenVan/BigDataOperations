#include "list_node.h"
double TIME_BREAK = 0.02;

struct num_pack_s
{
	list_node *num[10];
};

int rtn_length(list_node *list)
{
	int length = 0;
	list_node *p = list->aftr;
	while (p->data != '\0')
	{ //得到数字的长度
		p = p->aftr;
		length++;
	}
	return length;
}
pair<char, char> list_node::operator_bit(char c1, char c2, char bit_operator)
{
	pair<char, char> resbychar;
	int res;
	switch (bit_operator)
	{
	case '+':
		res = (int)c1 - 48 + (int)c2 - 48;
		break;
	case '-':
		res = (int)c1 - (int)c2;
		if (res < 0)
		{
			resbychar.first = '-';
			resbychar.second = 10 + res + 48;
		}
		else
		{
			resbychar.first = '0';
			resbychar.second = res + 48;
		}
		return resbychar;
	case '*':
		res = ((int)c1 - 48) * ((int)c2 - 48);
		break;
	case '/':
		resbychar.first = ((int)c1 - 48) / ((int)c2 - 48);
		resbychar.second = ((int)c1 - 48) % ((int)c2 - 48);
		return resbychar;
	}
	resbychar.first = (res / 10) + 48;
	resbychar.second = (res % 10) + 48;
	return resbychar;
}

pair<char, list_node *> list_node::estimatedv2(list_node *number, num_pack_t *numberpack)
{
	int i;
	number->is_zero();
	for (i = 9; i > 0; --i)
	{
		if (!(compare(numberpack->num[i], number) == 1))
			break;
	}
	pair<bool, list_node *> temp;
	temp = *number - *numberpack->num[i];
	return {(char)(i + 48), temp.second};
}

list_node *list_node::sublist(list_node *begins, list_node *ends)
{ //take sublist of listnode
	list_node *rtn_list = create_list();
	list_node *ptr = begins;
	while (ptr != ends)
	{
		rtn_list->push_back(ptr->data);
		ptr = ptr->aftr;
	}
	rtn_list->push_back(ptr->data);
	return rtn_list;
}

bool list_node::is_zero()
{
	list_node *ptr = this->aftr;
	bool zero = true;
	while (ptr->data != '\0')
	{
		if (ptr->data != '0')
		{
			zero = false;
			break;
		}
		ptr = ptr->aftr;
	}
	if (zero)
		*this = "0";
	else
	{
		ptr = this->aftr;
		while (ptr->data != '\0')
		{
			if (ptr->data == '0')
				ptr = this->DeleteItem(ptr);
			else
				break;
		}
	}
	return zero;
}
list_node *list_node::destructor()
{
	list_node *delpoint = this->aftr;
	if (delpoint == this)
		return this;
	list_node *delnext = delpoint->aftr;
	while (delnext->data != '\0')
	{
		delpoint->aftr = NULL;
		delpoint->prev = NULL;
		list_node *point = delpoint;
		delpoint = delnext;
		//delete point->aftr;
		//delete point->prev;
		delete point;
		delnext = delnext->aftr;
	}
	delpoint->aftr = NULL;
	delpoint->prev = NULL;
	delete delpoint;
	delnext->aftr = delnext;
	delnext->data = '\0';
	delnext->prev = delnext;
	return delnext;
} //

list_node *create_list(const string str)
{
	list_node *newlist = create_list();
	for (unsigned i = 0; i < str.length(); i++)
	{
		if (str[i] != ' ')
			newlist->push_back(str[i]);
	}
	newlist->is_zero();
	return newlist;
}
list_node *create_list()
{
	list_node *newlist = new list_node;
	newlist->prev = newlist;
	newlist->aftr = newlist;
	newlist->data = '\0';
	return newlist;
}
list_node *create_list(list_node *header)
{
	list_node *point = header->aftr;
	if (header->data != '\0')
		return create_list();
	list_node *newlist = create_list();
	while (1)
	{
		int buffer;
		buffer = point->get_data();
		if (buffer != -1)
			newlist->push_back(buffer + 48);
		else
			break;
		point = point->aftr;
	}
	return newlist;
}
string printl(list_node *list)
{
	string rtnstr = "";
	if (list == NULL || (list->aftr == list))
		return rtnstr;
	list_node *point = list->aftr;
	while (1)
	{
		int buffer;
		buffer = point->get_data();
		if (buffer != -1)
		{
			rtnstr = rtnstr + point->data;
		}
		else
			break;
		point = point->aftr;
	}
	return rtnstr;
}
string printl(pair<bool, list_node *> temp)
{
	string rtnstr = "";
	if (temp.first)
		return printl(temp.second);
	else
	{
		rtnstr = "-" + printl(temp.second);
		return rtnstr;
	}
}
int list_node::get_data() const
{
	if (this->data)
		return (int)data - 48;
	else
		return -1;
}
list_node *list_node::get_prev() const
{
	return prev;
}
list_node *list_node::get_aftr() const
{
	return aftr;
}
void list_node::InsertItem(const char item, list_node *p)
{ //insert an item after pointer.
	list_node *newitem = new list_node;
	list_node *paftr = p->aftr;
	newitem->data = item;
	if (this->aftr->data == '\0') //只有表头数据
	{
		p->aftr = newitem;
		newitem->prev = p;
		p->prev = newitem;
		newitem->aftr = p;
	}
	else
	{
		newitem->aftr = paftr;
		paftr->prev = newitem;
		newitem->prev = p;
		p->aftr = newitem;
	}
}
list_node *list_node::DeleteItem(list_node *p)
{ //delete the item,return a pointer after the item
	if (p->data == '\0')
		return this; //DeleteItem内不允许删除表头
	list_node *rtnpointer = p->aftr;
	p->prev->aftr = rtnpointer;
	rtnpointer->prev = p->prev;
	delete p;
	return rtnpointer;
}
void list_node::push_back(const char item)
{ //insert an item at the back of the list
	list_node *newitem = new list_node;
	newitem->data = item;
	list_node *enditem = this->prev;
	newitem->aftr = this;
	newitem->prev = enditem;
	this->prev = newitem;
	enditem->aftr = newitem;
}

void list_node::pop_back()
{ //delete the final item
	list_node *delpoint = this->prev;
	if (delpoint == this) //cannot delete header.
		return;
	list_node *prevpoint = delpoint->prev;
	this->prev = prevpoint;
	prevpoint->aftr = this;
	delpoint->aftr = NULL;
	delpoint->prev = NULL;
	delete delpoint;
}

list_node *list_node::operator=(list_node data)
{
	if (this->prev == data.prev) //like apple=apple,invalid
		return this;
	list_node *ptr = this->aftr;
	while (ptr->data != '\0')
		ptr = this->DeleteItem(ptr);
	ptr = data.aftr;
	while (ptr->data != '\0')
	{
		this->push_back(ptr->data);
		ptr = ptr->aftr;
	}
	return this;
}
list_node *list_node::operator=(string str)
{
	list_node *ptr = this->aftr;
	while (ptr->data != '\0')
		ptr = this->DeleteItem(ptr);
	for (unsigned i = 0; i < str.length(); i++)
	{
		if (str[i] != ' ')
			this->push_back(str[i]);
	}
	return this;
}
bool list_node::operator==(list_node &data)
{
	if (this->prev == data.prev)
		return true;
	list_node *ptr_this = this;
	list_node *ptr_data = &data;
	if ((ptr_data->data != '\0') || (ptr_this->data != '\0'))
		return false;
	ptr_data = ptr_data->aftr;
	ptr_this = ptr_this->aftr;
	while (ptr_this->data != '\0')
	{
		if (ptr_data->data != ptr_this->data)
			return false;
		else
		{
			ptr_data = ptr_data->aftr;
			ptr_this = ptr_this->aftr;
		}
	}
	if (ptr_data->data == '\0')
		return true;
	else
		return false;
}
list_node *list_node::operator+(list_node &data)
{
	bool is_carrybit = false, isfinal_p1 = false, isfinal_p2 = false;
	pair<char, char> temp;
	list_node *ptr1 = this->prev;
	list_node *ptr2 = data.prev;
	list_node *result = create_list();
	list_node *carrybit = create_list("0");
	while (!(isfinal_p1 && isfinal_p2))
	{
		if ((!isfinal_p1) && (!isfinal_p2))
		{
			temp = operator_bit(ptr1->data, ptr2->data, '+');
			result->InsertItem(temp.second, result);
			carrybit->InsertItem(temp.first, carrybit);
			if (temp.first != '0')
				is_carrybit = true;
		}
		else if ((isfinal_p1) && (!isfinal_p2))
		{
			result->InsertItem(ptr2->data, result);
			carrybit->InsertItem('0', carrybit); //insert at the beginning
		}
		else if ((!isfinal_p1) && (isfinal_p2))
		{
			result->InsertItem(ptr1->data, result);
			carrybit->InsertItem('0', carrybit); //insert at the beginning
		}
		if (ptr1->prev->data != '\0')
			ptr1 = ptr1->prev;
		else
			isfinal_p1 = true;
		if (ptr2->prev->data != '\0')
			ptr2 = ptr2->prev;
		else
			isfinal_p2 = true;
	}

	if (is_carrybit)
	{
		carrybit->is_zero(); //消除多余的0；
		list_node *rtn = *result + *carrybit;
		delete (carrybit->destructor());
		delete (result->destructor());
		return rtn;
	}
	else
	{
		delete (carrybit->destructor());
		return result;
	}
}
pair<bool, list_node *> list_node::operator-(list_node &data)
{
	pair<bool, list_node *> final;
	if (*this == data)
		return {true, create_list("0")};
	if (compare(this, &data) == -1)
	{
		final.first = false;
		final.second = (data - *this).second;
		return final;
	}
	list_node *res = create_list();
	bool is_cotn_data = true;
	bool is_borrow = false;
	pair<char, char> temp;
	list_node *ptr1 = this->prev;
	list_node *ptr2 = data.prev;
	while (ptr1->data != '\0')
	{
		char tempdt2 = '0';
		if (is_cotn_data)
			tempdt2 = ptr2->data;
		if (!is_borrow)
			temp = operator_bit(ptr1->data, tempdt2, '-');
		else
		{
			if (ptr1->data != '0')
				temp = operator_bit(ptr1->data - 1, tempdt2, '-');
			else
			{
				temp.first = '-';
				temp.second = '9' - tempdt2 + 48;
			}
		}
		if (temp.first == '-')
			is_borrow = true;
		else
			is_borrow = false;
		res->InsertItem(temp.second, res);
		if (ptr2->prev->data != '\0')
			ptr2 = ptr2->prev;
		else
			is_cotn_data = false;
		ptr1 = ptr1->prev;
	}
	final.first = true;
	res->is_zero();
	final.second = res;
	return final;
}
list_node *list_node::operator*(list_node &data)
{
	if (this->is_zero() || data.is_zero())
		return create_list("0");

	list_node *ptr1, *ptr2;
	if (compare(this, &data) == 1)
	{
		ptr2 = this;
		ptr1 = &data;
	}
	else
	{
		ptr1 = this;
		ptr2 = &data;
	}		//ptr1 is smaller
	num_pack_t *dt = new num_pack_t;
	init_pack(dt, ptr1);
	ptr2 = ptr2->prev;
	list_node *rtn_res = create_list("0"); //return rtn_res
	int count = 0;
	while (ptr2->data != '\0')
	{
		list_node *temp_res = create_list(dt->num[ptr2->get_data()]);  		//memory_loss
		for (int j = 1; j <= count; j++)
			temp_res->push_back('0'); 		//memory_loss
		list_node* temp_add_res = (*rtn_res + *temp_res);
		delete(temp_res->destructor());
		temp_add_res->replaceGuardian(rtn_res);
		//*rtn_res = *(*rtn_res + *temp_res);
		delete (temp_add_res);
		ptr2 = ptr2->prev;
		count++;
	}
	rm_pack(dt);
	rtn_res->is_zero();
	return rtn_res;
}

list_node *list_node::operator/(list_node &data)
{
	if ((data.aftr->get_data() == 1) && (data.aftr->aftr->data == '\0')) //data=1
		return create_list(this);
	if (*this == data) //note: if (this == &modulus) is error
		return create_list("1");
	else if (compare(&data, this) == 1)
		return create_list("0");

	pair<list_node *, list_node *> rtn_temp = d_m(&data);
	delete (rtn_temp.second->destructor());
	return rtn_temp.first;
}
list_node *list_node::operator%(list_node &modulus)
{
	if ((modulus.aftr->get_data() == 1) && (modulus.aftr->aftr->data == '\0')) //modulus=1
		return create_list("0");
	if (*this == modulus) //note: if (this == &modulus) is error
		return create_list("0");
	else if (compare(&modulus, this) == 1)
		return create_list(this);
	pair<list_node *, list_node *> rtn_temp = d_m(&modulus);
	delete (rtn_temp.first->destructor());
	return rtn_temp.second;
}

list_node *list_node::operator^(int power)
{
cout << "operator ^: dealing: " << printl(this) << " ^ " << power << endl;
	clock_t start, pause;
	double spend_time = 0.0;
	start = clock();
	if (power == 0)
	{
		return create_list("1");
	}
	num_pack_t *dt = new num_pack_t;
	init_pack(dt, this);
	list_node *rtnpower = create_list(this);
	for (int i = 1; i < power; i++)
	{
		//计算rtnpower * this，将res返回给rtnpower
		if (spend_time >= TIME_BREAK)
		{
			cout << " : " << spend_time << "s" << endl;
			cout << "break time:  Time = " << TIME_BREAK << "   spend time = " << spend_time << "  power/i = " << (power / i) << "  power%i=" << (power % i) << "  i = " << i << endl
				 << endl;
			TIME_BREAK *= 10;
			list_node *temp1 = (*rtnpower ^ (power / i));
			list_node *temp2 = (*this ^ (power % i));
cout << "multipling:";
			list_node *rtn = *temp1 * *temp2;
cout << "finished.\n";
			delete (temp1->destructor());
			delete (temp2->destructor());
			delete (rtnpower->destructor());
			rm_pack(dt);
			rtn->is_zero();
			return rtn;
		} //分解power:
		list_node *ptrpower = rtnpower->prev;
		list_node *respower = create_list("0");
		int count = 0;
		while (ptrpower->data != '\0')
		{
			list_node *temp_res = create_list(dt->num[ptrpower->get_data()]);
			for (int j = 1; j <= count; j++)
				temp_res->push_back('0');
			list_node *temp_add = (*respower + *temp_res);
			temp_add->replaceGuardian(respower);
			delete (temp_add);
			delete (temp_res->destructor());
			count++;
			pause = clock();
			spend_time = (double)(pause - start) / CLOCKS_PER_SEC;
			ptrpower = ptrpower->prev;
		}
		*rtnpower = *respower;
		delete (respower->destructor());
cout << ".";
	} 
cout << " : " << spend_time << "s" << endl;
	rm_pack(dt);
	rtnpower->is_zero();
	//cout << endl;
	return rtnpower;
}

int compare(list_node *data1, list_node *data2)
{ //0:equal , 1: data1 is bigger , -1: data2 is bigger , -99: error
	int n = 0;
	list_node *ptr1 = data1;
	list_node *ptr2 = data2;
	if ((ptr1->data != '\0') || (ptr2->data != '\0'))
		return -99;
	if (*data1 == *data2)
		return 0;
	while (ptr1->aftr->data != '\0')
	{
		n++;
		ptr1 = ptr1->aftr;
	}
	for (int i = 1; i <= n; i++)
	{
		ptr2 = ptr2->aftr;
		if (ptr2->data == '\0')
			return 1;
	}
	if (ptr2->aftr->data != '\0')
		return -1;
	else
	{
		ptr1 = data1->aftr;
		ptr2 = data2->aftr;
		for (int i = 1; i <= n; i++)
		{
			if ((ptr1->data) > (ptr2->data))
				return 1;
			else if (ptr1->data < ptr2->data)
				return -1;
			else
			{
				ptr1 = ptr1->aftr;
				ptr2 = ptr2->aftr;
			}
		} //for
	}	 //else
	return -99;
}

void init_pack(num_pack_t *numpack, list_node *num)
{
	numpack->num[0] = create_list("0");
	numpack->num[1] = create_list(num);
	for (int i = 2; i < 10; i++)
	{
		numpack->num[i] = *numpack->num[i - 1] + *numpack->num[1];
	}
}
void rm_pack(num_pack_t *numpack)
{
	for (int i = 0; i < 10; i++)
		delete (numpack->num[i]->destructor());
	delete numpack;
}


pair<list_node *, list_node *> list_node::d_m(list_node *opt)
{
	list_node *ptr_end = this;
	for (int i = 1; i <= rtn_length(opt); i++)
		ptr_end = ptr_end->aftr;
	list_node *sublist = this->sublist(this->aftr, ptr_end); //delete sublist
	list_node *rtn_list = create_list();
	num_pack_t *dt = new num_pack_t;
	init_pack(dt, opt);
	if (compare(sublist, opt) == -1)
	{
		ptr_end = ptr_end->aftr;
		sublist->push_back(ptr_end->data);
	}
	ptr_end = ptr_end->aftr;
	while (ptr_end->data != '\0')
	{
		pair<char, list_node *> temp;
		temp = estimatedv2(sublist, dt);
		rtn_list->push_back(temp.first);
		*sublist = *temp.second;
		sublist->push_back(ptr_end->data);
		ptr_end = ptr_end->aftr;
		delete (temp.second->destructor());
	}
	pair<char, list_node *> temp;
	temp = estimatedv2(sublist, dt);
	rtn_list->push_back(temp.first); 		// ->/
	temp.second->replaceGuardian(sublist);  // ->%
	rm_pack(dt);
	return {rtn_list, sublist};
}

void list_node::replaceGuardian(list_node *&newGuardian)
{
	if (this == newGuardian)
		return;
	newGuardian->destructor();
	this->prev->aftr = newGuardian;
	this->aftr->prev = newGuardian;
	this->addGuardian(newGuardian);
	this->aftr = this;
	this->prev = this;
}

void list_node::addGuardian(list_node *&newGuardian)
{
	newGuardian->data = this->data;
	newGuardian->aftr = this->aftr;
	newGuardian->prev = this->prev;
}
