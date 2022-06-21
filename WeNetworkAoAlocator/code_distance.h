//#ifndef CODE_DISTANCE_H
//#define CODE_DISTANCE_H

#include <iostream>
#include <math.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

using std::cout;
using std::endl;
using std::vector;

class Code_distance
{
public:
    Code_distance();
    ~Code_distance();

    double radians(double degree);
    vector<double> intersection(double x_1, double y_1, double angle_1, double x_2, double y_2, double angle_2);
    vector<double> moyenne_coord(vector<vector<double>> coordonnees);
    vector<vector<double>> distance(vector<vector<double>> coordonnees);
    __int64 point_moyen(vector<vector<double>> distances);
    vector<int> voisins(vector<double> distances, double tolerance);
    vector<double> asset_position(vector<vector<double>> data_locator);
    double quarter_verif(vector<double> intersection);
};
