/****************************************************************\
                      All Rights Reserved   
                      yanmaochang@126.com
*****************************************************************
  Project  :    GITHUB testing 
  Filename :    GithubTest.cpp
  History  :
             Date              Name              Modification                
             ----              ----              ------------
            2013-08-03        Yan-Maochang       Created              
\***************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

/****************************************************************\
Description: 
    Learn the formula from the input.txt
Inputs:
    whole_line: The whole line of formula
    uom: STL to save UOM
    ratio: STL to save ratio  
\****************************************************************/
void learn(string whole_line, vector<string>& uom, vector<double>& ratio)
{
    string segment;
    double value = 0.0, result = 0.0;
    istringstream line(whole_line);
    while(line >> segment)
    {
        if(segment == "1")
        {
            line >> segment;
            uom.push_back(segment);
        }   
        else if(segment == "=")
        {
            line >> segment;
            ratio.push_back(atof(segment.c_str()));                
        }
    }
    line.clear();
    return;
}

/****************************************************************\
Description: 
    Measured the value in metres
Inputs:
    value: The original value
    unit: The original unit 
    uom: STL to save UOM
    ratio: STL to save ratio   
Return:
    value measured in metres
\****************************************************************/
double resizing(double value, string unit, vector<string>& uom, vector<double>& ratio)
{   
    int i = 0;
    vector<string> :: iterator begin_uom = uom.begin();
    while(begin_uom != uom.end())
    {      
        if(unit.find("ee") != unit.npos)
        {
            unit.replace (unit.find("ee"),2,2,'o');
        }
        if( (unit == *begin_uom) || (unit == *begin_uom+"s") || (unit == *begin_uom+"es") )
        {
            return (value * ratio[i]);
        }
        begin_uom++;
        i++;
    }
}

/****************************************************************\
Description: 
    Calculate the results
Inputs:
    whole_line: The whole line of equation
    uom: STL to save UOM
    ratio: STL to save ratio   
Return:
    final result measured in metres
\****************************************************************/
double calculate(string whole_line, vector<string>& uom,vector<double>& ratio)
{
    string segment;
    double value = 0.0, result = 0.0;
    istringstream line(whole_line);
    while(line >> segment)
    {
        if(segment == "+")
        {
            line >> segment;
            value = atof(segment.c_str());
            line >> segment; 
            result += resizing(value, segment, uom, ratio);
        }
        else if(segment == "-")
        {
            line >> segment;
            value = atof(segment.c_str());
            line >> segment; 
            result -= resizing(value, segment, uom, ratio);
        }
        else
        {
            value = atof(segment.c_str());
            line >> segment;  
            result += resizing(value, segment, uom, ratio);
        }    
    }
    line.clear();
    return result;
}


int main(void)
{
    double result = 0.0;
    vector<string> uom; //STL to save UOM
    vector<double> ratio; //STL to save ratio  
    string whole_line;

    //creat the input file and output file
    ifstream input_file("input.txt");
    if(!input_file)
    {
        cerr << "ERROR: Can not open the input.txt !" << endl;
        return -1;
    }
    ofstream output_file("output.txt");
    if(!output_file)
    {
        cerr << "ERROR: Can not creat the output.txt !" << endl;
        return -1;
    }

    output_file << "yanmaochang@126.com" << "\n" << endl;

    while(getline(input_file, whole_line))
    {
        //Learn the formula
        if((whole_line.find("=")) != whole_line.npos)
        {
            learn(whole_line, uom, ratio); 
        }

        //calculate the results
        else if(((whole_line.find("=")) == whole_line.npos) && !(whole_line.empty()))
        {
            result = calculate(whole_line, uom, ratio); 

             //Output the result
            output_file << setiosflags(ios::fixed) << setprecision(2) << result << " m" <<endl;
        }
    }

    input_file.close();
    output_file.close();
    return 0;
}
