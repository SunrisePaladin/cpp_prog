#include <windows.h>
#pragma comment(lib, "winmm.lib")
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

using namespace std;

class slovo {
protected:
	int type; //создать уточнение
	//1 - существ. 2 - прил. 3 - местоим. 7 - предлог
	int rod; //мужской, женский, средний
	int obj; //лицо
	bool plural;
public:
	string meaning;
	slovo(string m) { meaning = m; type = 1; rod = 0; plural = false; obj = 3; }
	slovo() { meaning = "space"; type = 0; rod = 0; plural = false; obj = 3; };
	void define_type(int n) { type = n; };
	void define_obj(int n) { obj = n; };
	void define_rod(int n) { rod = n; }; //
	void define_plur(bool pl) { plural = pl; };
	int sized() {
		return meaning.size();
	};
	void print() {
		cout << meaning+" " << type;
		if (plural) cout << " plural\n";
		else cout << " singular\n";
	}
};

void manual_define(slovo& wrd) {
	cout << "Определение параметров слова в ручном режиме!\n";
	
}

void classify(slovo& wrd) {
	//проверка на предлоги
	if (wrd.meaning == "БЕЗ" || wrd.meaning == "БЛИЗ" || wrd.meaning == "В" || wrd.meaning == "ВНЕ"
		|| wrd.meaning == "ДЛЯ" || wrd.meaning == "ДО" || wrd.meaning == "ЗА" || wrd.meaning == "ИЗ"
		|| wrd.meaning == "ИЗ-ЗА" || wrd.meaning == "ИЗ-ПОД" || wrd.meaning == "К" || wrd.meaning == "МЕЖДУ" ||
		wrd.meaning == "НА" || wrd.meaning == "НАД" || wrd.meaning == "НАСЧЁТ" || wrd.meaning == "НЕСМОТРЯ" ||
		wrd.meaning == "О" || wrd.meaning == "ОБ" || wrd.meaning == "ОБО" || wrd.meaning == "ОКОЛО" ||
		wrd.meaning == "ОТ" || wrd.meaning == "ПЕРЕД" || wrd.meaning == "ПО" || wrd.meaning == "ПОД"
		|| wrd.meaning == "ПОПЕРЁК" || wrd.meaning == "С" || wrd.meaning == "У" || wrd.meaning == "ЧЕРЕЗ" || wrd.meaning == "СКВОЗЬ") {
		wrd.define_rod(0);
		wrd.define_obj(0);
		wrd.define_plur(false);
		wrd.define_type(7);
	}
	else if (wrd.meaning == "Я" || wrd.meaning == "МЕНЯ" || wrd.meaning == "МНЕ" || wrd.meaning == "МНОЙ" || wrd.meaning == "МНОЮ") {
		wrd.define_rod(0);
		wrd.define_obj(1);
		wrd.define_plur(false);
		wrd.define_type(3);
	}
	else if (wrd.meaning == "МЫ" || wrd.meaning == "НАС" || wrd.meaning == "НАМ" || wrd.meaning == "НАМИ") {
		wrd.define_rod(0);
		wrd.define_obj(1);
		wrd.define_plur(true);
		wrd.define_type(3);
	}
	else if (wrd.meaning == "ТЫ" || wrd.meaning == "ТЕБЯ" || wrd.meaning == "ТЕБЕ" || wrd.meaning == "ТОБОЙ") {
		wrd.define_rod(0); //УТОЧНИТЬ
		wrd.define_obj(2);
		wrd.define_plur(false);
		wrd.define_type(3);
	}
	else if (wrd.meaning == "ВЫ" || wrd.meaning == "ВАС" || wrd.meaning == "ВАМ" || wrd.meaning == "ВАМИ") {
		wrd.define_rod(0);
		wrd.define_obj(2);
		wrd.define_plur(true);
		wrd.define_type(3);
	}
	else if (wrd.meaning == "ОН" || wrd.meaning == "ЕГО" || wrd.meaning == "ЕМУ" || wrd.meaning == "НЁМ") {
		wrd.define_rod(1);
		wrd.define_obj(3);
		wrd.define_plur(false);
		wrd.define_type(3);
	}
	else if (wrd.meaning == "ОНА" || wrd.meaning == "ЕЁ" || wrd.meaning == "ЕЙ" || wrd.meaning == "НЕЙ") {
		wrd.define_rod(2);
		wrd.define_obj(3);
		wrd.define_plur(false);
		wrd.define_type(3);
	}
	else if (wrd.meaning == "ОНИ" || wrd.meaning == "ИХ" || wrd.meaning == "ИМ" || wrd.meaning == "ИМИ" || wrd.meaning == "НИХ") {
		wrd.define_rod(3);
		wrd.define_obj(3);
		wrd.define_plur(true);
		wrd.define_type(3);
	}
	else {
		if (wrd.sized() > 2) {
			if (wrd.meaning[wrd.sized() - 2] == 'А' && wrd.meaning[wrd.sized() - 1] == 'Я') {
				wrd.define_rod(2);
				wrd.define_plur(false);
				wrd.define_type(2);
			}
		}
		else {
			wrd.define_rod(3);
			wrd.define_plur(false);
			wrd.define_type(0);
		}
	}
}
void st(vector <slovo> &vect) {
	for (int i = 0; i < vect.size(); i++) {
		for (int j = 0; j < vect.size()-1; j++) {
			if (vect[j].meaning > vect[j + 1].meaning) {
				swap(vect[j], vect[j + 1]);
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	srand(unsigned(time(NULL)));

	//mciSendString("play Bonetrousle.mp3", NULL, 0, NULL);

	fstream fin("C:\\Users\\ArtSolo\\source\\repos\\Neyrobugurt\\Project6\\data.txt", ios::in);
	//fstream result("E:\\Projects\\C++\\Project6_lab\\Project6_lab\\result.res", ios::out);

	if (fin.is_open()) cout << "Все ОК! Файл открыт!" << endl;
	
	vector <slovo> words;
	int cnt = 0, aver = 0, strok = 0;
	
	while (!fin.eof()) {
		string tmp;
		fin >> tmp;
		if (tmp[tmp.size() - 1] == ',' || tmp[tmp.size() - 1] == '?') {
			tmp.resize(tmp.size() - 1); 
		}
		slovo sl(tmp);
		words.push_back(sl);
		slovo* link = &words[words.size() - 1];
		classify(*link);
		aver++;
		//words[words.size() - 1].print();

		if (words[cnt].meaning == "@") {
			words.pop_back();
			cnt--;
			strok++;
		}

		for (int i = 0; i < words.size(); i++) {
			if (words[i].meaning == tmp && i != (words.size() - 1)) {
				words.pop_back();
				cnt--;
			};
		}
		cnt++;
	}
	string prev = words[0].meaning, input = "bugurt";
	//sort(words.begin(), words.end());
	st(words);

	//int lim = rand() % (aver / 12) + 1;
	while (input != "stop") {
		int lim = rand() % 7 + 3;

		if (input == "bugurt" || input == "b" || input == "bug") {
			for (int j = 0; j < lim; j++) {
				int slov = rand() % ((aver / strok) - 1) + 3;
				for (slov; slov > 0; slov--) {
					int randword = rand() % words.size();
					if (words[randword].meaning != prev) {
						cout << words[randword].meaning << " ";
						prev = words[randword].meaning;
					}
				}
				if (j < lim - 1) cout << "\n@\n";
			}
			cout << "\n\n" << lim << endl;
		}
		else if (input == "print" || input == "abc" || input == "list") {
			for (int k = 0; k < words.size(); k++) {
				cout << words[k].meaning << endl;
			}
		}
		else if (input == "class") {
			for (int k = 0; k < words.size(); k++) {
				words[k].print();
			}
		}
		else cout << "Ваша команда не распознана\n";
		cin >> input;
	}
	
	return 0;
}