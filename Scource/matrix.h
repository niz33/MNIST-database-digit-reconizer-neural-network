#pragma once
#include<iostream>
#include<vector>
template <typename Ty>
class matrix_2 {
private:
	class row {
	public:
		vector<Ty>e;
		row(Ty) {

		}
		Ty& operator [](int column_index) {
			return e[column_index];
		}
	};
public:
	matrix_2 {

	}
	vector<row> rows;
	row& operator [] (int row_index) {
		return rows[row_index];
	}
	matix_2 operator + (matrix_2& a) {
		matrix_2 sum;

	}
};