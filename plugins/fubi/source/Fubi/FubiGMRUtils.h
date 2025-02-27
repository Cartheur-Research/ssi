// ****************************************************************************************
//
// FubiGMRUtils
// ---------------------------------------------------------
// Copyright (C) 2010-2015 Felix Kistler 
// 
// This software is distributed under the terms of the Eclipse Public License v1.0.
// A copy of the license may be obtained at: http://www.eclipse.org/org/documents/epl-v10.html
// 
// This code is based on the gmm-gmr implementation of Florent D'halluin, Sylvain Calinon,
// LASA Lab, EPFL, CH - 1015 Lausanne, Switzerland,
// http://www.calinon.ch, http://lasa.epfl.ch
// which was published in:
// @article{ Calinon07SMC,
//  title = "On Learning, Representing and Generalizing a Task in a Humanoid Robot",
//  author = "S. Calinon and F. Guenter and A. Billard",
//  journal = "IEEE Transactions on Systems, Man and Cybernetics, Part B.
//  Special issue on robot learning by observation, demonstration and
//  imitation",
//  year = "2007",
//  volume = "37",
//  number = "2",
//  pages = "286--298"
// }
// ****************************************************************************************

#pragma once

namespace FubiGMRUtils
{

#ifndef SIGN2
#define SIGN2(a,b) ((b) >= 0.0f ? fabs(a) : -fabs(a))
#endif
#ifndef ROUND
#define ROUND(x) (floor((x)+0.5f))
#endif

	class Vector
	{
		friend class Matrix;
	protected:
		unsigned int   row;
		float         *_;

	public:
		inline Vector()
		{
			row = 0;
			_ = 0x0;
		}
		inline virtual ~Vector()
		{
			Release();
		}
		inline Vector(const Vector &vector)
		{
			row = 0;
			_ = 0x0;
			Resize(vector.row, false);
			for (unsigned int i = 0; i < row; i++)
				_[i] = vector._[i];
		}
		inline Vector(unsigned int size, bool clear = true)
		{
			row = 0;
			_ = 0x0;
			Resize(size, false);
			if (clear)
				Zero();
		}
		inline Vector(const float array[], unsigned int size)
		{
			row = 0;
			_ = 0x0;
			Resize(size, false);
			for (unsigned int i = 0; i < row; i++)
				_[i] = array[i];
		}
		inline Vector& Zero()
		{
			for (unsigned int i = 0; i < row; i++)
				_[i] = 0.0f;
			return *this;
		}
		inline Vector& One()
		{
			for (unsigned int i = 0; i < row; i++)
				_[i] = 1.0f;
			return *this;
		}
		inline unsigned int Size() const
		{
			return row;
		}
		inline float *GetArray() const
		{
			return _;
		}
		inline float& operator[] (const unsigned int row)
		{
			if (row < this->row)
				return _[row];
			static float undef = 0;
			return undef;
		}
		inline float& operator() (const unsigned int row)
		{
			if (row < this->row)
				return _[row];
			static float undef = 0;
			return undef;
		}
		inline Vector operator - () const
		{
			Vector result(row, false);
			for (unsigned int i = 0; i < row; i++)
				result._[i] = -_[i];
			return result;
		}
		inline Vector& Set(const Vector &vector)
		{
			return (*this) = vector;
		}
		inline Vector& operator = (const Vector &vector)
		{
			Resize(vector.row, false);
			const unsigned int k = (row <= vector.row ? row : vector.row);
			for (unsigned int i = 0; i < k; i++)
				_[i] = vector._[i];
			for (unsigned int i = k; i < row; i++)
				_[i] = 0;
			return *this;
		}
		inline Vector& operator += (const Vector &vector)
		{
			const unsigned int k = (row <= vector.row ? row : vector.row);
			for (unsigned int i = 0; i < k; i++)
				_[i] += vector._[i];
			return *this;
		}
		inline Vector& operator -= (const Vector &vector)
		{
			const unsigned int k = (row <= vector.row ? row : vector.row);
			for (unsigned int i = 0; i < k; i++)
				_[i] -= vector._[i];
			return *this;
		}
		inline Vector& operator ^= (const Vector &vector)
		{
			const unsigned int k = (row <= vector.row ? row : vector.row);
			for (unsigned int i = 0; i < k; i++)
				_[i] *= vector._[i];
			return *this;
		}

		inline Vector& operator /= (const Vector &vector)
		{
			const unsigned int k = (row <= vector.row ? row : vector.row);
			for (unsigned int i = 0; i < k; i++)
				_[i] /= vector._[i];
			return *this;
		}
		inline Vector& operator += (float scalar)
		{
			for (unsigned int i = 0; i < row; i++)
				_[i] += scalar;
			return *this;
		}
		inline Vector& operator -= (float scalar)
		{
			for (unsigned int i = 0; i < row; i++)
				_[i] -= scalar;
			return *this;
		}
		inline Vector& operator *= (float scalar)
		{
			for (unsigned int i = 0; i < row; i++)
				_[i] *= scalar;
			return *this;
		}
		inline Vector& operator /= (float scalar)
		{
			scalar = 1.0f / scalar;
			for (unsigned int i = 0; i < row; i++)
				_[i] *= scalar;
			return *this;
		}
		inline Vector operator + (const Vector &vector) const
		{
			Vector result(row, false);
			return Add(vector, result);
		}
		inline Vector& Add(const Vector &vector, Vector& result) const
		{
			result.Resize(row, false);
			const unsigned int k = (row <= vector.row ? row : vector.row);
			for (unsigned int i = 0; i < k; i++)
				result._[i] = _[i] + vector._[i];
			for (unsigned int i = k; i < row; i++)
				result._[i] = _[i];
			return result;
		}
		inline Vector operator - (const Vector &vector) const
		{
			Vector result(row, false);
			return Sub(vector, result);
		}
		inline Vector& Sub(const Vector &vector, Vector& result) const
		{
			result.Resize(row, false);
			const unsigned int k = (row <= vector.row ? row : vector.row);
			for (unsigned int i = 0; i < k; i++)
				result._[i] = _[i] - vector._[i];
			for (unsigned int i = k; i < row; i++)
				result._[i] = _[i];
			return result;
		}
		inline Vector operator ^ (const Vector &vector) const
		{
			Vector result(row, false);
			return PMult(vector, result);
		}
		inline Vector& PMult(const Vector &vector, Vector& result) const
		{
			result.Resize(row, false);
			const unsigned int k = (row <= vector.row ? row : vector.row);
			for (unsigned int i = 0; i < k; i++)
				result._[i] = _[i] * vector._[i];
			for (unsigned int i = k; i < row; i++)
				result._[i] = _[i];
			return result;
		}
		inline Vector operator / (const Vector &vector) const
		{
			Vector result(row, false);
			return PDiv(vector, result);
		}
		inline Vector& PDiv(const Vector &vector, Vector& result) const
		{
			result.Resize(row, false);
			const unsigned int k = (row <= vector.row ? row : vector.row);
			for (unsigned int i = 0; i < k; i++)
				result._[i] = _[i] / vector._[i];
			for (unsigned int i = k; i < row; i++)
				result._[i] = _[i];
			return result;
		}
		inline float operator * (const Vector &vector) const
		{
			return this->Dot(vector);
		}
		inline Vector operator + (float scalar) const
		{
			Vector result(row, false);
			return Add(scalar, result);
		}
		inline Vector& Add(float scalar, Vector& result) const
		{
			result.Resize(row, false);
			for (unsigned int i = 0; i < row; i++)
				result._[i] = _[i] + scalar;
			return result;
		}
		inline Vector operator - (float scalar) const
		{
			Vector result(row, false);
			return Sub(scalar, result);
		}
		inline Vector& Sub(float scalar, Vector& result) const
		{
			result.Resize(row, false);
			for (unsigned int i = 0; i < row; i++)
				result._[i] = _[i] - scalar;
			return result;
		}
		inline Vector operator * (float scalar) const
		{
			Vector result(row, false);
			return Mult(scalar, result);
		}
		inline Vector& Mult(float scalar, Vector& result) const
		{
			result.Resize(row, false);
			for (unsigned int i = 0; i < row; i++)
				result._[i] = _[i] * scalar;
			return result;
		}
		inline Vector operator / (float scalar) const
		{
			Vector result(row, false);
			return Div(scalar, result);
		}
		inline Vector& Div(float scalar, Vector& result) const
		{
			result.Resize(row, false);
			scalar = 1.0f / scalar;
			for (unsigned int i = 0; i < row; i++)
				result._[i] = _[i] * scalar;
			return result;
		}
		inline bool operator == (const Vector& vector) const
		{
			if (row != vector.row) return false;
			for (unsigned int i = 0; i < row; i++)
				if (_[i] != vector._[i]) return false;
			return true;
		}
		inline bool operator != (const Vector& vector) const
		{
			return !(*this == vector);
		}
		inline float Sum() const
		{
			float result = 0.0f;
			for (unsigned int i = 0; i < row; i++)
				result += _[i];
			return result;
		}
		inline float Norm() const
		{
			return sqrtf(Norm2());
		}
		inline float Norm2() const
		{
			float result = 0.0f;
			for (unsigned int i = 0; i < row; i++)
				result += _[i] * _[i];
			return result;
		}
		inline void Normalize()
		{
			float scalar = 1.0f / Norm();
			(*this) *= scalar;
		}
		inline float Distance(const Vector &vector) const
		{
			return (*this - vector).Norm();
		}
		inline float Distance2(const Vector &vector) const
		{
			return (*this - vector).Norm2();
		}
		inline float Dot(const Vector &vector) const
		{
			const unsigned int k = (row <= vector.row ? row : vector.row);
			float result = 0.0f;
			for (unsigned int i = 0; i < k; i++)
				result += _[i] * vector._[i];
			return result;
		}
		inline Vector& SetSubVector(unsigned int startPos, const Vector &vector)
		{
			if (startPos < row){
				const unsigned int k = (row - startPos <= vector.row ? row - startPos : vector.row);
				for (unsigned int i = 0; i < k; i++){
					_[startPos + i] = vector._[i];
				}
			}
			return *this;
		}
		inline Vector GetSubVector(unsigned int startPos, unsigned int len)
		{
			Vector result(len, false);
			return GetSubVector(startPos, len, result);
		}
		inline Vector& GetSubVector(unsigned int startPos, unsigned int len, Vector &result)
		{
			result.Resize(len, false);
			if (startPos < row){
				const unsigned int k = (row - startPos <= len ? row - startPos : len);
				for (unsigned int i = 0; i < k; i++){
					result[i] = _[startPos + i];
				}
				for (unsigned int i = k; i < len; i++){
					result[i] = 0.0f;
				}

			}
			else{
				result.Zero();
			}
			return result;
		}
		inline float Max()
		{
			if (row == 0)
				return 0.0f;

			float res = _[0];
			for (unsigned int i = 1; i<row; i++){
				if (_[i]>res) res = _[i];
			}
			return res;
		}
		inline int MaxId()
		{
			if (row == 0)
				return -1;

			float mx = _[0];
			int   res = 0;
			for (unsigned int i = 1; i < row; i++){
				if (_[i] > mx){ mx = _[i]; res = i; }
			}
			return res;
		}
		inline Vector Abs()
		{
			Vector result(row);
			return Abs(result);
		}
		inline Vector& Abs(Vector &result) const
		{
			result.Resize(row, false);
			for (unsigned int i = 0; i < row; i++){
				result._[i] = fabs(_[i]);
			}
			return result;
		}
		inline Vector& GetSubVector(const Vector &ids, Vector &result) const
		{
			const unsigned int k = ids.Size();
			result.Resize(k);
			for (unsigned int i = 0; i < k; i++)
			{
				const unsigned int g = (unsigned int)(fabs(ROUND(ids._[i])));
				if (g < row){
					result._[i] = _[g];
				}
				else{
					result._[i] = 0.0f;
				}
			}
			return result;
		}
		inline Vector GetSubVector(const Vector &ids) const
		{
			Vector result(ids.Size(), false);
			return GetSubVector(ids, result);
		}
		inline virtual void Resize(unsigned int size, bool copy = true)
		{
			if (row != size)
			{
				if (size){
					float *arr = new float[size];
					if (copy){
						unsigned int m = (row < size ? row : size);
						for (unsigned int i = 0; i < m; i++)
							arr[i] = _[i];
						for (unsigned int i = m; i < size; i++)
							arr[i] = 0.0f;
					}
					if (_ != 0x0)
						delete[] _;
					_ = arr;
					row = size;
				}
				else
					Release();
			}
		}
	protected:
		inline void Release()
		{
			if (_ != 0x0)
				delete[] _;
			row = 0;
			_ = 0x0;
		}
	};

	class Matrix
	{
		friend class Vector;
	protected:
		unsigned int  row;
		unsigned int  column;
		float        *_;
	public:
		inline Matrix()
		{
			row = 0;
			column = 0;
			_ = 0x0;
		}
		inline virtual ~Matrix()
		{
			Release();
		}
		inline Matrix(const Matrix &matrix)
		{
			row = 0;
			column = 0;
			_ = 0x0;
			Resize(matrix.row, matrix.column, false);
			for (unsigned int j = 0; j < row; j++)
				for (unsigned int i = 0; i < column; i++)
					_[j*column + i] = matrix._[j*column + i];
		}
		inline Matrix(unsigned int rowSize, unsigned int colSize, bool clear = true)
		{
			row = 0;
			column = 0;
			_ = 0x0;
			Resize(rowSize, colSize, false);
			if (clear)
				Zero();
		}
		inline Matrix(const float _[], unsigned int rowSize, unsigned int colSize)
		{
			row = 0;
			column = 0;
			this->_ = 0x0;
			Resize(rowSize, colSize, false);
			for (unsigned int j = 0; j < row; j++)
				for (unsigned int i = 0; i < column; i++)
					this->_[j*column + i] = _[j*column + i];
		}
		inline Matrix& Zero()
		{
			for (unsigned int j = 0; j < row; j++)
				for (unsigned int i = 0; i < column; i++)
					_[j*column + i] = 0.0f;
			return *this;
		}
		inline unsigned int RowSize() const{
			return row;
		}
		inline unsigned int ColumnSize() const{
			return column;
		}
		inline float *Array() const{
			return _;
		}
		inline float& operator() (const unsigned int row, const unsigned int col)
		{
			if ((row < this->row) && (col < this->column))
				return _[row*column + col];
			static float undef = 0;
			return undef;
		}
		inline Vector GetRow(const unsigned int row) const
		{
			Vector result(column, false);
			return GetRow(row, result);
		}
		inline Vector& GetRow(const unsigned int row, Vector& result) const
		{
			result.Resize(column, false);
			for (unsigned int i = 0; i < column; i++)
				result._[i] = _[row*column + i];
			return result;
		}
		inline Vector GetColumn(const unsigned int col) const
		{
			Vector result(row, false);
			return GetColumn(col, result);
		}
		inline Vector& GetColumn(const unsigned int col, Vector& result) const
		{
			result.Resize(row, false);
			if (col < column){
				for (unsigned int j = 0; j < row; j++)
					result._[j] = _[j*column + col];
			}
			else{
				result.Zero();
			}
			return result;
		}
		inline Matrix GetColumnSpace(const unsigned int col, const unsigned int len) const
		{
			if (len > 0){
				Matrix result(row, len, false);
				return GetColumnSpace(col, len, result);
			}
			else
				return Matrix();
		}
		inline Matrix GetRowSpace(const unsigned int row, const unsigned int len) const
		{
			if (len > 0){
				Matrix result(len, column, false);
				return GetRowSpace(row, len, result);
			}
			else
				return Matrix();
		}
		inline Matrix& GetColumnSpace(const unsigned int col, const unsigned int len, Matrix &result) const
		{
			if (len > 0){
				const unsigned int end = col + len - 1;
				const unsigned int size = len;
				result.Resize(row, size, false);

				if (col < column){
					const unsigned int k = (end + 1 <= column ? end + 1 : column);

					for (unsigned int i = col; i < k; i++)
						for (unsigned int j = 0; j < row; j++)
							result._[j*size + (i - col)] = _[j*column + i];
					for (unsigned int i = k; i < end + 1; i++)
						for (unsigned int j = 0; j < row; j++)
							result._[j*size + (i - col)] = 0.0f;
				}
				else{
					result.Zero();
				}
			}
			else{
				result.Resize(0, 0, false);
			}
			return result;
		}
		inline Matrix& GetRowSpace(const unsigned int row, const unsigned int len, Matrix &result) const
		{
			if (len > 0){
				const unsigned int end = row + len - 1;
				const unsigned int size = len;
				result.Resize(size, column, false);

				if (row < this->row){
					const unsigned int k = (end + 1 <= this->row ? end + 1 : this->row);

					for (unsigned int j = 0; j < column; j++)
						for (unsigned int i = row; i < k; i++)
							result._[(i - row)*column + j] = _[i*column + j];
					for (unsigned int j = 0; j < column; j++)
						for (unsigned int i = k; i < end + 1; i++)
							result._[(i - row)*column + j] = 0.0f;
				}
				else{
					result.Zero();
				}
			}
			else{
				result.Resize(0, 0, false);
			}
			return result;
		}
		inline Matrix& SetRow(const Vector &vector, const unsigned int row)
		{
			if (row < this->row){
				const unsigned int ki = (column <= vector.row ? column : vector.row);
				for (unsigned int i = 0; i < ki; i++)
					_[row*column + i] = vector._[i];
			}
			return *this;
		}
		inline Matrix& SetColumn(const Vector &vector, const unsigned int col)
		{
			if (col < this->column){
				const unsigned int kj = (row <= vector.row ? row : vector.row);
				for (unsigned int j = 0; j < kj; j++)
					_[j*column + col] = vector._[j];
			}
			return *this;
		}
		inline Matrix& SetColumnSpace(const Matrix &matrix, const unsigned int col)
		{
			if (col < this->column){
				const unsigned int kj = (row <= matrix.row ? row : matrix.row);
				const unsigned int ki = (col + matrix.column <= this->column ? col + matrix.column : this->column);
				for (unsigned int j = 0; j < kj; j++)
					for (unsigned int i = col; i < ki; i++)
						_[j*column + i] = matrix._[j*matrix.column + (i - col)];
			}
			return *this;
		}
		inline Matrix& SetRowSpace(const Matrix &matrix, const unsigned int row)
		{
			if (row < this->row){
				const unsigned int ki = (column <= matrix.column ? column : matrix.column);
				const unsigned int kj = (row + matrix.row <= this->row ? row + matrix.row : this->row);
				for (unsigned int j = row; j < kj; j++)
					for (unsigned int i = 0; i < ki; i++)
						_[j*column + i] = matrix._[(j - row)*matrix.column + i];
			}
			return *this;
		}
		inline Matrix GetRowSpace(const Vector &ids) const
		{
			Matrix result(ids.Size(), column);
			return GetRowSpace(ids, result);
		}
		inline Matrix GetColumnSpace(const Vector &ids) const
		{
			Matrix result(row, ids.Size());
			return GetColumnSpace(ids, result);
		}
		inline Matrix GetMatrixSpace(const Vector &rowIds, const Vector &colIds) const
		{
			Matrix result(rowIds.Size(), colIds.Size());
			return GetMatrixSpace(rowIds, colIds, result);
		}
		inline Matrix& GetColumnSpace(const Vector &ids, Matrix &result) const
		{
			const unsigned int k = ids.Size();
			result.Resize(row, k);
			for (unsigned int i = 0; i < k; i++){
				const unsigned int g = (unsigned int)(fabs(ROUND(ids._[i])));
				if (g < column){
					for (unsigned int j = 0; j < row; j++)
						result._[j*k + i] = _[j*column + g];
				}
				else{
					for (unsigned int j = 0; j < row; j++)
						result._[j*k + i] = 0.0f;
				}
			}
			return result;
		}
		inline Matrix& GetRowSpace(const Vector &ids, Matrix &result) const
		{
			const unsigned int k = ids.Size();
			result.Resize(k, column);
			for (unsigned int i = 0; i < k; i++){
				const unsigned int g = (unsigned int)(fabs(ROUND(ids._[i])));
				if (g < row){
					for (unsigned int j = 0; j < column; j++)
						result._[i*column + j] = _[g*column + j];
				}
				else{
					for (unsigned int j = 0; j < column; j++)
						result._[i*column + j] = 0.0f;
				}
			}
			return result;
		}
		inline Matrix& GetMatrixSpace(const Vector &rowIds, const Vector &colIds, Matrix &result) const
		{
			const unsigned int k1 = rowIds.Size();
			const unsigned int k2 = colIds.Size();
			result.Resize(k1, k2);
			for (unsigned int i = 0; i < k1; i++){
				const unsigned int g1 = (unsigned int)(fabs(ROUND(rowIds._[i])));
				if (g1 < row){
					for (unsigned int j = 0; j < k2; j++){
						const unsigned int g2 = (unsigned int)(fabs(ROUND(colIds._[j])));
						if (g2 < column){
							result._[i*k2 + j] = _[g1*column + g2];
						}
						else{
							result._[i*k2 + j] = 0.0f;
						}
					}
				}
				else{
					for (unsigned int j = 0; j < k2; j++)
						result._[i*k2 + j] = 0.0f;
				}
			}
			return result;
		}
		inline Matrix operator - () const
		{
			Matrix result(row, column, false);
			for (unsigned int j = 0; j < row; j++)
				for (unsigned int i = 0; i < column; i++)
					result._[j*column + i] = -_[j*column + i];
			return result;
		}
		inline virtual Matrix& operator = (const Matrix &matrix)
		{
			Resize(matrix.row, matrix.column, false);
			for (unsigned int j = 0; j < row; j++)
				for (unsigned int i = 0; i < column; i++)
					_[j*column + i] = matrix._[j*column + i];
			return *this;
		}
		inline Matrix& operator += (const Matrix &matrix)
		{
			const unsigned int kj = (row <= matrix.row ? row : matrix.row);
			const unsigned int ki = (column <= matrix.column ? column : matrix.column);
			for (unsigned int j = 0; j < kj; j++)
				for (unsigned int i = 0; i < ki; i++)
					_[j*column + i] += matrix._[j*column + i];
			return *this;
		}
		inline Matrix& operator -= (const Matrix &matrix)
		{
			const unsigned int kj = (row <= matrix.row ? row : matrix.row);
			const unsigned int ki = (column <= matrix.column ? column : matrix.column);
			for (unsigned int j = 0; j < kj; j++)
				for (unsigned int i = 0; i < ki; i++)
					_[j*column + i] -= matrix._[j*column + i];
			return *this;
		}
		inline Matrix& operator ^= (const Matrix &matrix)
		{
			const unsigned int kj = (row <= matrix.row ? row : matrix.row);
			const unsigned int ki = (column <= matrix.column ? column : matrix.column);
			for (unsigned int j = 0; j < kj; j++)
				for (unsigned int i = 0; i < ki; i++)
					_[j*column + i] *= matrix._[j*column + i];
			return *this;
		}
		inline Matrix& operator /= (const Matrix &matrix)
		{
			const unsigned int kj = (row <= matrix.row ? row : matrix.row);
			const unsigned int ki = (column <= matrix.column ? column : matrix.column);
			for (unsigned int j = 0; j < kj; j++)
				for (unsigned int i = 0; i < ki; i++)
					_[j*column + i] /= matrix._[j*column + i];
			return *this;
		}
		inline Matrix& operator += (float scalar)
		{
			for (unsigned int j = 0; j < row; j++)
				for (unsigned int i = 0; i < column; i++)
					_[j*column + i] += scalar;
			return *this;
		}
		inline Matrix& operator -= (float scalar)
		{
			for (unsigned int j = 0; j < row; j++)
				for (unsigned int i = 0; i < column; i++)
					_[j*column + i] -= scalar;
			return *this;
		}
		inline Matrix& operator *= (float scalar)
		{
			for (unsigned int j = 0; j < row; j++)
				for (unsigned int i = 0; i < column; i++)
					_[j*column + i] *= scalar;
			return *this;
		}
		inline Matrix& operator /= (float scalar)
		{
			scalar = 1.0f / scalar;
			for (unsigned int j = 0; j < row; j++)
				for (unsigned int i = 0; i < column; i++)
					_[j*column + i] *= scalar;
			return *this;
		}
		inline Matrix operator + (const Matrix &matrix) const
		{
			Matrix result(row, column, false);
			return Add(matrix, result);
		}
		inline Matrix& Add(const Matrix &matrix, Matrix &result) const
		{
			result.Resize(row, column, false);
			const unsigned int kj = (row <= matrix.row ? row : matrix.row);
			const unsigned int ki = (column <= matrix.column ? column : matrix.column);
			for (unsigned int j = 0; j < kj; j++){
				for (unsigned int i = 0; i < ki; i++)
					result._[j*column + i] = _[j*column + i] + matrix._[j*column + i];
				for (unsigned int i = ki; i < column; i++)
					result._[j*column + i] = _[j*column + i];
			}
			for (unsigned int j = kj; j < row; j++)
				for (unsigned int i = 0; i < column; i++)
					result._[j*column + i] = _[j*column + i];
			return result;
		}
		inline Matrix operator - (const Matrix &matrix) const
		{
			Matrix result(row, column, false);
			return Sub(matrix, result);
		}
		inline Matrix& Sub(const Matrix &matrix, Matrix &result) const
		{
			result.Resize(row, column, false);
			const unsigned int kj = (row <= matrix.row ? row : matrix.row);
			const unsigned int ki = (column <= matrix.column ? column : matrix.column);
			for (unsigned int j = 0; j < kj; j++){
				for (unsigned int i = 0; i < ki; i++)
					result._[j*column + i] = _[j*column + i] - matrix._[j*column + i];
				for (unsigned int i = ki; i < column; i++)
					result._[j*column + i] = _[j*column + i];
			}
			for (unsigned int j = kj; j < row; j++)
				for (unsigned int i = 0; i < column; i++)
					result._[j*column + i] = _[j*column + i];
			return result;
		}
		inline Matrix operator ^ (const Matrix &matrix) const
		{
			Matrix result(row, column, false);
			return PMult(matrix, result);
		}
		inline Matrix& PMult(const Matrix &matrix, Matrix &result) const
		{
			result.Resize(row, column, false);
			const unsigned int kj = (row <= matrix.row ? row : matrix.row);
			const unsigned int ki = (column <= matrix.column ? column : matrix.column);
			for (unsigned int j = 0; j < kj; j++){
				for (unsigned int i = 0; i < ki; i++)
					result._[j*column + i] = _[j*column + i] * matrix._[j*column + i];
				for (unsigned int i = ki; i < column; i++)
					result._[j*column + i] = _[j*column + i];
			}
			for (unsigned int j = kj; j < row; j++)
				for (unsigned int i = 0; i < column; i++)
					result._[j*column + i] = _[j*column + i];
			return result;
		}
		inline Matrix operator / (const Matrix &matrix) const
		{
			Matrix result(row, column, false);
			return PDiv(matrix, result);
		}
		inline Matrix& PDiv(const Matrix &matrix, Matrix &result) const
		{
			result.Resize(row, column, false);
			const unsigned int kj = (row <= matrix.row ? row : matrix.row);
			const unsigned int ki = (column <= matrix.column ? column : matrix.column);
			for (unsigned int j = 0; j < kj; j++){
				for (unsigned int i = 0; i < ki; i++)
					result._[j*column + i] = _[j*column + i] / matrix._[j*column + i];
				for (unsigned int i = ki; i < column; i++)
					result._[j*column + i] = _[j*column + i];
			}
			for (unsigned int j = kj; j < row; j++)
				for (unsigned int i = 0; i < column; i++)
					result._[j*column + i] = _[j*column + i];
			return result;
		}
		inline Matrix operator + (float scalar) const
		{
			Matrix result(row, column, false);
			return Add(scalar, result);
		}
		inline Matrix& Add(float scalar, Matrix& result) const
		{
			result.Resize(row, column, false);
			for (unsigned int j = 0; j < row; j++)
				for (unsigned int i = 0; i < column; i++)
					result._[j*column + i] = _[j*column + i] + scalar;
			return result;
		}
		inline Matrix operator - (float scalar) const
		{
			Matrix result(row, column, false);
			return Sub(scalar, result);
		}
		inline Matrix& Sub(float scalar, Matrix& result) const
		{
			result.Resize(row, column, false);
			for (unsigned int j = 0; j < row; j++)
				for (unsigned int i = 0; i < column; i++)
					result._[j*column + i] = _[j*column + i] - scalar;
			return result;
		}
		inline Matrix operator * (float scalar) const
		{
			Matrix result(row, column, false);
			return Mult(scalar, result);
		}
		inline Matrix& Mult(float scalar, Matrix& result) const
		{
			result.Resize(row, column, false);
			for (unsigned int j = 0; j < row; j++)
				for (unsigned int i = 0; i < column; i++)
					result._[j*column + i] = _[j*column + i] * scalar;
			return result;
		}
		inline Matrix operator / (float scalar) const
		{
			Matrix result(row, column, false);
			return Div(scalar, result);
		}
		inline Matrix& Div(float scalar, Matrix& result) const
		{
			result.Resize(row, column, false);
			for (unsigned int j = 0; j < row; j++)
				for (unsigned int i = 0; i < column; i++)
					result._[j*column + i] = _[j*column + i] / scalar;
			return result;
		}
		inline bool operator == (const Matrix& matrix) const
		{
			if ((row != matrix.row) || (column != matrix.column)) return false;
			for (unsigned int j = 0; j < row; j++)
				for (unsigned int i = 0; i < column; i++)
					if (_[j*column + i] != matrix._[j*column + i]) return false;
			return true;
		}
		inline bool operator != (const Matrix& matrix) const
		{
			return !(*this == matrix);
		}
		inline Vector operator * (const Vector &vector) const
		{
			Vector result(row, false);
			return Mult(vector, result);
		}
		inline Vector Mult(const Vector &vector) const
		{
			Vector result(row, false);
			return Mult(vector, result);
		}
		inline Vector& Mult(const Vector &vector, Vector &result) const
		{
			result.Resize(row, false);
			const unsigned int ki = (column <= vector.row ? column : vector.row);
			for (unsigned int j = 0; j < row; j++){
				result._[j] = 0.0f;
				for (unsigned int i = 0; i < ki; i++)
					result._[j] += _[j*column + i] * vector._[i];
			}
			return result;
		}
		inline Matrix operator * (const Matrix &matrix) const
		{
			Matrix result(row, matrix.column, false);
			return Mult(matrix, result);
		}
		inline Matrix& Mult(const Matrix &matrix, Matrix &result) const
		{
			result.Resize(row, matrix.column, false);
			const unsigned int rrow = result.row;
			const unsigned int rcol = result.column;
			const unsigned int kk = (column <= matrix.row ? column : matrix.row);
			for (unsigned int j = 0; j < rrow; j++){
				for (unsigned int i = 0; i < rcol; i++){
					result._[j*rcol + i] = 0.0f;
					for (unsigned int k = 0; k< kk; k++)
						result._[j*rcol + i] += _[j*column + k] * matrix._[k*rcol + i];
				}
			}
			return result;
		}
		inline Matrix& Identity()
		{
			const unsigned int k = (row>column ? column : row);
			Zero();
			for (unsigned int i = 0; i < k; i++)
				_[i*column + i] = 1.0f;
			return *this;
		}
		inline Matrix& Diag(const Vector &vector)
		{
			const unsigned int k = (row>column ? column : row);
			const unsigned int k2 = (k > vector.row ? vector.row : k);
			Zero();
			for (unsigned int i = 0; i < k2; i++)
				_[i*column + i] = vector._[i];
			return *this;
		}
		inline Matrix Transpose() const
		{
			Matrix result(row, column, false);
			return Transpose(result);
		}
		inline Matrix& Transpose(Matrix &result) const
		{
			result.Resize(column, row, false);
			for (unsigned int j = 0; j < row; j++)
				for (unsigned int i = 0; i < column; i++)
					result._[i*row + j] = _[j*column + i];
			return result;
		}
		inline Matrix VCat(const Matrix& matrix)
		{
			Matrix result;
			return VCat(matrix, result);
		}
		inline Matrix& VCat(const Matrix& matrix, Matrix & result)
		{
			unsigned int k1 = (column>matrix.column ? column : matrix.column);
			result.Resize(row + matrix.row, k1, false);
			for (unsigned int j = 0; j < row; j++){
				for (unsigned int i = 0; i < column; i++)
					result._[j*k1 + i] = _[j*column + i];
				for (unsigned int i = column; i < k1; i++)
					result._[j*k1 + i] = 0.0f;
			}
			for (unsigned int j = 0; j < matrix.row; j++){
				for (unsigned int i = 0; i < matrix.column; i++)
					result._[(row + j)*k1 + i] = matrix._[j*matrix.column + i];
				for (unsigned int i = matrix.column; i < k1; i++)
					result._[(row + j)*k1 + i] = 0.0f;
			}
			return result;
		}
		inline Matrix HCat(const Matrix& matrix)
		{
			Matrix result;
			return HCat(matrix, result);
		}
		inline Matrix& HCat(const Matrix& matrix, Matrix & result)
		{
			unsigned int k1 = (row>matrix.row ? row : matrix.row);
			unsigned int k2 = column + matrix.column;
			result.Resize(k1, k2, false);
			for (unsigned int j = 0; j < row; j++)
				for (unsigned int i = 0; i < column; i++)
					result._[j*k2 + i] = _[j*column + i];
			for (unsigned int j = row; j < k1; j++)
				for (unsigned int i = 0; i < column; i++)
					result._[j*k2 + i] = 0.0f;

			for (unsigned int j = 0; j < matrix.row; j++)
				for (unsigned int i = 0; i < matrix.column; i++)
					result._[j*k2 + i + column] = matrix._[j*matrix.column + i];
			for (unsigned int j = matrix.row; j < k1; j++)
				for (unsigned int i = 0; i < matrix.column; i++)
					result._[j*k2 + i + column] = 0.0f;

			return result;
		}
		inline Matrix Inverse(float *determinant = 0x0) const
		{
			Matrix result;
			return Inverse(result, determinant);
		}
		inline Matrix& Inverse(Matrix &result, float *determinant = 0x0) const
		{
			if (row == column)
			{ // Square matrix
				if (determinant != 0x0)
					*determinant = 1.0f;
				result.Resize(row, column, false);
				const unsigned int n = row;
				Matrix MM(*this);
				result.Identity();
				for (unsigned int i = 0; i < n; i++)
				{
					float pivot = MM._[i*column + i];
					if (fabs(pivot) <= Fubi::Math::Epsilon)
					{
						for (unsigned int j = i + 1; j < n; j++)
						{
							if ((pivot = MM._[j*column + i]) != 0.0f)
							{
								MM.SwapRow(i, j);
								result.SwapRow(i, j);
								break;
							}
						}
						if (fabs(pivot) <= Fubi::Math::Epsilon)
						{
							if (determinant != 0x0)
								*determinant = 0.0f;
							return result;
						}
					}
					if (determinant != 0x0)
						*determinant *= pivot;
					pivot = 1.0f / pivot;
					for (unsigned int j = 0; j < n; j++)
					{
						MM._[i*column + j] *= pivot;
						result._[i*column + j] *= pivot;
					}
					for (unsigned int k = 0; k < n; k++)
					{
						if (k != i)
						{
							const float mki = MM._[k*column + i];
							for (unsigned int j = 0; j < n; j++)
							{
								MM._[k*column + j] -= MM._[i*column + j] * mki;
								result._[k*column + j] -= result._[i*column + j] * mki;
							}
						}
					}
				}
			}
			else
			{ // Moore-Penrose pseudo inverse
				if (determinant != 0x0)
					*determinant = 0.0f;
				if (row > column)
				{ // (JtJ)^(-1)Jt
					Matrix MT, SQ, SQInv;
					Transpose(MT);
					MT.Mult(*this, SQ);
					SQ.Inverse(SQInv);
					SQInv.Mult(MT, result);
				}
				else
				{ // Jt(JJt)^(-1)
					Matrix MT, SQ, SQInv;
					Transpose(MT);
					Mult(MT, SQ);
					SQ.Inverse(SQInv);
					MT.Mult(SQInv, result);
				}
			}
			return result;
		}
		inline Matrix& SwapRow(unsigned int j1, unsigned int j2)
		{
			if ((j1 < row) && (j2 < row))
			{
				float tmp;
				for (unsigned int i = 0; i < column; i++)
				{
					tmp = _[j1*column + i];
					_[j1*column + i] = _[j2*column + i];
					_[j2*column + i] = tmp;
				}
			}
			return *this;
		}
		inline Matrix& SwapColumn(unsigned int i1, unsigned int i2)
		{
			if ((i1 < column) && (i2 < column)){
				float tmp;
				for (unsigned int j = 0; j < row; j++){
					tmp = _[j*column + i1];
					_[j*column + i1] = _[j*column + i2];
					_[j*column + i2] = tmp;
				}
			}
			return *this;
		}
		Matrix& ClearColumn(unsigned int col)
		{
			if (col < column){
				for (unsigned int i = 0; i < row; i++){
					_[i*column + col] = 0.0f;
				}
			}
			return *this;
		}
		Vector SumRow()
		{
			Vector result(column);
			return SumRow(result);
		}
		Vector SumColumn()
		{
			Vector result(row);
			return SumColumn(result);
		}
		Vector & SumRow(Vector & result)
		{
			result.Resize(column, false);
			result.Zero();
			for (unsigned int i = 0; i < column; i++)
			{
				for (unsigned int j = 0; j < row; j++)
				{
					result._[i] += _[j*column + i];
				}
			}
			return result;
		}
		Vector & SumColumn(Vector & result)
		{
			result.Resize(row, false);
			result.Zero();
			for (unsigned int j = 0; j < row; j++)
			{
				for (unsigned int i = 0; i < column; i++)
				{
					result._[j] += _[j*column + i];
				}
			}
			return result;
		}
		inline virtual void Resize(unsigned int rowSize, unsigned int colSize, bool copy = true)
		{
			if ((row != rowSize) || (column != colSize))
			{
				if ((rowSize) && (colSize))
				{
					float *arr = new float[rowSize*colSize];
					if (copy)
					{
						unsigned int mj = (row < rowSize ? row : rowSize);
						unsigned int mi = (column < colSize ? column : colSize);
						for (unsigned int j = 0; j < mj; j++)
						{
							for (unsigned int i = 0; i < mi; i++)
								arr[j*colSize + i] = _[j*column + i];
							for (unsigned int i = mi; i < colSize; i++)
								arr[j*colSize + i] = 0.0f;
						}
						for (unsigned int j = mj; j < rowSize; j++)
						{
							for (unsigned int i = 0; i < colSize; i++)
								arr[j*colSize + i] = 0.0f;
						}
					}
					if (_ != 0x0)
						delete[] _;
					_ = arr;
					row = rowSize;
					column = colSize;
				}
				else
				{
					Release();
				}
			}
		}
	protected:
		inline void Release()
		{
			if (_ != 0x0)
				delete[] _;
			row = 0;
			column = 0;
			_ = 0x0;
		}
	};
}