#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

vector<int> Compression(string s1)
{
    cout << "Compression\n";
    int code = 256;
    int i;

    unordered_map<string, int> dict;

    for (i = 0; i <= 255; i++)
    {
        string ch = "";
        ch += char(i);
        dict[ch] = i;
    }

    string p = "";
    string c = "";

    p += s1[0];

    vector<int> compressOut;
    cout << "Current   Next  \tOutput          Addition\n";

    for (i = 0; i < s1.length(); i++)
    {
        if (i != s1.length() - 1)
            c += s1[i + 1];

        if (dict.find(p + c) != dict.end())
            p = p + c;

        else
        {
            cout << p << "\t  " << c << "\t\t" << dict[p] << "\t\t"<< p + c << "\t" << code << endl;
            compressOut.push_back(dict[p]);
            dict[p + c] = code;
            code++;
            p = c;
        }

        c = "";
    }

    cout << p << "\t  " << "-" << "\t\t" << dict[p] << endl;
    compressOut.push_back(dict[p]);

    return compressOut;
}

void Percent(float contIn, float contOut, int ok9, int ok10, int ok11)
{
    float reduced;
    if(ok11 == 1)
        reduced = (contIn * 100 * 11) / contOut;


    if(ok10 == 1)
        reduced = (contOut * 100 * 10) / contIn;


    if(ok9 == 1)
        reduced = (contOut * 100 * 9) / contIn;


    cout << "Text size was reduced by ";
    cout << reduced;
    cout << " percent";
    cout << endl << endl;

}

void Decompression(vector<int> decOut)
{
    cout << "\nDecompression\n";

    unordered_map<int, string> dict;
    int prev, cont = 256, n, i;

    for (i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        dict[i] = ch;
    }

    prev = decOut[0];

    string s = dict[prev];
    string c = "";

    c += s[0];
    cout << s;

    for (i = 0; i < decOut.size() - 1; i++)
    {
        n = decOut[i + 1];
        if (dict.find(n) == dict.end())
        {
            s = dict[prev];
            s = s + c;
        }
        else
            s = dict[n];

        cout << s;
        c = "";
        c += s[0];

        dict[cont] = dict[prev] + c;
        cont++;

        prev = n;
    }

}

void Help()
{
    cout << "For each compression and decompression you have a separate array\n";
    cout << "('s' for compression and 'arr' for decompression) to fill in with\n";
    cout << "the corresponding data.\n";
    cout << "Do not type characters in the command block!\n\n";
}

int main()
{
    /// Modify s for Compression and arr for decompression
    string s = "thisisthe";
    vector<int> arr = {116, 104, 105, 115, 258, 256, 101};

    int n;

    cout << "Welcome to Lempel-Ziv-Welch Algorithm!\n\n";
    cout << "Type the number from corresponding command below:\n";
    while(1)
    {
        cout << "1. Compression\n";
        cout << "2. Decompression\n";
        cout << "3. Help\n";
        cout << "4. Exit\n";
        cout << "> ";

        cin >> n;

        cout << endl;

        if(n == 1)
        {
            int  ok9 = 0, ok10 = 0, ok11 = 0, i;
            float contOut, contIn;

            contIn = s.size() * 8;
            vector<int> compressOut = Compression(s);
            contOut = compressOut.size();
            cout << "\nOutput: ";

            for (i = 0; i < compressOut.size(); i++)
            {
                cout << compressOut[i] << " ";
                if(compressOut[i] > 255 && compressOut[i] <= 511)
                    ok9 = 1;
                if(compressOut[i] > 511 && compressOut[i] <= 1023)
                    ok10 = 1;
                if(compressOut[i] > 1023)
                    ok11 = 1;
            }

            cout << endl;

            Percent(contIn, contOut, ok9, ok10, ok11);


        }

        else if(n == 2)
        {
            Decompression(arr);
            cout << endl << endl;;
        }

        else if(n == 3)
        {
            Help();
        }

        else if(n == 4)
        {
            break;
        }
        else
        {
            cout << "Wrong command, try again\n\n";

        }

    }

}

