#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

typedef vector< vector<double> > Matrix;

void initializeMatrix(Matrix& W, int rows, int cols)
{
  srand(5);
  for (int i=0; i < rows; i++)
  {
    vector<double> new_row;
    for (int j=0; j < cols; j++)
    {
      double val = 2 * ((double) rand() / (RAND_MAX)) - 1;
      new_row.push_back(val);
    }
    W.push_back(new_row);
  }
}




Matrix transpose(Matrix&M1)
{
  Matrix transpose_matrix;

  // Fill in dot matrix with 0's
  for (int i=0; i < M1[0].size(); i++)
  {
    vector<double> new_row;
    for (int j=0; j < M1.size(); j++)
    {
      new_row.push_back(0.0);
    }
    transpose_matrix.push_back(new_row);
  }

  // Transpose
  for (int i=0; i < M1.size(); i++)
  {
    for (int j=0; j < M1[i].size(); j++)
    {
        transpose_matrix[j][i] = M1[i][j];
    }
  }

  return transpose_matrix;
}





Matrix scalar_multiply(double scalar, Matrix& M1)
{
  Matrix scalar_mul_matrix;

  // Fill in dot matrix with 0's
  for (int i=0; i < M1.size(); i++)
  {
    vector<double> new_row;
    for (int j=0; j < M1[i].size(); j++)
    {
      new_row.push_back(0.0);
    }
    scalar_mul_matrix.push_back(new_row);
  }

  // Apply Scalar
  for (int i=0; i < M1.size(); i++)
  {
    for (int j=0; j < M1[i].size(); j++)
    {
        scalar_mul_matrix[i][j] = scalar * M1[i][j];
    }
  }

  return scalar_mul_matrix;

}





Matrix dot(Matrix&M1, Matrix&M2)
{
  Matrix dot_matrix;

  // Fill in dot matrix with 0's
  for (int i=0; i < M1.size(); i++)
  {
    vector<double> new_row;
    for (int j=0; j < M2[0].size(); j++)
    {
      new_row.push_back(0.0);
    }
    dot_matrix.push_back(new_row);
  }

  // Dot product
  for (int i=0; i < M1.size(); i++)
  {
    for (int j=0; j < M2[0].size(); j++)
    {
      double sum = 0.0;
      for (int k=0; k < M2.size(); k++)
      {
        double val1 = M1[i][k];
        double val2 = M2[k][j];
        sum += val1 * val2;
      }
      dot_matrix[i][j] = sum;
    }
  }
  return dot_matrix;
}





Matrix matrix_operation(Matrix& M1, Matrix& M2, string operation)
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

  // Operation
  for (int i=0; i < M1.size(); i++)
  {
    for (int j=0; j < M1[i].size(); j++)
    {
      if (operation == "add")
      {
          new_matrix[i][j] = M1[i][j] + M2[i][j];
      }
      else if (operation == "subtract")
      {
          new_matrix[i][j] = M1[i][j] - M2[i][j];
      }
      else if (operation == "multiply")
      {
          new_matrix[i][j] = M1[i][j] * M2[i][j];
      }
    }
  }

  return new_matrix;
}


Matrix add(Matrix& M1, Matrix& M2)
{
  return matrix_operation(M1, M2, "add");
}

Matrix subtract(Matrix& M1, Matrix& M2)
{
  return matrix_operation(M1, M2, "subtract");
}

Matrix multiply(Matrix& M1, Matrix& M2)
{
  return matrix_operation(M1, M2, "multiply");
}
