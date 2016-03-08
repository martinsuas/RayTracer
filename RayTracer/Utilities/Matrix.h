#pragma once
/*
Contains definition of a simple 4D matrix. 
*/
class Matrix {
public:	
	double	m[4][4]; // matrix

	// Constructors
	Matrix(void);
	Matrix(const Matrix& mat);
	~Matrix (void);	
	
	// Operators
	Matrix& operator= (const Matrix& rhs); 			
	Matrix operator* (const Matrix& mat) const;
	Matrix operator/ (const double d);

	// Operations
	void set_identity(void);	
};


