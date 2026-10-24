class Solution {
public:
    int convertDayOfYear(string &date, vector<int> &months) {
        int month = stoi(date.substr(0, 2));
        int day = stoi(date.substr(3, 2));

        int allDays = 0;

        for (int i=0; i<month-1; i++) {
            allDays+=months[i];
        }

        allDays+=day;

        return allDays;
    }
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        vector<int> months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        int aliceArrive = convertDayOfYear(arriveAlice, months);
        int aliceLeave = convertDayOfYear(leaveAlice, months);
        int bobArrive = convertDayOfYear(arriveBob, months);
        int bobLeave = convertDayOfYear(leaveBob, months);

        int arriveLate = max(aliceArrive, bobArrive);
        int leaveEarly = min(bobLeave, aliceLeave);

        int together = 0;
        if (leaveEarly >= arriveLate) {
            together = leaveEarly - arriveLate+1;
        }

        return together;
    }
};