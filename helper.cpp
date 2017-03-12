#include <iostream>
#include <vector>
#include <math.h>


using namespace std;

typedef vector< vector<double> > Matrix;

void build_vectors(Matrix& X, Matrix& Y)
{
  // Build X
  vector<double> x0 = {1, 0, 0};
  vector<double> x1 = {1, 0, 1};
  vector<double> x2 = {1, 1, 0};
  vector<double> x3 = {1, 1, 1};

  X.push_back(x0);
  X.push_back(x1);
  X.push_back(x2);
  X.push_back(x3);

  // Build Y
  vector<double> y0 = {0};
  vector<double> y1 = {1};
  vector<double> y2 = {1};
  vector<double> y3 = {0};

  Y.push_back(y0);
  Y.push_back(y1);
  Y.push_back(y2);
  Y.push_back(y3);

}


Matrix activate(Matrix M1, bool deriv=false)
{
  Matrix new_matrix;

  // Fill in dot matrix with 0's
  for (int i=0; i < M1.size(); i++)
  {
    vector<double> new_row;
    for (int j=0; j < M1[i].size(); j++)
    {
      new_row.push_back(0.0);
    }
    new_matrix.push_back(new_row);
  }



  // Activate
  for (int i=0; i < M1.size(); i++)
  {
    for (int j=0; j < M1[i].size(); j++)
    {
      if (deriv)
      {
        new_matrix[i][j] = exp(-M1[i][j]) * (1 - exp(-M1[i][j]));
      }
      else
      {
        new_matrix[i][j] = 1 / (1 + exp(-M1[i][j]));
      }
    }
  }

  return new_matrix;
}
