#include"MFuncs.h"
#include<fstream>
#include<string>
vector<vector<long double>>input(string path)
{
	vector<vector<long double>>res;
	pair<int, int>size;
	double x;
	fstream file;
	file.open(path);
	file >> size.first >> size.second;
	for (int i = 0; i < size.first; i++)
	{
		res.push_back(vector<long double>());
		for (int j = 0; j < size.second; j++)
		{
			file >> x;
			res[i].push_back(x);
		}
	}
	return res;
}


void Check(vector<vector<long double>>matrix, vector<long double>res)
{
	long double ur = 0;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size() - 1; j++)
		{
			ur += res[j] * matrix[i][j];
		}
		cout << "Ur" << i << " = " << ur << "   ";
		ur = 0;
	}
}

void uiGaus()
{
	vector<vector<long double>>matrix = input("C:/Users/valya/Documents/CHM/Gaus.txt");
	vector<long double>res;
	res = MathFuncs::Gaus(matrix);
	cout << endl << endl << endl;
	for (int i = 0; i < res.size(); i++)
	{
		cout << "x " << i << " = " << res[i] << "    ";
	}

	cout << endl << endl;
	Check(matrix, res);

}
void uiProg()
{
	vector<vector<long double>>matrix = input("C:/Users/valya/Documents/CHM/Progonka.txt");
	vector<long double>res;
	cout << matrix;
	res = MathFuncs::Progonka(matrix);
	cout << endl << endl << endl;
	for (int i = 0; i < res.size(); i++)
	{
		cout << "x " << i << " = " << res[i] << "    ";
	}

	cout << endl << endl;
	Check(matrix, res);
}

void uIterations()
{
	long double eps;
	vector<vector<long double>>matrix = input("C:/Users/valya/Documents/CHM/Iter.txt");
	vector<long double>res;
	cout << "eps: ";
	cin >> eps;
	cout << endl << endl << matrix;
	res = MathFuncs::Iterations(matrix, eps);
	cout << endl << endl << endl;
	for (int i = 0; i < res.size(); i++)
	{
		cout << "x " << i << " = " << res[i] << "    ";
	}

	cout << endl << endl;
	Check(matrix, res);
}


void uiZey()
{
	long double eps;
	vector<vector<long double>>matrix = input("C:/Users/valya/Documents/CHM/Iter.txt");
	vector<long double>res;
	cout << "eps: ";
	cin >> eps;
	cout << endl << endl << matrix;
	res = MathFuncs::Zeyd(matrix, eps);
	cout << endl << endl << endl;
	for (int i = 0; i < res.size(); i++)
	{
		cout << "x " << i << " = " << res[i] << "    ";
	}

	cout << endl << endl;
	Check(matrix, res);
}
