#include "big_int.h"
bool modulo_switch;
list_node* addition(list_node* data1, list_node* data2, list_node* modulus){
	clock_t start, end;
	start = clock();
	list_node* rtn = *data1 + *data2;
	end = clock();
	cout << "  Add Time : " << (double)(end - start) / CLOCKS_PER_SEC << "s\n";
	if (modulo_switch){
		start = clock();
		*rtn = *(*rtn % *modulus);
		end = clock();
		cout << "  Module Time : " << (double)(end - start) / CLOCKS_PER_SEC << "s\n  result: ";
	}
	TIME_BREAK = 0.02;
	return rtn;
}
pair<bool,list_node*> subtracion(list_node* data1, list_node* data2, list_node* modulus){
	clock_t start, end;
	start = clock();
	pair<bool, list_node*>temp = (*data1 - *data2);
	//bool oprt = (*data1 - *data2).first;
	//list_node* rtn = (*data1 - *data2).second;
	end = clock();
	cout << "  Subtract Time : " << (double)(end - start) / CLOCKS_PER_SEC << "s\n";
	if (modulo_switch){
		start = clock();
		*temp.second = *(*temp.second % *modulus);
		end = clock();
		cout << "  Module Time : " << (double)(end - start) / CLOCKS_PER_SEC << "s\n  result: ";
	}
	TIME_BREAK = 0.02;

	return{temp.first, temp.second };
}
list_node* multiplication(list_node* data1, list_node* data2, list_node* modulus){
	clock_t start, end;
	start = clock();
	list_node* rtn = *data1 * *data2;
	end = clock();
	cout << "  Mulitplicate Time : " << (double)(end - start) / CLOCKS_PER_SEC << "s\n";
	if (modulo_switch){
		start = clock();
		*rtn = *(*rtn % *modulus);
		end = clock();
		cout << "  Module Time : " << (double)(end - start) / CLOCKS_PER_SEC << "s\n  result: ";
	}
		TIME_BREAK = 0.02;

	return rtn;
}
list_node* division(list_node* data1, list_node* data2, list_node* modulus){
	clock_t start, end;
	start = clock();
	list_node* rtn = (*data1 / *data2);
	end = clock();
	cout << "  Division Time : " << (double)(end - start) / CLOCKS_PER_SEC << "s\n";
	if (modulo_switch){
		start = clock();
		rtn = *rtn % *modulus;
		end = clock();
		cout << "  Module Time : " << (double)(end - start) / CLOCKS_PER_SEC << "s\n  result:";
	}
	TIME_BREAK = 0.02;

	return rtn;
}
list_node* power(list_node* data, list_node* power, list_node* modulus){
	clock_t start, end;
	if (!modulo_switch)
		cout << "    Warning: this might create a very big number. modulo option cannot be disabled.\n";
	start = clock();
	if ((power->get_aftr()->get_data() == 0) && (power->get_aftr()->get_aftr()->get_data() == -1))
		return create_list("1");
	list_node* digit = create_list();
	list_node* two = create_list("2");
	list_node* rtn = create_list("1");
	list_node* cpy_power = create_list(power);
	if (!((cpy_power->get_aftr()->get_data() == 1) && (cpy_power->get_aftr()->get_aftr()->get_data() == -1))){
		while (1){
			pair<list_node*, list_node*> temp = cpy_power->d_m(two);
			*cpy_power = *temp.first;
			digit->InsertItem(temp.second->get_aftr()->get_data() + 48, digit);
			delete(temp.first->destructor());
			delete(temp.second->destructor());
			if ((cpy_power->get_aftr()->get_data() == 1) && (cpy_power->get_aftr()->get_aftr()->get_data() == -1))
				break;
		}
	}
	digit->InsertItem('1', digit);
	delete(two->destructor());
	delete(cpy_power->destructor());

	list_node* ptr_digit = digit->get_aftr();
	while (ptr_digit->get_data() != -1){
		list_node* temp = (*rtn * * rtn);
		*rtn = *(*temp % *modulus);
		delete(temp->destructor());
		if (ptr_digit->get_data() == 1){
			list_node* temp = (*rtn * * data);
			*rtn = *(*temp % *modulus);
			delete(temp->destructor());
		}
		ptr_digit = ptr_digit->get_aftr();
	}
	end = clock();
	cout << "  Module Time : " << (double)(end - start) / CLOCKS_PER_SEC << "s\n  result:";
	return rtn;
}


/*
clock_t start, end;
start = clock();
//printl(data);
list_node * rtn = (*data ^ power);
end = clock();
cout << "  Power Time : " << (double)(end - start) / CLOCKS_PER_SEC << "s\n";
if (modulo_switch){
start = clock();
//rtn = (*data ^ power);
//printl(rtn);
*rtn = *(*rtn % * modulus);
end = clock();
cout << "  Module Time : " << (double)(end - start) / CLOCKS_PER_SEC << "s\n  result:";
//TIME_BREAK = 1.0;
}
TIME_BREAK = 0.02;

*/
