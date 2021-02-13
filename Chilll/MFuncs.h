//
// Created by valya on 07.02.2021.
//
#pragma once
#include<vector>
#include<iostream>
#include<iterator>

using namespace std;

void operator-(vector<long double>& x, vector<long double>y)
{
    for (int i = min(x.size(), y.size()) - 1; i >= 0; i--)
    {
        x[i] -= y[i];
    }
}

void operator/(vector<long double>& x, long double y)
{
    for (int i = x.size() - 1; i >= 0; i--)
    {
        x[i] /= y;
    }
}

std::ostream& operator<< (std::ostream& out, const vector<vector<long double>> matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
            out << matrix[i][j] << '\t';
        out << endl;
    }
    return out;
}











class MathFuncs
{
private:
    static double ai(vector<vector<long double>>& m, int i)
    {
        return m[i][i - 1];
    }

    static double bi(vector<vector<long double>>& m, int i)
    {
        return m[i][i];
    }


    static double ci(vector<vector<long double>>& m, int i)
    {
        return m[i][i + 1];
    }


    static double di(vector<vector<long double>>& m, int i)
    {
        return m[i][m[i].size() - 1];
    }


    static void Findmaxim(vector<vector<long double>>& matrix, int i)
    {
        int k = -1;
        long double max = 0;
        for (int j = i; j < matrix.size(); j++)
        {
            if (abs(matrix[j][i]) > abs(max))
            {
                max = matrix[j][i];
                k = j;
            }
        }

        if ((k >= 0) && (k != i))
        {
            swap(matrix[i], matrix[k]);
            cout << endl << k << endl;
        }
        else
            cout << endl << i << endl;
    }











public:
    static vector<long double>Gaus(vector<vector<long double>>matrix)
    {
        bool pass = 1;
        int k = -1;
        vector<long double>res;
        long double resbuf = 0;

        cout << matrix << endl << endl;
        for (int i = 0; i < matrix.size(); i++)
        {
            Findmaxim(matrix, i);

            for (int j = i; j < matrix.size(); j++)
            {
                if (matrix[j][i] != 0)
                    matrix[j] / matrix[j][i];
            }
            for (int j = i + 1; j < matrix.size(); j++)
            {
                if (matrix[j][i] != 0)
                    matrix[j] - matrix[i];
            }
            cout << matrix << endl << endl;
        }
        for (int i = matrix.size() - 1; i >= 0; i--)
        {
            resbuf += matrix[i][matrix[i].size() - 1];
            for (int j = res.size() - 1; j >= 0; j--)
            {
                resbuf -= matrix[i][matrix[i].size() - 2 - j] * res[j];
            }
            res.push_back(resbuf);
            resbuf = 0;
        }
        std::reverse(res.begin(), res.end());
        return res;
    }







    static vector<long double>Progonka(vector<vector<long double>>matrix)
    {
        vector<long double>res = vector<long double>(matrix.size(), 0);
        vector<double> P, Q;
        double znam, chil;
        P = vector<double>(matrix.size(), 0);
        Q = P;
        P[0] = -ci(matrix, 0) / bi(matrix, 0);
        Q[0] = di(matrix, 0) / bi(matrix, 0);

        cout << "P0 = " << P[0] << "     ";
        cout << "Q0 = " << Q[0] << endl;

        P[P.size() - 1] = 0;
        for (int i = 1; i < P.size() - 1; i++)
        {
            znam = (bi(matrix, i) + ai(matrix, i) * P[i - 1]);
            P[i] = -ci(matrix, i) / znam;

            Q[i] = (di(matrix, i) - ai(matrix, i) * Q[i - 1]) / znam;

            cout << "P" << i << " = " << P[i] << "     " << "Q" << i << " = " << Q[i] << endl;

        }
        Q[Q.size() - 1] = (di(matrix, matrix.size() - 1) - ai(matrix, matrix.size() - 1) * Q[Q.size() - 2]) / (bi(matrix, matrix.size() - 1) + ai(matrix, matrix.size() - 1) * P[P.size() - 2]);
        res.back() = Q.back();

        cout << endl;

        for (int i = matrix.size() - 2; i >= 0; i--)
        {
            res[i] = P[i] * res[i + 1] + Q[i];
        }
        return res;
    }








    static vector<long double>Iterations(vector<vector<long double>>matrix, long double& eps)
    {
        bool pass = 0;
        long double epscheck = 0, xiibuf = 0;

        vector<vector<double>>xi;
        vector<long double>res;


        xi.push_back(vector<double>());

        for (int i = 0; i < matrix.size(); i++)
            xi[0].push_back(di(matrix, i)/*0*/);

        int curi = 1;
        while (!pass)
        {
            xi.push_back(vector<double>());
            for (int i = 0; i < matrix.size(); i++)
            {
                for (int j = 0; j < matrix[i].size() - 1; j++)
                {
                    if (i != j)
                        xiibuf -= matrix[i][j] * xi[curi - 1][j];
                }
                xiibuf += di(matrix, i);
                xiibuf /= matrix[i][i];
                xi[curi].push_back(xiibuf);
                xiibuf = 0;
            }

            for (int k = 0; k < xi[curi].size(); k++)
            {
                if (abs(xi[curi][k] - xi[curi - 1][k]) > epscheck)
                    epscheck = abs(xi[curi][k] - xi[curi - 1][k]);
            }
            if (epscheck <= eps)
            {
                pass = 1;
                eps = epscheck;
            }
            epscheck = 0;
            curi++;
        }

        for (int i = 0; i < xi.back().size(); i++)
            res.push_back(xi.back()[i]);
        return res;
    }





    static vector<long double>Zeyd(vector<vector<long double>>matrix, long double& eps)
    {
        bool pass = 0;
        long double epscheck = 0, xiibuf = 0;

        vector<vector<double>>xi;
        vector<long double>res;


        xi.push_back(vector<double>());

        for (int i = 0; i < matrix.size(); i++)
            xi[0].push_back(di(matrix, i)/*0*/);

        int curi = 1;
        while (!pass)
        {
            xi.push_back(vector<double>());
            for (int i = 0; i < matrix.size(); i++)
            {
                for (int j = 0; j < matrix[i].size() - 1; j++)
                {
                    if (j < i)
                        xiibuf -= matrix[i][j] * xi[curi][j];
                    else if (j > i)
                        xiibuf -= matrix[i][j] * xi[curi - 1][j];
                }
                xiibuf += di(matrix, i);
                xiibuf /= matrix[i][i];
                xi[curi].push_back(xiibuf);
                xiibuf = 0;
            }

            for (int k = 0; k < xi[curi].size(); k++)
            {
                if (abs(xi[curi][k] - xi[curi - 1][k]) > epscheck)
                    epscheck = abs(xi[curi][k] - xi[curi - 1][k]);
            }
            if (epscheck <= eps)
            {
                pass = 1;
                eps = epscheck;
            }
            epscheck = 0;
            curi++;
        }

        for (int i = 0; i < xi.back().size(); i++)
            res.push_back(xi.back()[i]);
        return res;
    }
};