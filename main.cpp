#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

using vec = vector<string>;
using matrix = vector<vec>;

matrix readCSV(string filename)
{
   char separator = ',';
   matrix result;
   string row, item;

   ifstream in(filename);
   while(getline(in,row))
   {
      vec R;
      stringstream ss(row);
      while (getline(ss, item, separator)) R.push_back(item);
      result.push_back(R);
   }
   in.close();
   return result;
}

void printMatrix(const matrix &M)
{
   for (vec row : M)
   {
      for (string s: row) cout << setw(12) << left << s << " ";
      cout << '\n';
   }
}

void deleteRow(matrix &M, int row)
{
   if (row < M.size()) M.erase(M.begin() + row);
}

void deleteCol(matrix &M, int col)
{
   for (vec &row: M)
   {
      if (col < row.size()) row.erase(row.begin() + col);
   }
}

void edit(matrix &M, int i, int j, string value)
{
   if (i < M.size() && j < M[i].size()) M[i][j] = value;
}

void calculateADI(matrix &M, int pCol, int qCol)
{
   int rowCount = 0;
   float adi;
   int numPeriods = 0;
   int numDemands = 0;

   for (vec &row: M)
   {
      if (rowCount > 0)
      {
         numPeriods++;
         numDemands+=std::stoi(row[2]);
      }
      rowCount++;
   }

   adi = (float)numPeriods/(float)numDemands;
   printf("%f\n", adi);
}

int main()
{
   matrix data = readCSV("test_data.csv");
   
   printMatrix(data);
   calculateADI(data, 1, 2);
}