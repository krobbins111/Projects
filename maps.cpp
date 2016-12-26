

#include"library.h"
#include<iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <sstream>


using namespace std;



bool number(char x)
{
	if (x >= '0' && x <= '9' || x == '.' || x != ' ')
	{
		return true;
	}
	else
	{
		return false;
	}
}

int stringtoint(string input)
{
	unsigned int num = 0;
	int i = 0;
	while (i < input.size())
	{
		num *= 10;
		num += input[i] - 48;
		i++;
	}
	return num;
}

struct place
{
	string code;
	string state;
	string city;
	string pop;
	string area;
	string latitude;
	string longitude;
	int roadcode;
	double extradist;
	long long int key;


public:
	void setkey()
	{
		unsigned int x = 1299709;
		string namec = this->city;
		string named = this->state;
		string names = namec + named;
		key = (x * stringtoint(names));
	}

	void setpvalues(place * guy)
	{
		this->code = guy->code;
		this->state = guy->state;
		this->city = guy->city;
		this->pop = guy->pop;
		this->latitude = guy->latitude;
		this->longitude = guy->longitude;
		this->roadcode = guy->roadcode;
		this->extradist = guy->extradist;
	}
};

class hash_node
{
protected:
	place * p;
	int counter;
	hash_node * next;

public:
	hash_node()
	{
		p = new place;
		counter = 0;
		next = NULL;
	}

	string getCity() //fname
	{
		return p->city;
	}

	string getState() //lname
	{
		return p->state;
	}

	int getkey()
	{
		return p->key;
	}

	place * getPlace()
	{
		return p;
	}

	void set_place(place * dude)
	{
		p = dude;
	}

	hash_node * getNext()
	{
		return next;
	}

	void setNext(hash_node * NEXT)
	{
		this->next = NEXT;
	}


	void count()
	{
		this->counter = this->counter + 1;
		//cout << " " << counter;
	}

	int getCount()
	{
		int theCount = this->counter;
		return theCount;
	}


};

int const size = 65536;

int closestIntersection(int n) // NEED FASTER SOLUTION
{
	ifstream fin1("/home/www/geographical/closests.txt");
	int a;
	string b;
	for (int i = 0; i < n; i++)
	{
		getline(fin1, b);
	}
	fin1 >> a;
	fin1.close();
	return a;

}

class hash_table
{
protected:
	hash_node ** table;


public:

	hash_table()
	{
		int const size = 65536;
		table = new hash_node*[size];
		for (int i = 0; i < size; i++)
		{
			table[i] = NULL;
		}
	}

	void add(place * dude)
	{
		int const size = 65536;
		int hash = (dude->key % size);
		if (table[hash] == NULL)
		{
			table[hash] = new hash_node;
			table[hash]->getPlace()->setpvalues(dude);
			table[hash]->count();
		}
		else
		{
			hash_node * entry = table[hash];
			while (entry->getNext() != NULL)
			{
				entry = entry->getNext();
			}
			hash_node * temp = new hash_node;
			temp->getPlace()->setpvalues(dude);
			entry->setNext(temp);
			table[hash]->count();
		}
	}

	void setup()
	{
		cout << "Loading..\n";
		int const size1 = 65536;
		int skip = 0;
		ifstream fin("named-places.txt");
		string code1 = "";
		string state1 = "";
		string city1 = "";
		string pop1 = "";
		string area1 = "";
		string latitude1 = "";
		string longitude1 = "";
		int roadcode1;
		double extradist1;
		place * testp;
		string line;
		string line2;
		string line3;
		string tempStr;
		string text;
		while (!fin.eof())
		{
			getline(fin, line);
			if (fin.fail())
			{
				cout << "Ready\n";
				break;
			}
			testp = new place;

			//cout << line << endl;
			int p = line.length();
			while (number(line[p])) p--;

			string input1 = line.substr(p, line.length());
			char const* in = input1.c_str();
			extradist1 = strtod(in, NULL);

			int o = 0;
			p -= 2;
			int end = p;
			while (line[p] != '.')
			{
				p--;
			}
			if (line[p + 7] == ' ')
			{
				if(number(line[p+8]))roadcode1 = stringtoint(line.substr(p + 8, end - (p + 7)));
				else roadcode1 = stringtoint(line.substr(p + 9, end - (p + 8)));
			}
			else roadcode1 = stringtoint(line.substr(p + 7, end - (p + 6)));
			roadcode1 = abs(roadcode1);
			code1 = line.substr(0, 8);
			state1 = line.substr(8, 2);
			int i = 0;
			int j = 9;
			while (i < 1)
			{
				j++;
				if (line[j] == ' ' && line[j + 1] == ' ') i++;
			}
			city1 = line.substr(10, j - 10);

			while (!number(line[j])) j++;
			int k = j;
			while (number(line[k])) k++;
			pop1 = line.substr(j, k - j);

			j = k + 1;
			while (!number(line[j])) j++;
			k = j;
			while (number(line[k])) k++;
			area1 = line.substr(j, k - j);

			if (line[j] == '-') k++;
			j = k + 1;
			while (!number(line[j]))
			{
				if (line[j] == '-') break;
				j++;
			}
			k = j;
			while (number(line[k]) && line[k] != '-') k++;
			latitude1 = line.substr(j, k - j);

			if (line[k] == '-' || line[k + 1] == '-') k--;
			j = k + 1;
			while (!number(line[j]))
			{
				if (line[j] == '-') break;
				j++;
			}
			k = j;
			while (number(line[k])) k++;
			longitude1 = line.substr(j, k - j);
			testp->code = code1;
			testp->state = state1;
			testp->city = city1;
			testp->pop = pop1;
			testp->area = area1;
			testp->latitude = latitude1;
			testp->longitude = longitude1;
			testp->roadcode = roadcode1;
			testp->extradist = extradist1;
			testp->setkey();
			add(testp);
			delete testp;
		}
		cout << endl << endl << endl;
		fin.close();
	}




	place * find(string f, string l)
	{
		int const size = 65536;
		string name1 = f + l;
		unsigned int x = 1299709;
		long long int checkey = (x * stringtoint(name1));
		long long int hashcheck = checkey % size;
		hash_node * search = table[hashcheck];
		if (search == NULL || search->getCity() == "")
		{
			cout << "Not here\n";
			return NULL;
		}
		else if (f == search->getCity() && l == search->getState())
		{
			place * you = search->getPlace();
			return you;
		}
		while (search->getCity() != f && search->getState() != l && search->getNext() != NULL)
		{
			search = search->getNext();
		}
		if (search == NULL) return NULL;
		if (f != search->getCity() && l != search->getState()) return NULL;
		place * you = search->getPlace();
		return you;// SHOULD MAKE WORK THE WAY IT IS OR WITH STRINGS FOR NAME
	}

	/*void printhash()
	{
	hash_node * check = table[828];
	while(check != NULL)
	{
	cout << check->getCity() << " " << check->getState() << endl;
	check = check->getNext();
	if (check == NULL) cout << "NULL\n";
	}
	}*/

	void fish()
	{
		int const size = 65536;
		int zero = 0;
		int one = 0;
		int two = 0;
		int three = 0;
		int four = 0;
		int five = 0;
		int six = 0;
		int seven = 0;
		int eight = 0;
		for (int i = 0; i < size; i++)
		{
			if (table[i] == NULL) zero++;
			else if (table[i]->getCount() == 1) one++;
			else if (table[i]->getCount() == 2) two++;
			else if (table[i]->getCount() == 3) three++;
			else if (table[i]->getCount() == 4) four++;
			else if (table[i]->getCount() == 5) five++;
			else if (table[i]->getCount() == 6) six++;
			else if (table[i]->getCount() == 7) seven++;
			else if (table[i]->getCount() == 8) eight++;
		}
		cout << "zero: " << zero << endl;
		cout << "one: " << one << endl;
		cout << "two: " << two << endl;
		cout << "three: " << three << endl;
		cout << "four: " << four << endl;
		cout << "five: " << five << endl;
		cout << "six: " << six << endl;
		cout << "seven: " << seven << endl;
		cout << "eight: " << eight << endl;
		cout << endl << endl << endl;
	}


	~hash_table()
	{
		int const size = 65536;
		for (int i = 0; i < size; i++)
			if (table[i] != NULL)
			{
				hash_node * prevEntry = NULL;
				hash_node * entry = table[i];
				while (entry != NULL)
				{
					prevEntry = entry;
					entry = entry->getNext();
					delete prevEntry;
				}
			}
		delete[] table;
	}
};

void printp(place * a)
{
	cout << a->code << " " << a->state << " " << a->city << " " << a->pop << " " << a->area << " " << a->latitude << " " << a->longitude << " " << a->extradist << " " << a->roadcode << endl;
}

struct connection
{
	string roadName, roadType;
	int end1, end2, mapnum;
	double length;

	connection(string rn, string rt, int e1, int e2, double l)
	{
		this->roadName = rn;
		this->roadType = rt;
		this->end1 = e1;
		this->end2 = e2;
		this->length = l;
	}
};

struct intersection
{
	double longitude, latitude, miles_from, distStart;
	string state, city;
	vector<connection *> roads;
	bool check;
	int location;

	intersection(double l, double la, double m, string s, string c)
	{
		this->longitude = l;
		this->latitude = la;
		this->miles_from = m;
		this->state = s;
		this->city = c;
		this->distStart = INT_MAX;
		this->check = false;
	}

	void addConnection(connection * c)
	{
		roads.push_back(c);
	}

	connection * getRoads(int i)
	{
		return this->roads[i];
	}

	int roadvSize()
	{
		return this->roads.size();
	}

	void printRoads(int num)
	{
		cout << "Roads leading away: \n";
		int end;
		for (int i = 0; i < this->roads.size(); i++)
		{
			if (roads[i]->end1 == num) end = roads[i]->end2;
			else if (roads[i]->end2 == num) end = roads[i]->end1;
			cout << i + 1 << ": " << roads[i]->length << " miles to location " << end << endl;
		}
		cout << endl;
	}

	void setDist(double dist)
	{
		this->distStart = dist;
	}

	double getDist()
	{
		return distStart;
	}
};

class queue
{
protected:
	vector<intersection *> node;

public:

	queue()
	{
	}

	void addNode(intersection * c)
	{
		node.push_back(c);
	}

	void popc()
	{
		node.pop_back();
	}

	bool empty()
	{
		if (node.empty()) return true;
		else return false;
	}

	bool inQ(intersection * a)
	{
		for (int i = 0; i < node.size(); i++)
		{
			if (node[i] == a) return true;
		}
		return false;
	}

	int qsize()
	{
		return node.size();
	}

	intersection * smallest() //find way to determine dist to start
	{
		intersection * curr = node.back();
		double small1 = curr->distStart;
		for (int i = 0; i < node.size(); i++)
		{
			if (node[i]->distStart < small1)
			{
				intersection * temp = curr;
				curr = node[i];
				node[i] = temp;
				small1 = curr->distStart;
			}
		}
		curr->check = true;
		node.pop_back();
		return curr;
	}
};

bool dubcompare(double a, double b)
{
	double margin = 0.001;
	if (abs(a - b) < margin) return true;
	else return false;
}

class map
{
protected:
	vector<intersection *> table;

public:
	map()
	{

	}

	void cleanup()
	{
		for(int i = 0; i < table.size(); i++)
		{
			table[i]->check = false;
			table[i]->distStart = INT_MAX;
		}
	}

	void addc(int loc, connection * c)
	{
		table[loc]->addConnection(c);
	}

	void add(intersection * a)
	{
		a->location = table.size();
		table.push_back(a);
	}

	void printMap()
	{
		for (int i = 0; i < table.size(); i++)
		{
			cout << table[i]->longitude << " " << table[i]->latitude << " " << table[i]->miles_from << " " << table[i]->state << " " << table[i]->city << endl;
		}
	}

	intersection * find(int location)
	{
		cout << "Location " << location << ", " << table[location]->miles_from << " miles from " << table[location]->city << ", " << table[location]->state << endl;
		return table[location];
	}

	int findNext(int location, int picked)
	{
		if (picked > table[location]->roads.size())
		{
			cout << "Road doesn't exist.\n";
			exit(1);
		}
		connection * temp = table[location]->roads[picked - 1];
		if (temp->end1 == location) return temp->end2;
		else if (temp->end2 == location) return temp->end1;
		cout << "Error, not valid input\n";
		exit(1);
	}

	void setup()
	{
		double longitude1, latitude1, miles_from1;
		string state1, citytemp, city1;
		ifstream finter("intersections.txt");
		intersection * testi;
		while (!finter.eof())
		{
			if (finter.fail())
			{
				cout << "FAIL\n";
				break;
			}
			finter >> longitude1 >> latitude1 >> miles_from1 >> state1;
			getline(finter, citytemp);
			city1 = citytemp.substr(1, citytemp.length() - 1);
			testi = new intersection(longitude1, latitude1, miles_from1, state1, city1);
			this->add(testi);
		}
		finter.close();

		string roadName1, roadType1;
		int enda, endb;
		double length1;
		ifstream fcon("connections.txt");
		connection * testc;
		while (!fcon.eof())
		{
			if (fcon.fail())
			{
				cout << "FAIL\n";
				break;
			}
			fcon >> roadName1 >> roadType1 >> enda >> endb >> length1;
			testc = new connection(roadName1, roadType1, enda, endb, length1);
			this->addc(enda, testc);
			this->addc(endb, testc);
		}
		fcon.close();
	}

	double shortestPath(int a, int b, string filename)
	{
		queue q;
		intersection * temp = NULL;
		if (a >= table.size() || b >= table.size())
		{
			cout << "Location not found\n";
			exit(1);
		}
		else if (a < 1 || b < 1)
		{
			cout << "Location not found\n";
			exit(1);
		}
		if (q.empty())
		{
			temp = table[a];
			temp->setDist(0);
			q.addNode(temp);
		}
		double eta;
		/////////////////////////////////////////////
		while (q.empty() == false)
		{
			cout << "LOOP" << endl;
			intersection * curr;
			//<< q.qsize() << endl;
			curr = q.smallest();
			//cout << q.qsize() << endl;
			eta = curr->getDist();
			cout << "Location " << curr->location << ", " << table[curr->location]->miles_from << " miles from " << table[curr->location]->city << ", " << table[curr->location]->state << endl;
			cout << "Calculating ETA: " << eta << endl;
			if (curr->location == b)
			{
				vector<intersection *> path;
				vector<connection *> way;
				path.push_back(curr);
				cout << "You are there" << endl; //path don't work
				bool breakp = false;
				while (curr->location != table[a]->location)
				{
					for (int h = 0; h < curr->roadvSize(); h++)
					{
						cout << curr->getDist() - curr->getRoads(h)->length << " versus " << table[curr->getRoads(h)->end2]->getDist() << " and " << table[curr->getRoads(h)->end1]->getDist() << endl;
						double pathfind = curr->getDist() - curr->getRoads(h)->length;
						if (dubcompare(pathfind, table[curr->getRoads(h)->end1]->getDist()))
						{
							way.push_back(curr->getRoads(h));
							curr = table[curr->getRoads(h)->end1]; //begin = end1
							if (curr->location == a)
							{
								breakp = true;
								cout << "break!\n";
								break;
							}
							path.push_back(curr);
							cout << curr->city << ", " << curr->state << endl;
							break;
						}
						if (dubcompare(pathfind, table[curr->getRoads(h)->end2]->getDist()))
						{
							way.push_back(curr->getRoads(h));
							curr = table[curr->getRoads(h)->end2];
							if (curr->location == a)
							{
								breakp = true;
								cout << "break!!!!!!!!!!!!!\n";
								break;
							}
							path.push_back(curr);
							cout << curr->city << ", " << curr->state << endl;
							break;
						}
						else if (h == curr->roadvSize() - 1)
						{
							breakp = true;
							cout << "break\n";
						}
					}
					if (breakp == true)
					{
						path.push_back(table[a]);
						for (int f = 0; f < curr->roadvSize(); f++)
						{
							if (dubcompare(curr->getDist(), curr->getRoads(f)->length))
							{
								way.push_back(curr->getRoads(f));
								cout << "Road added\n";
								break;
							}
						}
						break;
					}
				}
				cout << "Path: \n";
				for (int g = path.size() - 1; g >= 0; g--)
				{
					int d = g - 1;
					if (g >= 1)
					{
						cout << "Location " << path[g]->location << ", which is " << path[g]->miles_from << " miles from " << path[g]->city << ", " << path[g]->state << endl;
						cout << "take " << way[d]->roadName << " for " << way[d]->length << " miles to" << endl; // make work using above
					}
					else cout << "Location " << path[g]->location << ", which is " << path[g]->miles_from << " miles from " << path[g]->city << ", " << path[g]->state << endl;

				}
				cout << endl << "Total " << eta << " miles" << endl << endl << endl;
				ifstream line(filename, ios::in | ios::binary);
				int rows, cols, bytespixel, secondspixel, llongsec, toplatsecs;
				string r, c, bp, spix, llsec, tls;
				line >> r >> rows >> c >> cols >> bp >> bytespixel >> spix >> secondspixel >> llsec >> llongsec >> tls >> toplatsecs;
				//longsec/3600 is longitude and secondspixel is how many seconds in a pixel 
				//(llongsec, toplatsec) = (0,0); (llonsec - (long * 3600))/60     tls - lat 3600 
				cout << llongsec << endl;
				cout << (((path[path.size() - 1]->longitude * 3600) - llongsec) / secondspixel) << endl;
				cout << (-((path[path.size() - 1]->latitude * 3600) - toplatsecs) / secondspixel)<< endl;
				set_pen_width_color(3, color::black);
				cout << path[path.size() - 1]->longitude << endl;
				int t = path.size() - 1;
				move_to((((path[t]->longitude * 3600) - llongsec) / secondspixel), (-((path[t]->latitude * 3600) - toplatsecs) / secondspixel));
				write_string(table[a]->city);
				for(int y = 0; y < path.size(); y++)
				{ 
					move_to((((path[y]->longitude * 3600) - llongsec) / secondspixel), (-((path[y]->latitude * 3600) - toplatsecs) / secondspixel));
					draw_point();
					if (y < path.size() - 1)
					{
						draw_to((((path[y + 1]->longitude * 3600) - llongsec) / secondspixel), (-((path[y + 1]->latitude * 3600) - toplatsecs) / secondspixel));
					}
					
				}
				move_to((((path[0]->longitude * 3600) - llongsec) / secondspixel), (-((path[0]->latitude * 3600) - toplatsecs) / secondspixel));
				write_string(table[b]->city);
				return eta; 
			}
			cout << "Road vector size: " << curr->roadvSize() << endl;
			for (int k = 0; k < curr->roadvSize(); k++)
			{
				intersection * toPush;
				cout << curr->getRoads(k)->roadName << " the road from " << table[curr->getRoads(k)->end1]->location << " to " << table[curr->getRoads(k)->end2]->location << endl;
				if (curr->location == curr->getRoads(k)->end2)
				{
					toPush = table[curr->getRoads(k)->end1];
				}
				else if (curr->location == curr->getRoads(k)->end1)
				{
					toPush = table[curr->getRoads(k)->end2];
				}
				double neweta = eta + curr->getRoads(k)->length;
				//cout << toPush->getDist() << endl;
				if (toPush->getDist() > neweta) toPush->setDist(neweta);
				cout << toPush->location << " checked? " << toPush->check << endl; 
				if (toPush->check == false)
				{
					if (q.inQ(toPush) == true)
					{
						cout << "Already in queue\n";
					}
					else
					{
						q.addNode(toPush);
						cout << "pushed " << toPush->location << endl;
					}

				}

			}
			cout << "in queue: " << q.qsize() << endl;
			//delete curr;

		}
		cout << table[b]->city << ", " << table[b]->state << " cannot be reached from " << table[a]->city << ", " << table[a]->state << endl;
		return -1;
	}

};

struct fileDetails
{
	int west1, west2, north1, north2;
	string fileName;
};

class graph
{
protected:
	hash_table places;
	map america;

public:
	graph()
	{
		places.setup();
		america.setup();
	}

	string graphics(string cityA, string stateA, string cityB, string stateB)
	{
		
		double Wdiff, Ndiff, W1,W2, N1, N2; // W longtiude N latitude
		/*Wdiff = abs(abs((america.find(places.find(cityA, stateA)->roadcode)->longitude)) - abs(america.find(places.find(cityB, stateB)->roadcode)->longitude));   //num for latitude 70 - 130 multiples of 5
		Ndiff = abs(abs(america.find(places.find(cityA, stateA)->roadcode)->latitude) - abs(america.find(places.find(cityB, stateB)->roadcode)->latitude));
		D = Wdiff; 
		if (Ndiff > Wdiff) D = Ndiff;
		if (D <= 5) D = 5;
		if (D > 5 && D <= 10) D = 10;
		if (D > 10 && D <= 20) D = 20;
		if (D > 20 && D <= 30) D = 30;
		if (D > 30 && D <= 60) D = 60;
		if (D > 60) D = 80;
		if ((america.find(places.find(cityA, stateA)->roadcode)->longitude) > (america.find(places.find(cityB, stateB)->roadcode)->longitude)) W = (america.find(places.find(cityA, stateA)->roadcode)->longitude);
		else W = (america.find(places.find(cityB, stateB)->roadcode)->longitude);
		if (((america.find(places.find(cityA, stateA)->roadcode)->latitude)) > ((america.find(places.find(cityB, stateB)->roadcode)->latitude))) N = (america.find(places.find(cityA, stateA)->roadcode)->latitude);
		else N = (america.find(places.find(cityB, stateB)->roadcode)->latitude); // BRUTE FORCE SORT
		if (W <= 70) W = 70;
		if (W > 70 && W <= 75) W = 75;
		if (W > 75 && W <= 80) W = 80;
		if (W > 80 && W <= 85) W = 85;
		if (W > 85 && W <= 90) W = 90;
		if (W > 90 && W <= 95) W = 95;
		if (W > 95 && W <= 100) W = 100;
		if (W > 100 && W <= 105) W = 105;
		if (W > 105 && W <= 110) W = 110;
		if (W > 110 && W <= 115) W = 115;
		if (W > 115 && W <= 120) W = 120;
		if (W > 120 && W <= 125) W = 125;
		if (W > 125) W = 130;
		if (N <= 25) N = 25;
		if (N > 25 && N <= 30) N = 30;
		if (N > 30 && N <= 35) N = 35;
		if (N > 35 && N <= 40) N = 40;
		if (N > 40 && N <= 45) N = 45;
		if (N > 45) N = 50;
		 //num for longitude 25 - 50 multiples of 5
		//average abs((america.find(places.find(cityA, stateA)->roadcode)->longitude) + (america.find(places.find(cityB, stateB)->roadcode)->longitude))/(int)10) * 5; 
		string description = "usaW";
		stringstream iss;
		iss << description;
		iss << W;
		iss << 'N';
		iss << N;
		iss << 'D';
		iss << D; //greatest difference between longs or lats in 5, 10, 20, 30, 60, or 80 abs(america.find(places.find(cityA, stateA)->roadcode)->longitude - america.find(places.find(cityB, stateB)->roadcode)->longitude)
		string dat = ".dat";
		iss << dat;
		
		iss >> out;
		if (D == 20) out = "usaW125N50D20.dat";
		if (D == 30) out = "usaW125N50D30.dat";
		if (D == 60) out = "usaW125N50D60.dat";
		if (D == 80) out = "usaW130N50D80.dat";*/// function Have it go through  loop of file with all file names, if out doesnt match return false and have it make out whole country
		string file, out = "1";
		//OTHER EXCEPTIONS????????????// keep in mind alaska and puerto rico and hawaii not far from each other but require the whole map
		W1 = america.find(places.find(cityA, stateA)->roadcode)->longitude;
		W2 = america.find(places.find(cityB, stateB)->roadcode)->longitude;
		N1 = america.find(places.find(cityA, stateA)->roadcode)->latitude;
		N2 = america.find(places.find(cityB, stateB)->roadcode)->latitude;
		ifstream coverage("coverage.txt");
		int wbound1, wbound2, nbound1, nbound2;
		vector<fileDetails*> files;
		while (!coverage.eof())
		{
			fileDetails * testf = new fileDetails;
			coverage >> nbound1 >> nbound2 >> wbound1 >> wbound2 >> file;
			testf->north1 = nbound1;
			testf->north2 = nbound2;
			testf->west1 = wbound1;
			testf->west2 = wbound2;
			testf->fileName = file;
			files.push_back(testf);
		}
		for (int i = 0; i < files.size() - 1; i++)
		{
			int first = i;

			for (int j = i + 1; j < files.size(); j++)
			{

				if (files[j]->west1 > files[first]->west1) first = j;
				if(files[j]->west1 == files[first]->west1)
				{
					if (files[j]->north2 < files[first]->north2) first = j;
					if(files[j]->north2 == files[first]->north2)
					{
						if ((files[j]->north1 - files[j]->north2) < (files[first]->north1 - files[first]->north2)) first = j;
					}
				}
			}
			if (first != i)
			{
				fileDetails * temp = files[i];
				files[i] = files[first];
				files[first] = temp;
			}
		}
		for(int i = 0; i < files.size(); i++)
		{
			if (W1 >= files[i]->west1 && W1 < files[i]->west2 && W2 >= files[i]->west1 && W2 < files[i]->west2 && N1 <= files[i]->north1 && N1 > files[i]->north2 && N2 <= files[i]->north1 && N2 > files[i]->north2)
			{
				if (files[i]->fileName == "usaW130N50D80.dat" && out == "usaW125N50D60.dat") break;
				out = files[i]->fileName;
				if (files[i]->fileName == "usaW125N50D60.dat" || files[i]->fileName == "usaW130N50D80.dat") continue;
				else break;
			}
		}
		if (stateA == " AK" || stateB == "AK" || stateA == "HI" || stateB == "HI") out = "usaW130N50D80.dat";
		cout << out << endl;

		
		ifstream fin(out/*"usaW125N50D60.dat"*/, ios::in | ios::binary);
		
		if (fin.fail())
		{
			cerr << "can't open it\n";
			exit(1);
		}
		string c, b;
		int rows, cols, bytespixel, secondspixel, llongsec, toplatsecs, min, max;
		string r, co, bp, spix, llsec, tls, mins, maxs;
		fin >> r >> rows >> co >> cols >> bp >> bytespixel >> spix >> secondspixel >> llsec >> llongsec >> tls >> toplatsecs >> mins >> min >> maxs >> max;
		int sizeofline = cols * sizeof(short int);
		short int * a = new short int[cols];
		fin.read((char *)a, sizeofline);
		a[cols - 1] = 0;
		istringstream is((char *)a);
		cout << (char *)a << "\n";
		make_window(cols, rows);
		fin.seekg(cols * bytespixel, ios::beg);
		for (int i = 0; i < rows; i += 1)
		{
			//short int * b = new short int[cols];
			fin.read((char *)a, sizeofline);
			if (fin.fail())
				break;
			for (int j = 0; j < cols; j += 1) // drawing 10 extra cols
			{
				int ht = a[j];
				int col;
				if (ht == -500) col = color::blue;
				else if (ht >= 3 * max/ 4) col = color::brown;
				else if (ht > max / 4) col = color::orange;
				else if (ht > max/8) col = color::dark_green;
				else if (ht > 0) col = color::green;
				else col = color::yellow;
				set_pixel_color(j, i, col);
			}
		}
		fin.close();
		return out;
	}

	double path(string cityA, string stateA, string cityB, string stateB)
	{
		if (places.find(cityA, stateA) == NULL || places.find(cityB, stateB) == NULL)
		{
			cout << "Not Found. Try Again...\n";
			return 0;
		}
		int pointA = places.find(cityA, stateA)->roadcode;
		int pointB = places.find(cityB, stateB)->roadcode;
		string filename = graphics(cityA, stateA, cityB, stateB);
		double journey = america.shortestPath(pointA, pointB, filename);
		journey += places.find(cityA, stateA)->extradist + places.find(cityB, stateB)->extradist;
		america.cleanup();
		return journey;
	}

};

void main()
{
	graph maps;
	string line1, state1, city1;
	string line2, state2, city2;
	cout << "To search, type city name and state on one line (e.g. Coral Gables FL)\n";
	while (true)
	{
		cout << "Choose Location: ";
		getline(cin, line1);
		state1 = line1.substr(line1.length() - 2, 2);
		city1 = line1.substr(0, line1.length() - 3);
		cout << city1 << " " << state1<< endl;
		
		cout << "Choose Destination: ";
		getline(cin, line2);
		state2 = line2.substr(line2.length() - 2, 2);
		city2 = line2.substr(0, line2.length() - 3);
		cout << city2 << " " << state2 << endl;

		maps.path(city1, state1, city2, state2);
		cout << endl << endl;
	}
}
