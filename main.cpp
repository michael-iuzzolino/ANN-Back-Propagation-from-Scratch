#include <iostream>
#include <stdlib.h>
#include "helper.cpp"
#include "matrix.cpp"
#include <vector>

using namespace std;

typedef vector< vector<double> > Matrix;



Matrix calculate_error(Matrix Y, Matrix Y_hat, double& average_error)
{
  Matrix error = subtract(Y, Y_hat);

  double sum = 0.0;
  for (int i=0; i < error.size(); i++)
  {
    for (int j=0; j < error[i].size(); j++)
    {
      sum += fabs(error[i][j]);
    }
  }
  average_error = sum / error.size();

  return error;
}


void print_matrix(Matrix& M)
{
  for (int i=0; i < M.size(); i++)
  {
    for (int j=0; j < M[i].size(); j++)
    {
      cout << M[i][j] << ", ";
    }
    cout << endl;
  }
}


void run(Matrix& W0, Matrix& W1, Matrix X, Matrix Y)
{
  double average_error;
  double alpha = 0.1;
  int epochs = 60000;

  for (int i=0; i < epochs; i++)
  {
    // Feed Forward
    Matrix layer_1_net = dot(X, W0);
    Matrix layer_1_activation = activate(layer_1_net);
    Matrix layer_2_net = dot(layer_1_activation, W1);
    Matrix layer_2_activation = activate(layer_2_net);

    Matrix error = calculate_error(Y, layer_2_activation, average_error);

    // Back prop
    // Layer 2
    Matrix sigm_deriv_1 = activate(layer_2_activation, true);
    Matrix layer_2_delta = multiply(error, sigm_deriv_1);
    Matrix transpose_1 = transpose(layer_1_activation);
    Matrix dE_dW1 = dot(transpose_1, layer_2_delta);


    // Layer 1
    Matrix W1_transpose = transpose(W1);
    Matrix layer_1_error = dot(layer_2_delta, W1_transpose);
    Matrix sigm_deriv_2 = activate(layer_1_activation, true);
    Matrix layer_1_delta = multiply(layer_1_error, sigm_deriv_2);
    Matrix X_transpose = transpose(X);
    Matrix dE_dW0 = dot(X_transpose, layer_1_delta);

    Matrix delta_W1 = scalar_multiply(alpha, dE_dW1);
    W1 = add(W1, delta_W1);
    Matrix delta_W0 = scalar_multiply(alpha, dE_dW0);
    W0 = add(W0, delta_W0);


    if (i % 10000 == 0)
    {
      cout << "Epoch " << i << "\t---- \tError: " << average_error << endl;
    }
  }
}


int main(void)
{

  // Build Training Data
  Matrix X;
  Matrix Y;
  build_vectors(X, Y);

  // Initialize Topology parameters
  int input_neurons = 3;
  int hidden_neurons = 4;
  int output_neurons = 1;

  vector<int> topology = {input_neurons, hidden_neurons, output_neurons};


  // Initialize Matricies
  Matrix W0;
  Matrix W1;

  initializeMatrix(W0, input_neurons, hidden_neurons);
  initializeMatrix(W1, hidden_neurons, output_neurons);


  run(W0, W1, X, Y);


  return 0;
}
