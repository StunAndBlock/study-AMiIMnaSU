#include "matrix.hpp"

void matrix::show(const std::vector<std::vector<double>>& matrix) 
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
			std::cout << matrix[i][j] << '\t';
		std::cout << '\n';
	}
	std::cout << '\n';
}

void matrix::show(const std::vector<double>& vector) 
{
	for (int i = 0; i < vector.size(); i++)
		std::cout << vector[i] << '\n';
	std::cout << '\n';
}

std::vector<double> matrix::GaussMethod(std::vector<std::vector<double>>& A, std::vector<double>& B)
{
	std::cout << "System:\n";
	matrix::show(A);
	matrix::show(B);
	double n = 0.;
	std::vector<double> x = std::vector<double>(A.size());
	for (int i = 0; i < A.size(); i++)
	{
		
		if (A[i][i] == 0.)
		{
			int c = i;
			while (A[c][i] == 0)
				if (++c >= A.size())
					return B;
			std::swap(A[c], A[i]);
			std::swap(B[c], B[i]);
		}
		for (int k = i; k + 1 < A.size(); k++)
		{
			n = A[k + 1][i];
			for (int j = i; j < A.size(); j++)
			{
				A[k+1][j] -=  A[i][j] * n / A[i][i];
			}
			B[k+1] -=  B[i] * n / A[i][i];
		}
	}

	for (int i = x.size() - 1; i >= 0; i--)
	{
		x[i]  = B[i] / A[i][i];
		for (int j = x.size() - 1; j > i; j--)
			x[i] -= x[j] * A[i][j] / A[i][i];
	}
	return x;
}


std::vector<std::vector<double>> matrix::transpose(const std::vector<std::vector<double>>& matrix)
{
	std::vector<std::vector<double>> result(std::vector<std::vector<double>>(matrix[0].size(), std::vector<double>(matrix.size(), 0)));
	
	for (int i = 0; i < result.size(); i++)
		for (int j = 0; j < result[i].size(); j++)
			result[i][j] = matrix[j][i];
	return result;
}

std::vector<std::vector<double>> matrix::E(int size)
{
	std::vector<std::vector<double>> result = std::vector<std::vector<double>>(size, std::vector<double>(size, 0.));
	for (int i = 0; i < result.size(); i++)
		result[i][i] = 1.;
	return result;
}

std::vector<std::vector<double>> matrix::sub(const std::vector<std::vector<double>>& matrix1, const std::vector<std::vector<double>>& matrix2)
{
	std::vector<std::vector<double>> result = matrix1;
	for (int i = 0; i < result.size(); i++)
		for (int j = 0; j < result[i].size(); j++)
			result[i][j] -= matrix2[i][j];
	return result;
}

std::vector<std::vector<double>> matrix::mult(const std::vector<std::vector<double>>& matrix1, const std::vector<std::vector<double>>& matrix2)
{
	int size = matrix1.size();
	std::vector<std::vector<double>> result = matrix1;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			double sum = 0;
			for (int n = 0; n < size; n++)
				sum += matrix1[i][n] * matrix2[n][j];
			result[i][j] = sum;
		}
	}
	return result;
}

std::vector<std::vector<double>> matrix::pow(const std::vector<std::vector<double>>& matrix, int degr)
{
	std::vector<std::vector<double>> result = matrix;
	
	for (int i = 0; i < degr; i++)
		result = matrix::mult(result, matrix);
	return result;
}


double average(const std::vector<double>& data)
{
	double sum = 0.;
	for (int i = 0; i < data.size(); i++)
		sum += data[i];
	return sum / data.size();
}

double avgDev(const std::vector<double>& data)
{
	double avg = average(data);
	
	double sum = 0.;
	
	for (int i = 0; i < data.size(); i++)
		sum += std::pow(data[i] - avg, 2);
	
	return std::sqrt(sum / (data.size() - 1));
}