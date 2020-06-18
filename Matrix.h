#ifndef EX3_MATRIX_H
#define EX3_MATRIX_H
#include "Auxiliaries.h"

namespace mtm
{
    template <class T>
    class Matrix{
    private:
        Dimensions dim;
        int element_num;
        T* data;
        //const T* getData() const;
        //const mtm::Dimensions& getDim() const;
        Matrix<bool>& negateMatrix();
        static std::string printDim(Dimensions dim);
        
        public:
        Matrix(const Dimensions dimensions, const T init_val = T());
        explicit Matrix(const Matrix &Matrix);
        ~Matrix();
        Matrix& operator=(const Matrix& a);
        static Matrix Diagonal(int a, int b);
        int height() const;
        int width() const;
        int size() const;
        Matrix transpose() const;
        Matrix operator-() const;
        const T& operator() (const int row, const int col) const;
        T& operator() (const int row, const int col);
        Matrix<bool> operator< (const T t) const;
        Matrix<bool> operator==(const T t) const;
        Matrix<bool> operator<=(const T t) const;
        Matrix<bool> operator>(const T t) const;
        Matrix<bool> operator>=(const T t) const;
        Matrix<bool> operator!=(const T t) const;
        
        //Assumptions: none
        //template<class T> (this did not compile)
        friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat)
        {
            os << printMatrix(mat.data, mat.dim) << std::endl;
            return os;
        }
        
        //********Exceptions Classes*************
        
        class AccessIllegalElement 
        {
            public:
            const std::string what() const;
        };
        class IllegalInitialization 
        {
            public:
            const std::string what() const;
        };
        class DimensionMismatch 
        {
            public:
            Dimensions dim1;
            Dimensions dim2;
            DimensionMismatch(const Dimensions dim1, const Dimensions dim2) :
                dim1(dim1), dim2(dim2) {}
            const std::string what() const;
        };
    };

    //*****non-class functions & operators*****

    template<class T>
    Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b);
    template<class T>
    Matrix<T> operator-(const Matrix<T>& a, const Matrix<T>& b);
    template<class T>
    Matrix<T> operator+(const Matrix<T>& a, const T t);
    template<class T>
    Matrix<T> operator+(const T t, const Matrix<T>& b);
    template<class T>
    Matrix<T>& operator+=(Matrix<T>& a, const T t);
    template<class T>
    Matrix<T>& operator+=(const T t, Matrix<T>& b);
    template<class T>
    bool any(const Matrix<T>&);
    template<class T>
    bool all(const Matrix<T>&);

    //**************exceptions**************

    template <class T>
    const std::string Matrix<T>::AccessIllegalElement::what() const
    {
        return "Mtm matrix error: An attempt to access an illegal element";
    }

    template <class T>
    const std::string Matrix<T>::IllegalInitialization::what() const
    {
        return "Mtm matrix error: Illegal initialization values";
    }
    
    template <class T>
    const std::string Matrix<T>::DimensionMismatch::what() const
    {
         std::string str = "Mtm matrix error: Dimensions mismatch:\n" + printDim(dim1) + printDim(dim2);
         return str;
    }


    //**********private functions*************

    template <class T>
    std::string Matrix<T>::printDim(Dimensions dim)
    {
        std::string str;
        str += "(" + std::to_string(dim.mtm::Dimensions::getRow()) + "," + std::to_string(dim.mtm::Dimensions::getCol()) += ")";
        return str;
    }

    template<class T>
    Matrix<bool>& Matrix<T>::negateMatrix()
    {
        int height = this->height();
        int width = this->width();
        for(int i = 0 ; i < height ; i++)
        {
            for(int j = 0 ; j < width ; j++)
            {               
                (*this)(i , j) = ((*this)(i , j) == false ? true : false);
            }        
        }
        return *this;
    }

    /*template<class T>
    const T* Matrix<T>::getData() const
    {
        return this->data;
    }*/

    /*template<class T>
    const mtm::Dimensions& Matrix<T>::getDim() const
    {
        return this->dim;
    }*/



    //*****in-class member functions & operators by order******
    
    //Assumptions: c'tor, assignment operator, d'tor defined
    template <class T>    
    Matrix<T>::Matrix(const Dimensions dimensions, const T init_val) ://verify correctness
    dim(dimensions),
    element_num(dimensions.getRow() * dimensions.getCol()),
    data(new T[element_num])
    {
        if((dimensions.getRow() <= 0) || (dimensions.getCol() <= 0))
        {
            throw IllegalInitialization();
        }
        for (int i = 0; i < element_num; i++)
        {
            data[i] = init_val;
        }
    }    

    //Assumptions: c'tor, d'tor, assignment operator defined
    template<class T>
    Matrix<T>::Matrix(const Matrix &toCopy) :
        dim(toCopy.dim),
        element_num(toCopy.element_num),
        data(new T[element_num])
    {
        if(!toCopy)
        {
            throw Matrix::IllegalInitialization();
        }
        for (int i = 0; i < element_num; i++)
        {
            data[i] = toCopy.data[i];
        }
    }

    //Assumptions: d'tor defined
    template<class T>
    Matrix<T>::~Matrix<T>()
    {
        delete[] data;
    }

    
    //Assumptions: assignment operator defined
    template<class T>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T> &a)
    {
        dim = a.dim;
        element_num = a.element_num;
        {
            for (int i = 0; i < element_num; i++)
            {
                data[i] = a.data[i];
            }
        }
        return *this;
    }

    //Assumptions: c'tor, d'tor, assignment operator defined 
    template<class T>
    Matrix<T> Matrix<T>::Diagonal(int a, int b)
    {   
        Matrix<T> returnMat = Matrix<T>({a, b});
        for(int i = 0 ; i < a ; i++)
        {
            for(int j = 0 ; j < b ; j++)
            {
                if(i == j)
                {
                    returnMat(i , i) = b;                    
                }
            }
        }
        return returnMat;
    }
    
    //Assumptions: none
    template<class T>
    int Matrix<T>::height() const
    {
        return this->dim.getRow();
    }
    
    //Assumptions: none
    template<class T>
    int Matrix<T>::width() const
    {
        return this->dim.getCol();
    }
    
    //Assumptions: none
    template<class T>
    int Matrix<T>::size() const
    {
        return this->element_num;
    }

    //Assumptions: c'tor, d'tor, assignment operator defined
    template<class T>
    Matrix<T> Matrix<T>::transpose() const
    {
        Dimensions dim (this->dim.getCol(), this->dim.getRow());
        Matrix<T> matrix = Matrix<T>(dim);
        int height = this->Matrix<T>::height();
        int width = this->Matrix<T>::width();
        for(int n = 0; n < width*height; n++) 
        {
            int i = n / width;
            int j = n % width;
            matrix.data[n] = this->data[height*j + i];           
        }
        return matrix;
    }

    //Assumptions: assignment operator, c'tor, d'tor defined
    template<class T>
    Matrix<T> Matrix<T>::operator-() const
    {
        Matrix<T> matrix = Matrix<T>(*this);
        int height = this->Matrix<T>::height();
        int width = this->Matrix<T>::width();
        for(int i = 0 ; i < height ; i++)
        {
            for(int j = 0 ; j < width ; j++)
            {
                matrix(i, j) = -1*((*this)(i, j));
                            
            }
        }
        return matrix;
    }

    //Assumptions: + between T objects operator, assignment operator, c'tor, d'tor defined
    template<class T>
    Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b)
    {
        if(a.dim != b.dim)
        {
            throw DimensionMismatch(a.dim, b.dim);
        }
        Matrix<T> matrix = Matrix<T>(Dimensions(a.height(), a.width()));
        int height = a.height();
        int width = a.width();
        for(int i = 0 ; i < height ; i++)
        {
            for(int j = 0 ; j < width ; j++)
            {
                matrix(i, j) = a(i, j) + b(i, j);
            }
        }
        return matrix;
    }
    
    //Assumptions: + between T objects operator, unary -operator, c'tor, d'tor defined
    template<class T>
    Matrix<T> operator-(const Matrix<T>& a, const Matrix<T>& b)
    {
        return a + (-b);
    }

    //Assumptions: += operator, assignment operator, c'tor, d'tor defined
    template<class T>
    Matrix<T> operator+(const Matrix<T>& a, const T t)
    {
        Matrix<T> matrix = Matrix<T>(a);
        int height = a.height();
        int width = a.width();
        for(int i = 0 ; i < height ; i++)
        {
            for(int j = 0 ; j < width ; j++)
            {               
                matrix(i , j) += t;
            }        
        }
        return matrix;
    }

    //Assumptions: += operator, assignment operator, c'tor, d'tor defined
    template<class T>
    Matrix<T> operator+(const T a, const Matrix<T>& t)
    {
        return t + a;
    }

    //Assumptions: += operator, assignment operator, c'tor, d'tor defined    
    template<class T>
    Matrix<T>& operator+= (Matrix<T>& a, const T t)
    {
        a = (a + t);
        return a;
    }

    //Assumptions: += operator, assignment operator, c'tor, d'tor defined
    template<class T>
    Matrix<T>& operator+=(const T t, Matrix<T>& b)
    {
        return b += t;
    }

    //Assumptions: none
    template<class T>
    T& Matrix<T>::operator() (const int row, const int col)
    {
        int curr_row = this->dim.Dimensions::getRow();
        int curr_col = this->dim.Dimensions::getCol();
        if((row >= curr_row) || (row < 0) || (col >= curr_col) || (col < 0))
        {
            throw AccessIllegalElement();
        }
        return this->data[this->width()*row + col];
    }

    //Assumptions: none
    template<class T>
    const T& Matrix<T>::operator() (const int row, const int col) const
    {
        int curr_row = this->dim.Dimensions::getRow();
        int curr_col = this->dim.Dimensions::getCol();
        if((row >= curr_row) || (row < 0) || (col >= curr_col) || (col < 0))
        {
            throw AccessIllegalElement();
        }
        return this->data[this->width()*row + col];
    }


    //Assumptions: < operator defined
    template<class T>
    Matrix<bool> Matrix<T>::operator<(const T t) const
    {
        int height = this->height();
        int width = this->width();
        Matrix<bool> matrix = Matrix<bool>(Dimensions(height, width));
        for(int i = 0 ; i < height ; i++)
        {
            for(int j = 0 ; j < width ; j++)
            {               
                matrix(i , j) = ((*this)(i , j) < t ? true : false);
            }        
        }
        return matrix;
    }

    //Assumptions: == operator defined
    template<class T>
    Matrix<bool> Matrix<T>::operator==(const T t) const
    {
        int height = this->height();
        int width = this->width();
        Matrix<bool> matrix = Matrix<bool>(Dimensions(height, width));
        for(int i = 0 ; i < height ; i++)
        {
            for(int j = 0 ; j < width ; j++)
            {               
                matrix(i , j) = ((*this)(i , j) == t ? true : false);
            }        
        }
        return matrix;
    }

    //Assumptions: ==, < operators defined
    template<class T>
    Matrix<bool> Matrix<T>::operator<=(const T t) const
    {
        int height = this->height();
        int width = this->width();
        Matrix<bool> matrix = Matrix<bool>(Dimensions(height, width));
        for(int i = 0 ; i < height ; i++)
        {
            for(int j = 0 ; j < width ; j++)
            {               
                matrix(i , j) = ((((*this)(i , j) == t) || (*this)(i , j) < t) ? true : false);
            }        
        }
        return matrix;
    }

    //Assumptions: <, == operators defined
    template<class T>
    Matrix<bool> Matrix<T>::operator>(const T t) const
    {
        return ((*this) <= t).negateMatrix();
    }
    
    //Assumptions: <, == operators defined
    template<class T>
    Matrix<bool> Matrix<T>::operator>=(const T t) const
    {
        return ((*this) < t).negateMatrix();
    }

    //Assumptions: == operator defined
    template<class T>
    Matrix<bool> Matrix<T>::operator!=(const T t) const
    {
        return ((*this) == t).negateMatrix();
    }


    //Assumptions: == operator, bool() operator defined
    template<class T>
    bool any(const Matrix<T>& a)
    {
        int height = a.height();
        int width = a.width();
        bool res = false;
        for(int i = 0 ; i < height ; i++)
        {
            for(int j = 0 ; j < width ; j++)
            {               
                if(bool(a(i , j)) == true)
                {
                    res = true;
                }
            }
        }
        return res;
    }

    //Assumptions: == operator, bool() operator defined
    template<class T>
    bool all(const Matrix<T>& a)
    {
        int height = a.height();
        int width = a.width();
        bool res = true;
        for(int i = 0 ; i < height ; i++)
        {
            for(int j = 0 ; j < width ; j++)
            {               
                if(bool(a(i , j)) == false)
                {
                    res = false;
                }
            }
        }
        return res;
    }

}// namespace mtm


#endif //EX3_MATRIX_H