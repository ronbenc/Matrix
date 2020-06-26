#ifndef HW3_AUXILIARIES_H
#define HW3_AUXILIARIES_H

#include <iostream>
#include <string>

#include <cmath>

namespace mtm {
	enum Team { CPP, PYTHON };
	enum CharacterType { SOLDIER, MEDIC, SNIPER };
	typedef int units_t;

	struct GridPoint {
		int row, col;
		GridPoint(int row, int col) : row(row), col(col) {}
		GridPoint(const GridPoint& other)=default;
		~GridPoint()=default;
		GridPoint& operator=(const GridPoint& other)=default;
		bool operator==(const GridPoint& other) const {
			return this->row == other.row && this->col == other.col;
		}
		
		static int distance(const GridPoint& point1, const GridPoint& point2) {
			return 	std::abs(point1.row - point2.row) 
					+ std::abs(point1.col - point2.col);
		}
	};

			
	std::ostream& printGameBoard(std::ostream& os, const char* begin, 
		const char* end, unsigned int width);

	// from previous parts:
	
	
	class Dimensions {
        int row, col;
    public:
        Dimensions( int row_t,  int col_t);
        std::string toString() const;
        bool operator==(const Dimensions& other) const;
        bool operator!=(const Dimensions& other) const;
        int getRow() const ;
        int getCol() const ;
    };
    
    std::string printMatrix(const int* matrix,const Dimensions& dim);

    template<class ITERATOR_T>
    std::ostream& printMatrix(std::ostream& os,ITERATOR_T begin,
                                ITERATOR_T end, unsigned int width){
        unsigned int row_counter=0;
        for (ITERATOR_T it= begin; it !=end; ++it) {
            if(row_counter==width){
                row_counter=0;
                os<< std::endl;
            }
            os <<*it<<" ";
            row_counter++;
        }
        os<< std::endl;
        return os;
	}	
}

#endif
