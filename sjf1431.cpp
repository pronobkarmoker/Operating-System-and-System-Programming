#include <iostream>
#include <algorithm>

using namespace std;

struct process
{
    string processs;
    int bt;
    int pr;
} plist[5];

bool compareByBT(const process &a, const process &b)
{
    return a.bt < b.bt;
}

int ct[6], tat[5], wt[5], t_tat = 0, t_wt = 0;

int main()
{
    plist[0].processs = "p1";
    plist[1].processs = "p2";
    plist[2].processs = "p3";
    plist[3].processs = "p4";
    plist[4].processs = "p5";

    plist[0].bt = 2;
    plist[1].bt = 1;
    plist[2].bt = 8;
    plist[3].bt = 4;
    plist[4].bt = 5;

    plist[0].pr = 2;
    plist[1].pr = 1;
    plist[2].pr = 4;
    plist[3].pr = 2;
    plist[4].pr = 3;

    sort(plist, plist + 5, compareByBT);

    for (int i = 0; i < 5; i++)
    {
        cout << "|---";
        cout << plist[i].processs;
        cout << "---|";
    }
    cout << endl;

    ct[0] = 0;

    for (int i = 1; i <= 5; i++)
    {
        ct[i] = ct[i - 1] + plist[i - 1].bt;
    }

    for (int i = 0; i <= 5; i++)
    {
        cout << ct[i] << "        ";
        // cout << endl;
    }
    cout << endl;

    for (int i = 0; i < 5; i++)
    {
        tat[i] = ct[i + 1];
        wt[i] = tat[i] - plist[i].bt;
        t_tat += tat[i];
        t_wt += wt[i];
    }

    cout << "   TaT        WT    " << endl;

    for (int i = 0; i < 5; i++)
    {
        cout << "    " << tat[i] << "        " << wt[i] << "    " << endl;
    }

    cout << "Average Turnaround time: " << (float)t_tat / 5 << endl;
    cout << "Average Waiting time: " << (float)t_wt / 5 << endl;
    return 0;
}
