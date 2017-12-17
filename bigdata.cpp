#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include "list_node.h"
#include "big_int.h"
#include <math.h>
#define VERSION "2.0.0"
#define LAST_DATA "$MMR"
#define MOD_DATA "$MOD"
#define MAXPOWERS "4001"
#define MAXPOWERI 4001

using namespace std;
typedef map<string, list_node* > M_MMR;
M_MMR m_mmr;
list_node* LAST_DATA_MMR;
typedef enum { cal, fl, ver, h, q, mod, mmr } ALL_INSTR;
typedef enum { finished, unfinished, unknown_instr, error, exits } RTN_INSTR;
typedef enum {rm, touch, echo} MMR_INSTR;
typedef struct {
	list_node* base;
	int pow;
	list_node* modulus;
}s_modulus;
s_modulus system_modulus;
typedef struct {
	vector <string> decompose_instr;
	bool valid;
}ANALYSIS_PACK;
static ALL_INSTR status = q; //cal:cal ; fl:fl ; h:h ; mmr:mmr ; q:normal
bool is_number(string& str){
	bool is_positive = false;
	if (str == "")
		return false;
	for (unsigned i = 0; i < str.length(); i++){
		if (str[i] == ' ')
			continue;
		if ((str[i] >= '0') && (str[i] <= '9'))
			is_positive = true;
		else
			return false;
	}
	if (is_positive)
		return true;
	else
		return false;
}
list_node* analyze2list(string str){
	list_node* num;
	M_MMR::iterator iter ;
	string s_temp = "";
	if (str[0] == '$'){
		s_temp = str.substr(1, str.length());
		iter = m_mmr.find(s_temp);
		if (iter != m_mmr.end())
			num = create_list(iter->second);
		else
			return NULL;
	}
	else{
		if (is_number(str))
			num = create_list(str);
		else
			return NULL;
	}
	return num;

}
int analyze2int(list_node* list){
	list_node* nobigger = create_list(MAXPOWERS);
	if (compare(list, nobigger) == 1){
		cout << "Too large Operation.\n";
		return 0;
	}
	int count = 0;
	int rtn = 0;
	list_node* ptr = list->get_prev();
	while (ptr->get_data() != -1){
		rtn += ptr->get_data() * (int)pow(10, count);
		count++;
		ptr = ptr->get_prev();
	}
	return rtn;
}
string analyze2str(int n){
	stringstream ss;
	string str;
	ss << n;
	ss >> str;
	return str;
}
ALL_INSTR gets_status(string str){
	if (str == "cal")
		return cal;
	else if (str == "fl")
		return fl;
	else if (str == "h")
		return h;
	else if (str == "mmr")
		return mmr;
	else
		return q;
}
bool save_log(string& outputlog){
	ofstream logfile;
	logfile.open("log.log", ios_base::app);
	if (logfile.is_open()){
		logfile << outputlog << endl;
		logfile.close();
	}
	else
		return false;
	return true;
}
ANALYSIS_PACK analyze(string str){
	int ptr = 0;
	ANALYSIS_PACK rtnpack;
	string temp;
	unsigned i;
	for (i = 0; i <= str.length(); i++){
		if (str[i] != ' ')
			continue;
		temp = str.substr(ptr, i - ptr);
		ptr = i + 1;
		if (temp != "")
			rtnpack.decompose_instr.push_back(temp);
	}
	temp = str.substr(ptr, i - ptr);
	if (temp != "")
		rtnpack.decompose_instr.push_back(temp);
	if (rtnpack.decompose_instr.size() == 0)
		rtnpack.valid = false;
	else
		rtnpack.valid = true;
	return rtnpack;
}
RTN_INSTR open_log(string filename){
	ifstream file;
	string str = "";
	file.open(filename, ios_base::in);
	while (file.good()){
		getline(file, str);
		cout << " " << str << endl;
	}
	return finished;
}
RTN_INSTR handle_cal(vector<string> hdle){
	if ((hdle.size() == 1) && (hdle.at(0) == "--help")){
		open_log("helplog.cal");
		return finished;
	}
	if (hdle.size() != 3)
		return error;
	list_node* num1, *num2;
	num1 = analyze2list(hdle.at(0));
	num2 = analyze2list(hdle.at(2));
	if ((num1 == NULL) || (num2 == NULL)){
		cout << "        No variable found. Do you mean $[variable]?\n";
		return error;
	}
	string operators = hdle.at(1);
	//cout << "        Calc: " << printl(num1) << " " << operators << " " << printl(num2) << endl;
	string result_str = "";
	if (operators == "+"){
		list_node* temp = addition(num1, num2, system_modulus.modulus);
		*LAST_DATA_MMR = *temp;
		result_str = printl(LAST_DATA_MMR);
		cout << result_str << endl<<endl;
		delete(temp->destructor());
	}
	else if (operators == "-"){
		pair<bool, list_node*> temp = subtracion(num1, num2, system_modulus.modulus);
		*LAST_DATA_MMR = *temp.second;
		result_str = printl(temp);
		cout << result_str << endl << endl;
		delete(temp.second->destructor());
	}
	else if (operators == "*"){
		list_node* temp = multiplication(num1, num2, system_modulus.modulus);
		*LAST_DATA_MMR = *temp;
		result_str = printl(LAST_DATA_MMR);
		cout << result_str << endl << endl;
		delete(temp->destructor());
	}
	else if (operators == "/"){
		list_node* temp = division(num1, num2, system_modulus.modulus);
		*LAST_DATA_MMR = *temp;
		result_str = printl(LAST_DATA_MMR);
		cout << result_str << endl << endl;
		delete(temp->destructor());
	}
	else if (operators == "^"){
		//int x = analyze2int(num2);
		list_node* temp = power(num1, num2, system_modulus.modulus);
		*LAST_DATA_MMR = *temp;
		result_str = printl(LAST_DATA_MMR);
		cout << result_str << endl << endl;
		delete(temp->destructor());
	}
	else{
		cout << "    Unknown Operator.\n";
		delete(num1->destructor());
		delete(num2->destructor());
		return error;
	}
	string print = "";
	string pow_str = analyze2str(system_modulus.pow);
	if (modulo_switch)
		print = "( " + printl(num1) + " " + operators + " " + printl(num2) + " ) % ( " + printl(system_modulus.base) + " ^ " + pow_str + " ) = " + result_str;
	else
		print = "( " + printl(num1) + " " + operators + " " + printl(num2) + " ) = " + result_str;
	if (!save_log(print))
		cout << "    cannot record on logfile.\n";
	delete(num1->destructor());
	delete(num2->destructor());
	return finished;
}
RTN_INSTR handle_mmr(vector<string> hdle){
	if ((hdle.size() == 1) && (hdle.at(0) == "--help")){
		open_log("helplog.mmr");
		return finished;
	}
	string instr = hdle.at(0);
	if ((hdle.size() == 1) && (instr == "--help")){
		cout << "show help mmr log\n";
		return finished;
	}
	if (instr == "rm"){
		if (hdle.size() != 2){
			cout << "    parameter error. Too much or too little.\n";
			return error;
		}
		string del_temp = hdle.at(1);
		M_MMR::iterator iter = m_mmr.find(del_temp);
		if (iter != m_mmr.end()){
			//num = create_list(iter->second);
			iter->second->destructor();
			m_mmr.erase(iter);
		}
		else{
			cout << "    Variable " << del_temp << " not found.\n";
			return error;
		}
	}
	else if (instr == "touch"){
		if (hdle.size() != 3){
			cout << "    parameter error. Too much or too little.\n";
			return error;
		}
		string touch_temp = hdle.at(1);
		if (hdle.at(2) == LAST_DATA){
			m_mmr[touch_temp] = create_list(LAST_DATA_MMR);
			return finished;
		}
		if (hdle.at(2) == MOD_DATA){
			m_mmr[touch_temp] = create_list(system_modulus.modulus);
			return finished;
		}
		if (is_number(hdle.at(2))){
			m_mmr[touch_temp] = create_list(hdle.at(2));
			return finished;
		}
		else{
			cout << "    Unknown number.\n";
			return error;
		}
	}
	else if (instr == "echo"){
		if (hdle.size() != 1){
			cout << "    parameter error. Too much or too little.\n";
			return error;
		}
		if (m_mmr.size() == 0)
			cout << "no variable storaged.\n";
		else{
			M_MMR::iterator iter = m_mmr.begin();
			for (iter = m_mmr.begin(); iter != m_mmr.end();iter++){
				cout << iter->first << " : ";
				cout<<printl(iter->second) ;
				cout << endl;
			}
		}
	}
	else{
		cout << "    No such instruction for mmr.\n";
		return error;
	}
	return finished;
}
RTN_INSTR handle_mod(){
	cout << "    the modulus is: ";
	cout<<printl(system_modulus.base);
	cout << " ^ " << system_modulus.pow << endl;
	cout << "    please input the index and the base:\n    base: ";
	string base_temp;
	getline(cin, base_temp, '\n');
	if (!is_number(base_temp)){
		cout << "    incorrect input of number BASE.\n";
		return error;
	}
	int temp = 0;
	cout << "    index: ";
	cin >> temp;
	if ((temp <= 0)|| (temp >=MAXPOWERI)){
		cout << "    incorrect input of number index.\n";
		return error;
	}
	*system_modulus.base = base_temp;
	system_modulus.pow = temp;
	system_modulus.modulus = *system_modulus.base ^ system_modulus.pow;
	TIME_BREAK = 0.2;
	return finished;
}
RTN_INSTR handle_fl(string filename){
	ifstream file;
	file.open(filename, ios_base::in);
	if (file.is_open()){
		string str;
		int succ_count = 0, err_count = 0;
		clock_t start, end;
		start = clock();
		while (file.good()){
			getline(file, str);
			cout << " " << str << endl;
			ANALYSIS_PACK temp_pack;
			RTN_INSTR fl_status;
			temp_pack = analyze(str);
			if (!temp_pack.valid){
				err_count++;
				continue;
			}
			fl_status = handle_cal(temp_pack.decompose_instr);
			if (fl_status == finished)
				succ_count++;
			else{
				cout << "  Syntax error: instruction '" << str << "' could not been analyzed.\n";
				err_count++;
			}
		}
		end = clock();
		cout << "\n          Total: " << succ_count + err_count << " instruction(s) ,\n          Successful analyzed: " << succ_count << " instruction(s) ,\n          Syntax error: " << err_count << " instruction(s) .\n";
		cout << "\n                              Total Time: " << (double)(end - start) / CLOCKS_PER_SEC << "s\n";
		return finished;
	}
	else{
		cout << "    cannot open file: " << filename << " .\n";
		return error;
	}
}
int welcome(){
	ifstream in;
	char str;
	string filename = "welcome.log";
	in.open(filename);
	if (!in){
		return -1;
	}
	while (!in.eof()){
		in.read(&str, 1);
		printf("%c", str);
	}
	in.close();
	ofstream logfile;
	logfile.open("log.log");
	if (!logfile.is_open())
		return -1;
	logfile << "This is a logfile.\n";
	logfile.close();
	modulo_switch = true;
	system_modulus.base = create_list("2");
	system_modulus.pow = 50;
	system_modulus.modulus = (*system_modulus.base ^ system_modulus.pow);
	LAST_DATA_MMR = create_list("0");
	TIME_BREAK = 0.02;
	return 0;
}
RTN_INSTR execute(ANALYSIS_PACK& pack){
	string temp_instr = pack.decompose_instr.at(0);
	if (temp_instr == "q"){
		if ((pack.decompose_instr.size() == 2) && (pack.decompose_instr.at(1) == "--help")){
			open_log("helplog.q");
			return finished;
		}
		if (status == q){
			if (pack.decompose_instr.size() == 2)
				rename("log.log", pack.decompose_instr.at(1).c_str());
			else if (pack.decompose_instr.size() == 1){
				cout << "    You do not rename the logfile before exit. Do you want to quit anyway?(y/n) > ";
				char yon = ' ';
				cin >> yon;
				if ((yon == 'y') || (yon == 'Y'))
					return exits;
				else if ((yon == 'n') || (yon == 'N'))
					return finished;
				else
					return error;
			}
			else
				return error;
			return exits;
		}
		else
			status = q;
		return finished;
	}
	if (status == q){
		if (temp_instr == "cal"){
			vector<string> temp;
			for (unsigned i= 1; i < pack.decompose_instr.size(); ++i)
				temp.push_back(pack.decompose_instr.at(i));
			if (temp.size() == 0){
				status = gets_status(temp_instr);
				return unfinished;
			}
			return handle_cal(temp);
		}
		else if (temp_instr == "fl"){
			//return finished;
			if (pack.decompose_instr.size() == 1){
				status = fl;
				return unfinished;
			}
			else if (pack.decompose_instr.size() == 2){
				if (pack.decompose_instr.at(1) == "--help"){
					open_log("helplog.fl");
					return finished;
				}
				return handle_fl(pack.decompose_instr.at(1));
			}
			else{
				cout << "    parameter too more or too less.\n";
				return error;
			}
		}
		else if (temp_instr == "ver"){
			cout << "    VERSION: " << VERSION << endl;
			return finished;
		}
		else if (temp_instr == "h"){
			open_log("helplog.help");
			return finished;
		}
		else if (temp_instr == "mod"){
			if ((pack.decompose_instr.size() == 2) && (pack.decompose_instr.at(1) == "--help")){
				open_log("helplog.modulus");
				return finished;
			}
			else if (pack.decompose_instr.size() == 1)
				return handle_mod();
			else
				return error;
		}
		else if (temp_instr == "sys"){
			cout << "    modulus: ";
			cout<<printl(system_modulus.modulus);
			cout << "\n    MMR: ";
			cout<<printl(LAST_DATA_MMR);
			cout << "\n    storaged variables: " << m_mmr.size();
			cout << "\n    Break_time: " << TIME_BREAK << " s";
			cout << "\n    MAX_POW: " << MAXPOWERS;
			cout << "\n    Modulo Switch: " << modulo_switch<<endl;
			return finished;
		}
		else if (temp_instr == "mmr"){
			vector<string> temp;
			for (unsigned i = 1; i < pack.decompose_instr.size(); ++i)
				temp.push_back(pack.decompose_instr.at(i));
			if (temp.size() == 0){
				status = gets_status(temp_instr);
				return unfinished;
			}
			return handle_mmr(temp);
		}
		else{
			return unknown_instr;
		}
	}//if (status = q)
	else{  //status != q
		if (status == cal)
			return handle_cal(pack.decompose_instr);
		else if (status == mmr)
			return handle_mmr(pack.decompose_instr);
		else if (status == fl){
			if (pack.decompose_instr.size() == 1){
				if (pack.decompose_instr.at(0) == "--help"){
					open_log("helplog.fl");
					return finished;
				}
				return handle_fl(pack.decompose_instr.at(0));
			}
			else{
				cout << "    parameter too more or too less.\n";
				return error;
			}
		}
		else
			return unknown_instr;
	}
}
int main(){
	bool already_print = false;
	if (welcome() != 0)
		return -1;
	while (1){
		if (!already_print){
			switch (status)
			{
			case q:
				cout << "Big_Data > ";
				break;
			case h:
				cout << "help > ";
				break;
			case cal:
				cout << "cal > ";
				break;
			case fl:
				cout << "fl > ";
				break;
			case mmr:
				cout << "mmr > ";
				break;
			}
		}
		already_print = true;

		string instruction;
		ANALYSIS_PACK temp;
		fflush(stdin);
		cin.clear();
		getline(cin, instruction, '\n');
		if (instruction == "modulo_switch off"){
			modulo_switch = false;
			already_print = false;
			continue;
		}
		else if (instruction == "modulo_switch on"){
			modulo_switch = true;
			already_print = false;
			continue;
		}
		temp = analyze(instruction);
		if (!temp.valid)
			continue;
		switch (execute(temp))
		{
		case finished:
			break;
		case unfinished:
			break;
		case unknown_instr:
			cout << "    Unknown instruction: " << temp.decompose_instr[0] << " \n    Type 'h' for getting more help.\n";
			break;
		case error:
			cout << "    There is something error in your inputing. Probably be syntax error.\n    Type '--help' for getting more help.\n";
			break;
		case exits:
			return 0;
		}
		already_print = false;
	}
}


