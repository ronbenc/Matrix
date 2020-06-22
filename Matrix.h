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
        std::string printMatrix(const T* matrix, const Dimensions& dim);
        //Matrix<bool>& negateMatrix();
        //static Matrix<bool>& negateMatrix(Matrix<bool>& toNegate);
        static std::string printDim(Dimensions dim);
        
        public:
        Matrix(const Dimensions dimensions, const T init_val = T());
        Matrix(const Matrix &Matrix);
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
        template<class Functor>
        Matrix apply(Functor functor) const;
        
               
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
            ~DimensionMismatch() = default;
            const std::string what() const;
        };

        //********Itertor Classes*************
        class iterator;    
        iterator begin();
        iterator end(); 

        class const_iterator;
        const_iterator begin() const;
        const_iterator end() const; 
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
    Matrix<bool>& negateMatrix(Matrix<bool>& toNegate);


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
         std::string str = "Mtm matrix error: Dimension mismatch: " + printDim(dim1) + " " + printDim(dim2);
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

    
    Matrix<bool>& negateMatrix(Matrix<bool>& toNegate)
    {
        int height = toNegate.height();
        int width = toNegate.width();
        for(int i = 0 ; i < height ; i++)
        {
            for(int j = 0 ; j < width ; j++)
            {               
                toNegate(i , j) = (toNegate(i , j) == false ? true : false);
            }        
        }
        return toNegate;
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
    
    //Assumptions: c'tor without parameters, assignment operator, d'tor defined
    template <class T>    
    Matrix<T>::Matrix(const Dimensions dimensions, const T init_val) ://verify correctness
    dim(dimensions),
    element_num(dimensions.getRow() * dimensions.getCol())    
    {
        if((dimensions.getRow() <= 0) || (dimensions.getCol() <= 0))
        {
            throw IllegalInitialization();
        }
        data = new T[element_num];
        for (int i = 0; i < element_num; i++)
        {
            data[i] = init_val;
        }
    }    

    //Assumptions: c'tor without parameters, d'tor, assignment operator defined
    template<class T>
    Matrix<T>::Matrix(const Matrix &toCopy) :
        dim(toCopy.dim),
        element_num(toCopy.element_num),
        data(new T[element_num])
    {
        // if(!toCopy)
        // {
        //     throw Matrix::IllegalInitialization();
        // }
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
        if(this == &a)
        {
            return *this;
        }

        dim = a.dim;
        element_num = a.element_num;
        delete data;
        data = new T[element_num];
        {
            for (int i = 0; i < element_num; i++)
            {
                data[i] = a.data[i];
            }
        }
        return *this;
    }

    //Assumptions: c'tor without parameters, d'tor, assignment operator defined 
    template<class T>
    Matrix<T> Matrix<T>::Diagonal(int a, int b)
    {   
        // Dimensions dim(a,a);
        // Matrix<T> returnMat(dim, b);
        Matrix<T> returnMat({a, a});
        for(int i = 0 ; i < a ; i++)
        {
            for(int j = 0 ; j < a ; j++)
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

    //Assumptions: c'tor without parameters, d'tor, assignment operator defined
    template<class T>
    Matrix<T> Matrix<T>::transpose() const
    {
        Dimensions dim (this->dim.getCol(), this->dim.getRow());
        Matrix<T> matrix(dim);
        int height = this->Matrix<T>::height();
        int width = this->Matrix<T>::width();
        for(int n = 0; n < width*height; n++) 
        {
            int i = n / height;
            int j = n % height;
            matrix.data[n] = this->data[width*j + i];           
        }
        return matrix;
    }

    //Assumptions: assignment operator, c'tor without parameters, d'tor defined
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

    //Assumptions: + between T objects operator, assignment operator, c'tor without parameters, d'tor defined
    template<class T>
    Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b)
    {
        if((a.width() != b.width()) || (a.height() != b.height()))
        {
            Dimensions dim1(a.height(), a.width());
            Dimensions dim2(b.height(), b.width());
            //throw Matrix<T>::DimensionMismatch(dim1, dim2);
            throw typename Matrix<T>::DimensionMismatch(dim1, dim2);
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
    
    //Assumptions: + between T objects operator, unary -operator, c'tor without parameters, d'tor defined
    template<class T>
    Matrix<T> operator-(const Matrix<T>& a, const Matrix<T>& b)
    {
        return a + (-b);
    }

    //Assumptions: += operator, assignment operator, c'tor without parameters, d'tor defined
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

    //Assumptions: += operator, assignment operator, c'tor without parameters, d'tor defined
    template<class T>
    Matrix<T> operator+(const T a, const Matrix<T>& t)
    {
        return t + a;
    }

    //Assumptions: += operator, assignment operator, c'tor without parameters, d'tor defined    
    template<class T>
    Matrix<T>& operator+= (Matrix<T>& a, const T t)
    {
        a = (a + t);
        return a;
    }

    //Assumptions: += operator, assignment operator, c'tor without parameters, d'tor defined
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
        Matrix<bool> to_negate = ((*this) <= t);
        return negateMatrix(to_negate);
    }
    
    //Assumptions: <, == operators defined
    template<class T>
    Matrix<bool> Matrix<T>::operator>=(const T t) const
    {
        Matrix<bool> to_negate = ((*this) < t);
        return negateMatrix(to_negate);
    }

    //Assumptions: == operator defined
    template<class T>
    Matrix<bool> Matrix<T>::operator!=(const T t) const
    {
        Matrix<bool> to_negate = ((*this) == t);
        return negateMatrix(to_negate);
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

    //Assumptions: matrix is mutable and functor() is defined for all the matrix elements
    template<class T>
    template<class Functor>
    Matrix<T> Matrix<T>::apply(Functor functor) const
    {
        Matrix<T> result = *this;
        for(typename Matrix<T>::iterator it = result.begin(); it != result.end(); ++it)
        {
            *it = functor(*it);
        }

        return result;
    }

    //*************iterator********************************************************
    template<class T>
    class Matrix<T>::iterator
    {
        const Matrix<T>* matrix;
        int index;
        iterator(const Matrix<T>* matrix, int index);
        friend class Matrix<T>;

    public:
        T& operator*() const;
        iterator& operator++();
        iterator operator++(int);
        bool operator==(const iterator& it) const;
        bool operator!=(const iterator& it) const;
        iterator(const iterator&) = default;
        iterator& operator=(const iterator&) = default;
        ~iterator() = default;
    };

    template<class T>
    typename Matrix<T>::iterator Matrix<T>::begin()
    {
        return iterator(this, 0);
    }

    template<class T>
    typename Matrix<T>::iterator Matrix<T>::end()
    {
        return iterator(this, (*this).size());
    }

    template<class T>
    Matrix<T>::iterator::iterator(const Matrix<T>* matrix, int index) : matrix(matrix), index(index) {}

    template<class T>
    T& Matrix<T>::iterator::operator*() const
    {
        if(index >= (*matrix).size())
            throw AccessIllegalElement();

        return matrix->data[index];
    }

    template<class T>
    typename Matrix<T>::iterator& Matrix<T>::iterator::operator++() 
    {
        ++index;
        return *this;
    }

    template<class T>
    typename Matrix<T>::iterator Matrix<T>::iterator::operator++(int) 
    {
        iterator result = *this;
        ++*this;
        return result;
    }

    template<class T>
    bool Matrix<T>::iterator::operator==(const iterator& it) const
    {
        return index == it.index;
    }

    template<class T>
    bool Matrix<T>::iterator::operator!=(const iterator& it) const
    {
        return !(*this == it);
    }

    //*************const_iterator********************************************************
    template<class T>
    class Matrix<T>::const_iterator
    {
        const Matrix<T>* const matrix;
        int index;
        const_iterator(const Matrix<T>* const matrix, int index);
        friend class Matrix<T>;

    public:
        const T& operator*() const;
        const_iterator& operator++();
        const_iterator operator++(int);
        bool operator==(const const_iterator& it) const;
        bool operator!=(const const_iterator& it) const;
        const_iterator(const const_iterator&) = default;
        const_iterator& operator=(const const_iterator&) = default;
        ~const_iterator() = default;
    };

    template<class T>
    typename Matrix<T>::const_iterator Matrix<T>::begin() const
    {
        return const_iterator(this, 0);
    }

    template<class T>
    typename Matrix<T>::const_iterator Matrix<T>::end() const
    {
        return const_iterator(this, (*this).size());
    }

    template<class T>
    Matrix<T>::const_iterator::const_iterator(const Matrix<T>* const matrix, int index) : matrix(matrix), index(index) {}

    template<class T>
    const T& Matrix<T>::const_iterator::operator*() const
    {
        if(index >= (*matrix).size())
            throw AccessIllegalElement();

        return matrix->data[index];
    }

    template<class T>
    typename Matrix<T>::const_iterator& Matrix<T>::const_iterator::operator++() 
    {
        ++index;
        return *this;
    }

    template<class T>
    typename Matrix<T>::const_iterator Matrix<T>::const_iterator::operator++(int) 
    {
        iterator result = *this;
        ++*this;
        return result;
    }

    template<class T>
    bool Matrix<T>::const_iterator::operator==(const const_iterator& it) const
    {
        return index == it.index;
    }

    template<class T>
    bool Matrix<T>::const_iterator::operator!=(const const_iterator& it) const
    {
        return !(*this == it);
    }

    //ron: (this did not compile)
    //Assumptions: none
    template<class T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat)
    {
        int width = mat.width();
        return mtm::printMatrix(os, mat.begin(), mat.end(), width);        
    }

}// namespace mtm


#endif //EX3_MATRIX_H