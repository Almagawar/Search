#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <Windows.h>
#include <sstream>

using namespace std;

void getFiles(const string& inpath, string outpath, string exn, string flag)
{
	string mask = inpath + "\\*";
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	hf = FindFirstFile(mask.c_str(), &FindFileData);

	ofstream output;
	output.open(outpath + "\\data.txt", ios_base::app);

	if (hf != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (strcmp(FindFileData.cFileName, ".") == 0 ||
					strcmp(FindFileData.cFileName, "..") == 0) continue;
				getFiles(inpath + "\\" + FindFileData.cFileName, outpath, exn, flag);
			}
			else
			{
				string buff = FindFileData.cFileName;
				if (buff.find(exn.c_str()) != std::string::npos)
				{
					output << inpath << "\\" << FindFileData.cFileName << endl;
					if (flag == "0")
					{
						break;
					}
				}
			}
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}

	output.close();
}


int main()
{
	setlocale(LC_ALL, "rus");

	string inpath;
	cout << "¬ведите путь до директории поиска: "; //Enter path to the search folder
	cin >> inpath;

	string outpath;
	cout << "¬ведите путь до места создани€ файла с данными: "; //Enter path to the "data.txt" file
	cin >> outpath;

	string confpath;
	cout << "¬ведите путь до файла \"conf.txt\": "; //Enter path to the "conf.txt" file
	cin >> confpath;

	string line;
	string exn;
	string flag;
	ifstream file(confpath + "\\conf.txt");

	while (getline(file, line))
	{
		std::stringstream ss(line);
		while (getline(ss, line, '|'))
		{
			if (line == "1" || line == "0")
			{
				flag = line;
			}
			else
			{
				exn = line;
				continue;
			}
			ofstream output;
			output.open(outpath + "\\data.txt", ios_base::app);
			output << exn << "\n\n" << endl;
			getFiles(inpath, outpath, exn, flag);
			output << "\n" << endl;
			output.close();
		}
	}

	file.close();

	return 0;
}