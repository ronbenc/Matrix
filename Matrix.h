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
                                        
        public:
        //default c'tor - given matrix dimensions, default value by T c'tor
        //Assumptions for T: c'tor without parameters, assignment operator, d'tor defined
        Matrix(const Dimensions dimensions, const T init_val = T());

        //copy c'tor - construct new copy of a given matrix
        //Assumptions for T: c'tor without parameters, d'tor, assignment operator defined
        Matrix(const Matrix &Matrix);

        //default d'tor
        //Assumptions for T: d'tor defined
        ~Matrix();

        //assignment operator between two Matrix
        //Assumptions for T: assignment operator defined
        Matrix& operator=(const Matrix& a);

        //create new matrix which it's diagonal elements initialized to T, else T()
        //Assumptions for T: c'tor without parameters, d'tor, assignment operator defined 
        static Matrix Diagonal(int a, T t);

        //get a matrix height
        //Assumptions for T: none
        int height() const;

        //get a matrix width
        //Assumptions for T: none
        int width() const;

        //get number of elements in matrix
        //Assumptions for T: none
        int size() const;

        //returns a new matrix set to a given matrix's transpose
        //Assumptions for T: c'tor without parameters, d'tor, assignment operator defined
        Matrix transpose() const;

        //returns a new matrix with the negative elements of a given matrix
        //Assumptions on T: assignment operator, -operator (unary), c'tor without parameters, d'tor defined
        Matrix operator-() const;

        //read a given matrix (i , j) element
        //Assumptions on T: none
        const T& operator() (const int row, const int col) const;

        //access (with write permission) a given matrix (i , j) element
        //Assumptions on T: none
        T& operator() (const int row, const int col);

        //returns a new boolean matrix, that contains (i , j) boolean variables defining whether (i , j) element meets condition < b
        //Assumptions on T: < operator defined
        Matrix<bool> operator< (const T t) const;

        //returns a new boolean matrix, that contains (i , j) boolean variables defining whether (i , j) element meets condition == b
        //Assumptions on T: == operator defined
        Matrix<bool> operator==(const T t) const;

        //returns a new boolean matrix, that contains (i , j) boolean variables defining whether (i , j) element meets condition <= b
        //Assumptions on T: ==, < operators defined
        Matrix<bool> operator<=(const T t) const;

        //returns a new boolean matrix, that contains (i , j) boolean variables defining whether (i , j) element meets condition > b
        //Assumptions on T: <, == operators defined
        Matrix<bool> operator>(const T t) const;

        //returns a new boolean matrix, that contains (i , j) boolean variables defining whether (i , j) element meets condition >= b
        //Assumptions on T: <, == operators defined
        Matrix<bool> operator>=(const T t) const;

        //returns a new boolean matrix, that contains (i , j) boolean variables defining whether (i , j) element meets condition != b
        //Assumptions on T: == operator defined
        Matrix<bool> operator!=(const T t) const;

        //returns a new function contains in (i, j) functor imposed on (i , j) element of a given matrix
        //Assumptions on T: matrix is mutable and functor() is defined for all the matrix elements
        template<class Functor>
        Matrix apply(Functor functor) const;
        

        //********Iterator Classes*************

        //an itertor class to iterate over matrices elements
        class iterator;

        //set iterator to the first element in matrix    
        iterator begin();

        //set iterator to the end of a matrix
        iterator end(); 

        //an itertor class to iterate over constant matrices elements
        class const_iterator;

        //set iterator to the first element in a constant matrix
        const_iterator begin() const;

        //set iterator to the end of a constant matrix
        const_iterator end() const; 

             
        //********Exceptions Classes*************
        
        class Exception : public std::exception
        {
            public:
        };
        class AccessIllegalElement : public Exception
        {
            public:
            virtual const char* what() const noexcept override
            {
                return "Mtm matrix error: An attempt to access an illegal element";
            }
        };
        class IllegalInitialization : public Exception
        {
            public:
            virtual const char* what() const noexcept override
            {
                return "Mtm matrix error: Illegal initialization values";
            }
        };
        class DimensionMismatch : public Exception
        {
            public:
            Dimensions dim1;
            Dimensions dim2;
            std::string output;
            DimensionMismatch(const Dimensions dim1, const Dimensions dim2) :
                dim1(dim1), dim2(dim2)
                {
                    output = "Mtm matrix error: Dimension mismatch: " + dim1.toString() + " " + dim2.toString();
                }
            ~DimensionMismatch() = default;
            virtual const char* what() const noexcept override
            {                
                return this->output.std::string::c_str();    
            }
        };
    };

    //*****non-class functions & operators*****

    //returns a new matrix - sum of two matrix
    //Assumptions on T: + between T objects operator, assignment operator, c'tor without parameters, d'tor defined
    template<class T>
    Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b);

    //returns a new matrix - subtraction of two matrix
    //Assumptions on T: + between T objects operator, unary -operator, c'tor without parameters, d'tor defined
    template<class T>
    Matrix<T> operator-(const Matrix<T>& a, const Matrix<T>& b);
    
    //returns a new matrix - sum of a and static matrix which all objects initialized to t
    //Assumptions on T: += operator, assignment operator, c'tor without parameters, d'tor defined
    template<class T>
    Matrix<T> operator+(const Matrix<T>& a, const T t);

    //returns a new matrix - sum of a and static matrix which all objects initialized to t
    //Assumptions on T: += operator, assignment operator, c'tor without parameters, d'tor defined
    template<class T>
    Matrix<T> operator+(const T t, const Matrix<T>& b);
    
    //returns a by reference - sum of a and static matrix which all objects initialized to t
    //Assumptions on T: += operator, assignment operator, c'tor without parameters, d'tor defined    
    template<class T>
    Matrix<T>& operator+=(Matrix<T>& a, const T t);

    //returns a by reference - sum of a and static matrix which all objects initialized to b
    //Assumptions on T: += operator, assignment operator, c'tor without parameters, d'tor defined
    template<class T>
    Matrix<T>& operator+=(const T t, Matrix<T>& b);
    
    //returns true if and only if bool() conversion of least one element is true, false otherwise
    //Assumptions on T: == operator, bool() operator defined
    template<class T>
    bool any(const Matrix<T>& a);
    
    //returns true if and only if bool() conversions of all elements are true, false otherwise
    //Assumptions: == operator, bool() operator defined
    template<class T>
    bool all(const Matrix<T>& a);


    //*****in-class member functions & operators******
    
    template <class T>    
    Matrix<T>::Matrix(const Dimensions dimensions, const T init_val) :
    dim(dimensions),
    element_num(dimensions.getRow() * dimensions.getCol())    
    {
        if((dimensions.getRow() <= 0) || (dimensions.getCol() <= 0))
        {
            throw IllegalInitialization();
        }
        data = new T[element_num];
        try // handle T assigment failure
        {
            for (int i = 0; i < element_num; i++)
            {
                data[i] = init_val;
            }
        }
        catch(std::bad_alloc& e)
        {
            delete[] data;
            throw;
        }
    }    

    template<class T>
    Matrix<T>::Matrix(const Matrix &toCopy) :
        dim(toCopy.dim),
        element_num(toCopy.element_num),
        data(new T[element_num])
    {
        for (int i = 0; i < element_num; i++)
        {
            data[i] = toCopy.data[i];
        }
    }

    template<class T>
    Matrix<T>::~Matrix<T>()
    {
        delete[] data;
    }

    
    template<class T>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T> &a)
    {
        if(this == &a) // check self assignment
        {
            return *this;
        }

        dim = a.dim;
        element_num = a.element_num;
        delete[] data;
        data = new T[element_num];
        {
            for (int i = 0; i < element_num; i++)
            {
                data[i] = a.data[i];
            }
        }
        return *this;
    }

    template<class T>
    Matrix<T> Matrix<T>::Diagonal(int a, T t)
    {   
        Matrix<T> returnMat({a, a});
        for(int i = 0 ; i < a ; i++)
        {
            returnMat(i , i) = t;
        }
        return returnMat;
    }
    
    template<class T>
    int Matrix<T>::height() const
    {
        return this->dim.getRow();
    }
    
    template<class T>
    int Matrix<T>::width() const
    {
        return this->dim.getCol();
    }
    
    template<class T>
    int Matrix<T>::size() const
    {
        return this->element_num;
    }

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

    template<class T>
    Matrix<T> Matrix<T>::operator-() const
    {
        Matrix<T> matrix = Matrix<T>(*this);
        int height = this->Matrix<T>::height();
        int width = this->Matrix<T>::width();
        for(T& element : matrix)
        {
            element = -element;
        }
        return matrix;
    }

    template<class T>
    Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b)
    {
        if((a.width() != b.width()) || (a.height() != b.height()))
        {
            Dimensions dim1(a.height(), a.width());
            Dimensions dim2(b.height(), b.width());
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
    
    template<class T>
    Matrix<T> operator-(const Matrix<T>& a, const Matrix<T>& b)
    {
        return a + (-b);
    }

    template<class T>
    Matrix<T> operator+(const Matrix<T>& a, const T t)
    {
        Matrix<T> matrix = Matrix<T>(a);
        for(T& element : matrix)
        {
            element += t;
        }
        return matrix;
    }
    
    template<class T>
    Matrix<T> operator+(const T t, const Matrix<T>& a)
    {
        Matrix<T> matrix = Matrix<T>(a);
        for(T& element : matrix)
        {
            element = t + element;
        }
        return matrix;
    }
    
    template<class T>
    Matrix<T>& operator+= (Matrix<T>& a, const T t)
    {
        a = (a + t);
        return a;
    }

    template<class T>
    Matrix<T>& operator+=(const T t, Matrix<T>& a)
    {
        return a = t + a;
    }

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

    template<class T>
    Matrix<bool> Matrix<T>::operator>(const T t) const
    {
        Matrix<bool> to_negate = ((*this) <= t);
        for(bool& element : to_negate)
        {
            element -= true;
        }
        return to_negate;
    }
    
    template<class T>
    Matrix<bool> Matrix<T>::operator>=(const T t) const
    {
        Matrix<bool> to_negate = ((*this) < t);
        for(bool& element : to_negate)
        {
            element -= true;
        }
        return to_negate;
    }

    template<class T>
    Matrix<bool> Matrix<T>::operator!=(const T t) const
    {
        Matrix<bool> to_negate = ((*this) == t);
        for(bool& element : to_negate)
        {
            element -= true;
        }
        return to_negate;
    }

    template<class T>
    bool any(const Matrix<T>& a)
    {
        bool res = false;
        for(const T& element : a)
        {
             if((bool)element == true)
             {
                 res = true;
                 break;
             }
        }
        return res;
    }

    template<class T>
    bool all(const Matrix<T>& a)
    {
        bool res = true;
        for(const T& element : a)
        {
             if((bool)element == false)
             {
                 res = false;
                 break;
             }
        }
        return res;
    }

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
        // Assumptions: non for all iterator's methods

        //dereference current element to access element
        T& operator*() const;

        //advance iterator to next element in a matrix (prefix)
        iterator& operator++();

        //advance iterator to next element in a matrix (postfix)
        iterator operator++(int);

        //true if iterator are equal iterators. false otherwise
        bool operator==(const iterator& it) const;

        //true if iterator are not equal iterators. false otherwise
        bool operator!=(const iterator& it) const;

        //iterator constructor
        iterator(const iterator&) = default;

        //iterator assigment operator
        iterator& operator=(const iterator&) = default;

        //iterator destructor
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
        {
            throw AccessIllegalElement();
        }
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
        // Assumptions: non for all const iterator's methods

        //dereference current element to access element (read-only)
        const T& operator*() const;

        //advance iterator to next element in a matrix (prefix)
        const_iterator& operator++();

        //advance iterator to next element in a matrix (postfix)
        const_iterator operator++(int);

        //true if iterators are equal. false otherwise
        bool operator==(const const_iterator& it) const;

        //true if iterators are not equal iterators. false otherwise
        bool operator!=(const const_iterator& it) const;

        //const iterator constructor
        const_iterator(const const_iterator&) = default;

        //const iterator assigment operator
        const_iterator& operator=(const const_iterator&) = default;

        //const iterator destructor
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
        {
            throw AccessIllegalElement();
        }
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
        const_iterator result = *this;
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

    //Assumptions: none
    template<class T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat)
    {
        int width = mat.width();
        return mtm::printMatrix(os, mat.begin(), mat.end(), width);
    }

}// namespace mtm


#endif //EX3_MATRIX_H