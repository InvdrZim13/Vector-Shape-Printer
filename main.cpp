#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

void buildVector(ifstream&);
void printShapes();

vector<vector<char>> v1; //global 2D vector

int main()
{
	ifstream inFile;
	inFile.open("data.txt");
	string data;
	cout << "Enter the name of the data file: ";
	cin >> data;
	while (!inFile.eof()) //Runs functions until the end of the data file
	{
		buildVector(inFile);
		printShapes();
	}
	inFile.close();
	system("pause");
	return 0;

}

void buildVector(ifstream& infile)
{
	string command;
	char read='\0', output = '*';
	int rows, columns;
	bool isgo = false, outer = false, triangle = false, alphabetical = false;

	v1.clear();

	while (!isgo)
	{
		if (!infile.eof())
			infile.get(read);
		if (isdigit(read)); //If a digit is read, loop restarts
		else if (isspace(read)); //If a space is read, loop restarts
		else
		{
			infile.unget();
			infile >> command;

			//Each if/else if here checks for a command and parses it accordingly
			if (command == "rows") //Checks if the command read is for number of rows
			{
				while (!isdigit(read))
				{
					infile.unget(); //Goes back from current read
					infile.get(read);
					if (!isdigit(read))
						infile.unget();
				}
				infile.unget();
				infile >> rows;
				while (read != 's') //checks for end of columns (the s)
					infile.get(read);
			}
			else if (command == "columns") //Checks if the commaned readnis for number of columns
			{
					while (!isdigit(read))
					{
						infile.unget();
						infile.get(read);
						if (!isdigit(read))
							infile.unget();
					}
					infile.unget();
					infile >> columns;
					while (read != 's')
						infile.get(read);
			}
			//These statements check for the shape commands, hollow or not, aphabetical printing, and the go command, which tells the program to make that shape
			else if (command == "triangular")
				triangle = true;
			else if (command == "all")
				infile >> output;
			else if (command == "go")
				isgo = true;
			else if (command == "outer")
				outer = true;
			else if (command == "alphabetical")
			{
				alphabetical = true;
				output = 'A';
			}
		}
		}
	v1.resize(rows);

	int maxj;
	for (int i = 0; i < rows; i++) 
	{
		if (triangle)
			maxj = i + 1;
		else
			maxj = columns;
		v1[i].resize(maxj); //Resizes 1D vector
		for (int j = 0; j < maxj; j++)
		{
			if (outer && !(i == 0 || i == rows - 1) && !(j == 0 || j == maxj - 1))
				v1[i][j] = ' ';
			else
			{
				v1[i][j] = output;
				if (alphabetical)
					output++;
			} //Takes all of parsed data and prepares it for the output function
		}
	}
	return;
}

void printShapes()
{
	for (vector<vector<char>>::iterator it = v1.begin(); it != v1.end(); ++it)
	{
		for (vector<char>::iterator iter = (*it).begin(); iter != (*it).end(); ++iter)
		{
			cout << (*iter) << " ";
		}
		cout << endl;
	}
	cout << endl;
	return;
}
