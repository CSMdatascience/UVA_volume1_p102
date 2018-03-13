/*	This problem is from the UVA Online Judge problem set volume 1 (100-199)
URL:	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=38

From the assignment sheet:

"
Input
The input consists of a series of lines with each line containing 9 integers. The first three integers on a
line represent the number of brown, green, and clear bottles (respectively) in bin number 1, the second
three represent the number of brown, green and clear bottles (respectively) in bin number 2, and the
last three integers represent the number of brown, green, and clear bottles (respectively) in bin number
3. For example, the line
10 15 20 30 12 8 15 8 31
indicates that there are 20 clear bottles in bin 1, 12 green bottles in bin 2, and 15 brown bottles in bin
3.
Integers on a line will be separated by one or more spaces. Your program should process all lines in
the input file.
Output
For each line of input there will be one line of output indicating what color bottles go in what bin
to minimize the number of bottle movements. You should also print the minimum number of bottle
movements.
The output should consist of a string of the three upper case characters ‘G’, ‘B’, ‘C’ (representing
the colors green, brown, and clear) representing the color associated with each bin.
The first character of the string represents the color associated with the first bin, the second character
of the string represents the color associated with the second bin, and the third character represents the
color associated with the third bin.
The integer indicating the minimum number of bottle movements should follow the string.
If more than one order of brown, green, and clear bins yields the minimum number of movements
then the alphabetically first string representing a minimal configuration should be printed.

Sample Input
1 2 3 4 5 6 7 8 9
5 10 5 20 10 5 10 20 10

Sample Output
BCG 30
CBG 50
"
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <string>
#include <utility>

using namespace std;

//Bins hold quantities of brown, green, and clear bottles at start of program
struct Bin
{
		long long int b, g, c;
};

//split takes a line of user input and populates Bins with bottle quantities by color
void split(const string& bottles, Bin &bin1, Bin &bin2, Bin &bin3) 
{
	auto count = 0;
	auto i = 0;
	auto pos = bottles.find(' ');
	while (count < 9) 
	{
		if (count == 0)
		{
			bin1.b = stoi(bottles.substr(i, pos - i));
			count++;
		}
		else if (count == 1)
		{
			bin1.g = stoi(bottles.substr(i, pos - i));
			count++;
		}
		else if (count == 2)
		{
			bin1.c = stoi(bottles.substr(i, pos - i));
			count++;
		}
		else if (count == 3)
		{
			bin2.b = stoi(bottles.substr(i, pos - i));
			count++;
		}
		else if (count == 4)
		{
			bin2.g = stoi(bottles.substr(i, pos - i));
			count++;
		}
		else if (count == 5)
		{
			bin2.c = stoi(bottles.substr(i, pos - i));
			count++;
		}
		else if (count == 6)
		{
			bin3.b = stoi(bottles.substr(i, pos - i));
			count++;
		}
		else if (count == 7)
		{
			bin3.g = stoi(bottles.substr(i, pos - i));
			count++;
		}
		else if (count == 8)
		{
			bin3.c = stoi(bottles.substr(i, string::npos));
			count++;
		}
		else
			break;
		i = ++pos;
		pos = bottles.find(' ', pos);
	}
}

//find the number of moves associated with each possible packing order
void sumMoves(Bin bin1, Bin bin2, Bin bin3, vector<pair <string, long long int>> &orders)
{	
	orders.at(0) = make_pair("BGC", bin2.b + bin3.b + bin1.g + bin3.g + bin1.c + bin2.c);
	orders.at(1) = make_pair("BCG", bin2.b + bin3.b + bin1.c + bin3.c + bin1.g + bin2.g);
	orders.at(2) = make_pair("GBC", bin2.g + bin3.g + bin1.b + bin3.b + bin1.c + bin2.c);
	orders.at(3) = make_pair("GCB", bin2.g + bin3.g + bin1.c + bin3.c + bin1.b + bin2.b);
	orders.at(4) = make_pair("CBG", bin2.c + bin3.c + bin1.b + bin3.b + bin1.g + bin2.g);
	orders.at(5) = make_pair("CGB", bin2.c + bin3.c + bin1.g + bin3.g + bin1.b + bin2.b);
}

//this function allows us to sort our pairs of order names and # of moves by "second" value, i.e. # of moves
bool sortbysec(const pair<string, long long int> &a, const pair<string, long long int> &b)
{
	return (a.second < b.second);
}

//find minimum number of moves and print result
//in the case of a tie print order that comes first alphabetically, i.e. by "first" value in pair
void findMin(vector<pair<string, long long int>> &orders)
{	
	//this pair will hold the final result
	pair<string, long long int> min;
	//first we sort by number of moves
	sort(orders.begin(), orders.end(), sortbysec);
	//store this pair in "min" 
	min = orders.at(0);
	//in the case of a tie, sort order names alphabetically and assign result to min
	for (unsigned int i = 1; i < orders.size(); i++)
		if (orders.at(i).second == orders.at(0).second && orders.at(i).first < orders.at(0).first)
			min = orders.at(i);
	cout << min.first << " " << min.second << endl;
}

int main()
{
	//holds entire line of user input
	string bottles;
	//these vectors represent three separate bins
	Bin bin1, bin2, bin3;
	//vector of pair
	vector<pair<string,long long int>> orders(6);	
	//get user input
	getline(cin, bottles);
	//parse user input
	split(bottles, bin1, bin2, bin3);
	//find number of moves associated with each possible packing order
	sumMoves(bin1, bin2, bin3, orders);
	//find the order with least moves and print result
	findMin(orders);
	return 0;
}

/* Sample execution:
1 2 3 4 5 6 7 8 9
BCG 30
Press any key to continue . . .

5 10 5 20 10 5 10 20 10
CBG 50
Press any key to continue . . .

2147483647 2147483647 2147483647 2147483647 2147483647 2147483647 2147483647 2147483647 2147483647
BCG 12884901882
Press any key to continue . . .

*/