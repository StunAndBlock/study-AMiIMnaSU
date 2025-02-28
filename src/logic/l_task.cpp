#include "l_task.hpp"




L_TASK::L_TASK(const uint16_t& nExperimnets, const uint16_t& nJumps, 
        const std::string& nameResultDir, const std::string& nameInputDataFile){
    nExperiments_ = nExperimnets;
    nJumps_ = nJumps;
    nameResultDir_ = nameResultDir;
    nameInputDataFile_ = nameInputDataFile;

}


L_TASK::STATUS L_TASK::status() const{
    return runity_;
}


void L_TASK::readInput(){
    std::ifstream matrixFile(nameInputDataFile_);

		if (!matrixFile.is_open())
		{
            runity_ = STATUS::INPUTFILE_FAILURE;
            return;
		}

		double val = 0.;

		std::string line;

		while (matrixFile.good())
		{
			getline(matrixFile, line);
			if (line.size())
			{
				_pMatrix.push_back(std::vector<double>());
				std::istringstream str(line);
				while (str >> val){
				    _pMatrix.back().push_back(val);
                }
			}
		}
		matrixFile.close();
		_curState = rand() % _pMatrix.size();
        runity_ = STATUS::OK;
}

std::vector<double> L_TASK::balanceVector(){
    std::vector<double> p(_pMatrix.size(), 0.);
    p.back() = 1.;
    
    std::vector<std::vector<double>> p_t_e = matrix::sub(matrix::transpose(_pMatrix), matrix::E(_pMatrix.size()));
    
    p_t_e.back() = std::vector<double>(_pMatrix.size(), 1.);
    p = matrix::GaussMethod(p_t_e, p);
    std::cout << "Balance state vector:\n";
    return p;
}

std::vector<std::vector<double>> L_TASK::balanceMatrix()
{
    std::vector<double> p(balanceVector());
    
    std::vector<std::vector<double>> balanceMatrix(std::vector<std::vector<double>>(p.size(), std::vector<double>(p.size(), 0.)));
    for (int i = 0; i < p.size(); i++)
        for (int j = 0; j < p.size(); j++)
            balanceMatrix[i][j] = p[j];
    std::cout << "Balance state matrix:\n";
    return balanceMatrix;
}


void L_TASK::jump()
{
    int value = (rand() % 101);

    int i = 0;

    int sum = 0;

    for (int i = 0; i < _pMatrix.size(); i++)
    {
        int leftVal = sum + _pMatrix[_curState][i] * 100;
        if (sum < value && value <= leftVal)
        {
            _curState = i;
            i = _pMatrix.size();
        }
        sum = leftVal;
    }
}

void L_TASK::reset() { 
    _curState = rand() % _pMatrix.size(); 
}

void WriteGnu(int maxState, int maxTime)
{
	
	std::ofstream file;
	
	std::vector<const char*> names = {"Result/1.plt", "Result/2.plt", "Result/3.plt"};
	std::vector<const char*> datas = {"Result/1.dat", "Result/2.dat", "Result/3.dat"};
	for (int i = 0; i < names.size(); i++)
	{
		file.open(names[i]);
		file << "set grid\n";
		file << "set xlabel \"t\"\n";
		file << "set ylabel \"State\"\n";
		file << "set yrange [" << 0 << ':' << maxState + 1 << "]\n";
		file << "set xrange [" << 1 << ':' << maxTime << "]\n";
		file << "plot \"" << datas[i]<< "\" title \"states\" w lp lt 7\n";
		file.close();
	}
	for (auto name : names)
	{
		file.open(name, std::ios::app);
		file << '\n';
		file << "pause mouse\n";
		file.close();
	}
}


void L_TASK::run(){
    std::cout << "Original:\n";
	matrix::show(_pMatrix);
	
	std::cout << "Power 2:\n";
	matrix::show(matrix::pow(_pMatrix, 2));
	
	std::cout << "Power 3:\n";
	matrix::show(matrix::pow(_pMatrix, 3));

    matrix::show(balanceVector());
	
	matrix::show(balanceMatrix());

    std::vector<std::vector<double>> stats(std::vector<std::vector<double>>(_pMatrix.size(), std::vector<double>(nExperiments_, 0.)));
	
	std::vector<int> values(nExperiments_, 0);
	std::vector<int> connect(values);
	
	for (int i = 0; i < nExperiments_; i++)
		values[i] = i;
		
	random_shuffle(values.begin(), values.end());
	
	std::ostringstream title;
	
	std::vector<std::ofstream> records;
	
	for (int i = 0; i < 3; i++)
	{
		connect[values[i]] = i;
		
		title << "Result/" << i + 1 << ".dat";
		records.push_back(std::ofstream(title.str()));
		title.str("");
	}
	
	
	WriteGnu(_pMatrix.size() - 1, nJumps_);
	
	for (size_t e = 0; e < nExperiments_; e++)
	{
		std::vector<size_t> counter(_pMatrix.size(), 0);

		counter[_curState]++;

		if (e == values[0] || e == values[1] || e == values[2])
			records[connect[e]] << 1 << '\t' << _curState << '\n';
		for (size_t i = 0; i < nJumps_ - 1; i++)
		{
			if (e == values[0] || e == values[1] || e == values[2])
				records[connect[e]] << i + 2 << '\t' <<_curState << '\n';
			counter[_curState]++;
			jump();
		}

		reset();
		
		for (int i = 0; i < _pMatrix.size(); i++)
			stats[i][e] = (double)counter[i] / nJumps_;

	}
	
	for (int i = 0; i < 3; i++)
		records[i].close();
	
	std::cout << "Probabilities:\n";
	
	matrix::show(matrix::transpose(stats));
	
	std::cout << "Averages:\n";
	
	for (int i = 0; i < _pMatrix.size(); i++)
	{
		std::cout << average(stats[i]) << '\t';
	}
	std::cout << '\n';
	
	std::cout << "Deviations:\n";
	
	for (int i = 0; i < _pMatrix.size(); i++)
	{
		std::cout << avgDev(stats[i]) << '\t';
	}
	std::cout << '\n';
	
	
    system("gnuplot Result/1.plt");
    system("gnuplot Result/2.plt");
    system("gnuplot Result/3.plt");
    runity_ = L_TASK::STATUS::OK;
    return;
}