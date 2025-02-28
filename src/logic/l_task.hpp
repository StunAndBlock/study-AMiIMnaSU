#ifndef L_TASK_HPP_
#define L_TASK_HPP_

#include "l_math/matrix.hpp"
#include <string>
#include <fstream>
#include <sstream>


class L_TASK{
    public:
        enum class STATUS : uint16_t {OK, INPUTFILE_FAILURE};
        L_TASK(const uint16_t&,const uint16_t&, const std::string&, const std::string&);
        void readInput();
        STATUS status() const;
        void run();
        private:
        STATUS runity_;
        uint16_t nExperiments_;
        uint16_t nJumps_;
        uint16_t nRandExperiments_;
        std::string nameResultDir_; 
        std::string nameInputDataFile_;
        std::vector<std::vector<double>> _pMatrix;
        uint32_t _curState;
        std::vector<double> balanceVector();
        std::vector<std::vector<double>> balanceMatrix();
        void jump();
        void reset();
    };









#endif //!L_TASK_HPP_