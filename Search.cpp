#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <Windows.h>

using namespace std;

void getFiles(const string& where, string outpath)
{
    string mask = where + "\\*";
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
                if (strcmp(FindFileData.cFileName,".") == 0 ||
                    strcmp(FindFileData.cFileName,"..") == 0) continue;
                getFiles(where + "\\" + FindFileData.cFileName, outpath);
            }
            else
                output << where << "\\" << FindFileData.cFileName << endl;

        } while (FindNextFile(hf, &FindFileData) != 0);
        FindClose(hf);
    }

	output.close();
}


int main()
{
	string inpath;
	cout << "Enter search path: ";
	cin >> inpath;

	string outpath;
	cout << "Enter path for output data: ";
	cin >> outpath;

	getFiles(inpath, outpath);

}