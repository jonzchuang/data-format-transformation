/*1. Function: 将稀疏数据集重新填充后，第一列为数据标签，标签和数据特征在一个文件中。
Format: -1 0.2 0.5 1.2 ...
1  0.4 0.1 1.4 ...
Author：Chuang Zhang.
Date: Nov. 11, 2016.
Location: CS, Tianjin University.
Language: C++.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <windows.h>

using namespace std;

int main(int argc, char *argv[]){
	ifstream file_in("a1a", ios::in | ios::_Nocreate);
	string oneline;
	ofstream file_out("a1a.train", ios::out);
	istringstream std_in;
	int num_feature = 123;//特征数用于检测是否将一行完整处理结束。
	char ch;//字符:
	int index = 0;//表示实际index
	int label = 0;
	double featu = 0;
	int curIndex = 0;//稀疏数据中的curIndex
	int size_Dat = 0;
	bool flag = TRUE;
	while (getline(file_in, oneline)){//获取一行放入字符串对象oneline中
		std_in.str(oneline);//将输入字符串流对象与字符串oneline连接
		std_in >> label;//输入字符串流，逐个输入，空格为间隔.
		file_out << label << " ";
		std_in.clear();
		while (std_in >> curIndex){//定义curIndex为int，故接下来读取一个int,读取整型：5。
			//若定义为string,接下来读取字符串“5:0.2”，要准确理解字符串流的含义。
			index++;
			while (index <curIndex){
				file_out << setiosflags(ios::fixed) << setprecision(6) << 0 << " ";
				index++;
			}
			std_in >> ch >> featu;
			file_out << featu << " ";
		}
		std_in.clear();
		if (curIndex > num_feature){
			cout << "Inputed feature number error!" << endl;
			flag = FALSE;
			break;
		}
		while (index < max(curIndex, num_feature)){
			index++;
			file_out << setiosflags(ios::fixed) << setprecision(6) << 0 << " ";
		}
		file_out << endl;
		cout << "Line Num.: " << ++size_Dat << ", Feature Num.: " << index << "  Size istream:" << std_in.str().length() << endl;
		index = 0;
	}
	if (flag){
		cout << "I have finished, lucky!" << endl;
	}
	file_in.close();
	file_out.close();
	system("pause");
	return 0;
}
