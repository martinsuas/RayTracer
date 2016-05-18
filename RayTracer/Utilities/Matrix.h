/**
Disclaimer: Most code in this project is based on Kevin Suffern's book "Ray Tracing from the Ground Up". Any similarities in the code
reflect what was taught in the book and belong to the original author.
**/
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


