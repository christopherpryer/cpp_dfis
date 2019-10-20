#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
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

/*
𝐴𝐷𝐼=𝑝𝑛/𝑑𝑛
𝑝𝑛 : number of periods
𝑑𝑛 : number of demands
𝐴𝐷𝐼 : Average Demand Interval
*/
double calculateADI(matrix &M, int qCol)
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
   return adi;
}

/*
𝐶𝑉2=(𝜎𝑝/𝜇𝑝)2
𝜎𝑝: standard deviation of population
𝜇𝑝: average of population
𝐶𝑉2: coefficient of variation
*/
double calculateCV2(matrix &M, int qCol)
{
   int rowCount = 0;
   int total = 0;
   int count = 0;
   for (vec &row: M)
   {
       if (rowCount > 0)
      {
         total+=std::stoi(row[2]);
         count++;
      }
      rowCount++;
   }

   rowCount = 0;
   float var = 0.0;
   float mean = (float)total/(float)count;
   for (vec &row: M)
   {
       if (rowCount > 0)
      {
         int val = std::stoi(row[2]); 
         var += (val - mean) * (val - mean);
      }
      rowCount++;
   }

   var /= count;
   float cv2 = pow((sqrt(var)/mean), 2);
   return cv2;
}

int main()
{
   matrix data = readCSV("test_data.csv");
   
   printMatrix(data);
   float adi = calculateADI(data, 2);
   float cv2 = calculateCV2(data, 2);

   printf("adi:\t%f\n", adi);
   printf("cv2:\t%f\n", cv2);
   
   bool isSmooth = false;
   if ((adi < 1.32) && (cv2 < 0.49))
   {
      isSmooth = true;
   }
   printf("is smooth:\t%i\n", isSmooth);
}